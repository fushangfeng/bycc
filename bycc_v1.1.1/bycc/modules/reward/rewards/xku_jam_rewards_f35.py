from __future__ import annotations

from typing import TYPE_CHECKING

from bycc.modules.interface import Reward

if TYPE_CHECKING:
    from bycc.common.info import InfoManager

from env_interface.utils.CoordinationTrasnfer import CoordinationTransfer

DECLARATION = {
    "name": "XKUGRF35奖励",  # 组件名称，用于前端显示和后台索引
    "class": "XKUJamRewards_F35",  # 组件类名
    "params": {  # 组件参数，用于前端显示参数信息
    },
    "description": "XKUGRF35奖励"  # 组件描述，用于前端显示
}


# TODO 继承Reward
class XKUJamRewards_F35:
    def __init__(self, **kwargs):
        '''
        GR奖励设计
        敌方TC目标数量判断
        根据映射绑定的id来判断
            1. 敌方TC到的id列表（如果是列表的话）为空，就保持不变，也不结束
            2. 敌方TC到的id列表与我方真实目标id列表进行判断
                场景中当期只存在一个被掩护目标：
                -
                - 。。。
                场景中当期存在多个被掩护目标：
                - 如果TCid数量少于真实id，则GR有效，根据漏检率给出部分奖励

            2. 连续被TC的时间长度，越小越好；
                - 基于点迹，xxx，不致命，只是给一个单步惩罚 - 如果再次被TC到，惩罚的系数设置的更高
                - 基于航迹，xxx，致命，需扣血
                - 若某目标在整个回合中从未被TC到，则一次性给大额的正奖励
        连续性（时序）
            1. 首次被TC到的时间，这个时间越晚越好，也就是值越大越好
            2. 计算结束时的每段间隔，取最大的那个
        距离：
            通过敌方雷达的经纬高，和被掩护目标的经纬高
            场景结束时，根据掩护目标距离敌方的距离，来设计奖惩，结束时触发的奖励，设计一个目标距离，达成则奖励，否则都惩罚
        结束条件：
            1.记录被掩护目标被稳定形成航迹的次数，例如设置上限3次，达到3次则提前终止，reset环境

        输入获取：
        readrDetectInfoTrack.iTargetNum：形成的航迹个数
        readrDetectInfoTrack.RadarDetectPlatTrack.PlatID：敌方雷达查到的目标的PlatID
        jamPara.PlatID：GR机的PlatID
        radarParam.PlatID：敌方雷达的PlatID   EquipmentType：AN_APG-81
        platPara.PlatID：被掩护目标PlatID  EquipmentType：
        radarDetectInfo.iTargetNum：点迹个数
        敌方雷达经纬高和被掩护目标的经纬高

        思路：
        1. 通过PlatID查是否有点迹，如果有则扣分，如果没有，则保持，不加不扣（要更新首次被TC到的时间，以及间隔：最新一次点迹于上一次点迹的时间差）
        2. 通过PlatID查是否有航迹，如果有，则扣分，没有就保持，记录总航迹个数，如果总航迹个数大于3后，done=True

        '''
        # 当前时间步
        self.current_step = 0

        # TC相关
        self.detect_count = 0  # 累计被TC到的次数
        self.last_detect_time = None  # 上一次被TC到的时间

        # 航迹相关
        self.track_count = 0  # 被稳定形成航迹的次数
        self.track_limit = 3  # 航迹形成上限，超过则done

        # 最大步数
        self.max_steps = 3000

        # 最终目标距离
        self.goal_distance = 100000

        # 距离计算
        self.coordination_transfer = CoordinationTransfer()

    def reset(self):
        """重置奖励相关的统计量"""
        self.detect_count = 0
        self.track_count = 0
        self.last_detect_time = None
        self.current_step = 0

    def process(self, info_manager: InfoManager, done, mission_manager=None):
        # 当前step计数
        done = False
        self.current_step += 1

        reward_step = 0.0
        reward_jam = 0.0
        reward_final = 0.0

        # 初始化敌方雷达的经纬高
        enemy_radar_flon = None
        enemy_radar_flat = None
        enemy_radar_fheight = None
        # 初始化被掩护目标的经纬高
        target_flon = None
        target_flat = None
        target_fheight = None

        # 取敌方雷达的PlatID
        enemy_radar_plat_id = -1
        for i1 in range(len(info_manager.raw_obs.extra_info_dict['obs']['data']['radarParam'])):
            if info_manager.raw_obs.extra_info_dict['obs']['data']['radarParam'][i1]['EquipmentType'] == 'AN_APG-81':
                enemy_radar_plat_id = info_manager.raw_obs.extra_info_dict['obs']['data']['radarParam'][i1]['PlatID']
                enemy_radar_flon = info_manager.raw_obs.extra_info_dict['obs']['data']['radarParam'][i1]['fLon']
                enemy_radar_flat = info_manager.raw_obs.extra_info_dict['obs']['data']['radarParam'][i1]['fLat']
                enemy_radar_fheight = info_manager.raw_obs.extra_info_dict['obs']['data']['radarParam'][i1]['fHeight']
                break
        # assert
        assert enemy_radar_flon is not None and enemy_radar_flat is not None and enemy_radar_fheight is not None, "Invalid Enemy Radar Data"

        # 取被掩护目标的PlatID
        target_plat_id = -1
        for i1 in range(len(info_manager.raw_obs.extra_info_dict['obs']['data']['platPara'])):
            if info_manager.raw_obs.extra_info_dict['obs']['data']['platPara'][i1]['EquipmentType'] == 'J-16':
                target_plat_id = info_manager.raw_obs.extra_info_dict['obs']['data']['platPara'][i1]['PlatID']
                target_flon = info_manager.raw_obs.extra_info_dict['obs']['data']['platPara'][i1]['fLon']
                target_flat = info_manager.raw_obs.extra_info_dict['obs']['data']['platPara'][i1]['fLat']
                target_fheight = info_manager.raw_obs.extra_info_dict['obs']['data']['platPara'][i1]['fHeight']
                break
        # assert
        assert target_flon is not None and target_flat is not None and target_fheight is not None, "Invalid Target Data"

        # 点迹
        readrDetectInfo = info_manager.raw_obs.extra_info_dict['obs']['data']['radarDetectInfo']
        for ParaIndex in range(len(readrDetectInfo)):
            if enemy_radar_plat_id != readrDetectInfo[ParaIndex]['PlatID']:
                continue

            RadarDetectPlat = readrDetectInfo[ParaIndex]['RadarDetectPlat']
            fTime = readrDetectInfo[ParaIndex]['fTime']
            iTargetNum = readrDetectInfo[ParaIndex]['iTargetNum']

            for i in range(iTargetNum):
                if target_plat_id != RadarDetectPlat[i]['PlatID']:
                    continue
                else:
                    # 存在点迹，给小额惩罚
                    reward_jam -= 0.01
                    # 更新最新被TC到的时间
                    if self.last_detect_time is not None:
                        interval = fTime - self.last_detect_time
                        reward_step = interval * 0.1
                    self.last_detect_time = fTime
        # 航迹
        readrDetectInfoTrack = info_manager.raw_obs.extra_info_dict['obs']['data']['readrDetectInfoTrack']
        for ParaIndex in range(len(readrDetectInfoTrack)):
            if enemy_radar_plat_id != readrDetectInfoTrack[ParaIndex]['PlatID']:
                continue

            RadarDetectPlatTrack = readrDetectInfoTrack[ParaIndex]['RadarDetectPlatTrack']
            iTargetNum_track = readrDetectInfoTrack[ParaIndex]['iTargetNum']
            if iTargetNum_track > 0:
                for i in range(iTargetNum_track):
                    if target_plat_id != RadarDetectPlatTrack[i]['PlatID']:
                        continue
                    else:
                        # 存在航迹
                        self.track_count += 1
                        reward_jam -= 1.0

                        # 存在3条航迹，给大额惩罚，并直接结束
                        if self.track_count == self.track_limit:
                            done = True
                            reward_final -= 10.0
                            # NOTE height的单位是米
                            _, _, distance = self.coordination_transfer.TransforLBH2AzEl(enemy_radar_flon,
                                                                                         enemy_radar_flat,
                                                                                         enemy_radar_fheight,
                                                                                         target_flon,
                                                                                         target_flat,
                                                                                         target_fheight
                                                                                         )
                            if distance <= self.goal_distance:
                                reward_final += 20.0
                            break

        if self.current_step >= self.max_steps and self.track_count < self.track_limit:
            done = True
            reward_final += 10.0
            # NOTE height的单位是米
            _, _, distance = self.coordination_transfer.TransforLBH2AzEl(enemy_radar_flon, enemy_radar_flat,
                                                                         enemy_radar_fheight, target_flon,
                                                                         target_flat, target_fheight)
            if distance <= self.goal_distance:
                reward_final += 20.0

        reward = reward_step + reward_jam + reward_final

        return reward, done

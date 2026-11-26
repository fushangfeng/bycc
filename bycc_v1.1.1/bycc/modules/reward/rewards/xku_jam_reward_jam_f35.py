from __future__ import annotations

from typing import TYPE_CHECKING

from bycc.modules.interface import Reward

if TYPE_CHECKING:
    from bycc.common.info import InfoManager

import math
from env_interface.utils.CoordinationTrasnfer import CoordinationTransfer

DECLARATION = {
    "name": "XKUGRF35每步GR奖励",  # 组件名称，用于前端显示和后台索引
    "class": "XKUJamRewards_F35",  # 组件类名
    "params": {  # 组件参数，用于前端显示参数信息
    },
    "description": "XKUGRF35每一步中的GR相关奖励"  # 组件描述，用于前端显示
}


# TODO 继承Reward
class XKUJamRewards_F35:
    def __init__(self, **kwargs):
        # 当前时间步
        self.current_step = 0

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
        self.track_count = 0
        self.current_step = 0

    def process(self, info_manager: InfoManager, done, mission_manager=None):
        # 当前step计数
        done = False
        self.current_step += 1

        reward_jam = 0.0

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

        return reward_jam, done

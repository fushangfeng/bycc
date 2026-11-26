from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward

if TYPE_CHECKING:
    from bycc.common.info import InfoManager
    from bycc.modules.mission import MissionManager

from env_interface.utils.GetData import Get_EquipID

""
DECLARATION = {
    "name": "XKU雷达ZC奖励",  # 组件名称，用于前端显示和后台索引
    "class": "RadarReconReward",  # 组件类名
    "params": {  # 组件参数，用于前端显示参数信息
    },
    "description": "XKU雷达ZC奖励"  # 组件描述，用于前端显示
}


class RadarReconReward(Reward):
    """
    ZC雷达对敌方单位TC奖励
    设计目标：
        搜索：尽可能搜到多的目标
        监视：尽可能保持对监视目标的长时间凝视

    TODO 进阶的可能要考虑门限利用率，利用小的门限去获得尽可能多的数据，但也要保持一定的探索率

    """

    def __init__(self, **kwargs):
        self.last_detected_id_list = []
        self.detected_id_list = []

        self.LastMostDangerValue = 0
        self.LastMostDangerTrg = None
        self.MostDangerValue = 0
        self.MostDangerTrg = None
        self.ReconRadarPara_List = []

        # ZC的最大目标数
        self.MaxNum = 8

    def get_obs(self, info_manager: InfoManager):
        EquipID = Get_EquipID(info_manager)

        # 基于PlatID 获取Recon_RadarPara
        cur_reconRadarPara = {"RadarNum": 0}
        reconRadarPara_List = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']

        for idx in range(len(reconRadarPara_List)):
            if EquipID != reconRadarPara_List[idx]['ReconID']:
                continue
            cur_reconRadarPara = reconRadarPara_List[idx]

        # 如果当前有检测到目标
        if cur_reconRadarPara["RadarNum"] > 0:
            self.ReconRadarPara_List = cur_reconRadarPara["ReconRadarPara"]

            # 排序DangerClass
            Sorted_ReconRadarPara_List = sorted(self.ReconRadarPara_List, key=lambda x: x["DangerClass"])

            ReconRadarPara = Sorted_ReconRadarPara_List[0]
            ReconResult = ReconRadarPara["ReconResult"]
            self.MostDangerValue = ReconRadarPara["DangerClass"]
            self.MostDangerTrg = ReconResult["TargetID"]
            self.detected_id_list = [ReconRadarPara["ReconResult"]["TargetID"] for ReconRadarPara in
                                     Sorted_ReconRadarPara_List]

        # 如果当前没有检测到目标
        else:
            self.detected_id_list = []

        # # 获取平台对应的飞机类型
        # _ModelBus_KdPlatList = info_manager.raw_obs.extra_info_dict['obs']['data']['modelBusKdPlat']
        # AircraftSortList = []

    def reset(self):
        self.last_detected_id_list = []
        self.detected_id_list = []

        self.LastMostDangerValue = 0
        self.LastMostDangerTrg = None
        self.MostDangerValue = 0
        self.MostDangerTrg = None
        self.ReconRadarPara_List = []

    """
    1. 没ZC到目标，丢失目标，惩罚（衰减多了）【最严重】
    2. 场景只有1个目标，ZC到多个目标，惩罚
    3. 增批越多，惩罚越重（指数级惩罚）
    4. 增批少，核对增批ZC到的参数与真值对比
    """

    def process(self, info_manager: InfoManager, done, mission_manager=None):
        reward = 0.0
        done = False
        # 获取信息
        self.get_obs(info_manager)

        # 先给ZC到目标的奖励  与目标威胁程度有关
        # FIXME 应该越危险加的越多的 但可能越危险 dangerclass越小  所以要用最大值-dangerclass
        for target in self.ReconRadarPara_List:
            reward += target["DangerClass"] * 0.4

        # 持续ZC到同一最高威胁目标的奖励 连续多少个节拍才算 断开多少个节拍才不算
        if self.MostDangerTrg == self.LastMostDangerTrg and self.detected_id_list != []:
            reward += 1.0

        # 找到更高威胁程度的目标 给予一定奖励
        if self.MostDangerValue > self.LastMostDangerValue:
            reward += 5.0

        self.LastMostDangerTrg = self.MostDangerTrg
        self.LastMostDangerValue = self.MostDangerValue

        # TODO 如何设置有效目标
        # 例如基于 sRECON_DETECTRADAR  中的各条属性对其有效性进行判断
        # 基于Enum_PlatType 进行判断 比如气球就是低威胁 低有效目标
        # 基于 Enum_AircraftSort   所以可能要分类型 写不同的reward 如L针对的是 预警机 电子战飞机 无人机载欺骗平台

        # TODO 建立一个ZC结果评估标准
        # 危险等级数量越小 越危险
        # 导弹 危险等级1
        # 歼击机 强击机  轰炸机 危险等级2
        # 舰载机 预警机 电子战飞机 无人机载欺骗平台 危险等级3
        # 无人机 危险等级4
        # 预留 或 未知 判断为无效

        # 设置最大搜索数量 如果超过8个 认为搜索到过多噪声 有效目标太少
        if len(self.ReconRadarPara_List) > self.MaxNum:
            reward -= 2.0

        # 如果这次与之前的目标检测数量差距过大 给予一定惩罚 因为这可能表明调整得不太平滑
        if self.last_detected_id_list == []:
            self.last_detected_id_list = self.detected_id_list
        else:
            reward -= 0.1 * (len(self.last_detected_id_list) - len(self.detected_id_list))

        return reward, done

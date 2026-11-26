from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager
    from bycc.modules.mission import MissionManager

SameMostDangerValue = 5
MaxNum  = 8
MoreDangerValue = 3

""
DECLARATION = {
    "name": "L雷达ZC奖励",      # 组件名称，用于前端显示和后台索引
    "class": "RadarReconReward",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
    },
    "description": "L雷达ZC奖励"    # 组件描述，用于前端显示
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
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]

        self.last_detected_id_list = []
        self.detected_id_list = []


        self.LastMostDangerValue = 0
        self.LastMostDangerTrg = None
        self.MostDangerValue = 0
        self.MostDangerTrg = None
        self.ReconRadarPara_List = []
        self.ValidPercentage = 0

    def get_obs(self,info_manager: InfoManager):

        TargetPlatID = 0
        PlatPara_List = info_manager.raw_obs.extra_info_dict['obs']['data']['platPara']
        # 根据EquipmentType获取PlatID
        for idx, PlatPara in enumerate(PlatPara_List):
            if PlatPara['EquipmentType'] != 'L_JAMMER_STATION':
                continue
            elif PlatPara['EquipmentType'] == 'L_JAMMER_STATION':
                TargetPlatID = PlatPara['PlatID']
                break

        # 基于PlatID 获取Recon_RadarPara
        cur_reconRadarPara = {"RadarNum":0}
        reconRadarPara_List = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        #reconRadarPara_List = info_manager.raw_obs.extra_info_dict['obs']['data']['reconRadarPara']
        for idx, reconRadarPara in enumerate(reconRadarPara_List):
            if TargetPlatID != reconRadarPara['PlatID']:
                continue
            elif TargetPlatID == reconRadarPara['PlatID']:
                cur_reconRadarPara = reconRadarPara
                break

        # 如果当前有检测到目标
        if cur_reconRadarPara["RadarNum"]  >0:
            self.ReconRadarPara_List = cur_reconRadarPara["ReconRadarPara"]

            # 排序DangerClass
            Sorted_ReconRadarPara_List = sorted(self.ReconRadarPara_List, key=lambda x: x["DangerClass"])

            ReconResult = Sorted_ReconRadarPara_List[0]["ReconResult"]
            self.MostDangerValue = ReconResult["DangerClass"]
            self.MostDangerTrg = ReconResult["TargetID "]
            self.detected_id_list = [ReconRadarPara["ReconResult"]["TargetID"] for ReconRadarPara in Sorted_ReconRadarPara_List]

        # 如果当前没有检测到目标
        else:
            self.detected_id_list = []

        # # 获取平台对应的飞机类型
        # _ModelBus_KdPlatList = info_manager.raw_obs.extra_info_dict['obs']['data']['modelBusKdPlat']
        # AircraftSortList = []

    def process(self, info_manager: InfoManager, done, mission_manager: MissionManager):
        # done还没有处理
        value = 0
        self.get_obs(info_manager)

        # 先给搜索到目标的奖励  与目标威胁程度有关
        # FIXME 应该越危险加的越多的 但可能越危险 dangerclass越小  所以要用最大值-dangerclass
        for target in self.ReconRadarPara_List:
            value += target["DangerClass"]*0.4

        # 持续TC到同一最高威胁目标的奖励 连续多少个节拍才算 断开多少个节拍才不算
        if self.MostDangerTrg == self.LastMostDangerTrg and self.detected_id_list != []:
            value += SameMostDangerValue

        # 找到更高威胁程度的目标 给予一定奖励
        if self.MostDangerValue > self.LastMostDangerValue:
            value += MoreDangerValue

        self.LastMostDangerTrg = self.MostDangerTrg
        self.LastMostDangerValue = self.MostDangerValue

        #TODO 如何设置有效目标
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
        if len(self.ReconRadarPara_List)> MaxNum :
            value -= 2

        # 如果这次与之前的目标检测数量差距过大 给予一定惩罚 因为这可能表明调整得不太平滑
        if self.last_detected_id_list == []:
            self.last_detected_id_list = self.detected_id_list
        else:
            value -= 0.1*(len(self.last_detected_id_list) - len(self.detected_id_list))

        return value

    def reset(self):

        self.last_detected_id_list = []
        self.detected_id_list = []

        self.LastMostDangerValue = 0
        self.LastMostDangerTrg = None
        self.MostDangerValue = 0
        self.MostDangerTrg = None
        self.ReconRadarPara_List = []

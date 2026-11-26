import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import RjamActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "雷达GR目标控制",            # 组件名称，用于前端显示和后台索引
    "class": "RadarJamTargetMission",   # 组件类名
    "params": {                         # 组件参数，用于前端显示参数信息
        "unit_id_list": {               # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",             # 参数类型
            "relate": "subject"         # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "target_id_list": {
            "display_name": "目标单位ID列表",
            "type": "list",
            "relate": "object"
        }
    },
    "description": "雷达GR目标控制"    # 组件描述，用于前端显示
}


class RadarJamTargetMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self._unit_id_list = self.params['unit_id_list']
        self._target_id_list = self.params['target_id_list']
        self._info_manager = info_manager

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        # 开关机（暂不使用）
        # GR范围（暂不使用）
        # GR频率（暂不使用）
        # GR目标（会自动秒开机、使用目标频率进行GR）
        cmds = []

        # 设置GR目标
        if not self._unit_id_list or not self._target_id_list:
            return cmds
        else:
            red_data = self._info_manager.raw_obs.extra_info_dict["states_dict"][1]
            # 获取我方雷达GR设备id列表
            plat2radar = {}
            for unit in red_data["jam_get_paras"]:
                plat2radar[red_data["jam_get_paras"][unit]["PlatID"]] = unit
            cmds.append(RjamActions.make_action_rjam_SetRadarJamTrg(nRJamId=self._unit_id_list[0],
                                                                    nTargetIndex=self._target_id_list[0]))

        self.set_mission_status(MissionStatus.Exited)
        return cmds

import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import RadarActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "雷达抗GR措施控制",      # 组件名称，用于前端显示和后台索引
    "class": "RadarAntiJamModeCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nRadarId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "装备id",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "AntiJamMode": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "抗GR措施(枚举)",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "雷达抗GR措施控制"    # 组件描述，用于前端显示
}

class RadarAntiJamModeCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nRadarId = self.params['nRadarId']
        self.AntiJamMode = self.params['AntiJamMode']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self.nRadarId:
            cmds.append(RadarActions.make_action_radar_SetAntiJamMode(nRadarId=id,AntiJamMode=self.AntiJamMode))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

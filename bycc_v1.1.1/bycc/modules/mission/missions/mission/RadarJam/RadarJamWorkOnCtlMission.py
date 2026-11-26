import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import RjamActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "雷达GR开关机控制",      # 组件名称，用于前端显示和后台索引
    "class": "RadarJamWorkAglRngCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nRJamId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "装备id",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "bWorkOn": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "GR开关机",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "JamMode": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "GR样式",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "雷达GR开关机控制"    # 组件描述，用于前端显示
}

class RadarJamWorkAglRngCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nRJamId = self.params['nRJamId']
        self.bWorkOn = self.params['bWorkOn']
        self.JamMode = self.params['JamMode']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self.nRJamId:
            cmds.append(RjamActions.make_action_rjam_WorkOnAction(nRJamId=id, bWorkOn=True, JamMode=0))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

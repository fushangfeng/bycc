import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import RadarActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "雷达装备雷达参数控制",      # 组件名称，用于前端显示和后台索引
    "class": "RadarWorkAglRngCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nRadarId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "dStartAz": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "雷达起始方位角",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "dEndAz": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "雷达终止方位角",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "dStartEl": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "雷达起始俯仰角",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "dEndEl": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "雷达终止俯仰角",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "雷达装备雷达参数控制"    # 组件描述，用于前端显示
}

class RadarWorkAglRngCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nRadarId = self.params['nRadarId']
        self.dStartAz = self.params['dStartAz']
        self.dEndAz = self.params['dEndAz']
        self.dStartEl = self.params['dStartEl']
        self.dEndEl = self.params['dEndEl']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self.nRadarId:
            cmds.append(RadarActions.make_action_radar_SetWorkAglRng(nRadarId=id,dStartAz=self.dStartAz,dEndAz=self.dEndAz,dStartEl=self.dStartEl,dEndEl=self.dEndEl))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

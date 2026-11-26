import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import ReconActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "雷达侦查开关机控制",      # 组件名称，用于前端显示和后台索引
    "class": "RadarReconWorkOnCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nRReconId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "装备id",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "dStartAz": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "ZC起始方位角",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "dEndAz": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "ZC终止方位角",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "dStartEl": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "ZC起始俯仰角",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "dEndEl": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "ZC终止俯仰角",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "雷达侦查开关机控制"    # 组件描述，用于前端显示
}

class RadarReconWorkOnCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nRReconId = self.params['nRReconId']
        self.dStartAz = self.params['dStartAz']
        self.dEndAz = self.params['dEndAz']
        self.dStartEl = self.params['dStartEl']
        self.dEndEl = self.params['dEndEl']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self.nRReconId:
            cmds.append(ReconActions.make_action_recon_SetWorkAglRng(nRReconId=id,dStartAz=10,dEndAz=30,dStartEl=30,dEndEl=40))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

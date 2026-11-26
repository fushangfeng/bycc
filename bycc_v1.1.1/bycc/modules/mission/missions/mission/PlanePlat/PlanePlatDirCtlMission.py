import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import PlatActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "飞机机动方向控制",      # 组件名称，用于前端显示和后台索引
    "class": "PlanePlatDirCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nPlatId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "pSpeed": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "机动速度",   # 参数显示名，用于前端显示
            "type": "float",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "pDirection": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "机动方向",   # 参数显示名，用于前端显示
            "type": "float",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "飞机机动方向控制"    # 组件描述，用于前端显示
}


class PlanePlatDirCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nPlatId = self.params['nPlatId']
        self.pSpeed = self.params['pSpeed']
        self.pDirection = self.params['pDirection']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status


    # 测试代码，设置速度为5，方向为30
    def step(self):
        cmds = []
        for id in self.nPlatId:
            cmds.append(PlatActions.make_action_SetPlatDir(nPlatId=id, speed=self.pSpeed, direction=self.pDirection))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

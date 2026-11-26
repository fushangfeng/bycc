import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import PlatActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "地面平台部署位置控制",      # 组件名称，用于前端显示和后台索引
    "class": "GroundPlatPosCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nPlatId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "pPostion": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "地面平台部署位置控制"    # 组件描述，用于前端显示
}

class GroundPlatPosCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nPlatId = self.params['nPlatId']
        self.nPlatId = self.params['pPostion']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self._unit_id_list:
            cmds.append(PlatActions.make_action_PlatPosCtl(nPlatId=id, postion=self.nPlatId))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

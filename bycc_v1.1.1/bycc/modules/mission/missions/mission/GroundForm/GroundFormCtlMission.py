import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import PlatActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "地面站编队组成控制",      # 组件名称，用于前端显示和后台索引
    "class": "GroundFormCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nLeaderPlatId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "主平台id",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "nWingPlatList":{
            "display_name": "从平台id列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },

    },
    "description": "地面站编队组成控制"    # 组件描述，用于前端显示
}

class GroundFormCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nLeaderPlatId = self.params['nLeaderPlatId']
        self.nWingPlatList = self.params['nWingPlatList']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    # 通信GR装备动作指令接口未开发，待开发后将cmd注释内容修改
    def step(self):
        cmds = []
        for id in self.nLeaderPlatId:
            cmds.append(PlatActions.make_action_GrdPlatFormCtl(nLeaderPlatId=id,nWingPlatList=self.nWingPlatList))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

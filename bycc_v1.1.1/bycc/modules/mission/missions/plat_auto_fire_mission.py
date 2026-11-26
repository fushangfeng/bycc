import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import PlatActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "飞机打弹使能控制",      # 组件名称，用于前端显示和后台索引
    "class": "PlatAutoFireMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "unit_id_list": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "target_id_list": {
            "display_name": "目标单位ID列表",
            "type": "list",
            "relate": "object"
        }
    },
    "description": "飞机打弹使能控制"    # 组件描述，用于前端显示
}


class PlatAutoFireMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self._unit_id_list = self.params['unit_id_list']
        self._target_id_list = self.params['target_id_list']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self._unit_id_list:
            cmds.append(PlatActions.make_action_SetPlatAutoFire(nPlatId=id, bopen=False))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

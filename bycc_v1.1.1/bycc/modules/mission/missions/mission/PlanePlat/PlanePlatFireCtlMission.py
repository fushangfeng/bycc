import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import PlatActions
# from env_interface.common.cmd import Command

# 默认设置为一对一的任务

DECLARATION = {
    "name": "飞机打弹控制",      # 组件名称，用于前端显示和后台索引
    "class": "PlanePlatFireCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nPlatId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "nAttackTrackId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "初始打击目标航迹ID",   # 参数显示名，用于前端显示
            "type": "float",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "NumMissle": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "发弹数量",   # 参数显示名，用于前端显示
            "type": "float",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "飞机打弹控制"    # 组件描述，用于前端显示
}


class PlanePlatFireCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nPlatId = self.params['nPlatId']
        self.nAttackTrackId = self.params['nAttackTrackId']
        self.NumMissle = self.params['NumMissle']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    # （12.26）目前测试阶段暂时不调用这个动作组件，后期需要明确attack_trackId与target_id_list的关系，目前版本step函数参考价值较低
    def step(self):
        cmds = []
        # if self._target_id_list:
        #     for id in self._unit_id_list:
        #         target = random.choice(self._target_id_list)
        #         cmds.append(PlatActions.make_action_SetPlatFireCtl(nPlatId=id, attack_trackId=target, attack_postion=, num_missle=))
        # self.set_mission_status(MissionStatus.Exited)
        return cmds

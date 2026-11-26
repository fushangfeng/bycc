import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import RjamActions, RadarActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "预警雷达开关机",      # 组件名称，用于前端显示和后台索引
    "class": "WarnRadarWorkOnMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "unit_id_list": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        # 参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"parameter"
        },
        "open_flag": {                      # 参数名称，python代码中传入的实际参数名
            "display_name": "开/关机",  # 参数显示名，用于前端显示
            "type": "list",    # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"    分别是：主语  宾语  参数
        }

    },
    "description": "预警雷达开关机"    # 组件描述，用于前端显示
}


class WarnRadarWorkOnMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self._unit_id_list = self.params['unit_id_list']
        self._open_flag = self.params['open_flag']
        # print("=========当前预警雷达开关动作的id有=========", self._unit_id_list)
        # print("=========当前预警雷达开关动作是=========", self._open_flag)
        # self._target_id_list = self.params['target_id_list']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        """
        注意：目前id传入的是PlatID，因为单位id可能不唯一，只有PlatID是唯一的
        所以下面需要根据平台id从对应的雷达单位中选择相对应的雷达单位，去执行指令

        """
        cmds = []
        for id in self._unit_id_list:
            # 找到对应的单位id ， 决策空间是平台id
            entity_info = self.info_manager.unit_manager._unit_dict[id]
            entity_id = entity_info.attribute.entity_id

            # print("当前雷达的id是----------", entity_id)
            # print("当前雷达执行的动作是---------", self._open_flag)           # 0表示关机，1表示开机

            if self._open_flag == 0:
                flag = False
            else:
                flag = True

            # 雷达开关机
            cmds.append(RadarActions.make_action_radar_WorkOnAction(nRadarId=entity_id, bWorkOn=flag))

        self.set_mission_status(MissionStatus.Exited)
        return cmds

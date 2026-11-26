import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import PlatActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "电子ZC编组协同频率分配控制",      # 组件名称，用于前端显示和后台索引
    "class": "EquipFormCoorFreqCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nEquipFormId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "装备id",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "nStartFrequency":{
            "display_name": "起始频率",   # 参数显示名，用于前端显示
            "type": "float",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "nEndFrequency":{
            "display_name": "终止频率",   # 参数显示名，用于前端显示
            "type": "float",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "电子ZC编组协同频率分配控制"    # 组件描述，用于前端显示
}

class EquipFormCoorFreqCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nEquipFormId = self.params['nEquipFormId']
        self.nStartFrequency = self.params['nStartFrequency']
        self.nEndFrequency = self.params['nEndFrequency']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self.nEquipFormId:
            cmds.append(PlatActions.make_action_CoorFreqCtl(nEquipFormId=id, nStartFrequency=self.nStartFrequency, nEndFrequency=self.nEndFrequency))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

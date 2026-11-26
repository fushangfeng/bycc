from bycc.common.mission import Mission, MissionStatus


DECLARATION = {
    "name": "XKU雷达ZC衰减控制",  # 组件名称，用于前端显示和后台索引
    "class": "XKUReconDecayMission",  # 组件类名
    "params": {  # 组件参数，用于前端显示参数信息
        "DecayValue1_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "衰减值索引1",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        }
    },
    "description": "XKU雷达ZC衰减控制"  # 组件描述，用于前端显示
}


class XKUReconDecayMission(Mission):
    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self._info_manager = info_manager

        self.decayValue1_idx = self.params['DecayValue1_idx']

        # xku衰减值1步进5dB，0~35dB全阵统一衰减
        self.AttenuatorList1 = [0, 5, 10, 15, 20, 25, 30, 35]

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = {}

        decayValue1 = self.AttenuatorList1[self.decayValue1_idx]
        # decayValue2 = self.AttenuatorList2[self.decayValue2_idx]

        Attenuator = {
            "decayValue1": decayValue1
        }

        cmds['SetRadarReconParam_Agent'] = Attenuator
        self.set_mission_status(MissionStatus.Exited)
        return [cmds]

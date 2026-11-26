from bycc.common.mission import Mission, MissionStatus


DECLARATION = {
    "name": "L雷达ZC衰减控制",  # 组件名称，用于前端显示和后台索引
    "class": "LReconDecayMission",  # 组件类名
    "params": {  # 组件参数，用于前端显示参数信息
        "DecayValue1_idx": {  # 参数名称，python代码中传入的实际参数名
            "display_name": "衰减值索引1",  # 参数显示名，用于前端显示
            "type": "int",  # 参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"
        }
    },
    "description": "L雷达ZC衰减控制"  # 组件描述，用于前端显示
}


class LReconDecayMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self._info_manager = info_manager
        self.decayValue1_idx = self.params['DecayValue1_idx']
        # self.decayValue2_idx = self.params['DecayValue2_idx']

        self.PlatID = 0
        PlatPara_List = info_manager.raw_obs.extra_info_dict['obs']['data']['platPara']
        for idx, PlatPara in enumerate(PlatPara_List):
            if PlatPara['EquipmentType'] != 'L_JAMMER_STATION':
                continue
            elif PlatPara['EquipmentType'] == 'L_JAMMER_STATION':
                self.PlatID = PlatPara['PlatID']
                break

        self.AttenuatorList1 = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                           26, 27, 28, 29, 30]
        # self.AttenuatorList2 = [0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 5.5, 6.0, 6.5, 7.0, 7.5, 8.0, 8.5,
        #                    9.0, 9.5, 10.0, 10.5, 11.0, 11.5, 12.0, 12.5, 13.0, 13.5, 14.0, 14.5, 15.0, 15.5, 16.0, 16.5,
        #                    17.0, 17.5, 18.0, 18.5, 19.0, 19.5, 20.0, 20.5, 21.0, 21.5, 22.0, 22.5, 23.0, 23.5, 24.0,
        #                    24.5, 25.0, 25.5, 26.0, 26.5, 27.0, 27.5, 28.0, 28.5, 29.0, 29.5, 30.0]

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = {}

        decayValue1 = self.AttenuatorList1[self.decayValue1_idx]
        # decayValue2 = self.AttenuatorList2[self.decayValue2_idx]

        Attenuator = {
            "decayValue1": decayValue1
            # "decayValue2": decayValue2
        }

        # cmds.append(XKU_RadarActions.make_action_SetRadarReconDecay(self.PlatID, Attenuator))

        cmds['SetRadarReconParam_Agent'] = Attenuator
        self.set_mission_status(MissionStatus.Exited)
        return [cmds]

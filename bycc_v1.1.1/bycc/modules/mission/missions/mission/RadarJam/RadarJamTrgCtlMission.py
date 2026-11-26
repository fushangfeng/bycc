import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import RjamActions
from env_interface.env.ewx_cmds import PlatActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "雷达GR目标控制",      # 组件名称，用于前端显示和后台索引
    "class": "RadarJamTrgCtlMission",  # 组件类名
    "params": {
        "nJamId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "装备id",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "nTargetIndex": {
            "display_name": "GR目标ID",
            "type": "list",
            "relate": "object"
        },
        "dCenterFreg": {
            "display_name": "GR样式",
            "type": "list",
            "relate": "parameter"
        },
        "JamMode": {
            "display_name": "中心频率",
            "type": "list",
            "relate": "parameter"
        },
        "dBandWidth": {
            "display_name": "带宽",
            "type": "list",
            "relate": "parameter"
        },
        "dPower": {
            "display_name": "GR功率",
            "type": "list",
            "relate": "parameter"
        }


    },
    "description": "雷达GR目标控制"    # 组件描述，用于前端显示
}

class RadarJamTrgCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nJamId = self.params['nJamId']
        self.nTargetIndex = self.params['nTargetIndex']
        self.JamMode = self.params['JamMode']
        self.dCenterFreg = self.params['dCenterFreg']
        self.dBandWidth = self.params['dBandWidth']
        self.dPower = self.params['dPower']


    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self.nJamId:
            cmds.append(RjamActions.make_action_rjam_SetRadarJamTrg(nRJamId=id, nTargetIndex=1, JamMode=0, dCenterFreg=50,
                                                       dBandWidth=100))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

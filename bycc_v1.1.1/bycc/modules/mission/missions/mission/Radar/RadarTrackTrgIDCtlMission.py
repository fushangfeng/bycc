import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import RadarActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "雷达装备跟踪航迹目标控制",      # 组件名称，用于前端显示和后台索引
    "class": "RadarTrackTrgIDCtlMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "nRadarId": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "装备id",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "TrackIdList": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "目标id列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "parameter"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        }
    },
    "description": "雷达装备跟踪航迹目标控制"    # 组件描述，用于前端显示
}

class RadarTrackTrgIDCtlMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self.nRadarId = self.params['nRadarId']
        self.TrackIdList = self.params['TrackIdList']

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        cmds = []
        for id in self.nRadarId:
            cmds.append(RadarActions.make_action_radar_SetTrackTrgID(nRadarId=id,TrackIdList=self.TrackIdList))
        self.set_mission_status(MissionStatus.Exited)
        return cmds

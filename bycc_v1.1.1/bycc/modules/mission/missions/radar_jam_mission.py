import random
from bycc.common.mission import Mission, MissionStatus
from env_interface.env.ewx_cmds import RjamActions
# from env_interface.common.cmd import Command


DECLARATION = {
    "name": "雷达GR目标",          # 组件名称，用于前端显示和后台索引
    "class": "RadarJamMission",   # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "unit_id_list": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        # 参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "target_id_list": {
            "display_name": "目标单位ID列表",
            "type": "list",
            "relate": "object"
        }
    },
    "description": "雷达GR目标"    # 组件描述，用于前端显示
}


class RadarJamMission(Mission):

    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        self._unit_id_list = self.params['unit_id_list']
        self._target_id_list = self.params['target_id_list']
        self._info_manager = info_manager

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status

    def step(self):
        # 开关机（暂不使用）
        # GR范围（暂不使用）
        # GR频率（暂不使用）
        # GR目标（会自动秒开机、使用目标频率进行GR）

        cmds = []
        states_dict = self._info_manager.raw_obs.extra_info_dict["states_dict"]
        red_data, blue_data, judge_data = states_dict[1], states_dict[2], states_dict["judgement_data"]

        # 获取蓝方id列表
        enemy_ra_list = [enemy for enemy in blue_data["radar_paras"]]
        enemy_pl_list = [enemy for enemy in blue_data["plat_paras"]
                         if blue_data["plat_paras"][enemy]["EquipmentType"] == "F-35"]
        # 获取我方雷达GR设备id列表
        red_jam = {}
        for unit in red_data["jam_get_paras"]:
            red_jam[unit] = 0
            # cmds.append(RjamActions.make_action_rjam_WorkOnAction(nRJamId=unit, bWorkOn=True, JamMode=0))

        # 获取目前被GR的蓝方id
        blue_jamed_id = []
        for juda in judge_data["rjamJudge"]:
            if juda["RadarID"] in enemy_pl_list and juda["bJam"]:
                blue_jamed_id.append(juda["RadarID"])
                if juda["JammerID"] not in red_jam:
                    red_jam[juda["JammerID"]] = 0
                else:
                    red_jam[juda["JammerID"]] += 1
        blue_rejam_id = [eid for eid in enemy_pl_list if eid not in blue_jamed_id]

        # 雷达GR目标为单个目标
        for red_id in red_data["jam_get_paras"]:
            if red_jam[red_id] < 3 and blue_rejam_id:
                for bl_reid in blue_rejam_id:
                    red_jam[red_id] += 1
                    blue_rejam_id.remove(bl_reid)
                    cmds.append(RjamActions.make_action_rjam_SetRadarJamTrg(nRJamId=red_id, nTargetIndex=[bl_reid]))
                    if red_jam[red_id] >= 3: break

        # 雷达GR目标为多个目标List
        # jam_cmds = {}
        # for red_id in red_data["jam_get_paras"]:
        #     if red_jam[red_id] < 3 and blue_rejam_id:
        #         for bl_reid in blue_rejam_id:
        #             red_jam[red_id] += 1
        #             blue_rejam_id.remove(bl_reid)
        #             if red_id not in jam_cmds:
        #                 jam_cmds[red_id] = [bl_reid]
        #             else:
        #                 jam_cmds[red_id].append(bl_reid)
        #             if red_jam[red_id] >= 3: break
        # for jc in jam_cmds:
        #     cmds.append(RjamActions.make_action_rjam_SetRadarJamTrg(nRJamId=jc, nTargetIndex=jam_cmds[jc]))

        self.set_mission_status(MissionStatus.Exited)
        return cmds
        # return []

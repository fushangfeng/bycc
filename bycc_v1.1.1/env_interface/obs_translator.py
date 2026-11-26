import copy
import json
import os
from collections import defaultdict
from copy import deepcopy
from dataclasses import dataclass
from typing import Optional, Dict, List

from bycc.common.entity.base_entity import BaseEntityInfo
from bycc.environment.env_data import ObsData
from bycc.environment.std_io.obs.std_info import SpatialInfo
from bycc.environment.translator.obs_translator import ObsTranslator
from env_interface.data_types import (RadarJammerInfo, ProtectUnitInfo, WarningRadarInfo, AircraftInfo, PlatParaInfo,
                                      RadReconParaInfo, RadarParaInfo, RadarDetectInfo, RadReconDetectParaInfo,
                                      RadarDetectTrackInfo, CommonInfo,
                                      ComJamParaInfo, ComReconParaInfo, ComReconDetectParaInfo
                                      )
from env_interface.data_types.label_info import LabelInfo
from env_interface.env.env_def import Side, EquipmentType
from env_interface.game_config import total_atts
from env_interface.protos.output.ai_pb2 import REPLY_STATES


@dataclass
class StdObs:
    """
    用于保存标准态势数据的类，属性可以是StdInfo对象
    """
    sim_time: float
    common_info: CommonInfo
    units: Dict[str, List[BaseEntityInfo]]
    spatial_info: SpatialInfo
    label_info: Optional[LabelInfo] = None


class EWXObsTranslator(ObsTranslator):
    def __init__(self):
        super().__init__()
        # 预警雷达的id值  目前只有一个预警雷达
        self.warning_radar_id = 0
        self.n = 1  # 局数
        self.step = 0

    @staticmethod
    def _get_enemy_side(self_side):
        if self_side == Side.BLUE:
            return Side.RED
        elif self_side == Side.RED:
            return Side.BLUE
        else:
            raise ValueError("阵营不存在")

    def write_obs(self, merged_units_data):
        if not os.path.exists(f"obs/{self.n}"):
            os.makedirs(f"obs/{self.n}")

        self.step += 1
        with open(f"obs/{self.n}/obs{self.step}.txt", "w", encoding="utf-8") as f:
            json.dump(merged_units_data, f, ensure_ascii=False, indent=4)
            print(merged_units_data)

    def translate(self, obs_dict):
        merged_units_data = obs_dict["merged_units_data"]
        cmds = obs_dict.get("cmds", {})
        proto_obs: REPLY_STATES = obs_dict["proto"]
        missile_obs = proto_obs.missleParent.missleParent

        # todo: 态势处理操作 merged_units_data进行处理

        # 为了态势文件和态势输入对应，后续态势处理在merged_units_data进行处理，不在转换标准格式时操作
        # self.write_obs(merged_units_data)

        # bycc标准格式转换
        side_list = [Side.RED, Side.BLUE]
        player2stdobs = {}

        for side in side_list:
            self_side_units = []
            enemy_side_units = []
            enemy_side = self._get_enemy_side(side)

            for plat_info in merged_units_data.get(side, []):
                plat_info.update(
                    dict(
                        id=plat_info["PlatID"],
                        entity_id=plat_info["PlatID"],
                        side=str(plat_info["ATT"]),
                        unit_type=plat_info['EquipmentType'],
                    )
                )

                need_process_methods = {
                    "radars": self.process_radars_obs,
                    "recons": self.process_recons_obs,
                    "jammers": self.process_jammers_obs,
                    "com_jammers": self.process_com_jammers_obs,
                    "com_recons": self.process_com_recons_obs,
            }

                for item, method in need_process_methods.items():
                    self_unit, enemy_unit = method(plat_info.get("PlatID"), plat_info.get(item, []), side, enemy_side)
                    plat_info[item] = self_unit
                    self_side_units.extend(self_unit)
                    enemy_side_units.extend(enemy_unit)

                for missile in missile_obs:
                    if missile.PlatID == plat_info["PlatID"]:
                        plat_info['missiles'] = missile.MissleParaInner
                        break

                self_side_units.append(PlatParaInfo.from_dict(plat_info))

            units = {
                str(side): self.deduplicate(self_side_units),
                str(enemy_side): self.deduplicate(enemy_side_units)
            }
            player2stdobs[str(side)] = self.make_std_obs(obs_dict, units, cmds_data=cmds.get(str(side),[]))

        # god obs
        god_units = {side: obs.obs.units[str(side)] for side, obs in player2stdobs.items()}
        for side, std_obs in player2stdobs.items():
            std_obs.extra_info_dict['god_obs'] = self.make_std_obs(obs_dict, god_units)

        if obs_dict["episode_done"]:
            self.n += 1
            self.step = 0

        return player2stdobs

    @staticmethod
    def deduplicate(units):
        seen = {}
        unique_list = [seen.setdefault(unit.id, unit) for unit in units if unit.id not in seen]
        return unique_list

    @staticmethod
    def process_recons_obs(plat_id, recons, self_side, enemy_side):
        self_units = []
        enemy_units = []

        for recon in recons:
            recon_get_param = recon.get("recon_get_param")
            if recon_get_param:
                recon_copy = copy.deepcopy(recon_get_param)
                recon_copy.update(
                    dict(
                        id=recon_copy["ReconID"],
                        entity_id=recon_copy["ReconID"],
                        side=str(recon_copy["ATT"]),
                        unit_type=recon_copy['EquipmentType'],
                        PLatID=plat_id
                    )
                )
                recon_copy["results"] = []
                recon_radar_param = recon.get("recon_radar_param", [])

                for detect in recon_radar_param:
                    recon_result = detect.get("ReconResult", {})
                    if not recon_result:
                        continue
                    locate_result = recon_result.get('LocateResult', {})

                    detect_copy = copy.deepcopy(detect)
                    detect_copy.update(recon_result)
                    detect_copy.update(locate_result)
                    detect_copy.update(
                        dict(
                            id=detect_copy["RadarID"],
                            entity_id=detect_copy["RadarID"],
                            side=str(detect_copy["ATT"]),
                            unit_type=detect_copy['PlatType'],
                        )
                    )
                    target = RadReconDetectParaInfo.from_dict(detect_copy)
                    recon_copy["results"].append(target)
                    enemy_units.append(target)

                recon_info = RadReconParaInfo.from_dict(recon_copy)
                self_units.append(recon_info)

        return self_units, enemy_units

    @staticmethod
    def process_com_recons_obs(plat_id, recons, self_side, enemy_side):
        self_units = []
        enemy_units = []

        for recon in recons:
            recon_copy = copy.deepcopy(recon)
            recon_copy.update(
                dict(
                    id=recon_copy["ReconID"],
                    entity_id=recon_copy["ReconID"],
                    side=str(recon_copy["ATT"]),
                    unit_type=recon_copy['EquipmentType'],
                    PLatID=plat_id
                )
            )
            recon_info = ComReconParaInfo.from_dict(recon_copy)
            self_units.append(recon_info)

            com_recon_dectet = recon.get("com_recon_dectet", {})
            trg_paras = com_recon_dectet.get("TrgPara", [])
            for detect in trg_paras:
                detect_copy = copy.deepcopy(detect)
                detect_copy.update(com_recon_dectet)
                detect_copy.update(
                    dict(
                        id=detect_copy["TrgID"],
                        entity_id=detect_copy["TrgID"],
                        side=str(enemy_side),
                        unit_type='',
                    )
                )
                target = ComReconDetectParaInfo.from_dict(detect_copy)
                enemy_units.append(target)

        return self_units, enemy_units

    @staticmethod
    def process_radars_obs(plat_id, radars, self_side, enemy_side):
        self_units = []
        enemy_units = []
        for radar in radars:
            radar_param = radar.get("radar_param")
            radar_detect_info = radar.get("radar_detect_info", [])
            radar_detect_info_track = radar.get("radar_detect_info_track", [])

            if radar_param:
                radar_param = copy.deepcopy(radar_param)
                radar_param.update(
                    dict(
                        id=radar_param["RadarID"],
                        entity_id=radar_param["RadarID"],
                        side=str(radar_param["ATT"]),
                        unit_type=radar_param['EquipmentType'],
                        PLatID=plat_id
                    )
                )

                radar_para_info = RadarParaInfo.from_dict(radar_param)
                self_units.append(radar_para_info)

            for radar_detect in radar_detect_info:
                radar_detect = copy.deepcopy(radar_detect)
                radar_detect.update(
                    dict(
                        id=radar_detect["PlatID"],
                        entity_id=radar_detect["PlatID"],
                        side=str(radar_detect["ATT"]),
                        unit_type=radar_detect['ePlatType'],
                    )
                )
                radar_detect = RadarDetectInfo.from_dict(radar_detect)
                enemy_units.append(radar_detect)

            for radar_detect_track in radar_detect_info_track:
                radar_detect_track.update(
                    dict(
                        id=radar_detect_track["PlatID"],
                        entity_id=radar_detect_track["PlatID"],
                        side=str(radar_detect_track["ATT"]),
                        unit_type=radar_detect_track['ePlatType'],
                    )
                )
                radar_detect_track = RadarDetectTrackInfo.from_dict(radar_detect_track)
                enemy_units.append(radar_detect_track)

        return self_units, enemy_units

    @staticmethod
    def process_jammers_obs(plat_id, jammers, self_side, enemy_side):
        self_units = []
        enemy_units = []

        for recon in jammers:
            jammer_get_param = recon.get("jammer_get_param")
            if not jammer_get_param:
                continue

            jammer_copy = copy.deepcopy(jammer_get_param)
            jammer_copy.update(jammer_copy.get("jammer_param", {}))
            jammer_copy.update(
                dict(
                    id=jammer_copy["JammerID"],
                    entity_id=jammer_copy["JammerID"],
                    side=str(jammer_copy["ATT"]),
                    unit_type=jammer_copy['EquipmentType'],
                )
            )
            recon = RadarJammerInfo.from_dict(jammer_copy)
            self_units.append(recon)

        return self_units, enemy_units

    @staticmethod
    def process_com_jammers_obs(plat_id, jammers, self_side, enemy_side):
        self_units = []
        enemy_units = []

        for jammer in jammers:
            jammer_copy = copy.deepcopy(jammer)
            jammer_copy.update(
                dict(
                    id=jammer_copy["JammerID"],
                    entity_id=jammer_copy["JammerID"],
                    side=str(jammer_copy["ATT"]),
                    unit_type=jammer_copy['EquipmentType'],
                )
            )
            equip = ComJamParaInfo.from_dict(jammer_copy)
            self_units.append(equip)

        return self_units, enemy_units

    def make_std_obs(self, obs_dict, bycc_units, cmds_data=None):
        cmds_data = self._make_std_label(cmds_data)
        std_obs = ObsData(obs=StdObs(sim_time=obs_dict['metaData']['SIM_TIME'],
                                     common_info=CommonInfo(
                                         sim_state=int(obs_dict['metaData']['SIM_STATE']),
                                         sim_time=obs_dict['metaData']['SIM_TIME'],
                                         sim_speed=obs_dict['metaData']['SIM_RATE']),
                                     units=bycc_units,
                                     spatial_info=None,
                                     label_info=LabelInfo(cmds_data),
                                     ),
                          episode_done=obs_dict["episode_done"],
                          extra_info_dict={'obs': obs_dict})
        return std_obs

    # 参考的刘明建的代码，指令数据疑似是被fake了，不太明白用法
    @staticmethod
    def _make_std_label(cmds_data):
        if not cmds_data:
            return {}
        else:
            cmds_data = {
                "label_0jmL3mHzob_category": 1,
                "label_RE0RVqMycB_single_selective": 1,
            }
        return cmds_data

    def translate2(self, obs_dict):
        # 为了保持和 12.20 验收的 demo 兼容，translate 在逻辑上分为两段，states_dict 为 demo 所用，进行了阵营切分并转化为字典
        # todo 阵营信息如何获取

        # states_dict = defaultdict(lambda: defaultdict(dict))
        states_dict = defaultdict(lambda: {'plat_paras': {},
                                           'radar_paras': {},
                                           'radar_ranges': {},
                                           'radar_detect_infos': {},
                                           'recon_areas': {},
                                           'recon_radar_paras': {},
                                           'jam_get_paras': {},
                                           'jam_paras': {},
                                           'recon_get_paras': {},
                                           "protect_area": {}})

        data = obs_dict['data']
        episode_done = obs_dict["episode_done"]
        radarid2att = {}
        reconid2att = {}

        # todo att 表示敌我属性  1表示红方，2表示蓝方    雷达包含两方面，红方的，也有蓝方的，蓝方飞机上挂载的雷达模块
        for info in data['radarParam']:
            id = info['RadarID']
            att = info['ATT']
            radarid2att[id] = att
            states_dict[att]['radar_paras'][id] = info  # 雷达状态报/雷达参数

            # 当前只有这一个预警雷达，记录下其id值
            if info["EquipmentType"] == EquipmentType.RADAR_STATION:
                self.warning_radar_id = id
            # 详见 SimuModelDataOut.proto   sRADAR_PARA

        for info in data['radarRange']:
            id = info['RadarID']
            att = radarid2att.get(id)
            if att:
                states_dict[att]['radar_ranges'][id] = info  # 雷达TC参数（范围）
                # 详见 SimuModelDataOut.proto   sRADAR_RANGE

        for info in data['radarDetectInfo']:
            id = info['RadarID']
            # todo： 可能出现 radarParam 中没有该雷达id的情况
            att = radarid2att.get(id)
            # 目前训练，只考虑红方ZC到的蓝方雷达信息
            if att == 1:
                if len(info['RadarDetectPlat']) != 0:
                    states_dict[att]['radar_detect_infos'][id] = info  # 雷达TC结果   红方预警雷达及蓝方飞机携带的雷达
                    # 拿到ZC目标后，需要通过PlatIDl去plat param中读取响应的平台的信息
                    # print("Red Warning Detect Info 当前预警雷达TC得到的目标信息有--------", info)
            elif att == 2:
                if len(info['RadarDetectPlat']) != 0:
                    states_dict[att]['radar_detect_infos'][id] = info  # 雷达TC结果   蓝方飞机携带的雷达
                    # 拿到ZC目标后，需要通过PlatIDl去plat param中读取响应的平台的信息
                    # print("Blue Warning Detect Info 当前蓝方雷达TC得到的目标信息有--------", info)

        for info in data['platPara']:
            # 排除gps卫星
            if info["EquipmentType"] == EquipmentType.GPS_AIR:
                continue
            else:
                id = info['PlatID']
                att = info["ATT"]
                states_dict[att]['plat_paras'][id] = info  # 平台数据

                # 将保护地的信息单独存储一下
                if info['EquipmentType'] == EquipmentType.PROTECT_TARGET:
                    states_dict[att]['protect_area'][id] = info

        for info in data['reconGetPara']:
            id = info['ReconID']
            att = info['ATT']
            reconid2att[id] = att
            states_dict[att]['recon_get_paras'][id] = info  # TC定位区域信息
            # 详见 SimuModelDataOut.proto   sRECON_Get_PARA

        for info in data['reconArea']:
            id = info['ReconID']
            # att = reconid2att[id]
            att = reconid2att.get(id)
            if att:
                states_dict[att]['recon_areas'][id] = info  # TC雷达信息
                # 详见 SimuModelDataOut.proto   sRECON_AREA

        for info in data['reconRadarPara']:
            id = info['ReconID']
            # att = reconid2att[id]
            att = reconid2att.get(id)
            if att:
                states_dict[att]['recon_radar_paras'][id] = info  # 雷达ZC辐射源工作特征参数
                # 详见 SimuModelDataOut.proto   sRECON_RADARPARA

        for info in data['jamGetPara']:
            id = info['JammerID']
            att = info['ATT']
            # if len(info["lJamedTrgVal"]) != 0:
            #     print("当前存在GR-----------", )
            states_dict[att]['jam_get_paras'][id] = info  # GR机GR结果参数报
            # 详见 SimuModelDataOut.proto   sJAM_Get_PARA

        for info in data['jamPara']:
            id = info['JammerID']
            att = info['ATT']
            states_dict[att]['jam_paras'][id] = info  # GR机GR交互基本参数报
            # 详见 SimuModelDataOut.proto   sJAM_PARA

        # print(f"共计{len(states_dict) - 1}个阵营")
        # for att in states_dict.keys():
        #     if att != 'meta_data':
        #         print(f"收到{len(states_dict[att]['radar_paras'])}个radar_paras！", end='')
        #         print(f"收到{len(states_dict[att]['radar_ranges'])}个radar_ranges！", end='')
        #         print(f"收到{len(states_dict[att]['radar_detect_infos'])}个radar_detect_infos！", end='')
        #         print(f"收到{len(states_dict[att]['plat_paras'])}个plat_paras！", end='')
        #         print(f"收到{len(states_dict[att]['recon_areas'])}个recon_areas！", end='')
        #         print(f"收到{len(states_dict[att]['recon_radar_paras'])}个recon_radar_paras！", end='')
        #         print(f"收到{len(states_dict[att]['jam_get_paras'])}个jam_get_paras！", end='')
        #         print(f"收到{len(states_dict[att]['jam_paras'])}个jam_paras！")
        # print()

        states_dict = dict(states_dict)
        metadata = obs_dict['metaData']
        judgement_data = obs_dict['judgementdata']

        # 预警雷达是否被GR
        warning_radar_flag = 0
        # todo 当前存在GR裁决数据   蓝方EA-18G会发射辐射弹来GR红方的预警雷达
        if len(judgement_data["rjamJudge"]) != 0:
            # print("--------------当前存在GR裁决数据--------------------")

            for jam_data in judgement_data["rjamJudge"]:
                # 判断当前预警雷达，是否被雷达GR了（目前只有一个预警雷达）
                if jam_data["RadarID"] == self.warning_radar_id and jam_data["bJam"] is True:
                    warning_radar_flag = 1
                    break

        for att, value in states_dict.items():
            states_dict[att]['meta_data'] = deepcopy(metadata)

        # real_time, sim_time = metadata.REAL_TIME, metadata.SIM_TIME
        # states_dict['meta_data'] = {'real_time':real_time, 'sim_time':sim_time}
        states_dict['meta_data'] = metadata
        states_dict['judgement_data'] = judgement_data
        states_dict['raw_obs'] = obs_dict
        # 全局信息
        states_dict['god'] = deepcopy(states_dict)
        # todo 确认全部阵营信息
        self.players = total_atts

        godview2units = defaultdict(list)
        player2units = defaultdict(list)
        player2stdobs = {"1": [], "2": []}

        for player in self.players:
            if player == Side.BLUE:
                pass

            else:
                # 1. 红方GR机的信息
                for jam_id, jam in states_dict[player]['jam_get_paras'].items():

                    jam_att = str(jam['ATT'])
                    jam_info = RadarJammerInfo(id=jam["JammerID"],
                                               entity_id=jam["JammerID"],
                                               side=jam_att,
                                               unit_type=jam['EquipmentType'],
                                               fLat=jam['fLat'],
                                               fLon=jam['fLon'],
                                               fHeight=jam['fHeight'],
                                               PlatID=jam['PlatID'],
                                               WorkState=jam['WorkState'],
                                               JamPointAmount=jam['JamPointAmount'],
                                               iTrgNum=max(0, jam['iTrgNum']),
                                               iJamedTrgNum=max(0, jam['iJamedTrgNum']),
                                               )
                    godview2units[jam_att].append(jam_info)
                    if jam['ATT'] == player:
                        player2units[jam_att].append(jam_info)
                    else:
                        continue

                # 2. 红方保护地的信息
                for p_area_id, p_area in states_dict[player]['protect_area'].items():
                    p_area_att = str(p_area['ATT'])
                    area_info = ProtectUnitInfo(id=p_area['PlatID'],
                                                entity_id=-1,  # pin保护地给一个默认值  -1
                                                side=p_area_att,
                                                unit_type=p_area['EquipmentType'],
                                                fLat=p_area['fLat'],
                                                fLon=p_area['fLon'],
                                                iActiveFlag=p_area['iActiveFlag'],
                                                )
                    godview2units[p_area_att].append(area_info)
                    if p_area['ATT'] == player:
                        player2units[p_area_att].append(area_info)
                    else:
                        continue

                # 3. 红方ZC到的敌方雷达-蓝方平台的信息   目前蓝方都是飞机
                radar_detect_plat_id_list = []
                detect_plat_list = []
                if len(states_dict[player]['radar_detect_infos']) != 0:
                    for radar_id, target_dict in states_dict[player]['radar_detect_infos'].items():
                        # 当前雷达所属的阵营
                        radar_att = str(states_dict[player]["radar_paras"][radar_id]["ATT"])

                        detect_info_list = target_dict["RadarDetectPlat"]
                        for detect_info_dict in detect_info_list:

                            plat_id = detect_info_dict['PlatID']
                            # 添加 去重
                            if plat_id not in detect_plat_list:
                                detect_plat_list.append(plat_id)

                                detect_info_dict['ATT'] = str(detect_info_dict['ATT'])
                                # 找到当前ZC到的目标的平台id， PlatID  可以用其取相应的数据
                                # 从敌方Plat 信息中拿到相应的数据
                                target_air_info_dict = states_dict[2]["plat_paras"][
                                    detect_info_dict['PlatID']]  # todo 目前目标胡阵营，写死是2了  暂时这样

                                target_air_info = AircraftInfo(id=detect_info_dict['PlatID'],
                                                               entity_id=-1,  # 没有的话 给一个默认值  -1
                                                               side="2",  # todo 目前目标胡阵营，写死是2了  暂时这样
                                                               unit_type=target_air_info_dict['EquipmentType'],
                                                               fLat=detect_info_dict['fLat'],
                                                               fLon=detect_info_dict['fLon'],
                                                               fHeight=detect_info_dict['fHeight'],
                                                               fSpeed=target_air_info_dict['fSpeed'],
                                                               fDirection=target_air_info_dict['fDir'],
                                                               )
                                godview2units[radar_att].append(target_air_info)

                                radar_detect_plat_id_list.append(detect_info_dict['PlatID'])
                                if radar_att == str(player):
                                    player2units[radar_att].append(target_air_info)
                                else:
                                    continue

                # 雷侦 拿到雷达id，根据雷达id查找搭载雷达的平台
                if states_dict[player]['recon_radar_paras']:
                    detect_enemy_radar_id_list = []
                    radar_att = str(player)
                    for r_id, info in states_dict[player]['recon_radar_paras'].items():
                        for recon_radar_para in info['ReconRadarPara']:
                            detect_enemy_radar_id_list.append(recon_radar_para['RadarID'])
                    detect_enemy_radar_id_list = list(set(detect_enemy_radar_id_list))

                    for r_id, r_info in states_dict[2]['radar_paras'].items():  # todo: 写死了2
                        if r_id in detect_enemy_radar_id_list and r_info["PlatID"] not in radar_detect_plat_id_list:
                            target_air_info = AircraftInfo(id=r_info['PlatID'],
                                                           entity_id=r_info['RadarID'],  # 没有的话 给一个默认值  -1
                                                           side="2",  # todo 目前目标胡阵营，写死是2了  暂时这样
                                                           unit_type=r_info['EquipmentType'],
                                                           fLat=r_info['fLat'],
                                                           fLon=r_info['fLon'],
                                                           fHeight=r_info['fHeight'],
                                                           fSpeed=0,
                                                           fDirection=0,
                                                           )
                            godview2units[radar_att].append(target_air_info)
                            player2units[radar_att].append(target_air_info)

                # 4. 红方预警雷达的信息   目前只针对红方的预警雷达
                # todo 注意： platid是唯一的，但是radarid和别的id可能会重复，推荐使用platid
                for radar_id, radar in states_dict[player]['radar_paras'].items():
                    radar_att = str(radar['ATT'])
                    if radar["EquipmentType"] == EquipmentType.RADAR_STATION:
                        warn_radar_info = WarningRadarInfo(
                            id=radar['PlatID'],
                            entity_id=radar["RadarID"],
                            side=radar_att,
                            unit_type=radar['EquipmentType'],

                            fLat=radar['fLat'],
                            fLon=radar['fLon'],
                            fDir=0,  # todo 目前态势中没有，先给一个默认值  0
                            iActiveFlag=radar['SurvivalState'],  # 0表示正常，1表示被摧毁 ，对应MEnStruct_Macros.h 文件中
                            WorkState=radar['WorkState'],  # 0表示正常，1表示被摧毁 ，对应MEnStruct_Macros.h 文件中
                            # jam_flag = warning_radar_flag       # 新增，当前预警雷达是否被GR中
                        )
                        godview2units[radar_att].append(warn_radar_info)
                        if radar['ATT'] == player:
                            player2units[radar_att].append(warn_radar_info)
                        else:
                            continue

                god_obs = ObsData(obs=StdObs(sim_time=states_dict['meta_data']['SIM_TIME'],
                                             common_info=CommonInfo(
                                                 sim_state=int(states_dict['meta_data']['SIM_STATE']),
                                                 sim_time=states_dict['meta_data']['SIM_TIME'],
                                                 sim_speed=states_dict['meta_data']['SIM_RATE']),
                                             units=godview2units,
                                             spatial_info=None,
                                             ),
                                  episode_done=episode_done,
                                  extra_info_dict={'states_dict': states_dict})

                std_obs = ObsData(obs=StdObs(sim_time=states_dict['meta_data']['SIM_TIME'],
                                             common_info=CommonInfo(
                                                 sim_state=int(states_dict['meta_data']['SIM_STATE']),
                                                 sim_time=states_dict['meta_data']['SIM_TIME'],
                                                 sim_speed=states_dict['meta_data']['SIM_RATE']),
                                             units=player2units,
                                             spatial_info=None,
                                             ),
                                  episode_done=episode_done,
                                  extra_info_dict={'states_dict': states_dict,
                                                   'god_obs': god_obs,
                                                   'obs': obs_dict})
                player2stdobs[str(player)] = std_obs

        # todo  算法平台运行需要，后续蓝方需替换为自己的态势
        player2stdobs['2'] = player2stdobs['1']

        return player2stdobs

    if __name__ == '__main__':
        pass

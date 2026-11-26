import copy
from typing import cast

from google.protobuf.json_format import MessageToDict
from google.protobuf.descriptor import FieldDescriptor
from env_interface.env.env_def import Side
from env_interface.protos.output.ai_pb2 import REPLY_STATES


class RawObs(object):

    def __init__(self, raw_obs):
        self._raw_obs = raw_obs
        self.proto = cast(REPLY_STATES, DecodedProtoWrapper(self._raw_obs))

    def to_dict(self):

        self._obs_dict = MessageToDict(
            self._raw_obs,
            including_default_value_fields=True,
            use_integers_for_enums=True,
            preserving_proto_field_name=True
        )

        self._convert_bytes_fields_to_utf8(self._raw_obs, self._raw_obs.DESCRIPTOR, self._obs_dict)

        self._obs_dict['merged_units_data'] = self._merge_data(self._obs_dict)
        self._obs_dict['调试用的grpc原始信息，后续需删除'] = self._raw_obs  # FIXME： 由于转字典时，grpc信息为空的字段可能在字典中不体现，为便于调试，暂时将原始信息传入
        self._obs_dict['proto'] = self.proto

        return self._obs_dict

    def _convert_bytes_fields_to_utf8(self, message, descriptor, res_message):
        if isinstance(res_message, dict):
            for field, value in res_message.items():
                field_descriptor = descriptor.fields_by_name[field]
                if field_descriptor.type == FieldDescriptor.TYPE_BYTES:
                    res_message[field] = getattr(message, field).decode('utf-8')
                elif field_descriptor.type == FieldDescriptor.TYPE_MESSAGE:
                    self._convert_bytes_fields_to_utf8(getattr(message, field), field_descriptor.message_type, value)
        elif isinstance(res_message, list):
            for i, value in enumerate(res_message):
                for field in descriptor.fields:
                    if field.type == FieldDescriptor.TYPE_BYTES:
                        value[field.name] = getattr(message[i], field.name).decode('utf-8')
                    if field.message_type is not None:
                        if field.name in value:
                            self._convert_bytes_fields_to_utf8(getattr(message[i], field.name), field.message_type, value[field.name])

    def _merge_data(self, obs_dict):
        # 将分散在各个字段中的的态势聚合到一起
        units_dict = {Side.RED: [], Side.BLUE: [], Side.OTHERS: []}
        plat_params = obs_dict['data']['platPara']
        for plat_info in plat_params:
            if plat_info['ATT'] in units_dict.keys():
                unit_info = copy.deepcopy(plat_info)

                self._merge_radar_info(unit_info, obs_dict)
                self._merge_recon_info(unit_info, obs_dict)
                self._merge_jammer_info(unit_info, obs_dict)
                self._merge_com_jammer_info(unit_info, obs_dict)
                self._merge_com_recon_info(unit_info, obs_dict)

                units_dict[plat_info['ATT']].append(unit_info)
            else:
                raise ValueError(f'Unknown ATT: {plat_info["ATT"]} !!!')

        return units_dict

    @staticmethod
    def _merge_radar_info(unit_info, obs_dict):
        if unit_info['PlatID'] in [radarParam['PlatID'] for radarParam in obs_dict['data']['radarParam']]:
            # 获取合并后的雷达信息：platInfo + radarParam + radarDetectInfo
            unit_info['radars'] = []  # 一个平台可能有多个雷达
            for radar_param in obs_dict['data']['radarParam']:
                if radar_param['PlatID'] == unit_info['PlatID']:
                    unit_info['radars'].append({'radar_param': radar_param})

            for radar in unit_info['radars']:
                if 'RadarID' in radar['radar_param']:
                    for radar_detect_info in obs_dict['data']['radarDetectInfo']:
                        if radar_detect_info['RadarID'] == radar['radar_param']['RadarID']:
                            radar['radar_detect_info'] = radar_detect_info.get('RadarDetectPlat', [])  # 只记录TC到的平台列表

                    for radar_detect_info_track in obs_dict['data']['readrDetectInfoTrack']:
                        if radar_detect_info_track['RadarID'] == radar['radar_param']['RadarID']:
                            radar['radar_detect_info_track'] = radar_detect_info_track.get('RadarDetectPlatTrack', [])

                    # TODO: radarRange字段中的RadarID应该和哪里对应？
                    for radar_range in obs_dict['data']['radarRange']:
                        if radar_range['RadarID'] == radar['radar_param']['RadarID']:
                            radar['radar_range'] = radar_range

    @staticmethod
    def _merge_recon_info(unit_info, obs_dict):
        if unit_info['PlatID'] in [recon_get_param['PlatID'] for recon_get_param in obs_dict['data']['reconGetPara']]:
            # 获取合并后的recon信息，platINFO + reconGetPara + reconRadarParam + reconArea
            unit_info['recons'] = []
            for recon_get_param in obs_dict['data']['reconGetPara']:
                if recon_get_param['PlatID'] == unit_info['PlatID']:
                    unit_info['recons'].append({'recon_get_param': recon_get_param})

            for recon in unit_info['recons']:
                if 'ReconID' in recon['recon_get_param']:
                    for recon_radar_param in obs_dict['data']['reconRadarPara']:
                        if recon_radar_param['ReconID'] == recon['recon_get_param']['ReconID']:
                            recon['recon_radar_param'] = recon_radar_param.get('ReconRadarPara', [])

                    for recon_area in obs_dict['data']['reconArea']:
                        if recon_area['ReconID'] == recon['recon_get_param']['ReconID']:
                            recon['recon_area'] = recon_area

    @staticmethod
    def _merge_jammer_info(unit_info, obs_dict):
        if unit_info['PlatID'] in [jammer_get_param['PlatID'] for jammer_get_param in obs_dict['data']['jamGetPara']]:
            unit_info['jammers'] = []
            for jam_get_param in obs_dict['data']['jamGetPara']:
                if jam_get_param['PlatID'] == unit_info['PlatID']:
                    unit_info['jammers'].append({'jammer_get_param': jam_get_param})

            for jam in unit_info['jammers']:
                if 'JammerID' in jam['jammer_get_param']:
                    for jammer_param in obs_dict['data']['jamPara']:
                        if jammer_param['JammerID'] == jam['jammer_get_param']['JammerID']:
                            jam['jammer_param'] = jammer_param

    @staticmethod
    def _merge_com_jammer_info(unit_info, obs_dict):
        unit_info['com_jammers'] = []
        for com_jammer_info in obs_dict['data']['comMjampara']:
            if com_jammer_info['PlatID'] == unit_info['PlatID']:
                unit_info['jammers'].append(com_jammer_info)

    @staticmethod
    def _merge_com_recon_info(unit_info, obs_dict):
        unit_info['com_recons'] = []
        for com_recon_info in obs_dict['data']['comReconpara']:
            if com_recon_info['PlatID'] == unit_info['PlatID']:
                unit_info['com_recons'].append(com_recon_info)
        for com_recon in unit_info['com_recons']:
            for com_recon_dectet in obs_dict['data']['comMdetectPara']:
                if com_recon['ReconID'] == com_recon_dectet['EquipID']:
                    com_recon['com_recon_dectet'] = com_recon_dectet

class DecodedProtoWrapper:
    def __init__(self, proto):
        self._proto = proto

    @property
    def proto(self):
        return self._proto

    def __getattr__(self, name: str):
        value = getattr(self._proto, name)
        field = self._proto.DESCRIPTOR.fields_by_name.get(name)

        if field is None:
            return value

        if field.type == FieldDescriptor.TYPE_BYTES and isinstance(value, bytes):
            try:
                return value.decode('utf-8')
            except UnicodeDecodeError:
                return value

        if field.type == FieldDescriptor.TYPE_MESSAGE:
            if field.label == FieldDescriptor.LABEL_REPEATED:
                return [DecodedProtoWrapper(v) for v in value]
            return DecodedProtoWrapper(value)

        if field.type == field.LABEL_REPEATED:
            return list(value)
        return value
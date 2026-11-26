# -*- coding: utf-8 -*-
from dataclasses import dataclass
from typing import List

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature
from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.data_types.jammer.com_jammer import ComJamParaInfo
from env_interface.data_types.jammer.radar_jammer import RadarJammerInfo
from env_interface.data_types.radar.radar_para import RadarParaInfo
from env_interface.data_types.recon.com_recon import ComReconParaInfo
from env_interface.data_types.recon.rad_recon import RadReconParaInfo
from env_interface.protos.output.ai_pb2 import MISSLEPARA_INNER


class PlatPara(ewxEntity):
    """
    平台--状态组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class PlatParaInfo(ewxEntityInfo):
    sRID: str
    PlatID: int
    EquipmentName: str
    EquipmentType: str
    ATT: int
    fTime: float
    fLon: float
    fLat: float
    fHeight: float
    fSpeed: float
    fDir: float
    fPitch: float
    fRoll: float
    iActiveFlag: int
    nRCSNum: int
    RCSArray: List
    PlatType: int
    radars: List[RadarParaInfo]
    recons: List[RadReconParaInfo]
    jammers: List[RadarJammerInfo]
    com_jammers: List[ComJamParaInfo]
    com_recons: List[ComReconParaInfo]
    missiles: List[MISSLEPARA_INNER]

    @classmethod
    def get_entity_cls(cls):
        return PlatPara


@dataclass
class PlatParaStateSpace(ewxStateSpace):
    PlatID: PlainFeature
    ATT: PlainFeature
    fTime: PlainFeature
    fLon: PlainFeature
    fLat: PlainFeature
    fHeight: PlainFeature
    fSpeed: PlainFeature
    fDir: PlainFeature
    fPitch: PlainFeature
    fRoll: PlainFeature
    iActiveFlag: PlainFeature
    nRCSNum: PlainFeature
    PlatType: PlainFeature

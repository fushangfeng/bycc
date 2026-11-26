# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature
from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo


# from env_interface.const import *

class RadarDetectTrack(ewxEntity):
    """
    雷达TC设备--航迹TC结果组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class RadarDetectTrackInfo(ewxEntityInfo):
    PlatID: int
    fTime: float
    ePlatType: int
    ATT: int
    nTrackNum: int
    eTrkState: int
    eTasMode: int
    fLon: float
    fLat: float
    fHeight: float
    fTrgDis: float
    fTrgAz: float
    fTrgEl: float
    fSpeed: float
    fDir: float
    fMovPitch: float
    fAZError: float
    fELError: float
    fDisError: float

    @classmethod
    def get_entity_cls(cls):
        return RadarDetectTrack

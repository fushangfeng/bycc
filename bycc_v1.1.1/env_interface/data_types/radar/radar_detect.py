# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature
from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo


# from env_interface.const import *

class RadarDetect(ewxEntity):
    """
    雷达TC设备--雷达TC结果组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class RadarDetectInfo(ewxEntityInfo):
    PlatID: int
    fTime: float
    ePlatType: int
    ATT: int
    fLon: float
    fLat: float
    fHeight: float
    fAZError: float
    fELError: float
    fDisError: float

    @classmethod
    def get_entity_cls(cls):
        return RadarDetect


@dataclass
class RadarDetectInfoStateSpace(ewxStateSpace):
    fTime: PlainFeature
    ePlatType: PlainFeature
    fLon: PlainFeature
    fLat: PlainFeature
    fHeight: PlainFeature
    fAZError: PlainFeature
    fELError: PlainFeature
    fDisError: PlainFeature

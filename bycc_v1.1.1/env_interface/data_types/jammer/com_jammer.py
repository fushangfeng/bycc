# -*- coding: utf-8 -*-
from dataclasses import dataclass
from typing import List

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature
from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo


# from env_interface.const import *

class ComJamPara(ewxEntity):
    """
    通信GR装备--状态组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class ComJamParaInfo(ewxEntityInfo):
    sRID: str
    JammerID: int
    ATT: int
    EquipmentName: str
    EquipmentType: str
    PlatType: int
    fLon: float
    fLat: float
    fHeight: float
    fTime: float
    AntennaType: int
    nAntDotNum: int
    AntData: List[float]
    nJamNum: int
    JamPara: list
    PlatID: int

    @classmethod
    def get_entity_cls(cls):
        return ComJamPara


@dataclass
class ComJamParaStateSpace(ewxStateSpace):
    JammerID: PlainFeature
    ATT: PlainFeature
    PlatType: PlainFeature
    fLon: PlainFeature
    fLat: PlainFeature
    fHeight: PlainFeature
    fTime: PlainFeature
    AntennaType: PlainFeature
    nAntDotNum: PlainFeature
    # AntData: list[float]
    nJamNum: PlainFeature
    # JamPara: list
    PlatID: PlainFeature
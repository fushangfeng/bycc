# -*- coding: utf-8 -*-
# from env_interface.const import *

from dataclasses import dataclass

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature, \
    BinaryhotFeature
from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo


class ComReconPara(ewxEntity):
    """
    通信ZC装备--状态组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class ComReconParaInfo(ewxEntityInfo):
    sRID: str
    ReconID: int
    ATT: int
    EquipmentName: str
    EquipmentType: str
    fLon: float
    fLat: float
    fHeight: float
    PlatID: int
    fTime: float
    StartAZ: float
    EndAZ: float
    fStartEL: float
    fEndEL: float
    StartRF: float
    EndRF: float
    SurvivalState: int
    WorkState: int
    WorkMode: int

    @classmethod
    def get_entity_cls(cls):
        return ComReconPara


@dataclass
class ComReconParaStateSpace(ewxStateSpace):
    ReconID: PlainFeature
    ATT: PlainFeature
    fLon: PlainFeature
    fLat: PlainFeature
    fHeight: PlainFeature
    PlatID: PlainFeature
    fTime: PlainFeature
    StartAZ: PlainFeature
    EndAZ: PlainFeature
    fStartEL: PlainFeature
    fEndEL: PlainFeature
    StartRF: PlainFeature
    EndRF: PlainFeature
    SurvivalState: PlainFeature
    WorkState: PlainFeature
    WorkMode: PlainFeature


# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature
from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo


# from env_interface.const import *

class RadarPara(ewxEntity):
    """
    雷达TC装备--状态组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class RadarParaInfo(ewxEntityInfo):
    sRID: str
    RadarID: int
    EquipmentName: str
    EquipmentType: str
    PlatID: int
    ePlatType: int
    fTime: float
    ATT: int
    WorkState: int
    SurvivalState: int
    eRadarSort: int
    eRadarWorkMode: int
    fLon: float
    fLat: float
    fHeight: float
    fRF: float
    fRFMax: float
    fRFMin: float
    fPt: float
    fLt: float
    fGt: float
    fAzBeamWidth: float
    fElBeamWidth: float
    AntAZ: float
    AntEl: float
    fAziMax: float
    fAziMin: float
    fElMax: float
    fElMin: float
    ScanCycle: float
    PCM: int
    RFT: int
    PRI: float
    PRIT: int
    PW: float
    RBand: float
    POT: int
    fSlmGt: float
    fSL1Gt: float
    fSL1BeamWidth: float
    nJamLevel: float

    @classmethod
    def get_entity_cls(cls):
        return RadarPara


@dataclass
class RadarParaStateSpace(ewxStateSpace):
    ePlatType: PlainFeature
    fTime: PlainFeature
    WorkState: PlainFeature
    SurvivalState: PlainFeature
    eRadarSort: PlainFeature
    eRadarWorkMode: PlainFeature
    fLon: PlainFeature
    fLat: PlainFeature
    fHeight: PlainFeature
    fRF: PlainFeature
    fRFMax: PlainFeature
    fRFMin: PlainFeature
    fPt: PlainFeature
    fLt: PlainFeature
    fGt: PlainFeature
    fAzBeamWidth: PlainFeature
    fElBeamWidth: PlainFeature
    AntAZ: PlainFeature
    AntEl: PlainFeature
    fAziMax: PlainFeature
    fAziMin: PlainFeature
    fElMax: PlainFeature
    fElMin: PlainFeature
    ScanCycle: PlainFeature
    PCM: PlainFeature
    RFT: PlainFeature
    PRI: PlainFeature
    PRIT: PlainFeature
    PW: PlainFeature
    RBand: PlainFeature
    POT: PlainFeature
    fSlmGt: PlainFeature
    fSL1Gt: PlainFeature
    fSL1BeamWidth: PlainFeature
    nJamLevel: PlainFeature

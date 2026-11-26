# -*- coding: utf-8 -*-
from dataclasses import dataclass

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature, \
    BinaryhotFeature
from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo


class ComReconDetectPara(ewxEntity):
    """
    通信ZC装备--目标感知结果组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class ComReconDetectParaInfo(ewxEntityInfo):
    sRID: str
    EquipID: int
    PlatID: int
    EquipmentName: str
    EquipmentType: str
    fTime: float
    nTrgNum: int
    TrgID: int
    Bandwidth: float
    CMD: int
    SignalType: int
    InfoType: int
    StartRF: float
    EndRF: float
    Duration: float
    fLon: float
    fLat: float
    iHopRate: int
    iNetID: int
    FreqNo: int
    FreqSet: list
    AZ: float
    EL: float
    DIS: float
    SignalState: int
    fAZError: float
    fELError: float
    fLocDisError: float
    fCaptureProb: float

    @classmethod
    def get_entity_cls(cls):
        return ComReconDetectPara


@dataclass
class ComReconDetectParaStateSpace(ewxStateSpace):
    EquipID: PlainFeature
    PlatID: PlainFeature
    fTime: PlainFeature
    nTrgNum: PlainFeature
    TrgID: PlainFeature
    Bandwidth: PlainFeature
    CMD: PlainFeature
    SignalType: PlainFeature
    InfoType: PlainFeature
    StartRF: PlainFeature
    EndRF: PlainFeature
    Duration: PlainFeature
    fLon: PlainFeature
    fLat: PlainFeature
    iHopRate: PlainFeature
    iNetID: PlainFeature
    FreqNo: PlainFeature
    # FreqSet: list
    AZ: PlainFeature
    EL: PlainFeature
    DIS: PlainFeature
    SignalState: PlainFeature
    fAZError: PlainFeature
    fELError: PlainFeature
    fLocDisError: PlainFeature
    fCaptureProb: PlainFeature







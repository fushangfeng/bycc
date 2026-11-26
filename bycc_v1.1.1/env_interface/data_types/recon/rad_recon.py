# -*- coding: utf-8 -*-
# from env_interface.const import *
import typing
from typing import List

from dataclasses import dataclass, fields

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature, \
    BinaryhotFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.data_types.recon.rad_recon_detect import RadReconDetectParaInfo
from env_interface.game_config import DefaultValue


class RadReconPara(ewxEntity):
    """
    雷达对抗ZC设备--状态组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class RadReconParaInfo(ewxEntityInfo):
    id: int
    PLatID: int
    ATT: int
    EquipmentName: str
    EquipmentType: str
    fLon: float
    fLat: float
    fHeight: float
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
    results: List[RadReconDetectParaInfo]

    @classmethod
    def get_entity_cls(cls):
        return RadReconPara


@dataclass
class RadReconParaStateSpace(ewxStateSpace):
    id: PlainFeature
    fLon: PlainFeature
    fLat: PlainFeature
    fHeight: PlainFeature
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


if __name__ == '__main__':
    d = RadReconParaInfo.__annotations__
    d2 = typing.get_type_hints(RadReconParaInfo)
    print(RadReconParaInfo.get_entity_cls().__doc__)
    print(d)

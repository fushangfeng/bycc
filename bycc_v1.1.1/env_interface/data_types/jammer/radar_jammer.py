# -*- coding: utf-8 -*-
from dataclasses import dataclass, field
from typing import List

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue
from env_interface.utils import to_str
from env_interface.const import RCL670_JAMMER_MaxJamTargetNum, X_KU_JAMMER_MaxJamTargetNum


# from env_interface.const import *

class RadarJammer(ewxEntity):
    """
    雷达GR装备
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class RadarJammerInfo(ewxEntityInfo):
    sRID: str
    JammerID: int
    PlatID: int

    WorkState: int
    SurvivalState: int
    fLon: float
    fLat: float
    fHeight: float
    JamPointAmount: int
    iTrgNum: int
    lTrgVal: List
    iJamedTrgNum: int
    lJamedTrgVal: List

    # RadarID: int
    # fTime: float
    # EquipmentName: str
    # EquipmentType: str
    # ATT: int
    # eAntPolarType: int
    # fPower: float
    # fGt: float
    # fSLGain: float
    # fLoss: float
    # JamPointAZ: float
    # JamPointEL: float
    # fBeamWidth: float
    # fBeamPitchWidth: float

    @classmethod
    def get_entity_cls(cls):
        return RadarJammer

    @property
    def MaxJamTargetNum(self):
        """
        最大GR目标数量
        """
        if to_str(self.unit_type) == 'RCL670_JAMMER':
            return RCL670_JAMMER_MaxJamTargetNum
        elif to_str(self.unit_type) == 'X_KU_JAMMER':
            return X_KU_JAMMER_MaxJamTargetNum


@dataclass
class RadarJammerStateSpace(ewxStateSpace):
    fLat: PlainFeature
    fLon: PlainFeature
    fHeight: PlainFeature
    WorkState: PlainFeature
    JamPointAmount: PlainFeature
    iTrgNum: PlainFeature
    iJamedTrgNum: PlainFeature
    SurvivalState: PlainFeature

    # todo: sJAM_PARA 当前态势sJAM_PARA为空
    # fTime: PlainFeature
    # ATT: PlainFeature
    # eAntPolarType: PlainFeature
    # fPower: PlainFeature
    # fGt: PlainFeature
    # fSLGain: PlainFeature
    # fLoss: PlainFeature
    # JamPointAZ: PlainFeature
    # JamPointEL: PlainFeature
    # fBeamWidth: PlainFeature
    # fBeamPitchWidth: PlainFeature
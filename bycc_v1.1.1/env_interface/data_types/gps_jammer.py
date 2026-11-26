# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue


# from env_interface.const import *

class GpsJammer(ewxEntity):
    """
    雷达GR装备
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class GpsJammerInfo(ewxEntityInfo):
    fLat: float  # = field()
    fLon: float  # = field()
    WorkState: Union[int, str]
    JamPointAmount: int
    iTrgNum: int
    iJamedTrgNum: int

    @classmethod
    def get_entity_cls(cls):
        return GpsJammer


@dataclass
class GpsJammerStateSpace(ewxStateSpace):
    fLat: PlainFeature
    fLon: PlainFeature
    WorkState: OnehotFeature
    JamPointAmount: OnehotFeature
    iTrgNum: OnehotFeature
    iJamedTrgNum: OnehotFeature


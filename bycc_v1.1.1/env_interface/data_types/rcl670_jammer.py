# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue


# from env_interface.const import *

class Rcl670Jammer(ewxEntity):
    """
    rcl670 雷达GR装备(这个GR信息，目前只有在平台信息中有，jammer信息中没有)
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class Rcl670JammerInfo(ewxEntityInfo):
    fLat: float  # = field()
    fLon: float  # = field()
    PlatID: int
    WorkState: Union[int, str]
    JamPointAmount: int
    iTrgNum: int
    iJamedTrgNum: int

    @classmethod
    def get_entity_cls(cls):
        return Rcl670Jammer


@dataclass
class Rcl670JammerStateSpace(ewxStateSpace):
    fLat: PlainFeature
    fLon: PlainFeature
    fHeight: PlainFeature
    WorkState: OnehotFeature
    JamPointAmount: OnehotFeature
    iTrgNum: OnehotFeature
    iJamedTrgNum: OnehotFeature


# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue


# from env_interface.const import *

class H9TtrRadar(ewxEntity):
    """
    H9的火控雷达
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class H9TtrRadarInfo(ewxEntityInfo):
    fLat: float  # = field()
    fLon: float  # = field()
    iActiveFlag: int  # = field()
    # PlatID: int
    # WorkState: Union[int, str]

    @classmethod
    def get_entity_cls(cls):
        return H9TtrRadar


@dataclass
class H9TtrRadarStateSpace(ewxStateSpace):
    fLat: PlainFeature
    fLon: PlainFeature
    # WorkState: OnehotFeature
    iActiveFlag: OnehotFeature  # = field()

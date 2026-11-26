# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue


# from env_interface.const import *

class ProtectUnit(ewxEntity):
    """
    红方保护要地
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class ProtectUnitInfo(ewxEntityInfo):
    fLat: float  # = field()
    fLon: float  # = field()
    # PlatID: int
    # WorkState: Union[int, str]
    iActiveFlag: int

    @classmethod
    def get_entity_cls(cls):
        return ProtectUnit


@dataclass
class ProtectUnitStateSpace(ewxStateSpace):
    fLat: PlainFeature
    fLon: PlainFeature
    iActiveFlag: OnehotFeature

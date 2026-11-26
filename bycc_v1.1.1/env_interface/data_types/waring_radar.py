# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue


# from env_interface.const import *

class WarningRadar(ewxEntity):
    """
    预警雷达
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class WarningRadarInfo(ewxEntityInfo):
    fLat: float  # = field()
    fLon: float  # = field()
    fDir: float  # = field()
    iActiveFlag: int  # = field()
    WorkState: Union[int, str]
    # jam_flag: int

    @classmethod
    def get_entity_cls(cls):
        return WarningRadar


@dataclass
class WarningRadarStateSpace(ewxStateSpace):
    fLat: PlainFeature
    fLon: PlainFeature
    fDir: PlainFeature  # = field()
    iActiveFlag: OnehotFeature  # = field()
    WorkState: OnehotFeature  # = field()
    # jam_flag: OnehotFeature  # = field()            # 当前预警机知否被GR了
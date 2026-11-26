# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue


# from env_interface.const import *

class XKuJammer(ewxEntity):
    """
    x/ku 雷达GR装备
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class XKuJammerInfo(ewxEntityInfo):
    fLat: float  # = field()
    fLon: float  # = field()
    fHeight: float  # = field()
    PlatID: int
    WorkState: Union[int, str]
    JamPointAmount: int  #GR波束个数
    iTrgNum: int  #对抗目标个数
    iJamedTrgNum: int   #被GR的目标个数

    @classmethod
    def get_entity_cls(cls):
        return XKuJammer


@dataclass
class XKuJammerStateSpace(ewxStateSpace):
    fLat: PlainFeature
    fLon: PlainFeature
    fHeight: PlainFeature
    WorkState: OnehotFeature
    JamPointAmount: OnehotFeature
    iTrgNum: OnehotFeature
    iJamedTrgNum: OnehotFeature

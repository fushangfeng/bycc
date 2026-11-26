# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue
from env_interface.data_types import Aircraft, AircraftInfo, AircraftStateSpace


class F35Aircraft(ewxEntity):
    """
    蓝方目标: F35
    后续可能会有导弹等信息
    """
    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class F35AircraftInfo(AircraftInfo):
    """
    蓝方目标的主要的态势信息   目前主要是从态势中获取，和proto文件不一定对的上
    """
    pass


    @classmethod
    def get_entity_cls(cls):
        return F35Aircraft


@dataclass
class F35AircraftStateSpace(AircraftStateSpace):
    """
    态势构建
    """
    pass
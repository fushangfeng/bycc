# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue
from env_interface.data_types import Aircraft, AircraftInfo, AircraftStateSpace


class EA18Aircraft(ewxEntity):
    """
    蓝方目标: EA18G   后续可能有导弹信息等
    """
    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class EA18AircraftInfo(AircraftInfo):
    """
    蓝方目标的主要的态势信息   目前主要是从态势中获取，和proto文件不一定对的上
    """
    pass

    @classmethod
    def get_entity_cls(cls):
        return EA18Aircraft


@dataclass
class EA18AircraftStateSpace(AircraftStateSpace):
    """
    态势构建
    """
    pass
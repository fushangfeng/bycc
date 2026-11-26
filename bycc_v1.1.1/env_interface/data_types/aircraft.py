# -*- coding: utf-8 -*-
# from env_interface.const import *
from dataclasses import dataclass, field
from typing import Union

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo, BaseEntityStateSpace
from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo
from env_interface.game_config import DefaultValue


class Aircraft(ewxEntity):
    """
    目前蓝方目标，第二个场景：主要是F35 和GR机 ea-18g  e-2d，
    """
    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class AircraftInfo(ewxEntityInfo):
    """
    蓝方目标的主要的态势信息   目前主要是从态势中获取，和proto文件不一定对的上
    """
    fLat: float  # = field()
    fLon: float  # = field()
    fHeight: float  # = field()
    # WorkState: Union[int, str]
    fSpeed: float
    fDirection: float

    # AirMaxBattleRadius: float
    # AirMaxCirRadius: float
    # AirMaxCruise: float
    # AirMaxFlight: float
    # AirMinSpeed: float
    # AirMaxSpeed: float
    # AirMaxHeight: float
    # AirType: float
    # AirModel: float
    # Airline: float
    # MissileNum: float
    # MissileMaxNum: float
    # MissileMaxqsNum: float


    @classmethod
    def get_entity_cls(cls):
        return Aircraft


@dataclass
class AircraftStateSpace(ewxStateSpace):
    """
    态势构建
    """
    fLat: PlainFeature
    fLon: PlainFeature
    fHeight: PlainFeature
    # WorkState: OnehotFeature
    fSpeed: PlainFeature
    fDirection: PlainFeature

    # AirMaxBattleRadius: PlainFeature
    # AirMaxCirRadius: PlainFeature
    # AirMaxCruise: PlainFeature
    # AirMaxFlight: PlainFeature
    # AirMinSpeed: PlainFeature
    # AirMaxSpeed: PlainFeature
    # AirMaxHeight: PlainFeature
    # AirType: PlainFeature
    # AirModel: PlainFeature
    # Airline: PlainFeature
    # MissileNum: PlainFeature
    # MissileMaxNum: PlainFeature
    # MissileMaxqsNum: PlainFeature

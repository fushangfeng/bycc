from dataclasses import dataclass

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature
from bycc.environment.std_io.obs.std_info import StdInfo, StdStateSpace


@dataclass
class CommonInfo(StdInfo):
    sim_time: float
    sim_speed: float
    sim_state: int


@dataclass
class CommonInfoStateSpace(StdInfo):
    sim_time: RangedFeature
    # sim_speed: PlainFeature
    # sim_state: PlainFeature

    @classmethod
    def data_class(cls) -> type(StdInfo):
        return CommonInfo

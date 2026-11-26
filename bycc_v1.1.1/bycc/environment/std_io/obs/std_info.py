from dataclasses import dataclass, field
from typing import List, Dict, Any

from bycc.common.data_types.data_type import DataType
from bycc.common.data_types.grid_map import GridMap
from bycc.ai.feature.feature import RangedFeature, VectorFeature, SpatialFeature


"""
用于记录StdObs中的各类信息，包括CommonInfo、 EntityInfo等
"""


@dataclass
class StdInfo:
    """
    用于定义Obs属性
    属性需要和对应的ObsSpace子类一一匹配
    """

    def get_attribute_value(self, attribute_name):
        attribute = self.__getattribute__(attribute_name)
        if isinstance(attribute, DataType):
            return attribute.value()
        else:
            return attribute

    def get_feature_dict(self, attributes: List[str]):
        """
        从对象中获取attributes各个属性名对应的值，组成字典并返回，主要用于构建神经网络输入
        Parameters
        ----------
        attributes: List[str]
            属性名组成的字典
        """
        feature_dict = {}
        for attr in attributes:
            attribute = self.get_attribute_value(attr)
            feature_dict[attr] = attribute
            # feature = self.__getattribute__(attr)
            # if isinstance(feature, DataType):
            #     feature_dict[attr] = feature.value()
            # else:
            #     feature_dict[attr] = feature
        return feature_dict


# class InfoFetcher:

#     def __call__(self, raw_data):
#         return self.call(raw_data)

#     def call(self, raw_data) -> StdInfo:
#         raise NotImplementedError


@dataclass
class StdStateSpace:
    """
    用于定义属性对应的Feature类型，包括PlainFeature、RangedFeature、VectorFeature、OnehotFeature等
    StateSpace
    属性需要和对应的StdInfo子类一一匹配
    如：
    id: PlainFeature
    unit_type: OnehotFeature
    """
    @classmethod
    def data_class(cls) -> type(StdInfo):
        raise NotImplementedError

    # def info_fetcher(self, fetcher: InfoFetcher):
    #     self.__info_fetcher = fetcher
    #     return self

    # def get_obs(self, raw_data) -> StdInfo:
    #     std_obs = self.__info_fetcher(raw_data)
    #     return std_obs


@dataclass
class CommonInfo(StdInfo):
    sim_time: float
    absolute_sim_time: Any


@dataclass
class CommonInfoStateSpace(StdStateSpace):
    sim_time: RangedFeature
    absolute_sim_time: RangedFeature

    @classmethod
    def data_class(cls) -> type(StdInfo):
        return CommonInfo


@dataclass
class SpatialInfo(StdInfo):
    self_entity_map: GridMap = field(default=None)
    enemy_entity_map: GridMap = field(default=None)


@dataclass
class SpatialInfoStateSpace(StdStateSpace):
    self_entity_map: SpatialFeature
    enemy_entity_map: SpatialFeature

    @classmethod
    def data_class(cls) -> type(StdInfo):
        return SpatialInfo

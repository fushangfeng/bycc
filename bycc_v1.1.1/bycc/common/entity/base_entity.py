from typing import Union
from dataclasses import dataclass, field
from bycc.common.entity.entity import Entity
from bycc.environment.std_io.std_def import UnitType, UnitSubType
from bycc.environment.std_io.obs.std_info import StdStateSpace, StdInfo

from bycc.common.data_types.position import Position
from bycc.common.data_types.lon_lat_position import LonLatPosition
from bycc.ai.feature.feature import PlainFeature, RangedFeature, OnehotFeature


@dataclass
class BaseEntityInfo(StdInfo):
    id: int
    side: str
    alive: bool
    position: Union[Position, LonLatPosition] = field(metadata={"help": "position列表包括x、y、z三个元素，Position使用相对坐标，非绝对坐标，单位：米， LonLatPosition使用经纬度坐标"})
    angle: float = field(metadata={"help": "单位朝向角，以y轴正方向或正北方为0度，顺时针旋转，范围0-360度"})
    unit_type: UnitType
    unit_subtype: Union[UnitSubType, None] = field(metadata={"help": "当仿真中未明确实体类型时，使用抽象单位类型，此时subtype可为None"})

    @classmethod
    def get_entity_cls(cls):
        # 返回Info类匹配的Entity类
        raise NotImplementedError


@dataclass
class BaseEntityStateSpace(StdStateSpace):

    id: PlainFeature
    side: OnehotFeature  # 原始数据类型为string，转为onehot后输入到神经网络
    alive: OnehotFeature
    position: RangedFeature
    angle: RangedFeature
    unit_type: OnehotFeature
    unit_subtype: OnehotFeature


class BaseEntity(Entity):

    def __init__(self, attribute: BaseEntityInfo):
        self.cmds = []
        self.__attribute = attribute

    def run(self):
        pass

    @property
    def attribute(self):
        return self.__attribute

    def __getattr__(self, item):
        if item == "__setstate__":
            raise AttributeError(item)
        else:
            return getattr(self.__attribute, item)

    def update(self, data: BaseEntityInfo = None):
        self.cmds.clear()
        if data:
            self.__attribute = data

    @property
    def id(self):
        return self.__attribute.id

    @property
    def side(self):
        return self.__attribute.side

    @property
    def position(self):
        return self.__attribute.position

    @property
    def unit_type(self):
        return self.__attribute.unit_type

    @property
    def unit_subtype(self):
        return self.__attribute.unit_subtype

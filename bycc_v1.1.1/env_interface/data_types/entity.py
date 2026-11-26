from dataclasses import dataclass, fields

from env_interface.game_config import DefaultValue
from bycc.common.entity.base_entity import BaseEntityStateSpace, BaseEntityInfo, BaseEntity
from bycc.environment.std_io.obs.std_info import StdInfo
from bycc.environment.std_io.obs.std_info import StdStateSpace
from typing import Union


# from env_interface.data_types.unit_def import UnitType

class ewxEntity(BaseEntity):
    def __init__(self, unit_info):
        super().__init__(unit_info)


@dataclass
class ewxEntityInfo(StdInfo):
    id: int                 # 平台id , PlatID
    entity_id: int          # 单位id   装备id
    side: Union[int, str]  # 暂定为att
    unit_type: Union[int, str]  # UnitType

    @classmethod
    def from_dict(cls, data):
        try:
            field_names = {f.name for f in fields(cls)}
            known_fields = {k: v for k, v in data.items() if k in field_names}
            instance = cls(**known_fields)
        except:
            print(data)
            raise ValueError("field error")
        return instance


@dataclass
class ewxStateSpace(StdStateSpace):
    pass

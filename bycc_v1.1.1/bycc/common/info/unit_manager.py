from collections import defaultdict
from typing import Any, Dict, List, Union, Set

from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo
from bycc.common.data_types import RelativeSide
from bycc.common.data_types.grid_map import GridMap
from bycc.environment.env_data import ObsData
from bycc.environment.std_io.std_def import UnitSubType, UnitType
from bycc.common.info.manager import AbstractInfoManager


class UnitManager(AbstractInfoManager):

    def __init__(self):
        self._unit_dict = defaultdict(BaseEntity)

    def add_unit(self, unit: BaseEntity):
        self._unit_dict[unit.id] = unit

    def update(self, std_obs: ObsData):
        updated_ids = []
        for side, unit_info_list in std_obs.obs.units.items():
            unit_info: BaseEntityInfo
            for unit_info in unit_info_list:
                if unit_info.id not in self._unit_dict:
                    cls = unit_info.get_entity_cls()
                    self.add_unit(cls(unit_info))
                else:
                    self._unit_dict[unit_info.id].update(unit_info)
                updated_ids.append(unit_info.id)

        # 态势信息中没有数据的单位为不可用状态（通常为已阵亡、在战争迷雾里或者在机场），需要从unit_dict中删除
        for u_id in list(self._unit_dict.keys()):
            if u_id not in updated_ids:
                self._unit_dict.pop(u_id)

    def get_all_units(self) -> List[BaseEntity]:
        """
        返回Unit Manager中所有的单位
        """
        return list(self._unit_dict.values())

    def get_by_side(self, side):

        if not isinstance(side, (list, tuple, set)):
            side = {side}

        unit_list = []
        for unit in self._unit_dict.values():
            unit: BaseEntity
            if unit.attribute.side in side:
                unit_list.append(unit)

        return unit_list

    def get_by_id(self, unit_id: Any) -> BaseEntity:
        return self._unit_dict.get(unit_id, None)

    def get_by_type(
            self,
            unit_type: Union[
                UnitType,
                UnitSubType,
                List[Union[UnitType, UnitSubType]],
                Set[Union[UnitType, UnitSubType]],
            ],
            side: Any = None
    ) -> List[BaseEntity]:
        """
        返回特定类型的单位，传入多个类型组成的列表，返回列表中所有类型的单位
        """
        if isinstance(unit_type, (list, set, tuple)):
            unit_type = set(unit_type)
        elif isinstance(unit_type, (UnitType, UnitSubType)):
            unit_type = {unit_type}
        else:
            raise TypeError(f'Unsupported unit type: {type(unit_type)}')

        if side:
            side_unit_list = self.get_by_side(side)
        else:
            side_unit_list = list(self._unit_dict.values())
        unit_list = []
        for unit in side_unit_list:
            unit: BaseEntity
            # TODO: 把符合unit_type的子类型也都找出来
            if unit.attribute.unit_type in unit_type or unit.attribute.unit_subtype in unit_type:
                unit_list.append(unit)
        return unit_list

    def get_by_class(
            self,
            unit_cls: Union[type(BaseEntity), List[type(BaseEntity)]],
            side: Any = None
    ) -> List[BaseEntity]:

        if side:
            side_unit_list = self.get_by_side(side)
        else:
            side_unit_list = list(self._unit_dict.values())

        unit_list = []
        for unit in side_unit_list:
            if isinstance(unit_cls, list):
                if isinstance(unit, tuple(unit_cls)):
                    if unit:
                        unit_list.append(unit)
            else:
                if isinstance(unit, unit_cls):
                    if unit:
                        unit_list.append(unit)

        return unit_list

    def get_by_class_name(
            self,
            unit_cls_name: Union[str, List[str]],
            side: Any = None
    ) -> List[BaseEntity]:
        """
        通过类名字符串获取对应实体
        """
        if side:
            side_unit_list = self.get_by_side(side)
        else:
            side_unit_list = list(self._unit_dict.values())

        unit_list = []
        for unit in side_unit_list:
            if isinstance(unit_cls_name, list):
                if unit.__class__.__name__ in unit_cls_name:
                    if unit:
                        unit_list.append(unit)
            else:
                if unit.__class__.__name__ == unit_cls_name:
                    if unit:
                        unit_list.append(unit)

        return unit_list

    def get_entity_map(self, units, x_min, y_min, x_max, y_max, x_grid_num, y_grid_num):
        entity_map = GridMap(
            x_min, y_min, x_max, y_max, x_grid_num, y_grid_num
        )
        for unit in units:
            entity_map.set_grid_value(unit.position.x, unit.position.y, 1)

        return entity_map

    def reset(self):
        self._unit_dict.clear()

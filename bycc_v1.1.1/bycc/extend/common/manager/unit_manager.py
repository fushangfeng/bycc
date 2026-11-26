from collections import defaultdict
from typing import Any, Dict, Iterable, List, Set, Union

from bycc.common.data_types import RelativeSide
from bycc.common.entity.base_entity import BaseEntity, BaseEntityInfo
from bycc.environment.env_data import ObsData
from bycc.environment.std_io.std_def import UnitSubType, UnitType
from bycc.extend.common.manager.hub import ManagerHub
from bycc.extend.common.manager.manager import Manager


class UnitManager(Manager):
    """
    通过{side: {}}形式存储不同阵营的单位
    在gd项目中，每个unit_manager仅存储一个阵营的单位，但是并未考虑opponent包含多个side的情况

    """

    def __init__(self, player: Any, params: Dict, manager_hub: ManagerHub):
        """单位管理

        Args:
            player:
            params: {}  # 自定义参数
            manager_hub:
        """
        super().__init__(player, params, manager_hub)
        self._side_to_units = defaultdict(dict)
        self.sides = player.sides

    def reset(self):
        for _, units in self._side_to_units.items():
            units.clear()

    def update(self, obs_data: ObsData):
        for side, unit_infos in obs_data.obs.units.items():
            self._update_side_units(unit_infos, self._side_to_units[side])

    def _update_side_units(self, unit_infos: List, cache: Dict):
        """更新一个阵营的实体信息

        更新逻辑
            对已存在的实体，更新数据
            对不存在的实体，构造一个实体
            删除消失的实体

        """
        active_unit_ids = set()
        for unit_info in unit_infos:
            if unit_info.id not in cache:
                cache[unit_info.id] = unit_info.get_entity_cls()(unit_info)
            else:
                cache[unit_info.id].update(unit_info)
            active_unit_ids.add(unit_info.id)
        deactivate_unit_ids = set(cache.keys()) - active_unit_ids
        for unit_id in deactivate_unit_ids:
            del cache[unit_id]

    def add_unit(self, unit: BaseEntity):
        self._side_to_units[unit.side][unit.id] = unit

    def get_all_units(self) -> List[BaseEntity]:
        """
        返回Unit Manager中所有的单位
        """
        units = []
        for side in self._side_to_units:
            units.extend(self._side_to_units[side].values())
        return units

    def get_by_side(self, side: Union[str, int, Iterable]) -> List:
        """ 返回指定阵营的所有单位

        Args:
            side: 阵营信息，自持多阵营输入
        Returns:
            units: 所有单位列表
        """
        if not isinstance(side, Iterable):
            side = [side]

        units = []
        for side_ in side:
            units.extend(self._side_to_units[side_].values())

        return units

    def get_by_id(self, side, unit_id: Any) -> BaseEntity:
        return self._side_to_units[side].get(unit_id)

    def get_by_type(
        self,
        unit_type: Union[
            UnitType,
            UnitSubType,
            List[Union[UnitType, UnitSubType]],
            Set[Union[UnitType, UnitSubType]],
        ],
        side: Any = None,
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
            side_unit_list = self.get_all_units()
        unit_list = []
        for unit in side_unit_list:
            unit: BaseEntity
            # TODO: 把符合unit_type的子类型也都找出来
            if unit.attribute.unit_type in unit_type or unit.attribute.unit_subtype in unit_type:
                unit_list.append(unit)
        return unit_list

    def get_by_class(
        self, unit_cls: Union[type(BaseEntity), List[type(BaseEntity)]], side: Any = None
    ) -> List[BaseEntity]:

        if side:
            side_unit_list = self.get_by_side(side)
        else:
            side_unit_list = self.get_all_units()

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

    def get_interactive_inputs(self):
        """构建特征

        """

        return {}

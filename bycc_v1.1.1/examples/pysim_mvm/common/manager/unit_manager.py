from typing import Any, Dict

from bycc.common.data_types import RelativeSide

from bycc.extend.common.manager.hub import ManagerHub
from bycc.extend.common.manager.unit_manager import UnitManager


class CustomUnitManager(UnitManager):

    def __init__(self, player: Any, params: Dict, manager_hub: ManagerHub):
        super().__init__(player, params, manager_hub)

    def get_interactive_inputs(self):
        """构建特征

        Fixme: 这样构建仅限于开发模式，对配置模式不友好

        """

        raw_obs = {RelativeSide.SELF: {}, RelativeSide.ALLY: {}, RelativeSide.ENEMY: {}}
        for _, unit in self._side_to_units[self.sides[RelativeSide.SELF]].items():
            raw_obs[RelativeSide.SELF][unit.id] = {
                "unit_id": unit.id,
                "name": unit.name,
                "type": unit.type,
                "desc_type": unit.desc_type,
                "position": unit.position,
                "speed": unit.speed,
                "direction": unit.direction,
                "altitude": unit.altitude,
                "weapons": unit.weapons,
                "cur_state": unit.cur_state,
                "base_units": unit.base_units,
                "target": unit.target,
                "health": unit.health,
                "health_percent": unit.health_percent,
                "inbase": unit.inbase,
                "base": unit.base,
            }
        for side in self.sides[RelativeSide.ENEMY]:
            for _, unit in self._side_to_units[side].items():
                raw_obs[RelativeSide.ENEMY][unit.id] = {
                    "unit_id": unit.id,
                    "name": unit.name,
                    "type": unit.type,
                    "desc_type": unit.desc_type,
                    "position": unit.position,
                    "speed": unit.speed,
                    "direction": unit.direction,
                    "altitude": unit.altitude,
                }
        return raw_obs

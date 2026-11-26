from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward

if TYPE_CHECKING:
    from bycc.common.info import InfoManager


DECLARATION = {
    "name": "敌方即时奖励",      # 组件名称，用于前端显示和后台索引
    "class": "EnemyImmediateLoss",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
    },
    "description": "some text"    # 组件描述，用于前端显示
}


class EnemyImmediateLoss(Reward):

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self._last_value = None

    def process(self, info_manager: InfoManager, done):
        entities = []
        for side in info_manager.enemy_sides:
            entities.extend(info_manager.unit_manager.get_by_class(
                    self._entity_map[self._entity],
                    side
                )
            )
        value = sum([getattr(entity, self._feature) for entity in entities])
        if self._last_value is not None:
            diff = self._last_value - value
            self._last_value = value
            return diff
        else:
            self._last_value = value
            return 0

    def reset(self):
        self._last_value = None

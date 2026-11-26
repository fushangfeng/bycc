from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "我方即时攻击蓝方目标单步奖励",      # 组件名称，用于前端显示和后台索引
    "class": "SelfImmediateAttackReward",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
    },
    "description": "some text"    # 组件描述，用于前端显示
}


class SelfImmediateAttackReward(Reward):
    """
    1. 计算前后两帧，红方攻击掉多少蓝方目标，目前主要是飞机  F35  EA 18G
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self._last_value = None

    def process(self, info_manager: InfoManager, done):

        entities = info_manager.unit_manager.get_by_class(
            self._entity_map[self._entity],
            info_manager.self_side
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

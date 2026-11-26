from __future__ import annotations

import datetime
from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "我方被保护单位存活奖励",      # 组件名称，用于前端显示和后台索引
    "class": "ProtectReward",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
    },
    "description": "我方被保护单位存活奖励"    # 组件描述，用于前端显示
}


class ProtectReward(Reward):
    """
    我方保护单位存活数量
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]

    def process(self, info_manager: InfoManager, done):

        if done:
            protect_area = info_manager.raw_obs.extra_info_dict["states_dict"][1]["protect_area"]
            return len(protect_area)

        return 0

    def reset(self):
        pass

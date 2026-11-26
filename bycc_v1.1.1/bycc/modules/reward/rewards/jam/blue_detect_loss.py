from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "我方保护地被TC损失",      # 组件名称，用于前端显示和后台索引
    "class": "ProtectDetectedLoss",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
    },
    "description": "我方保护地被TC损失"    # 组件描述，用于前端显示
}


class ProtectDetectedLoss(Reward):
    """
    GR裁决结果中我方GR装备GR敌方飞机有效的数量
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self._all_value = 0

    def process(self, info_manager: InfoManager, done):
        protect_list = [10, 11, 12]
        detected_protect_ids = []

        blue_detect_infos = info_manager.raw_obs.extra_info_dict["states_dict"][2]["radar_detect_infos"]
        for b_id, b_info in blue_detect_infos.items():
            detect_infos = blue_detect_infos[b_id]["RadarDetectPlat"]
            for d_info in detect_infos:
                if d_info["PlatID"] in protect_list:
                    detected_protect_ids.append(d_info["PlatID"])

        return -0.2 * len(detected_protect_ids)

    def reset(self):
        self._all_value = 0

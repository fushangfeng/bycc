from __future__ import annotations

import datetime
from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "我方雷达GR敌方飞机奖励",      # 组件名称，用于前端显示和后台索引
    "class": "JamTrgReward",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
    },
    "description": "我方雷达GR敌方飞机奖励"    # 组件描述，用于前端显示
}


class JamTrgReward(Reward):
    """
    GR裁决结果中我方GR装备GR敌方飞机有效的数量
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self._all_value = 0

    def process(self, info_manager: InfoManager, done):
        jam_value = 0

        jam_tar = []
        judge_data = info_manager.raw_obs.extra_info_dict["states_dict"]["judgement_data"]
        for juda in judge_data["rjamJudge"]:
            if juda.get("bJam", False):
                if juda["RadarID"] not in jam_tar:
                    jam_value += 0.01
                    jam_tar.append(juda["RadarID"])
                # else:
                #     jam_value -= 0.02

        self._all_value += jam_value
        if done:
            print(f"reward: {self._all_value} {datetime.datetime.now()}")

        return jam_value

    def reset(self):
        self._all_value = 0

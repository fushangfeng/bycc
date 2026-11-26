from __future__ import annotations

import datetime
from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "我方雷达GR敌方飞机奖励1",      # 组件名称，用于前端显示和后台索引
    "class": "JamTrgReward1",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
    },
    "description": "我方雷达GR敌方飞机奖励1"    # 组件描述，用于前端显示
}


class JamTrgReward1(Reward):
    """
    GR裁决结果中我方GR装备GR敌方飞机有效的数量
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]

        # 历史GR到的目标数量
        self.last_jam_num = 0

    def process(self, info_manager: InfoManager, done):
        # 只关注GR成功的数量
        jam_num = 0
        jam_reward = 0
        jam_list = []

        judge_data = info_manager.raw_obs.extra_info_dict["states_dict"]["judgement_data"]

        # print("当前开始计算GR奖励值-------", judge_data)
        for juda in judge_data["rjamJudge"]:
            if juda.get("bJam", True):
                if juda["RadarID"] not in jam_list:
                    jam_list.append(juda["RadarID"])
                    # 成功GR了一个新的蓝方飞机
                    jam_num += 1
            else:
                # GR了，但是没有成功，不进行处理
                pass

        if jam_num - self.last_jam_num > 0:
            jam_reward = jam_num - self.last_jam_num

        else:
            jam_reward = 0

        # 更新统计值
        self.last_jam_num = jam_num

        return jam_reward

    def reset(self):
        self.last_jam_num = 0

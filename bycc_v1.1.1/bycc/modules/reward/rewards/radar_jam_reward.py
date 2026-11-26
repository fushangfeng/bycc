from __future__ import annotations

import datetime
from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "我方雷达GR敌方飞机局部奖励",      # 组件名称，用于前端显示和后台索引
    "class": "RadarJamReward",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
    },
    "description": "我方雷达GR敌方飞机局部奖励"    # 组件描述，用于前端显示
}


class RadarJamReward(Reward):
    """
    1. GR裁决结果中我方GR装备GR敌方飞机有效的数量
    2. 敌方TC我方法保护单位
    3. 我方保护单位存活数量
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self._last_value = None
        self._all_value = 0
        self._protect_unit_live = 3
        self._jam_history = []

    def process(self, info_manager: InfoManager, done):
        # return 0
        protect_value = 0
        jam_value = 0

        # 保护我方(我方保护单位存活情况) 死一个-10
        protect_area = info_manager.raw_obs.extra_info_dict["states_dict"][1]["protect_area"]
        protect_list = [pro_id for pro_id in protect_area]
        pul = len(protect_area)
        if pul < self._protect_unit_live:
            protect_value += 10 * (pul - self._protect_unit_live)
            self._protect_unit_live = pul

        # # GR敌方 1.裁决信息中我方GR敌方情况 2.敌方雷达TC我方保护目标情况
        # jam_tar = []
        # judge_data = info_manager.raw_obs.extra_info_dict["states_dict"]["judgement_data"]
        # for juda in judge_data["rjamJudge"]:
        #     if juda.get("bJam", False):
        #         if juda["RadarID"] not in jam_tar:
        #             jam_value += 0.01
        #             jam_tar.append(juda["RadarID"])
        #     # else:
        #     #     jam_value -= 0.01

        # # 保护目标被TC到 -1
        # brdi = []
        # blue_detect_infos = info_manager.raw_obs.extra_info_dict["states_dict"][2]["radar_detect_infos"]
        # for de_id in blue_detect_infos:
        #     rdps = blue_detect_infos[de_id]["RadarDetectPlat"]
        #     for rdp in rdps:
        #         if rdp["PlatID"] not in brdi and rdp["PlatID"] in protect_list:
        #             brdi.append(rdp["PlatID"])
        # detect_value = -1 * len(brdi)

        # self._last_value = protect_value + jam_value + detect_value
        self._last_value = protect_value + jam_value
        self._all_value = self._all_value + self._last_value
        # print(f"------------------------------------")
        # print(f"now protect_value is {protect_value}")
        # print(f"now jam_value is {jam_value}")
        # print(f"now detect_value is {detect_value}")
        # print(f"now _last_value is {self._last_value}")
        # print(f"now _all_value is {self._all_value}")
        if done:
            print(f"reward: {self._all_value} {datetime.datetime.now()}")
            # if self._all_value < 0:
            #     print("1q113weas")
        return self._last_value

    def reset(self):
        self._last_value = None
        self._protect_unit_live = 3
        self._all_value = 0

from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "预警雷达TC奖励",      # 组件名称，用于前端显示和后台索引
    "class": "RadarDetectReward",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息

    },
    "description": "some text"    # 组件描述，用于前端显示
}


class RadarDetectReward(Reward):
    """
    预警雷达对敌方单位TC奖励
    前一stepTC到敌方单位,且当前step也TC到敌方单位才计算奖励
    如果前一step没有TC到敌方单位,当前stepTC到,不给奖励,避免重复开关机以获取更高奖励
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self._last_detected_id_list = []

    def process(self, info_manager: InfoManager, done):
        # FIXME: 为了保证通用性,原则上在组件里不应该读取raw_obs,需要用到的态势信息应该都添加到std_obs中,此处为了跑通,暂且先使用raw_obs
        radars = info_manager.unit_manager.get_by_class(
            self._entity_map[self._entity],
            info_manager.self_side
        )
        raw_red_units_obs = info_manager.raw_obs.extra_info_dict['states_dict']['raw_obs']['merged_units_data'][1]  # TODO: 态势数据有点乱,建议再整理整理
        detected_platforms = []
        for radar in radars:
            for red_unit_obs_dict in raw_red_units_obs:
                if red_unit_obs_dict['PlatID'] == radar.id:
                    for radar_info in red_unit_obs_dict['radars']:
                        if 'radar_detect_info' in radar_info:
                            detected_platforms.extend([detected_plat['PlatID'] for detected_plat in radar_info['radar_detect_info']['RadarDetectPlat']])

        value = 0
        for plat_id in detected_platforms:
            if plat_id in self._last_detected_id_list:
                value += 1
        self._last_detected_id_list = detected_platforms

        return value

    def reset(self):
        self._last_detected_id_list = []

from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "我方单位最终剩余奖励",      # 组件名称，用于前端显示和后台索引
    "class": "SelfFinalLeftReward",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        # "unit_id_list": {         # 参数名称，python代码中传入的实际参数名
        #     "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
        #     "type": "list",       # 参数类型
        #     "relate": "subject"  # 关联项，"subject"/"object"/"parameter"
        # },
        # "open_flag": {                      # 参数名称，python代码中传入的实际参数名
        #     "display_name": "开/关机",  # 参数显示名，用于前端显示
        #
        #     "type": "list",    # 参数类型
        #     "relate": "parameter"  # 关联项，"subject"/"object"/"parameter"    分别是：主语  宾语  参数
        # }
    },
    "description": "some text"    # 组件描述，用于前端显示
}


class SelfFinalLeftReward(Reward):
    """
    计算我方推演结束时的指定单位剩余数量，用于计算最终奖励
    """
    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]

    def process(self, info_manager: InfoManager, done):
        """
        考虑被击毁了几个预警雷达
        :param info_manager:
        :param done:
        :return:
        """
        if done:
            entities = info_manager.unit_manager.get_by_class(
                self._entity_map[self._entity],
                info_manager.self_side
            )
            return len(entities)
        else:
            return 0

    def reset(self):
        pass

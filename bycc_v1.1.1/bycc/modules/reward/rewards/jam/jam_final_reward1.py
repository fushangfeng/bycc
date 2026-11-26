from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "场景一GR单局终局奖励1",      # 组件名称，用于前端显示和后台索引
    "class": "EpisodeFinalReward2",  # 组件类名
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


class EpisodeFinalReward2(Reward):
    """
    终局奖励，赢了奖励，输了惩罚
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self.final_reward = 0

    def process(self, info_manager: InfoManager, done):
        """
        考虑被击毁了几个保护地
        :param info_manager:
        :param done:
        :return:
        """
        entities = info_manager.unit_manager.get_by_class(
            self._entity_map[self._entity],
            info_manager.self_side
        )

        # print("当前的单位信息是----------", entities, done)
        # print("当前的单位信息是----111------", [getattr(entity, self._feature) for entity in entities])

        # 当前红方有4个保护地
        if done is True:
            if len(entities) == 3:
                # print("当前单局结束了，3个保护地都还在，红方胜利")
                self.final_reward = 1
            else:
                # print("当前单局结束了，红方失败")
                self.final_reward = -1

        return self.final_reward

    def reset(self):
        self.final_reward = 0

from __future__ import annotations

from typing import TYPE_CHECKING
from bycc.modules.interface import Reward


if TYPE_CHECKING:
    from bycc.common.info import InfoManager

DECLARATION = {
    "name": "我方即时单步保护地被击毁损失",      # 组件名称，用于前端显示和后台索引
    "class": "SelfImmediateLoss1",  # 组件类名
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


class SelfImmediateLoss1(Reward):
    """
    1. 计算前后帧，目前有几个预警雷达被打死了，虽然目前只有一个
    2. 这边计算只是返回两帧之间的差值，权重的值是在前端配置的
    不过预警雷达被击毁的话，态势里面就没有这个单位了，哪里还来的特征字段信息呢
    """

    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self._last_value = None
        self.last_entities_num = 3  # 目前红方有三个保护地

    def process(self, info_manager: InfoManager, done):
        """
        考虑被击毁了几个预警雷达
        :param info_manager:
        :param done:
        :return:
        """
        entities = info_manager.unit_manager.get_by_class(
            self._entity_map[self._entity],
            info_manager.self_side
        )

        # print("当前的单位信息是----------", entities)
        # print("当前的单位信息是----111------", [getattr(entity, self._feature) for entity in entities])
        destoried_num = self.last_entities_num - len(entities)

        self.last_entities_num = len(entities)
        return destoried_num

    def reset(self):
        self._last_value = None
        self.last_entities_num = 3  # 当前场景一有三个保护地

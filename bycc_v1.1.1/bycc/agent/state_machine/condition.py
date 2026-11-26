from __future__ import annotations

import uuid
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from bycc.agent.state_machine.base import Event, State
    from bycc.agent.cache_state import CacheState


class Condition(object):
    """条件基类
    用于构造状态机条件，返回true时执行条件对应事件所包含的行动
    """

    def __init__(self, name: str):
        self.name = name
        self.id = uuid.uuid3(uuid.NAMESPACE_DNS, self.__class__.__name__)
        self.description = ""

    def step(self, state: State, event: Event) -> bool:
        """"""

    def get_id(self):
        """生成一个「state->event->action」的唯一id，作为状态缓存的key"""

from __future__ import annotations

import abc
from typing import TYPE_CHECKING, Dict, Union, Any
from bycc.extend.consts import MissionStatus

if TYPE_CHECKING:
    from bycc.extend.specs import MissionParameterSpec
    from bycc.extend.common.manager.hub import ManagerHub


class Mission(abc.ABC):
    """任务基类
    --------------------

    anything the agent outputs is treated as mission

    """

    def __init__(
        self,
        mission_parameter: MissionParameterSpec,
        manager_hub: ManagerHub,
        **kwargs,
    ):
        self.id = mission_parameter.id
        self.manager_hub = manager_hub
        self.start_time = manager_hub.relative_time  # 任务开始时间
        self.status = MissionStatus.Created
        self.type = mission_parameter.type
        self.params = mission_parameter.params
        self.group = None  # dev
        self.priority = None  # dev

    @abc.abstractmethod
    def build(self):
        """状态跳转，mission初始化"""
        raise NotImplementedError

    @abc.abstractmethod
    def step(self, *args, **kwargs):
        raise NotImplementedError

    def set_mission_status(self, status: MissionStatus):
        self.status = status

    @classmethod
    def is_ready(cls, manager_hub: ManagerHub) -> bool:
        """
        判断当前step此mission是否处于可执行状态，如此step不可执行，则会mask掉次mission
        注意此方法为类方法，子类复写此方法时需加上@classmethod装饰器！
        Args:
            manager_hub: 信息传递模块
        Returns:
            True/False
        """
        return True

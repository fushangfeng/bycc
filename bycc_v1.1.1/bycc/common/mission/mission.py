from __future__ import annotations

import abc
import enum
from dataclasses import dataclass
from typing import TYPE_CHECKING, Dict, Union, Any
from bycc.utils.logger.logger import Logger


if TYPE_CHECKING:
    from bycc.common.info import InfoManager, MissionManager


@dataclass
class MissionParameter:
    """任务参数， make feng ge happy
    --------------------

    所有智能体生成的指令，都会被视为mission参数，实例化mission后通过step执行生成command

    """

    mission_type: str | enum.Enum
    mission_params: Dict[str:Any]


@dataclass
class CommandParameter:
    """命令参数
    --------------------

    和环境直接交互的指令

    """

    type: str
    params: Dict[str:Any]


class MissionStatus(enum.IntEnum):
    """mission基础状态管理"""

    Invalid = 0  # 无效
    Created = 1  # 已创建，检查通过、初始化单位完成
    Waiting = 2  # 等待中，表示当前无法执行，通常用于等待战场资源，直到mission超时/模拟结束
    Ready = 3  # 可执行
    Running = 4  # 执行中，参考mission执行类型
    Token1 = 5  # 备用状态
    Paused = 6  # 暂停，备用状态
    Exited = 7  # 终止，执行完成/不可再执行，step不再触发标记为停止状态的mission


class Mission(abc.ABC):
    """任务基类
    --------------------

    every thing to environment is mission

    """

    def __init__(
        self,
        mission_id: Union[int, str],
        mission_parameter: MissionParameter,
        info_manager: InfoManager,
        mission_manager: MissionManager,
        logger=None,
        **kwargs,
    ):
        self.id = mission_id
        self.info_manager = info_manager
        self.mission_manager = mission_manager
        self.start_time = info_manager.sim_time  # 任务开始时间
        self.status = MissionStatus.Created
        self.type = mission_parameter.mission_type
        self.params = mission_parameter.mission_params
        self.group = None  # dev
        self.priority = None  # dev
        self.logger = logger

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
    def is_ready(cls, info_manager: InfoManager) -> bool:
        """
        判断当前step此mission是否处于可执行状态，如此step不可执行，则会mask掉次mission
        注意此方法为类方法，子类复写此方法时需加上@classmethod装饰器！
        Args:
            info_manager: 当前step的仿真态势信息
        Returns:
            True/False
        """
        return True

    def set_logger(self, logger: Logger):
        self._logger = logger

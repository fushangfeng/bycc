from __future__ import annotations

import enum
from typing import TYPE_CHECKING, Dict, List, Union

if TYPE_CHECKING:
    from pysim.core.side import Side


class MissionStatus(enum.IntEnum):
    """
    mission常用状态管理
    """

    Invalid = 0  # 无效

    Created = 1  # 已创建，检查通过、初始化单位完成
    Waiting = 2  # 等待中，表示当前无法执行，通常用于等待战场资源，直到mission超时/模拟结束
    Ready = 3  # 可执行
    Running = 4  # 执行中，参考mission执行类型

    Token1 = 5  # 占位，避免模型训练时无法直接onehot

    Paused = 6  # 暂停，备用状态
    Exited = 7  # 终止，执行完成/不可再执行，step不再触发标记为停止状态的mission


class Mission(object):
    """
    内部mission基类，通过side和环境交互，初始状态为 MissionStatus.created，结束状态为MissionStatus.exited
    """

    def __init__(self, mission_id: Union[int, str], side_data: Side, mission_dict: Dict):
        self._mission_id = mission_id
        self._side_data = side_data
        self._mission_type = mission_dict["type"]
        self._status = MissionStatus.Created
        self._mission_type = -1
        self._unit_ids = set()

    def step(self, tick_time: float):
        """
        mission的对外接口，单位通过调用mission.step实现状态的更新
        Args:
            tick_time: 模拟时间
        Returns:
            cmds: 决策指令
        """
        raise NotImplementedError

    def add_units(self, unit_ids: List):
        self._unit_ids.update(unit_ids)

    def remove_units(self, unit_ids: List):
        self._unit_ids.difference_update(unit_ids)

    def is_done(self):
        """判定mission终止，status跳转MissionStatus.exited"""
        return False

    @property
    def mission_id(self):
        return self._mission_id

    @property
    def mission_type(self):
        return self._mission_type

    @property
    def status(self):
        return self._status

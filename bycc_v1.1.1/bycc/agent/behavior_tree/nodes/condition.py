from abc import abstractmethod
from typing import Any, Dict


class Condition:

    def __init__(self, logger=None):
        self._logger = logger

    @abstractmethod
    def judge(self, obs: Any, blackboard: Dict, msg=None) -> bool:
        """

        Args:
            obs: 仿真态势信息
            blackboard: 行为树黑板字典，用于在节点之间传递信息
                应注意blackboard字典在行为树每个step都会清空，如需在一个episode周期内维护变量，要在BTAction子类中自行维护
            msg: 组合智能体中由上层智能体传递过来的信息
        Returns:
            条件结果（True/False）
        """
        raise NotImplementedError

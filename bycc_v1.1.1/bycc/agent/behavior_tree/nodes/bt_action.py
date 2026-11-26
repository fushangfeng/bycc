from abc import ABC, abstractmethod
from typing import Any, Tuple, List, Dict
from bycc.agent.config_def import BehaviorTreeNodeResult


class BTAction(ABC):
    """
    行为树行动节点中的行动执行逻辑
    """

    def __init__(self, logger=None):
        self._logger = logger

    @abstractmethod
    def step(self, obs: Any, blackboard: Dict, msg=None) -> Tuple[List, BehaviorTreeNodeResult, Dict]:
        """
        Args:
            obs: 仿真态势信息
            blackboard: 行为树黑板字典，用于在节点之间传递信息
                应注意blackboard字典在行为树每个step都会清空，如需在一个episode周期内维护变量，要在BTAction子类中自行维护
            msg: 组合智能体中由上层智能体传递过来的信息

        Returns:
            节点指令列表，行为树执行状态（成功、失败、运行中），分层信息输出
        """
        raise NotImplementedError

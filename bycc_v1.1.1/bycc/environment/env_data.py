import numpy as np
from typing import Any, Dict
from dataclasses import dataclass, field


@dataclass
class ObsData:
    """
    仿真环境对接输出的数据结构，一般情况下，obs可为任意类型；
    在需要输出标准态势时, obs为StdInfo类型
    """
    obs: Any
    episode_done: bool
    extra_info_dict: Dict[str, Any] = field(default_factory=dict)
    agent_name: str = ""


@dataclass
class ActionData:
    action: Dict[str, np.ndarray]    # action_head name to action
    predict_output: Dict[str, np.ndarray]
    action_mask: Dict[str, np.ndarray] = field(default_factory=dict)    # action_head name to mask
    agent_name: str = ""

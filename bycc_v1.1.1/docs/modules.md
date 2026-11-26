# 业务组件

## 组件接口说明

### 学习型智能体决策任务组件接口

* 决策任务组件用于学习型智能体的谓语动作，智能体决策时，从一组谓语动作中选择一个对应的决策任务并执行
* 决策任务是无状态的，智能体的每个step都会重新实例化决策任务对象
```
# 接口路径：bycc/common/mission/mission.py

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

```

### 奖励函数接口

```
# 接口路径：bycc/agent/auto_agent_player/reward.py

from abc import abstractmethod

class Reward:

    def __init__(self, **kwargs):
        """
        接收奖励配置参数
        """
        raise NotImplementedError

    @abstractmethod
    def process(self, info_manager, done):
        """
        每步更新奖励信息
        如果是即时奖励，则每步返回reward值；
        如果是最终奖励，则done=True时返回reward值，其余step返回0
        return：reward
        """
        raise NotImplementedError

    @abstractmethod
    def reset(self):
        """
        重置奖励函数
        """
        raise NotImplementedError
```


### 统计信息接口

```
# 接口路径：bycc/agent/auto_agent_player/statistic.py

from abc import abstractmethod

class Statistic:

    def __init__(self, **kwargs):
        """
        接收统计配置参数
        """
        raise NotImplementedError

    @abstractmethod
    def update(self, info_manager):
        """
        每步更新统计信息
        """
        raise NotImplementedError

    def summary(self):
        """
        输出统计值（单个值）
        """
        raise NotImplementedError

    def reset(self):
        raise NotImplementedError
```

### 评估指标接口

```
# 接口路径：bycc/ai/evaluation/indicator.py

from typing import Any, Dict
from abc import ABC, abstractmethod

class Indicator(ABC):

    @abstractmethod
    def evaluate(self):
        """
        生成评估结果，一般在一局done的时候调用此方法
        Returns:
            eval result: Dict
        """
        raise NotImplementedError

    @abstractmethod
    def update(self, obs: Dict, cmds: Any):
        """
        更新指标信息
        Args:
            obs: 仿真态势字典，为全局态势，包括各个阵营（player）的态势信息
            cmds: 待评估智能体指令
        Returns:
            无
        """
        raise NotImplementedError
```

### 行为树行动节点接口
* 行为树行动节点是有状态的，在每一局开始时实例化，用户可在类中维护所需的历史变量

```
# 接口路径：bycc/agent/behavior_tree/nodes/bt_action.py

from abc import ABC, abstractmethod
from typing import Any, Tuple, List, Dict
from bycc.ai.player.auto_player.config_def import BehaviorTreeNodeResult

class BTAction(ABC):
    """
    行为树行动节点中的行动执行逻辑
    """
    @abstractmethod
    def step(self, obs: Any, blackboard: Dict) -> Tuple[List, BehaviorTreeNodeResult]:
        """
        Args:
            obs: 仿真态势信息
            blackboard: 行为树黑板字典，用于在节点之间传递信息
                应注意blackboard字典在行为树每个step都会清空，如需在一个episode周期内维护变量，要在BTAction子类中自行维护
        Returns:
            节点指令列表，行为树执行状态（成功、失败、运行中）
        """
        raise NotImplementedError
```

### 行为树条件节点接口

```
# 接口路径：bycc/agent/behavior_tree/nodes/condition.py

from abc import abstractmethod
from typing import Any, Dict

class Condition:

    @abstractmethod
    def judge(self, obs: Any, blackboard: Dict) -> bool:
        """
        Args:
            obs: 仿真态势信息
            blackboard: 行为树黑板字典，用于在节点之间传递信息
                应注意blackboard字典在行为树每个step都会清空，如需在一个episode周期内维护变量，要在BTAction子类中自行维护
        Returns:
            条件结果（True/False）
        """
        raise NotImplementedError
```
### 行动节点装饰器接口
```
# 接口路径：bycc/agent/behavior_tree/nodes/bt_decorator.py

from abc import ABC, abstractmethod
from typing import Any, Dict

class BTDecorator(ABC):
    """
    行为树行动节点的装饰类，对行动节点的obs进行预处理，再传入行动任务中
    """
    @abstractmethod
    def process(self, obs: Any, blackboard: Dict):
        """
        Args:
            obs: 仿真态势信息，obs传入前会进行deepcopy，原地修改obs不会对其他节点obs造成影响
            blackboard: 行为树黑板字典，用于在节点之间传递信息
                应注意blackboard字典在行为树每个step都会清空，如需在一个episode周期内维护变量，要在BTAction子类中自行维护

        Returns:
            预处理后的obs
        """
        raise NotImplementedError
```


## 组件注册及使用
用户可通过注册器将开发好的业务组件注册，便于在代码中使用。注册器主要有两种使用方式：
* 方式一  
将组件代码存放在bycc/modules对应目录下，使用相应组件注册器的装饰器装饰组件类，如：
```
from bycc.modules.interface import Reward
from bycc.modules.reward import REWARDS

@REWARDS.register_decorator("my_reward")  # 其中"my_reward"参数为组件注册名称，如果不传参数，则默认使用类名为注册名称（本例中为"MyReward"）
class MyReward(Reward):

    def __init__(self, **kwargs):
        pass

    def process(self, info_manager: InfoManager, done, mission_manager):
        pass

    def reset(self):
        pass
```
* 方式二  
在用户代码中自行维护组件类，并动态注册组件
```
from bycc.modules import BT_ACTIONS, BT_CONDITIONS
from my_codes import MyCondition

BT_CONDITIONS.register_module("my_condition", MyCondition)
```

用户将组件注册好后，可按如下方式获取组件类：
```
action = BT_ACTIONS.modules["my_action"]  # "my_action"为组件注册名称
```

## 组件声明
如果业务组件通过“智能体生产线”平台维护，则需要在组件代码文件中加入组件声明内容，以便平台自动识别组件参数等信息。
### 声明内容格式
```
DECLARATION = {
    "name": "空对空打击任务",      # 组件名称，用于前端显示和后台索引
    "class": "A2AAttackMission",  # 组件类名
    "params": {                   # 组件参数，用于前端显示参数信息
        "unid_id_list": {         # 参数名称，python代码中传入的实际参数名
            "display_name": "任务执行主体ID列表",   # 参数显示名，用于前端显示
            "type": "list",        #  参数类型
            "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        },
        "target_id_list": {
            "display_name": "目标单位ID列表",
            "type": "list",
            "relate": "object"
        },
        "weapon_type": {
            "display_name": "武器类型",
            "type": "enum",
            "members": ["gun", "missile", "grenade"],  # 枚举值可选元素
            "default": "gun"  # 默认值，如无此字段，则不提供默认值，未提供默认值的为必填项
            "relate": "parameter"
        }
    },
    "description": "some text"    # 组件描述，用于前端显示
}
```
* 声明参数类型  

|  序号  |  类型   |      值      |  备注   |  
|:----:|:-----:|:-----------:|:-----:|
|  1   |  字符   |    "str"    |       |  
|  2   |  整型   |    "int"    |       |
|  3   |  浮点   |   "float"   |       |
|  4   |  布尔   |   "bool"    |       |
|  5   |  枚举   |   "enum"    |       |
|  6   |  列表   |   "list"    |       |
|  7   |  字典   |   "dict"    |       |
|  8   | 字典列表  | "dict_list" |       |
|  9   | 实体类  | "entity" |       |
|  8   | 实体特征  | "feature" |       |


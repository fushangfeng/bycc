# 业务组件

## 样例（Atari环境）

### 学习型智能体决策任务样例

```
from bycc.common.mission import Mission
from bycc.common.mission import MissionStatus

"""
DECLARATION用于声明决策任务的中文名、类名、参数列表，用于组件加载时读取
name:定义了组件在前端显示时的名字
class:指定了处理当前决策任务运行时处理结果、将参数转换为指令的类
params:定义了决策任务所接受的参数的信息，每个参数需要分别定义display_name、type和relate三个参数
    display_name:任务参数的前端显示名
    type:决策任务转换成指令时接收的任务参数的类型
    relate:参数类型，对应决策任务中的主语(subject)、宾语(object)、谓语(predicate)和参数(parameter)
           通常主语、宾语两类参数需要接收单选/多选解码器的输出，谓语接收分类解码器输出，参数接收分类或连续值输出解码器输出
description:描述决策任务的功能
"""
DECLARATION = {
    "name": "Atari攻击移动",  # 组件名称，用于前端显示和后台索引
    "class": "AtariMoveAndAttack",  # 组件类名
    "params": {  # 组件参数，用于前端显示参数信息
        # "self_unit_index_list": {  # 参数名称，python代码中传入的实际参数名
        #     "display_name": "任务执行主体ID列表",  # 参数显示名，用于前端显示
        #     "type": "list",  # 参数类型
        #     "relate": "subject"  # 关联项，"subject"/"object"/"predicate"/"parameter"
        # },
        "action_param": {"display_name": "参数", "type": "int", "relate": "parameter"}
    },
    "description": "控制单位列表中的所有单位攻击目标敌方单位"  # 组件描述，用于前端显示
}

"""
决策任务实现代码，类名必须和DECLARATION中一致，至少需要完成对__init__、step和build函数的重载
"""
class AtariMoveAndAttack(Mission):
    def __init__(self, mission_id, mission_parameter, info_manager, mission_manager):
        """
        决策任务初始化代码，读取任务参数的实际结果值，存储
        @param mission_id: 用于唯一标识任务实体，会自动生成，业务代码不处理
        @param mission_parameter: 用于传递参数结果
        @param info_manager: 用于读取当前态势信息
        @param mission_manager: 用于管理决策任务，业务代码不处理
        @return:
        """
        super().__init__(mission_id, mission_parameter, info_manager, mission_manager)
        # 读取模型输出的任务参数结果，与DECLARATION的params对应
        self.action_param = self.params["action_param"]

    def step(self):
        # 将任务参数转换为仿真可接受的指令形式，结果cmds是指令列表
        cmds = [int(self.action_param)]
        # 决策任务需要step完毕后将任务状态设置为Exited，无状态
        self.set_mission_status(MissionStatus.Exited)
        return cmds

    def build(self):
        self.set_mission_status(MissionStatus.Ready)
        return self.status
```

### 奖励函数样例

```
from __future__ import annotations
from typing import TYPE_CHECKING
from bycc.modules.interface import Reward
import numpy as np

if TYPE_CHECKING:
    from bycc.common.info import InfoManager

"""
DECLARATION用于声明奖励函数的中文名、类名、参数列表，用于组件加载时读取
name:定义了组件在前端显示时的名字
class:指定了处理当前奖励函数计算奖励值的类
params:定义了计算奖励函数时需要的参数，通常情况下奖励可以从态势中直接计算，不用额外参数
description:描述奖励函数的功能
"""
DECLARATION = {
    "name": "Atari Sign奖励",  # 组件名称，用于前端显示和后台索引
    "class": "AtariSignReward",  # 组件类名
    "params": {},  # 组件参数，用于前端显示参数信息
    "description": "Atari Sign奖励"  # 组件描述，用于前端显示
}


class AtariSignReward(Reward):
    def __init__(self, **kwargs):
        self._entity = kwargs["entity"]
        self._feature = kwargs["feature"]
        self._entity_map = kwargs["entity_map"]
        self._last_value = None

    def process(self, info_manager: InfoManager, done, mission_manager=None):
        return np.sign(info_manager.raw_obs.extra_info_dict.get('reward', 0))

    def reset(self):
        self._last_value = None

```

### 统计信息样例

```

```


### 评估指标样例

```

```

### 行为树行动节点样例

```

```


### 行为树条件节点样例

```

```


### 行动节点装饰器样例

```

```

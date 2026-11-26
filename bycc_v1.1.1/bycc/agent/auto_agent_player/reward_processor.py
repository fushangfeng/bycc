import json
from typing import List
from copy import deepcopy
from bycc.modules import REWARDS
from bycc.constant import REWARD_FUNCTION_MODULE_DIR
from bycc.utils.utils import get_module_and_register
from bycc_config.config_models.player_configs.scenario_adaption_config import RewardConfig


class RewardProcessor:

    def __init__(self, name, side, reward_config: List[RewardConfig], class_map, reward_cls_map=None):
        self._name = name
        self._side = side
        self._reward_config = reward_config
        self._class_map = class_map
        self._reward_cls_map = reward_cls_map
        self._reward_instance_dict = {}
        self._episode_reward = 0
        self._reward_summary = {}
        self._reward_weight = {}
        self._init()

    def _init(self):
        if self._reward_config is not None:
            for reward_item in self._reward_config:
                reward_display_name = reward_item.parameters_template["instance_name"]
                reward_module = get_module_and_register(
                    self._reward_cls_map,
                    REWARDS,
                    reward_item.name,
                    reward_item
                )

                self._reward_weight[reward_display_name] = reward_item.parameters_template["weight"]

                params = reward_item.parameters_template.get('params', {})
                self._reward_instance_dict[reward_display_name] = reward_module(
                    params=params,
                    feature=params.get('feature'),  # FIXME: entity和feature已全移入params中，此处为兼容老版组件代码，临时处理
                    entity=params.get('entity'),
                    entity_map=self._class_map
                )

    def process(self, info_manager, god_info_manager, done, mission_manager):

        step_reward = 0
        env_done_requested = False

        for reward_display_name, reward_module in self._reward_instance_dict.items():
            reward_result = reward_module.process(god_info_manager, done, mission_manager)

            if isinstance(reward_result, tuple) and len(reward_result) == 2:
                reward, env_done = reward_result
                if env_done:
                    env_done_requested = True
            else:
                reward = reward_result
            
            reward = reward * self._reward_weight[reward_display_name]
            if f"reward_{reward_display_name}_{self._side}_{self._name}" in self._reward_summary:
                self._reward_summary[f"reward_{reward_display_name}_{self._side}_{self._name}"] += reward
            else:
                self._reward_summary[f"reward_{reward_display_name}_{self._side}_{self._name}"] = reward
            self._episode_reward += reward
            step_reward += reward

        if done:
            self._reward_summary[f"episode_reward_{self._name}"] = self._episode_reward
            return step_reward, self._reward_summary, env_done_requested

        else:
            return step_reward, {}, env_done_requested

    def reset(self):
        for reward_module in self._reward_instance_dict.values():
            reward_module.reset()

        self._episode_reward = 0
        self._reward_summary = {}

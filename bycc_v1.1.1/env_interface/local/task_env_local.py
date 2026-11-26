"""
本地运行行为节点
"""
import time
from bycc.common.info import InfoManager
from bycc.modules.bt_action.bt_actions.void_action import VoidAction
from bycc_config.bycc_config_parser import bycc_config_parser
from bycc_config.env_interface_config import scenario_to_env_config
from env_interface.env.ewx_env import EWXEnv
from env_interface.env_config import env_config
from env_interface.obs_translator import EWXObsTranslator


class TaskEnvLocal(EWXEnv):
    def __init__(self, env_id, config, extra_info):
        super(TaskEnvLocal, self).__init__(env_id, config, extra_info)

class TaskRunner:
    def __init__(self, env_params, player_dict):
        self._env = TaskEnvLocal(**env_params)
        self._obs_translator = EWXObsTranslator()
        self._play_dict = player_dict
        self._info_manager = {}
        self._init()
        self.blackboard = {}
        self.msg = None

    def _init(self):
        raw_obs = self._env.reset()
        std_obs = self._obs_translator.translate(raw_obs)
        for agent_side, agent_info in self._play_dict.items():
            side_relation = self._build_side_relation(agent_side)

            self._info_manager[agent_side] = InfoManager(
                self_side=side_relation.get('self'),
                enemy_side_list=side_relation.get('enemy'),
                ally_side_list=side_relation.get('ally', None),
                neutral_side_list=side_relation.get('neutral', None)
            )
            self._info_manager[agent_side].update(std_obs[agent_side])
        self._done_flag = False

    def step(self):
        command_dict = {}
        for agent_side, agent_info in self._play_dict.items():
            command_dict[agent_side] = []
            for agent_name, player in agent_info.items():
                cmd, status, msg = player.step(self._info_manager[agent_side], self.blackboard, self.msg)
                command_dict[agent_side].extend(cmd)
        raw_obs, done_flag = self._env.step(command_dict)
        std_obs = self._obs_translator.translate(raw_obs)
        for side, info_manager in self._info_manager.items():
            info_manager.update(std_obs[agent_side])
        self._done_flag = done_flag
        return raw_obs, done_flag

    def is_done(self):
        return self._done_flag

    def _build_side_relation(self, agent_side):
        if agent_side == "1" or agent_side == "red":
            return {
                "self": "1",
                "enemy": "2",
                "ally": [],
                "neutral": []
            }
        elif agent_side == "2" or agent_side == "blue":
            return {
                "self": "2",
                "enemy": "1",
                "ally": [],
                "neutral": []
            }


if __name__ == "__main__":
    scenario_config = bycc_config_parser.scenario_config[0]
    scenario_name = scenario_config['scenario_name']

    config = scenario_to_env_config[scenario_name]
    player_config = bycc_config_parser.scenario_config.get_player_config(scenario_name)
    env_params = {
        "env_id": 0,
        "config": env_config,
        "extra_info": config.get('params', {}).get('extra_info', {})
    }
    play_dict = {
        "1": {
            "VoidAction": VoidAction(void_param=[])
        }
    }
    task_runner = TaskRunner(env_params=env_params, player_dict=play_dict)
    while True:
        task_runner.step()
        if task_runner.is_done():
            break
        time.sleep(1)

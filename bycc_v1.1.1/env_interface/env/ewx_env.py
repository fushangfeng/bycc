import logging
import os
import pickle
import sys
import time
from pathlib import Path

from bycc.global_config import GlobalConfig, Mode
from env_interface.env.env_clinet_EWX import EnvClient
from env_interface.env.env_manager import EnvManager
from env_interface.env.env_def import EquipmentType
from env_interface.env.raw_obs import RawObs

project_path = Path(__file__).resolve().parents[3]
files_path = os.path.join(project_path, "data")


def get_git_project_name(git_url):
    project_name = git_url.split('.')[-2].split('/')[-1]
    return project_name


def rename_folder_name(folder_path, new_name):
    import os
    folder_dir = os.path.dirname(folder_path)
    # logging.error(f"{folder_path}", f"{os.path.join(folder_dir, str(new_name))}")
    # os.rename(folder_path, os.path.join(folder_dir, str(new_name)))
    # if not os.path.exists(os.path.join(folder_dir, str(new_name))):
    try:
        os.system(f"rm -rf {os.path.join(folder_dir, str(new_name))}")
        os.system(f"mv {folder_path} {os.path.join(folder_dir, str(new_name))}")
    except Exception as e:
        print(e)


def record_imitation_data(func):
    def wrapper(env: 'EWXEnv', *args, **kwargs):
        cmds = {}
        for player, act_list in args[0].items():
            cmds[player] = [act.SerializeToString().hex() for act in act_list]
        imitation_pair = {
            "raw_obs": env.last_obs.SerializeToString().hex(),
            "cmds": cmds,
        }
        env.imitation_data.append(imitation_pair)
        res = func(env, *args, **kwargs)
        if res[1]:
            # 写入最后一帧用于done判断,执行func后last_obs已刷新
            imitation_pair = {
                "raw_obs": env.last_obs.SerializeToString().hex(),
                "cmds": cmds,
            }
            env.imitation_data.append(imitation_pair)
            with open(f'{files_path}/imitation_data_{env.reset_counter}.pkl', 'wb') as f:
                pickle.dump(env.imitation_data, f)
        return res
    return wrapper

def local_debug_step(func):
    def wrapper(env: 'EWXEnv', *args, **kwargs):
        if sys.gettrace():
            env.env_client.sim_control_resume()
            res = func(env, *args, **kwargs)
            env.env_client.sim_control_pause()
        else:
            res = func(env, *args, **kwargs)
        return res
    return wrapper


class EWXEnv:
    def __init__(self, env_id, config, extra_info):
        self.env_id = env_id + 1
        self.config = config

        # todo: 临时加在了训练配置extend
        self.extend = extra_info["extend"]
        self.config.update(self.extend)
        self.max_game_time = self.config.get('max_game_time', 10800)
        self.sim_speed = self.config.get('sim_speed', 20)
        self.action_interval = self.config.get('action_interval', 10)
        self.judge_done_param = extra_info["extend"].get("judge_done", "1")
        self.reset_counter = 0
        self.env_manager = None

        if GlobalConfig().mode != Mode.LOCAL:
            self.scenario_weight_dict = {}
            self.pull_scenario(extra_info['extend']['scenario_git_repo'])

            docker_server_port = self.config.get("docker_server_port", 30089)
            image_name = self.config['image_name']
            self.env_manager = EnvManager(
                self.env_id,
                base_port=docker_server_port,
                image_name=image_name,
                # volume_maps=self.config['volume_maps']
                # volume_maps=[[scenario_path, "/data/scenario"]],
                scenarios_weights_dict=self.scenario_weight_dict,
            )
            game_port = self.env_manager.get_server_port()
            game_ip = "127.0.0.1"
        else:
            game_ip = self.config.get('server_ip')
            game_port = self.config.get('server_port', 50000)

        self.env_client = EnvClient(game_ip, game_port)

        self.last_time = 0
        self.last_obs = None
        self.imitation_data = []

    def pull_scenario(self, scenario_git_repos):
        # scenario_git_repo:  {"http://10.0.0.200:2080/scenario/jammer_scenario.git": 0.7}
        from bycc.utils import clone_from_git
        from bycc.constant import GIT_USER_NAME, GIT_TOKEN, PROJECT_PATH

        scenarios_repo_dict = {}
        if isinstance(scenario_git_repos, str):
            scenarios_repo_dict[scenario_git_repos] = 1
        if isinstance(scenario_git_repos, dict):
            scenarios_repo_dict = scenario_git_repos

        self.scenario_weight_dict = {}
        for git_repo, weight in scenarios_repo_dict.items():
            scenario_path = os.path.join(PROJECT_PATH, get_git_project_name(git_repo))
            clone_from_git(git_repo, scenario_path, GIT_USER_NAME, GIT_TOKEN)
            self.scenario_weight_dict[scenario_path] = weight

    def reset(self):
        # todo reset 可能有问题，可能需要用 try 多连几次
        logging.error("--------------reset------------------")
        if self.env_manager:
            self.env_manager.reset()

        self.env_client.sim_control_reset()
        time.sleep(5)
        self.env_client.sim_control_start()
        time.sleep(1)
        self.env_client.set_sim_speed(self.sim_speed)
        time.sleep(0.1)

        self.last_time = 0
        self.reset_counter += 1
        self.imitation_data = []
        print(f"[* 环境重启 *] | 第{self.reset_counter}次！")
        obs = self.get_sim_states()
        # 调试模式发送暂停
        # if sys.gettrace():
        #     self.env_client.sim_control_pause()
        return obs

    def get_sim_states(self):
        response_obs = self.env_client.get_raw_obs()
        self.last_obs = response_obs
        obs = RawObs(response_obs).to_dict()
        done = self.judge_done(obs, self.judge_done_param)
        obs["episode_done"] = done
        return obs

    # @record_imitation_data
    # @local_debug_step
    def step(self, commands):
        self.env_client.take_actions(commands)

        while True:
            obs = self.env_client.get_raw_obs()
            sim_time = obs.metaData.SIM_TIME
            if sim_time - self.last_time > self.action_interval:
                break
            time.sleep(0.02)

        obs = self.get_sim_states()
        done = obs["episode_done"]
        print(f"sim time: {obs['metaData']['SIM_TIME']}")
        # logging.error(f"sim time: {obs['metaData']['SIM_TIME']}")
        self.last_time = obs['metaData']['SIM_TIME']

        return obs, done

    def step_piece_time(self, interval=0):
        self.env_client.step_piece_time(interval or self.action_interval)

    def judge_done(self, obs_dict, judge_done_param):
        return self.judge_done_1(obs_dict)

    def judge_done_1(self, obs_dict):
        """
        基础结束判定条件
        """
        # 1. 判断仿真时间是否达到最大值
        # print("当前的仿真时间是-----------", obs_dict['metaData']['SIM_TIME'])
        # print(obs_dict['metaData']['SIM_TIME'])
        if obs_dict['metaData']['SIM_TIME'] > self.max_game_time:
            logging.error("--------------------done---------------------")
            # print("-------------------------done------------------------")
            return True
        return False

    def judge_done_2(self, obs_dict):
        """
        第二个场景：雷达开关机，结束判断条件   时间和预警雷达是否存在
        """
        # 1. 判断仿真时间是否达到最大值
        # print("当前的仿真时间是-----------", obs_dict['metaData']['SIM_TIME'])
        if obs_dict['metaData']['SIM_TIME'] > self.max_game_time:
            print("-------------------------done------------------------")
            return True

        else:
            # 2. 判断当前红方预警雷达是否被打死
            radar_exit_flag = False
            radar_info_list = obs_dict['data']['radarParam']
            for radar_dict in radar_info_list:
                if radar_dict["ATT"] == 2:
                    continue
                else:
                    # 当前红方的预警雷达还在，没死，死了的话，态势中就没有这个单位了
                    if radar_dict['EquipmentType'] == EquipmentType.RADAR_STATION:
                        # print("当前红方预警雷达还存在")
                        radar_exit_flag = True

            # 如果在达到结束时间之前，红方预警雷达死了，程序就结束了
            if radar_exit_flag is False:
                print("当前预警雷达已经被击毁，运行结束")
                return True
            else:
                return False

        # 3. 后续可能会更改为新的判断条件

    def __del__(self):
        logging.error("ewx_env error")
        if self.env_manager:
            self.env_manager.stop_docker()
            logging.error("stop and rm container")


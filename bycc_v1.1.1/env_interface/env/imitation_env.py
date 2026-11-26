import json
import os
import pickle
import random
import shutil
import zipfile
from collections import deque
from urllib.parse import urlparse

from bycc.constant import PROJECT_PATH
from bycc.utils import load_config_file
from bycc.utils.minio_utils import download_file
from bycc_config.bycc_config_parser import bycc_config_path
from env_interface.env.ewx_env import EWXEnv
from env_interface.env.raw_obs import RawObs
from env_interface.protos.output.ai_pb2 import REPLY_STATES, Action


class ImitationEnv(EWXEnv):
    def __init__(self, env_id, config, extra_info):
        config["use_docker"] = False
        super().__init__(env_id, config, extra_info)
        self.files_path = os.path.join(PROJECT_PATH, "data")
        self._load_config()
        self._init_paths()
        self._prepare_data_files()
        self.file_list = self._scan_files()  # 预先扫描文件
        self.file_queue = deque()
        self._populate_queue()  # 初始化队列
        self.imitation_data = []
        self.steps = 0

    def _load_config(self):
        config = load_config_file(bycc_config_path).get("train_config", {}).get("train_data", {})
        self.train_data = config.get("path_url") or "http://10.0.0.200:30074/browser/algo-platform/imitation_data_1.zip"
        self.minio_access = config.get("minio_user", "admin")
        self.minio_secret = config.get("minio_password", "admin123")

    def _init_paths(self):
        if os.path.exists(self.files_path):
            shutil.rmtree(self.files_path)
        os.makedirs(self.files_path, exist_ok=True)

    @staticmethod
    def parse_minio_url(url):
        parsed = urlparse(url)
        minio_url = "10.0.0.200:30074"
        path_parts = parsed.path.strip("/browser").strip("/").split("/")
        bucket = path_parts[0]
        object_name = "/".join(path_parts[1:])
        return minio_url, bucket, object_name

    def _prepare_data_files(self):
        minio_url, bucket, object_name = self.parse_minio_url(self.train_data)
        zip_path = os.path.join(self.files_path, f"{object_name}.zip")
        download_file(minio_url, self.minio_access, self.minio_secret, bucket, object_name, zip_path)

        if not os.path.exists(zip_path):
            raise FileNotFoundError(f"{zip_path} does not exist")

        with zipfile.ZipFile(zip_path, "r") as zip_ref:
            zip_ref.extractall(self.files_path)

        os.remove(zip_path)


    def _scan_files(self):
        if not os.path.exists(self.files_path):
            raise FileNotFoundError(f"Folder path '{self.files_path}' does not exist.")

        file_extensions = (".pkl", ".json")
        file_list = [os.path.join(root, file)
                     for root, _, files in os.walk(self.files_path)
                     for file in files if file.endswith(file_extensions)]

        if not file_list:
            raise FileNotFoundError(
                f"No {', '.join(file_extensions)} files found in '{self.files_path}' or its subdirectories."
            )
        return file_list

    def _populate_queue(self):
        random.shuffle(self.file_list)
        self.file_queue.extend(self.file_list)

    def load_data_pkl(self, file_path):
        with open(file_path, 'rb') as file:
            self.imitation_data = pickle.load(file)

    def load_data_json(self, file_path):
        with open(file_path, 'r', encoding='utf-8') as file:
            self.imitation_data = json.load(file)

    def sample_file(self):
        if not self.file_queue:
            self._populate_queue()

        return os.path.abspath(self.file_queue.popleft())

    def _load_file(self):
        file_path = self.sample_file()
        if file_path.endswith(".pkl"):
            self.load_data_pkl(file_path)
        else:
            self.load_data_json(file_path)

    def reset(self):
        self._load_file()
        self.last_time = 0
        self.reset_counter += 1
        print(f"[* 环境重启 *] | 第{self.reset_counter}次！")
        self.steps = 0
        obs = self.get_sim_states()
        obs["cmds"] = self.get_cmds()
        self.steps += 1
        return obs

    def get_sim_states(self):
        response_obs = self.imitation_data[self.steps]["raw_obs"]
        response_obs = REPLY_STATES.FromString(bytes.fromhex(response_obs))
        obs = RawObs(response_obs).to_dict()
        done = self.judge_done(obs, self.judge_done_param)
        obs["episode_done"] = done
        return obs

    def get_cmds(self):
        commands = self.imitation_data[self.steps]["cmds"]
        cmds = {}
        for player, act_list in commands.items():
            cmds[player] = [Action.FromString(bytes.fromhex(act)) for act in act_list]
        return cmds

    def step(self, commands):
        obs = self.get_sim_states()
        print(f"sim time: {obs['metaData']['SIM_TIME']}")
        self.last_time = obs['metaData']['SIM_TIME']

        obs["cmds"] = self.get_cmds()
        done = obs["episode_done"]
        self.steps += 1
        return obs, done

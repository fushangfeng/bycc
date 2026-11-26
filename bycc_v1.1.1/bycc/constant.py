import os
from pathlib import Path

PREFIX = os.path.dirname(__file__)
PROJECT_PATH = Path(__file__).resolve().parent.parent

BT_ACTION_MODULE_DIR = os.path.abspath(os.path.join(PREFIX, "./modules/bt_action"))
BT_CONDITION_MODULE_DIR = os.path.abspath(os.path.join(PREFIX, "./modules/bt_condition"))
BT_DECORATOR_MODULE_DIR = os.path.abspath(os.path.join(PREFIX, "./modules/bt_decorator"))
EVALUATION_INDICATOR_MODULE_DIR = os.path.abspath(os.path.join(PREFIX, "./modules/evaluation_indicator"))
MISSION_MODULE_DIR = os.path.abspath(os.path.join(PREFIX, "./modules/mission"))
REWARD_FUNCTION_MODULE_DIR = os.path.abspath(os.path.join(PREFIX, "./modules/reward"))
STATISTIC_MODULE_DIR = os.path.abspath(os.path.join(PREFIX, "./modules/statistic"))
STATE_MACHINE_MODULE_DIR = os.path.abspath(os.path.join(PREFIX, "./modules/state_machine"))

# 是否支持多想定训练
MULTI_SCENARIO: bool = False
# 是否为本地运行模式, 用于部署场景，此时不import git，不再尝试拉取模块
LOCAL_RUN: bool = False

# 是否启用数据收集功能
ENABLE_DATA_COLLECTION: bool = True
# 是否启用元数据收集功能
ENABLE_METADATA_COLLECTION: bool = True
# 是否存储数据到Minio
ENABLE_MINIO_STORAGE: bool = False
# 是否启用PostgreSQL存储功能(#ToDo 原tiance写的功能 先不做更改 后续讨论后和在一块)
ENABLE_POSTGRESQL_STORAGE: bool = False
# 是否存储评估数据到PostgreSQL（针对29s新增的数据收集功能）
ENABLE_EVALUATION_DATA_TO_POSTGRESQL: bool = True

# Minio配置
MINIO_CONFIG = {
    'endpoint': '127.0.0.1:2222',
    'access_key': 'access_key',
    'secret_key': 'secret_key',
    'secure': False,
    'bucket_name': 'bycc-evaluation-data'
}

EVAL_MAIN_FILE_LIST = ["evaluate.py", "agent_service.py"]
LOCAL_MAIN_FILE_LIST = ["train_debug.py", "local.py"]

# 智能体推理数据收集 - 观测考虑要素
OBSERVATION_FACTORS = ["地理信息", "天气气象", "敌我态势", "装备状态"]


def change_git_info(git_user_name, git_token):
    global GIT_USER_NAME, GIT_TOKEN
    GIT_USER_NAME = git_user_name
    GIT_TOKEN = git_token


class TrainType:
    # bycc_config.json配置文件中train_type字段名
    RL = "rl"
    BC = "bc"
    SELF_PLAY = "self-play"
    ASYMMETRIC_TRAIN = "asymmetric-play"

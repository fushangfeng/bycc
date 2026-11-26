import os
import sys

from bycc.global_config import GlobalConfig, Mode, LogLevel
from bycc.utils.logger.default_logger import DefaultLogger
from bycc_config.bycc_config_legacy import BYCCConfigLegacy
from bycc_config.bycc_config import BYCCConfig

TRAIN_CONFIG_PATH = "/job/config/bycc_config.json"

if os.path.exists(TRAIN_CONFIG_PATH):
    bycc_config_path = TRAIN_CONFIG_PATH
else:
    bycc_config_path = os.path.abspath(os.path.join(os.path.dirname(__file__), 'bycc_config.json'))

# 新版本BYCCConfig，为保证兼容性，暂时临时保留两个版本解析逻辑
bycc_config_parser_new = BYCCConfig.parse_file(bycc_config_path)

# 老版本BYCCConfig解析，后续逐渐弃用
bycc_config_parser = BYCCConfigLegacy(bycc_config_path)

main_file_name = os.path.basename(sys.argv[0])

if GlobalConfig().mode == Mode.TRAIN:
    GlobalConfig().log_format = "%(asctime)s " \
                                f"{bycc_config_parser.train_task_id} " \
                                "%(levelname)s " \
                                "%(process)d " \
                                "[%(name)s]%(filename)s:%(funcName)s:line %(lineno)d " \
                                "- " \
                                "%(message)s"

DefaultLogger.init(
    level=GlobalConfig().log_level,
    log_path=GlobalConfig().log_path,
    max_bytes=200 * 1024 * 1024,
    backup_count=0,
    fmt=GlobalConfig().log_format
)

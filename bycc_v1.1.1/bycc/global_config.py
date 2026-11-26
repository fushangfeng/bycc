import os
import re
import sys
import enum

from bycc.constant import (
    EVAL_MAIN_FILE_LIST, LOCAL_MAIN_FILE_LIST, ENABLE_DATA_COLLECTION, 
    ENABLE_METADATA_COLLECTION, ENABLE_MINIO_STORAGE, MINIO_CONFIG,
    ENABLE_POSTGRESQL_STORAGE, ENABLE_EVALUATION_DATA_TO_POSTGRESQL
)


class Mode(enum.IntEnum):
    TRAIN = enum.auto()
    LOCAL = enum.auto()
    EVALUATE = enum.auto()


class LogLevel:
    DEBUG = 'DEBUG'
    INFO = 'INFO'
    WARNING = 'WARNING'
    ERROR = 'ERROR'
    CRITICAL = 'CRITICAL'


class GlobalConfig:

    _instance = None
    _initialized = False

    def __new__(cls, *args, **kwargs):
        if cls._instance is None:
            cls._instance = super(GlobalConfig, cls).__new__(cls, *args, **kwargs)
            cls._instance._init()
        return cls._instance

    def _init(self):
        def match_filename(filename, file_list):
            pattern = r'^(' + '|'.join(re.escape(name.split(".")[0]) for name in file_list) + r')(\.[^.]+)*$'
            return bool(re.match(pattern, filename))

        main_file_name = os.path.basename(sys.argv[0])
        if match_filename(main_file_name, EVAL_MAIN_FILE_LIST):
            self._load_eval_config()
        elif match_filename(main_file_name, LOCAL_MAIN_FILE_LIST):
            self._load_local_config()
        else:
            self._load_train_config()

    def _load_train_config(self):
        self.mode = Mode.TRAIN
        self.module_dir = os.path.abspath(os.path.join(os.path.dirname(__file__), './modules'))
        self.log_path = "/job/logs/bycc_log.log"
        self.log_level = LogLevel.INFO
        self.log_format = "%(asctime)s " \
                          "%(levelname)s " \
                          "%(process)d " \
                          "[%(name)s]%(file_name)s:%(func_name)s:line %(line_no)d " \
                          "- " \
                          "%(message)s"

    def _load_eval_config(self):
        self.mode = Mode.EVALUATE
        self.log_path = os.path.abspath(os.path.join(os.path.dirname(os.path.dirname(__file__)), 'bycc_log.log'))
        self.log_level = LogLevel.INFO
        self.log_format = "%(asctime)s " \
                          "%(levelname)s " \
                          "%(process)d " \
                          "[%(name)s]%(file_name)s:%(func_name)s:line %(line_no)d " \
                          "- " \
                          "%(message)s"
        
        # 数据收集配置
        self.enable_data_collection = ENABLE_DATA_COLLECTION
        self.enable_metadata_collection = ENABLE_METADATA_COLLECTION
        self.enable_minio_storage = ENABLE_MINIO_STORAGE
        
        # PostgreSQL存储配置
        self.enable_postgresql_storage = ENABLE_POSTGRESQL_STORAGE
        self.enable_evaluation_data_to_postgresql = ENABLE_EVALUATION_DATA_TO_POSTGRESQL
        
        # Minio配置
        self.minio_config = MINIO_CONFIG.copy()

    def _load_local_config(self):
        self.mode = Mode.LOCAL
        self.log_path = os.path.abspath(os.path.join(os.path.dirname(os.path.dirname(__file__)), 'bycc_log.log'))
        self.log_level = LogLevel.DEBUG
        self.log_format = "%(asctime)s " \
                          "%(levelname)s " \
                          "%(process)d " \
                          "[%(name)s]%(file_name)s:%(func_name)s:line %(line_no)d " \
                          "- " \
                          "%(message)s"

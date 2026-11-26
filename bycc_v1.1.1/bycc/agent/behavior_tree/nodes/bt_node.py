from abc import abstractmethod
from typing import Any

from bycc.utils.logger.default_logger import DefaultLogger


class BTNode:

    def __init__(self, name, instance_name=None):
        self._name = name
        self._instance_name = instance_name
        self._logger = DefaultLogger.get_logger(instance_name or name)

    @abstractmethod
    def execute(self, obs: Any, cmds_buffer: dict, msg_out_buffer: dict, black_board: dict, msg_in=None):
        raise NotImplementedError

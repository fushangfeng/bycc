import os
from bycc.environment.std_io.std_def import UnitType


class PlayerConfig:
    MY_UNIT_TYPES = [UnitType.FIGHTER]
    MAX_MY_UNIT_LEN = 16

    EN_UNIT_TYPES = [UnitType.FIGHTER]
    MAX_EN_UNIT_LEN = 16
    GLOBAL_MOVE_SIZE = 10
    MINI_MAP_SIZE = 10


PREFIX = os.path.dirname(__file__)
IMAGE_NAME = 'registry.inspir.ai:5000/sim_fast:v3.2'
ENV_ID_SHIFT = 0

IP = '127.0.0.1'


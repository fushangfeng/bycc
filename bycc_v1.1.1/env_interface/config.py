from env_interface.env.ewx_env import EWXEnv
from env_interface.env.imitation_env import ImitationEnv
from env_interface.obs_translator import EWXObsTranslator
from env_interface.env_config import env_config

from env_interface.bycc_map.class_map import CLASS_MAP
from env_interface.bycc_map.state_space_map import STATE_SPACE_MAP


config = {
    "environment": {
        "class": EWXEnv,
        "params": {
            "config": env_config
        }
    },
    "obs_translator": {
        "class": EWXObsTranslator,
        "params": {}
    },
    "cmd_translator": {},
    "entity_map": CLASS_MAP,
    "state_space_map": STATE_SPACE_MAP
}

imitation_config = {
    "environment": {
        "class": ImitationEnv,
        "params": {
            "config": env_config
        }
    },
    "obs_translator": {
        "class": EWXObsTranslator,
        "params": {}
    },
    "cmd_translator": {},
    "entity_map": CLASS_MAP,
    "state_space_map": STATE_SPACE_MAP
}

from env_interface.data_types import PlatParaInfo
from env_interface.env.ewx_cmds import PlatActions, RjamActions
from env_interface.env.ewx_env import EWXEnv
from env_interface.env_config import env_config
from env_interface.obs_translator import EWXObsTranslator

RED_SIDE = '1'

class TestEnv(EWXEnv):
    def __init__(self):
        extra_info = {'extend': {}}
        super(TestEnv, self).__init__(1, env_config, extra_info)

    def get_obs(self):
        obs = self.get_sim_states()
        return EWXObsTranslator().translate(obs)

    def get_red_units(self):
        obs = self.get_obs()
        red_obs = obs[RED_SIDE].obs
        red_units = red_obs.units[RED_SIDE]
        return red_units

    def test_SetPlatFormation(self):
        env.step_piece_time()
        obs = self.get_obs()
        red_obs = obs[RED_SIDE].obs
        red_units = red_obs.units[RED_SIDE]
        self.test_v_formation(red_units)

    def test_v_formation(self, units: list[PlatParaInfo]):
        leader_id = units and units[0].id
        wing_id_list = [unit.id for unit in units[1:]]
        cmds = []
        cmds.append(PlatActions.make_action_PlatFormCtl(leader_id, wing_id_list))
        cmds.append(PlatActions.make_action_FormStyleCtl(leader_id, ["V",500,30,-1,-1]))
        self.step({RED_SIDE: cmds})
        self.step_piece_time(1000)

    def test_auto_fire(self):
        cmd = PlatActions.make_action_SetPlatAutoFire(2, True)
        cmds = [cmd]
        self.step({RED_SIDE: cmds})
        self.step_piece_time(100)

    def test_fire(self):
        cmd = PlatActions.make_action_SetPlatFireCtl(2, 6, num_missile=1)
        self.step({RED_SIDE: [cmd]})
        self.step_piece_time(10)
        # cmd = PlatActions.make_action_SetPlatFireCtl(2, 6, num_missle=1)
        # self.step({RED_SIDE: [cmd]})
        self.step_piece_time(10)

    def test_jammer(self):
        obs = self.get_obs()
        cmd = RjamActions.make_action_rjam_SetRadarJamTrg(2, False)





if __name__ == "__main__":
    env = TestEnv()
    env.reset()
    # env.test_SetPlatFormation()
    env.step_piece_time(1200)
    env.test_fire()
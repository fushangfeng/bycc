from typing import Any, List

from bycc.common.data_types import RelativeSide
from bycc.environment.env_data import ObsData
from bycc.common.info.manager import AbstractInfoManager
from bycc.common.info.unit_manager import UnitManager


class InfoManager(AbstractInfoManager):

    def __init__(
            self,
            self_side: Any,
            enemy_side_list: List,
            ally_side_list: List = None,
            neutral_side_list: List = None
    ):
        """
        Parameters
        ----------
        # side: Any
        #     标记智能体所属方，根据仿真和场景不同，可为任意值，如：'red', 'blue', 'green'等
        # camp: Union[None, Any]
        #     标记智能体所属阵营，可为None或任意值，如：1, 2, None等
        #     camp值相同，则互为同盟方；值不同的互为敌对方；camp为None，则无阵营，可认为是中立方

        # side_map : Dict[str, Any]
        #     记录已方、敌方、友方、中立等阵营信息,value对应player中的side属性,如:
        #     {
        #         "self":'red', # 己方
        #         "ally":['yellow',"orange'], # 同盟方
        #         "enemy":['blue',"green'], # 敌方
        #         "neutral":['white','black'], # 中立方
        #     }
        #     如果某些阵营不存在(如ally和neutral),则在宁典中不包含对应字段
        self_side: Any
             我方智能体阵营名称
             如： 'red'
        enemy_side_list: List
            敌方智能体阵营名称列表（考虑敌方多方结盟）
            如： ['blue', 'green']
        ally_side_list: List
            我方同盟智能体阵营名称列表，为None时不存在同盟
            如： ['black']
        neutral_side_list: List
            中立放智能体阵营名称列表，为None时不存在中立方
            如： ['white', 'yellow']
        """
        # self._side = side
        # self._camp = camp

        self._side = self_side
        self._enemy_sides = enemy_side_list
        self._ally_sides = ally_side_list
        self._neutral_sides = neutral_side_list

        self._sim_time = None
        self._common_info = None

        self._raw_obs = None

        self._unit_manager = UnitManager()

        # todo: 方便用户在自定义组件中做一些数据存储，供后续使用
        self.custom_dict = {}

    @property
    def raw_obs(self):
        return self._raw_obs

    @property
    def unit_manager(self):
        return self._unit_manager

    def relative_side_to_absolute_side(self, relative_side):
        if relative_side == RelativeSide.SELF:
            side = self.self_side
        elif relative_side == RelativeSide.ENEMY:
            side = self.enemy_sides
        elif relative_side == RelativeSide.ALLY:
            side = self.ally_sides
        elif relative_side == RelativeSide.NEUTRAL:
            side = self.neutral_sides
        else:
            raise ValueError(f'Unknown relative side: {relative_side}!!!')

        return side

    @property
    def self_side(self):
        return self._side

    @property
    def enemy_sides(self):
        return self._enemy_sides

    @property
    def ally_sides(self):
        return self._ally_sides

    @property
    def neutral_sides(self):
        return self._neutral_sides

    @property
    def sim_time(self):
        return self._sim_time

    def get_common_info(self):
        return self._common_info

    def get_spatial_info(self):
        return self._spatial_info

    def update(self, std_obs: ObsData):
        self._raw_obs = std_obs
        self._sim_time = std_obs.obs.sim_time
        self._common_info = std_obs.obs.common_info
        self._spatial_info = std_obs.obs.spatial_info

        self._unit_manager.update(std_obs)

    def reset(self):
        self._unit_manager.reset()

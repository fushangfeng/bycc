from bycc.environment.translator.obs_translator import ObsTranslator
from bycc.environment.env_data import ObsData
from bycc.environment.std_io.obs.std_info import StdInfo, CommonInfo, SpatialInfo
from bycc.environment.std_io.obs.std_obs import StdObs
from bycc.common.entity.ground.airport.airport import AirportInfo
from bycc.common.entity.air.fighter.fighter import FighterInfo
from bycc.common.entity.air.awacs.awacs import AWACSInfo
from bycc.environment.std_io.std_def import UnitType
from bycc.common.data_types.position import Position
from bycc.common.data_types.grid_map import GridMap

from examples.air_8v8.env_interface.env_def import UnitType as NJ01UnitType, MapInfo
from examples.air_8v8.constant import PlayerConfig


class NJ01ObsTranslator(ObsTranslator):

    def translate(self, raw_obs):
        std_obs = {}
        for side, side_obs in raw_obs.items():
            if side == 'red_side':
                std_obs[side] = self._make_std_obs(side_obs, 'red_side')
            else:
                std_obs[side] = self._make_std_obs(side_obs, 'blue_side')
        return std_obs

    def _make_std_obs(self, side_obs: ObsData, side: str):
        if side == 'red_side':
            red_units = self._make_self_units(side_obs.obs['red_side'], 'red_side')
            blue_units = self._make_opp_units(side_obs.obs['red_side']['qb'], 'blue_side')
        else:
            red_units = self._make_opp_units(side_obs.obs['blue_side']['qb'], 'red_side')
            blue_units = self._make_self_units(side_obs.obs['blue_side'], 'blue_side')

        std_obs = ObsData(
            obs=StdObs(
                sim_time=side_obs.obs['sim_time'],
                common_info=CommonInfo(
                    sim_time=side_obs.obs['sim_time'],  # 此处用sim time仅作为例子
                    absolute_sim_time=side_obs.obs['sim_time']
                ),
                units={
                    'red_side': red_units,
                    'blue_side': blue_units
                },
                spatial_info=SpatialInfo(
                    self_entity_map=self._make_entity_map(red_units) if side == 'red_side' else self._make_entity_map(blue_units),
                    enemy_entity_map=self._make_entity_map(blue_units) if side == 'red_side' else self._make_entity_map(red_units)
                ),
            ),
            episode_done=side_obs.episode_done,
        )
        god_obs = side_obs.extra_info_dict.get('god_obs', None)
        if god_obs:
            # 训练时计算reward需要god_obs，推演部署时，不需要god_obs
            red_units = self._make_self_units(side_obs.extra_info_dict['god_obs']['red'], 'red_side')
            blue_units = self._make_self_units(side_obs.extra_info_dict['god_obs']['blue'], 'blue_side')
            std_obs.extra_info_dict['god_obs'] = ObsData(
                obs=StdObs(
                    sim_time=side_obs.extra_info_dict['god_obs']['sim_time'],
                    common_info=CommonInfo(
                        sim_time=side_obs.extra_info_dict['god_obs']['sim_time'],
                        absolute_sim_time=side_obs.extra_info_dict['god_obs']['sim_time'],
                    ),
                    units={
                        'red_side': red_units,
                        'blue_side': blue_units
                    },
                    spatial_info=SpatialInfo(),
                ),
                episode_done=std_obs.episode_done
            )
        return std_obs

    def _make_self_units(self, units, side):
        units_list = []
        for airport_dict in units['airports']:
            units_list.append(AirportInfo(
                id=airport_dict['ID'],
                side=side,
                position=Position(airport_dict['X'], airport_dict['Y'], airport_dict['Z']),
                angle=0,
                unit_type=UnitType.AIRPORT,
                unit_subtype=None,
                fighter_num=airport_dict['AIR'],
                bomber_num=airport_dict['BOM'],
                alive=airport_dict['WH']
            ))
        for u_dict in units['units']:
            if u_dict['LX'] == NJ01UnitType.A2A:
                units_list.append(FighterInfo(
                    id=u_dict['ID'],
                    side=side,
                    position=Position(u_dict['X'], u_dict['Y'], u_dict['Z']),
                    angle=u_dict['HX'],
                    unit_type=UnitType.FIGHTER,
                    unit_subtype=None,
                    direction=u_dict['HX'],
                    speed=u_dict['SP'],
                    alive=u_dict['WH']
                )),
            elif u_dict['LX'] == NJ01UnitType.AWACS:
                units_list.append(AWACSInfo(
                    id=u_dict['ID'],
                    side=side,
                    position=Position(u_dict['X'], u_dict['Y'], u_dict['Z']),
                    angle=u_dict['HX'],
                    unit_type=UnitType.AWACS,
                    unit_subtype=None,
                    direction=u_dict['HX'],
                    speed=u_dict['SP'],
                    alive=u_dict['WH']
                ))
        return units_list

    def _make_opp_units(self, units, side):
        unit_list = []
        for u_dict in units:
            if u_dict['LX'] == NJ01UnitType.A2A:
                unit_list.append(FighterInfo(
                    id=u_dict['ID'],
                    side=side,
                    direction=u_dict['HX'],
                    position=Position(u_dict['X'], u_dict['Y'], u_dict['Z']),
                    angle=u_dict['HX'],
                    speed=u_dict['SP'],
                    unit_type=UnitType.FIGHTER,
                    unit_subtype=None,
                    alive=u_dict['WH']
                ))
            elif u_dict['LX'] == NJ01UnitType.AWACS:
                unit_list.append(AWACSInfo(
                    id=u_dict['ID'],
                    side=side,
                    direction=u_dict['HX'],
                    position=Position(u_dict['X'], u_dict['Y'], u_dict['Z']),
                    angle=u_dict['HX'],
                    speed=u_dict['SP'],
                    unit_type=UnitType.AWACS,
                    unit_subtype=None,
                    alive=u_dict['WH']
                ))
            elif u_dict['LX'] == NJ01UnitType.AIRPORT:
                unit_list.append(AirportInfo(
                    id=u_dict['ID'],
                    side=side,
                    position=Position(u_dict['X'], u_dict['Y'], u_dict['Z']),
                    angle=0,
                    unit_type=UnitType.AIRPORT,
                    unit_subtype=None,
                    fighter_num=0,
                    bomber_num=0,
                    alive=u_dict['WH']
                ))
        return unit_list

    def _make_entity_map(self, units):
        entity_map = GridMap(
            MapInfo.X_MIN,
            MapInfo.Y_MIN,
            MapInfo.X_MAX,
            MapInfo.Y_MAX,
            PlayerConfig.MINI_MAP_SIZE,
            PlayerConfig.MINI_MAP_SIZE
        )
        for unit in units:
            entity_map.set_grid_value(unit.position.x, unit.position.y, 1)

        return entity_map

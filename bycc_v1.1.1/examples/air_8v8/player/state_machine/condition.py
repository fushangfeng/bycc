from bycc.agent.state_machine.condition import Condition
from bycc.common.info import InfoManager
from bycc.environment.std_io.std_def import UnitType


class AirplaneNumNotZeroCondition(Condition):
    def __init__(self, name):
        super().__init__(name)

    def step(self, state, event):
        info_manager: InfoManager = event.info_manager
        params = event.params
        airport_index = params["airport_index"]
        airports = info_manager.unit_manager.get_by_type(UnitType.AIRPORT)
        airport = airports[airport_index]
        return airport.attribute.fighter_num > 0


class AirplaneNumZeroCondition(Condition):
    def __init__(self, name):
        super().__init__(name)

    def step(self, state, event):
        info_manager: InfoManager = event.info_manager
        params = event.params
        airport_index = params["airport_index"]
        airports = info_manager.unit_manager.get_by_type(UnitType.AIRPORT)
        airport = airports[airport_index]
        return airport.attribute.fighter_num <= 0

from typing import Any, Dict, List, Union
from bycc.environment.env_data import ObsData


class ObsTranslator:

    def translate(self, raw_obs: Any) -> Dict[str, ObsData]:
        raise NotImplementedError

    def data_convert(self, raw_obs: Any) -> Union[List[Dict[str, Any]], Dict[str, List[Any]]]:
        raise NotImplementedError

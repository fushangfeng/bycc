from dataclasses import dataclass

from bycc.environment.std_io.obs.std_info import StdStateSpace, StdInfo


@dataclass
class LabelInfo(StdInfo):
    def __init__(self, cmd_info):
        for key, value in cmd_info.items():
            setattr(self, key, value)


@dataclass
class LabelInfoStateSpace(StdStateSpace):
    @classmethod
    def data_class(cls) -> type(StdInfo):
        return LabelInfo

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        for key, value in kwargs.items():
            setattr(self, key, value)
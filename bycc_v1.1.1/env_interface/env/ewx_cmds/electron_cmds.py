from env_interface.env.ewx_cmds.base import BaseAction


class RadarAction(BaseAction):
    model_type: str = 'Radar'

    @classmethod
    def WorkOnCtl(cls, nRadarId: int, bWorkOn: bool):
        # 雷达开关机控制
        return cls._make_action(locals())

    @classmethod
    def RadarModeCtl(cls, nRadarId, RadarWorkMode):
        # 雷达工作模式
        return cls._make_action(locals())

    @classmethod
    def RadarAglRngCtl(cls, nRadarId, dStartAz, dEndAz, dStartEl, dEndEl):
        # 雷达参数控制
        return cls._make_action(locals())

    @classmethod
    def RadarFreqRngCtl(cls, nRadarId, dTarFreMin, dTarFreMax):
        # 雷达频率控制
        return cls._make_action(locals())

    @classmethod
    def RadarAntiJamModeCtl(cls, nRadarId, AntiJamMode):
        # 雷达抗GR措施控制
        return cls._make_action(locals())

    @classmethod
    def TrackTrgIDCtl(cls, nRadarId, TrackIdList):
        # 设置雷达跟踪航迹目标id
        return cls._make_action(locals())

    @classmethod
    def GuidCmdAction(cls, nRadarId, bguid):
        # 雷达制导控制指令
        return cls._make_action(locals())


class CommAction(BaseAction):
    model_type: str = 'Comm'

    @classmethod
    def WorkOnCtl(cls, nCommId: int, bWorkOn: bool):
        # 开关机控制
        return cls._make_action(locals())

    @classmethod
    def CommModeCtl(cls, nCommId, CommWorkMode):
        # 工作模式
        return cls._make_action(locals())

    @classmethod
    def CommPowCtl(cls, ):
        # 功率控制
        # todo 补充参数
        return cls._make_action(locals())

    @classmethod
    def CommAntiJamModeCtl(cls, nCommId, AntiJamMode):
        # 抗GR措施控制
        return cls._make_action(locals())

from env_interface.env.ewx_cmds.base import BaseAction


class RadarReconAction(BaseAction):
    model_type: str = 'RadarRecon'

    @classmethod
    def ReconZone(cls):
        """
        ZC重点空域控制

        """
        # todo 补充参数
        return cls._make_action(locals())

    @classmethod
    def ReconTgtCtl(cls):
        """
        ZC重点目标控制

        """
        # todo 补充参数
        return cls._make_action(locals())

    @classmethod
    def WorkOnCtl(cls, nRReconId: int, bWorkOn: bool):
        """
        ZC工作状态控制
        装备id,ZC开关机（turnoff/turnon）
        """
        return cls._make_action(locals())

    @classmethod
    def ReconAglRngCtl(cls, nRReconId, dStartAz, dEndAz, dStartEl=-90, dEndEl=90):
        """
        ZC方向控制
        装备id,ZC起始方位角,ZC终止方位角,ZC起始俯仰角,ZC终止俯仰角
        """
        return cls._make_action(locals())

    @classmethod
    def ReconFreqRngCtl(cls, nRReconId, dRFMin, dRFMax):
        """
        ZC频段控制
        装备id,ZC起始频率,ZC终止频率
        单位：现在确定用兆赫兹（10^6赫兹)
        """
        return cls._make_action(locals())

    @classmethod
    def SetRecoPara(cls, ):
        """
        设置ZC参数（仅对样机）
        装备id,类别,视距/超视距,滤波器,衰减,极化
        """
        # todo 补充参数
        return cls._make_action(locals())

    @classmethod
    def SetRecoSpectrThresh(cls, ):
        """
        频谱门限控制（仅对样机）
        装备id,检测门限
        """
        # todo 补充参数
        return cls._make_action(locals())


class RadarJamAction(BaseAction):
    model_type: str = 'RadarJam'

    @classmethod
    def WorkOnCtl(cls, nJamId: int, bWorkOn: bool, JamMode=0):
        """
        GR工作状态控制
        装备id,GR开关机,GR样式（可选）
        """
        return cls._make_action(locals())

    @classmethod
    def JamTrgCtl(cls, nJamId, nTargetIndex, JamMode=0, dCenterFreg=-1, dBandWidth=-1):
        """
        GR目标控制
        装备id,GR目标ID,GR样式（可选,枚举）,中心频率（可选,默认-1）,带宽（可选,默认-1）功率？！
        """
        return cls._make_action(locals())

    @classmethod
    def JamTypeCtl(cls, ):
        """
        GR样式控制
        装备id,GR样式,GR参数
        """
        # todo 补充参数
        return cls._make_action(locals())

    @classmethod
    def RadarJamAglRngCtl(cls, nJamId, dStartAz, dEndAz, dStartEl, dEndEl):
        """
        GR方向控制
        装备id,GR波束起始方位,GR终止方位,GR起始俯仰,GR终止俯仰
        """
        return cls._make_action(locals())

    @classmethod
    def RadarJamFreqRngCtl(cls, nJamId, dTarFreMin, dTarFreMax):
        """
        GR频率控制
        装备id,GR起始频率,GR终止频率
        单位：现在确定用兆赫兹（10^6赫兹)
        """
        return cls._make_action(locals())

    @classmethod
    def SetJamTrgPra(cls, ):
        """
        GR引导参数控制（仅对样机）
        装备id,类别,启停,子阵方式,GR决策
        """
        # todo 补充参数
        return cls._make_action(locals())

    @classmethod
    def SetJamTypePara(cls, ):
        """
        GR样式控制（仅对样机）
        装备id,类别,目标id,方位指向、俯仰指向、极化、GR样式,GR参数
        """
        # todo 补充参数
        return cls._make_action(locals())


class CommReconAction(BaseAction):
    model_type: str = 'CommRecon'

    @classmethod
    def WorkOnCtl(cls, nReconId: int, bWorkOn: bool):
        """
        ZC开关机控制
        装备id,ZC开关机
        """
        return cls._make_action(locals())

    @classmethod
    def ReconAglRngCtl(cls, nReconId, dStartAz, dEndAz, dStartEl, dEndEl):
        """
        ZC参数控制
        装备id,ZC起始方位角,ZC终止方位角,ZC起始俯仰角,ZC终止俯仰角
        """
        return cls._make_action(locals())

    @classmethod
    def ReconFreqRngCtl(cls, nReconId, dTarFreMin, dTarFreMax):
        """
        ZC频率控制
        装备id,ZC起始频率,ZC终止频率
        单位：现在确定用兆赫兹（10^6赫兹)
        """
        return cls._make_action(locals())


class CommJamAction(BaseAction):
    model_type: str = 'CommJam'

    @classmethod
    def WorkOnCtl(cls, nJamId: int, bWorkOn: bool, JamMode=0):
        """
        GR开关机控制
        装备id,GR开关机,GR样式（可选）
        """
        return cls._make_action(locals())

    @classmethod
    def JamAglRngCtl(cls, nJamId, dStartAz, dEndAz, dStartEl, dEndEl):
        """
        GR参数控制
        装备id,GR区域起始方位,GR区域终止方位,GR区域起始俯仰,GR区域终止俯仰
        """
        return cls._make_action(locals())

    @classmethod
    def JamFreqRngCtl(cls, nJamId, dTarFreMin, dTarFreMax):
        """
        GR频率控制
        装备id,GR起始频率,GR终止频率
        单位：现在确定用兆赫兹（10^6赫兹)
        """
        return cls._make_action(locals())

    @classmethod
    def JamTrgCtl(cls, nJamId, nTargetIndex, JamMode=0, dCenterFreg=-1, dBandWidth=-1):
        """
        GR目标控制
        装备id,GR目标ID,GR样式（可选,枚举）,中心频率（可选,默认-1）,带宽（可选,默认-1）
        """
        return cls._make_action(locals())


class MultifunctionAction(BaseAction):
    model_type: str = 'Multifunction'

    @classmethod
    def SetWorkModeAction(cls, ):
        """
        设置任务模式
        装备id,任务模式
        """
        # todo 补充参数
        return cls._make_action(locals())

    @classmethod
    def SetKcgSdjSubModeCtrl(cls, ):
        """
        一体化模式子模式指定控制
        装备id,ZC子模式,TC子模式,GR子模式
        """
        # todo 补充参数
        return cls._make_action(locals())

    @classmethod
    def SetKcgSdjTimeCtrl(cls, ):
        """
        一体化模式子模式执行时间控制
        装备id,一体化模式帧周期,侦干比
        """
        # todo 补充参数
        return cls._make_action(locals())


if __name__ == '__main__':
    action = RadarReconAction.ReconAglRngCtl(1, 2, 3)
    print(action)

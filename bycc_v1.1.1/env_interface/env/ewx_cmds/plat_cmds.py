from env_interface.env.ewx_cmds.base import BaseAction
from typing import Tuple

class PlanePlatAction(BaseAction):
    model_type = 'PlanePlat'

    @classmethod
    # 纬度、经度、高度
    def PlatPosCtl(cls, nPlatId: int, pSpeed: float, pPostion: Tuple[float, float, float]):
        """
        飞机机动位置控制（脚本控制规划航路）
        飞机id,机动速度,位置点(纬度、经度、高度)
        """
        return cls._make_action(locals())

    @classmethod
    def PlatPatrolCtl(cls, nPlatId, sRouteStyle, StyleParamsList, dSpeed):
        """
        飞机区域巡逻控制（脚本控制）
        飞机id,巡逻区进入点,巡逻阵位样式,样式参数,巡航速度
        """
        return cls._make_action(locals())

    @classmethod
    def PlatAutoDodgeCtl(cls, nPlatId, bopen=0):
        """
        机动规避使能控制（脚本控制）
        飞机id,是否开启
        """
        return cls._make_action(locals())

    @classmethod
    def PlatAutoFireCtl(cls, nPlatId, bopen=0):
        """
        武器使能控制（脚本控制）
        飞机id,是否开启
        """
        return cls._make_action(locals())

    @classmethod
    def PlatFireCtl(cls, nPlatId: int, nAttackTrackId: int, nAttackPostion: Tuple[float, float, float], NumMissle: int):
        """
        武器发射控制(先发武器使能为False)
        飞机id,初始打击目标航迹ID或者打击位置点,武器类型,发弹数量
        """
        return cls._make_action(locals())

    @classmethod
    def PlatSelfDefenseCtl(cls, nPlatId: int, bopen: bool):
        """
        飞机自卫GR使能控制（脚本控制箔条和红外诱饵弹）
        飞机id,是否开启
        """
        return cls._make_action(locals())


class EWPlaneAction(BaseAction):
    model_type = 'EWPlane'

    @classmethod
    def PlatSixDoFCtl(cls, nPlatId, dYawRate, dPitchRate, dRollRate, dThrottle):
        """
        飞机六自由度控制
        飞机id,方位角,俯仰角,滚转角,油门
        角度为相对值,油门为绝对值
        """
        return cls._make_action(locals())

    @classmethod
    def PlatDirCtl(cls, nPlatId: int, pSpeed: float, pDirection: float):
        """
        飞机机动方向控制
        飞机id,机动速度,机动方向
        都是double标量,direction的范围为360°
        """
        return cls._make_action(locals())

    @classmethod
    # 纬度、经度、高度
    def PlatPosCtl(cls, nPlatId: int, pSpeed: float, pPostion: Tuple[float, float, float]):
        """
        飞机机动位置控制（脚本控制规划航路）
        飞机id,机动速度,位置点(纬度、经度、高度)
        """
        return cls._make_action(locals())

    @classmethod
    def PlatPatrolCtl(cls, nPlatId, sRouteStyle, StyleParamsList, dSpeed):
        """
        飞机任务区域控制（脚本控制）
        飞机id,任务区进入点,任务阵位样式,样式参数,巡航速度
        """
        return cls._make_action(locals())

    @classmethod
    def PlatFireCtl(cls, nPlatId: int, nAttackTrackId: int, nAttackPostion: Tuple[float, float, float], NumMissle: int):
        """
        武器发射控制(先发武器使能为False)
        飞机id,初始打击目标航迹ID或者打击位置点,武器类型,发弹数量
        """
        return cls._make_action(locals())


class ShipPlatAction(BaseAction):
    model_type = 'ShipPlat'

    @classmethod
    def PlatPatrolCtl(cls, nPlatId, sRouteStyle, StyleParamsList, dSpeed):
        """
        舰船区域巡逻指令（脚本控制）
        舰船id,巡逻区进入点,巡逻阵位样式,样式参数,巡航速度
        """
        return cls._make_action(locals())

    @classmethod
    def PlatAutoFireCtl(cls, nPlatId, bopen=0):
        """
        武器使能控制（脚本控制）
        飞机id,是否开启
        """
        return cls._make_action(locals())


class GroundPlatAction(BaseAction):
    model_type = 'GroundPlat'

    @classmethod
    def PlatDirCtl(cls, nPlatId: int, pDirection: float):
        """
        部署朝向控制
        平台id,机动方向（部署朝向）
        """
        return cls._make_action(locals())

    @classmethod
    # 纬度、经度、高度
    def PlatPosCtl(cls, nPlatId: int, pPostion: Tuple[float, float, float]):
        """
        部署位置
        平台id,位置点(纬度、经度、高度)
        """
        return cls._make_action(locals())

    @classmethod
    def PlatTgtCtl(cls, ):
        """
        武器控制
        平台id,目标航迹id（初始打击位置点的可以中途设置）
        """
        # todo 补充参数
        return cls._make_action(locals())

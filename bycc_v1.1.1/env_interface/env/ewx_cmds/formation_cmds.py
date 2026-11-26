from env_interface.env.ewx_cmds.base import BaseAction
from typing import Union, Dict, List,Tuple

class ReconFormAction(BaseAction):
    model_type = 'ReconForm'
    # todo 有一些参数定义名称并不合理，比如：DeterminedId 为List，这样的定义很容易混淆，这个要和马老师确认。
    @classmethod
    #
    def FormCtl(cls, nLeaderPlatId: int, nWingPlatList: List[int]):
        """
        指令含义：协同关系规划
        返回格式：主装备id,[从装备1id,从装备2id,从装备3id,从装备4id…]
        """
        return cls._make_action(locals())

    @classmethod
    def CoorTaskZoneCtl(cls, nEquipFormId: int, ConerPosition: List[float], nRadius: float):
        """
        指令含义：协同空域划分
        返回格式：主装备id,[装备id,区域中心(经纬高),区域半径]（脚本WsfZone）
        """
        return cls._make_action(locals())

    @classmethod
    def CoorTgtCtl(cls, nEquipFormId, DeterminedId:List):
        """
        指令含义：协同目标分配
        返回格式：[装备id,目标类型列表]   {"CoorTgtCtl"：[装备id:目标类型列表]},{"CoorTgtCtl"：[装备id:目标类型列表]}
        """
        return cls._make_action(locals())

    @classmethod
    def CoorLocateCtl(cls):
        """
        指令含义：协同定位规划
        返回格式：主装备id,定位方式（时差、交叉）,定位阵位样式,样式参数
        # todo 具体参数待定义
        """
        return cls._make_action(locals())

class JamFormAction(BaseAction):
    model_type = 'JamForm'

    @classmethod
    def FormCtl(cls, nLeaderPlatId: int, nWingPlatList: List[int]):
        """
        指令含义：协同关系规划
        返回格式：主装备id,[从装备1id,从装备2id,从装备3id,从装备4id…]
        """
        return cls._make_action(locals())

    @classmethod
    def CoorTgtCtl(cls, nEquipFormId: int, DeterminedId: List[int]):
        """
        指令含义：协同目标分配
        返回格式：主装备id,[装备id,目标id列表]
        """
        return cls._make_action(locals())

    @classmethod
    def CoorPosCtl(cls):
        """
        # todo 参数待定
        指令含义：协同阵位规划
        返回格式：主装备id,GR阵位样式,样式参数
        """
        return cls._make_action(locals())

class EWUAVFormAction(BaseAction):
    model_type = 'EWUAVForm'

    @classmethod
    def FormCtl(cls, nLeaderPlatId: int, nWingPlatList: List[int]):
        """
        指令含义：协同关系规划
        返回格式：主装备id,[从装备1id,从装备2id,从装备3id,从装备4id…]
        """
        return cls._make_action(locals())

    @classmethod
    def CoorTgtCtl(cls, nEquipFormId: int, DeterminedId: List[int]):
        """
        指令含义：协同目标分配
        返回格式：主装备id,[装备id,目标id列表]
        """
        return cls._make_action(locals())

    @classmethod
    def CoorTaskZoneCtl(cls,  nEquipFormId: int, ConerPosition: List[float], nRadius: float):
        """
        指令含义：协同任务区域规划
        返回格式：主装备id,[装备id,区域中心(经纬高),区域半径]
        """
        return cls._make_action(locals())

class EscortJamFormAction(BaseAction):
    """
    随队支援GR编队
    """
    model_type = 'EscortJamForm'

    @classmethod
    def CoorRelationCtl(cls, nLeaderPlatId: int, nWingPlatList: List[int]):
        """
        指令含义：协同GR关系规划
        返回格式：长机id,[飞机1id，飞机2id，飞机3id…]
        """
        return cls._make_action(locals())

    @classmethod
    def CoorPosCtl(cls, nLeaderPlatId: int, sRouteStyle: str, PlatInterval, VAngle):
        """
        指令含义：协同阵位规划
        返回格式：长机id,任务阵位(V字形)，阵位参数（平台间隔，相对角度）
        """
        return cls._make_action(locals())

    @classmethod
    def CoorWorkOnCtl(cls, nEquipId: int, bWorkOnAllow: bool):
        """
        指令含义：协同GR时机
        返回格式：[装备id,GR允许]
        """
        return cls._make_action(locals())

    @classmethod
    def CoorRouteCtl(cls,nLeaderPlatId: int, pSpeed: float, pPostion: Tuple[float, float, float]):
        """
        指令含义：协同机动航路规划
        返回格式：长机id,机动速度，位置点(纬度、经度、高度)
        """
        return cls._make_action(locals())

    @classmethod
    def PlatFireCtl(cls, nPlatId: int, nAttackTrackId: int, nAttackPostion: Tuple[float, float, float], NumMissle: int):
        """
        武器发射控制(先发武器使能为False)
        飞机id,打击目标航迹ID或者打击位置点,武器类型,发弹数量
        """
        return cls._make_action(locals())

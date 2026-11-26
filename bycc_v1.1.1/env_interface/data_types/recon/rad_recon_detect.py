# -*- coding: utf-8 -*-
from dataclasses import dataclass, field
from typing import List

from bycc.ai.feature.feature import OnehotFeature, PlainFeature, RangedFeature, VectorFeature, SpatialFeature, BinaryhotFeature

from env_interface.data_types import ewxEntity, ewxStateSpace, ewxEntityInfo


class RadReconDetectPara(ewxEntity):
    """
    雷达对抗ZC设备--目标感知结果组件
    """

    def __init__(self, entity_dict):
        super().__init__(entity_dict)


@dataclass
class RadReconDetectParaInfo(ewxEntityInfo):
    id: int
    ReconID: int
    RadarID: int
    RadarPlatID: int
    ATT: int
    PlatType: int
    DangerClass: int
    SignalState: int
    pRF: List[float]
    
    TargetID: int
    ESMType: float           # 类型,1-交叉定位，2-时差定位，3-交叉+时差定位
    bLocateSucceed: float           # 定位成功标志
    fRealTargetLon: float           # 真实位置X，单位：度
    fRealTargetLat: float           # 当次定位，单位：度
    fRealTargetHeight: float            # 当次定位，单位：m
    fTargetLon: float           # 当次定位假想X，单位：度
    fTargetLat: float           # 当次定位，单位：度
    fTargetHeight: float           # 当次定位，单位：m
    bEEPValid: float           # 定位误差椭圆是否有效
    X: float           # 定位性能误差椭圆中心X，单位：km
    Y: float           # 定位性能误差椭圆中心Y，单位：km
    A: float           	# 定位性能误差椭圆X轴，单位：km
    B: float           	# 定位性能误差椭圆Y轴，单位：km
    theta: float           	# 定位性能误差椭圆长轴相对X角度，0-180单位：度

    bReconed: bool            # 是否ZC到
    bIsInFrequenceRange: bool  # 是否满足频段要求
    bIsInAzVision: bool       # 是否满足方位视场
    bIsInELVision: bool       # 是否满足俯仰视场，bUseOTH为false时有效
    bIsInLOS: bool            # 是否满足视距视场，bUseOTH为false时有效
    bIsTerrainVisible: bool   # 是否满足地形通视
    bIsInSensity: bool        # 是否满足灵敏度要求
    bIsSignalRecognise: bool  # 信号能否识别
    AZ: float                 # 目标方位，单位：度
    EL: float                 # 目标俯仰，单位：度
    DIS: float                # 目标距离，单位：Km
    ReconMaxRange: float      # 对目标最大ZC距离，单位：Km
    DOAError: float           # 侧向误差，单位：度，ZC到有效
    LocationError: float      # 定位误差，单位：Km，有定位功能且ZC到有效
    CaptureProb: float        # 截获概率，范围：0~1，本截获概率仅指方位搜索时对脉冲雷达信号的截获概率
    fVisDist: float           # 视距，km
    bUseOTH: bool             # 是否是超视距计算
    fDectProb: float          # 检测概率，bUseOTH为true时有效
    fOTHDistMin: float        # 超视距近界，km，bUseOTH为true时有效
    equipTotalNum: float      # 从站时为1，只报自己的ZC结果参数
    bLocate: bool             # 是否具备定位能力

    @classmethod
    def get_entity_cls(cls):
        return RadReconDetectPara


@dataclass
class RadReconDetectParaStateSpace(ewxStateSpace):
    PlatType: PlainFeature
    DangerClass: PlainFeature
    SignalState: PlainFeature

    ESMType: PlainFeature           # 类型,1-交叉定位，2-时差定位，3-交叉+时差定位
    bLocateSucceed: PlainFeature           # 定位成功标志
    fRealTargetLon: PlainFeature           # 真实位置X，单位：度
    fRealTargetLat: PlainFeature           # 当次定位，单位：度
    fRealTargetHeight: PlainFeature            # 当次定位，单位：m
    fTargetLon: PlainFeature           # 当次定位假想X，单位：度
    fTargetLat: PlainFeature           # 当次定位，单位：度
    fTargetHeight: PlainFeature           # 当次定位，单位：m

    bEEPValid: PlainFeature  # 定位误差椭圆是否有效
    X: PlainFeature  # 定位性能误差椭圆中心X，单位：km
    Y: PlainFeature  # 定位性能误差椭圆中心Y，单位：km
    A: PlainFeature  # 定位性能误差椭圆X轴，单位：km
    B: PlainFeature  # 定位性能误差椭圆Y轴，单位：km
    theta: PlainFeature  # 定位性能误差椭圆长轴相对X角度，0-180单位：度

    bReconed: OnehotFeature  # 是否ZC到
    bIsInFrequenceRange: OnehotFeature  # 是否满足频段要求
    bIsInAzVision: OnehotFeature  # 是否满足方位视场
    bIsInELVision: OnehotFeature  # 是否满足俯仰视场，bUseOTH为false时有效
    bIsInLOS: OnehotFeature  # 是否满足视距视场，bUseOTH为false时有效
    bIsTerrainVisible: OnehotFeature  # 是否满足地形通视
    bIsInSensity: OnehotFeature  # 是否满足灵敏度要求
    bIsSignalRecognise: OnehotFeature  # 信号能否识别
    AZ: PlainFeature  # 目标方位，单位：度
    EL: PlainFeature  # 目标俯仰，单位：度
    DIS: PlainFeature  # 目标距离，单位：Km
    ReconMaxRange: PlainFeature  # 对目标最大ZC距离，单位：Km
    DOAError: PlainFeature  # 侧向误差，单位：度，ZC到有效
    LocationError: PlainFeature  # 定位误差，单位：Km，有定位功能且ZC到有效
    CaptureProb: PlainFeature  # 截获概率，范围：0~1，本截获概率仅指方位搜索时对脉冲雷达信号的截获概率
    fVisDist: PlainFeature  # 视距，km
    bUseOTH: OnehotFeature  # 是否是超视距计算
    fDectProb: PlainFeature  # 检测概率，bUseOTH为true时有效
    fOTHDistMin: PlainFeature  # 超视距近界，km，bUseOTH为true时有效
    equipTotalNum: PlainFeature  # 从站时为1，只报自己的ZC结果参数
    bLocate: OnehotFeature  # 是否具备定位能力







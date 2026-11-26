import math
from dataclasses import dataclass

from geographiclib.geodesic import Geodesic
from geopy.distance import geodesic

from env_interface.const import *


@dataclass
class Position:
    lat: float
    lon: float
    alt: float


@dataclass()
class RoutePoint(Position):
    speed: float = 600


# 计算球面距离等的函数
class pos:
    def __init__(self,lat,lon):
        self.fLat = lat
        self.fLon = lon

def in_jam_angle(enemy, rjam, init_angle):
    """
    判断雷达与目标的角度是否合适
    """
    azi = azimuth_calculator([rjam.fLat, rjam.fLon], [enemy.fLat, enemy.fLon])

    return init_angle-45 < azi < init_angle+45


def in_jam_range(enemy, rjam):
    """
    判断目标是否在雷达的范围之内
    """
    dis = dis_calculator([rjam.fLat, rjam.fLon], [enemy.fRealTargetLat, enemy.fRealTargetLon])
    # todo 从约束接口获取GR距离
    return dis < MY_JAM_DIST_RANGE


def in_jam_rf(enemy_radar, rjam):
    """
    判断目标是否在雷达的频率之内
    """
    return True
    # rf, band = rjam.fRF, rjam.fJamSigBW
    # # todo 从约束接口获取雷达频率
    rf = rjam.fRF
    band = MY_JAM_FJAMSIGBW

    radar_rf = enemy_radar.pRF[0]

    return (rf - band / 2) < radar_rf < (rf + band / 2)


def cal_WorkAglRng(source, target):
    """
    """
    # el = pitch_calculator([source.fLat, source.fLon, source.fHeight], [target.fLat, target.fLon, target.fHeight])
    el = pitch_calculator([source.fLat, source.fLon, getattr(source, '_fHeight', 0)], [target.fLat, target.fLon, target.fHeight])
    az = azimuth_calculator([source.fLat, source.fLon], [target.fLat, target.fLon])
    # return dict(dStartAz=az, dEndAz=az, dStartEl=el, dEndEl=el)
    return az, el


def cal_JamWorkFregRng(rjam, enemy_radar):
    # return dict(nRJamId=rjam.id, dTarFreMin=enemy_radar.fRF, dTarFreMax=enemy_radar.fRF)
    return enemy_radar.fRF


def normalizer(value, scale):
    """
    标准化函数
    """
    return value / scale


def dis_calculator(p1, p2):
    """
        p1 到 p2 的距离
        输入顺序为纬经度
    """
    dis = geodesic(p1, p2).km
    return dis

def dis_calculator_of_meter(p1, p2):
    """
        p1 到 p2 的距离
        输入顺序为纬经度
    """
    dis = geodesic(p1, p2).m
    return dis


def azimuth_calculator(p1, p2):
    """
        p1 到 p2 的方位角，注意到和 p2 到 p1 的方位角之间存在差值
        输入顺序为纬经度
        输出单位为角度
    """
    azimuth = Geodesic.WGS84.Inverse(*p1, *p2)['azi1']
    return azimuth

def azimuth_calculator_unit(p1, p2):
    """
        p1 到 p2 的方位角，注意到和 p2 到 p1 的方位角之间存在差值
        输入为具有fLat, fLon属性的实体
        输出单位为角度
    """
    azimuth = azimuth_calculator((p1.fLat, p1.fLon), (p2.fLat, p2.fLon))
    return azimuth

def azimuth_calculator_target(p1, p2):
    """
        p1 到 p2 的方位角，注意到和 p2 到 p1 的方位角之间存在差值
        输入p1为具有fLat, fLon属性的实体
        输入p1为具有fRealTargetLat, fRealTargetLon属性的实体
        输出单位为角度
    """
    azimuth = azimuth_calculator((p1.fLat, p1.fLon), (p2.fRealTargetLat, p2.fRealTargetLon))
    return azimuth


def pitch_calculator(p1, p2):
    """
        p1 到 p2 的俯仰角
        输入顺序为纬经高（千米）
        输出单位为角度
    """
    relative_height = p2[2] - p1[2]
    dis = dis_calculator(p1[:2], p2[:2])
    pitch = math.atan2(relative_height, dis) / math.pi * 180
    return pitch


def to_str(s):
    if isinstance(s, bytes):
        return s.decode()
    return s


if __name__ == '__main__':
    # print(dis_calculator([0, 0], [3, 4]))
    print(azimuth_calculator([0, 0], [3, 4]))
    print(pitch_calculator([0, 0, 0], [3, 4, 5]))

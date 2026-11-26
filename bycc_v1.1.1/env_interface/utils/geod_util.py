import re
import sys
import time

from bycc.common.data_types import Position
from env_interface.const import geod

from env_interface.data_types import PlatParaInfo
from env_interface.data_types.recon.rad_recon_detect import RadReconDetectParaInfo


def distance_of_position(p1: Position, p2: Position) -> float:
    g_res = geod.inv(p1.x, p1.y, p2.x, p2.y)
    return round(g_res[2], 2)

def distance_of_plat(p1: PlatParaInfo, p2: RadReconDetectParaInfo) -> float:
    g_res = geod.inv(p1.fLon, p1.fLat, p2.fRealTargetLon, p2.fRealTargetLat)
    return round(g_res[2], 2)

def position_of_heading(p: Position, heading: float, distance: float=1000) -> Position:
    g_res = geod.fwd(p.x, p.y, heading, distance)
    return Position(g_res[0], g_res[1], p.z)

def sonic_velocity(altitude: float) -> float:
    # 计算声速
    # 声速公式: c = 1449.2 + 4.6 * T - 0.055 * T^2 + 1.39 * (10 ** -3) * H
    # T = 温度(摄氏度), H = 深度(米)
    # 假设温度为25摄氏度, 深度为0米
    temperature = 25
    depth = altitude
    return 1449.2 + 4.6 * temperature - 0.055 * temperature ** 2 + 1.39 * (10 ** -3) * depth


def dms2decimal(dms_string: str) -> float:
    matches = re.findall(r"([\d.]+|[NSEWnsew])", dms_string)
    degrees, minutes, seconds = map(float, matches[:3])
    direction = matches[3]
    decimal_degrees = degrees + minutes / 60.0 + seconds / 3600.0
    if direction in ('S', 'W', 's', 'w'):
        decimal_degrees = -decimal_degrees
    return decimal_degrees

def dms_pair_2_position(dms_string: str) -> Position:
    lat, lon = dms_string.split(' ')
    lat = dms2decimal(lat)
    lon = dms2decimal(lon)
    return lat, lon

if __name__ == '__main__':
    print('dsa')
    func_name = sys.argv[1]
    if func_name == 'dms2decimal':
        dms_string = sys.argv[2]
        degrees = dms2decimal(dms_string)
        print(degrees)
    sys.stdout.flush()
    time.sleep(3)
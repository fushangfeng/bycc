from pyproj import Geod

geod = Geod(ellps="WGS84")
"""
模拟约束接口
"""

# todo 约束数据 ，后期需要从数据库取约束数据
# GR雷达工作频率
MY_JAM_FRF = 200
# GR雷达脉宽
MY_JAM_FJAMSIGBW = 100
# 最大GR距离
MY_JAM_DIST_RANGE = 400

# Jammer的最大GR目标数量
X_KU_JAMMER_MaxJamTargetNum = 4
RCL670_JAMMER_MaxJamTargetNum = 2

# Jammer的GR目标方位视场
RCL670_JAMMER_azimuth_field_of_view = 30
X_KU_JAMMER_azimuth_field_of_view = 30

# Jammer的驻守角度范围
X_KU_JAMMER_azimuth_fix_view = 90

# 雷达最大TC距离
RADAR_MAX_DETECT_RANGE = 500

METER_OF_NMI = 1852

JAMMER_LIMIT_ANGLE_RANGE = {
    7: [20, 110], 8: [20, 110], 9: [20, 110],
    4: [10, 100], 5: [45, 135], 6: [70, 160],
    # 7: [10, 100], 8: [10, 100], 9: [10, 100],
    # 4: [80, 170], 5: [80, 170], 6: [80, 170],
}

BLOCKED_FREQ_AREA = [{"SilentArea": [[35.5, 123, 100], [35.5, 123.5, 100], [35, 123, 100], [35, 123.5, 100]],
                      "dBlockedRFMin": 0, "dBlockedRFMax": 120}]

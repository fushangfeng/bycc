"""pysim 常量配置"""

Training = False  # 是否为训练模式

# 数据换算
PI = 3.1415
Mile2Kilometre = 1.852  # 海里换算为公里

# 功能屏蔽
IgnoreFireInterval = False  # 屏蔽开火间隔
IgnoreFireChannel = True  # 屏蔽开火通道限制
IgnoreTakeOffInterval = False  # 屏蔽起飞间隔
IgnoreRunWayNum = False  # 屏蔽跑道数量对起飞的限制

# 指令优先级
MoveFirst = True  # 移动指令优先于攻击指令，否则攻击指令优先于移动指令

# 自动返航
AutoReturn = True
AutoReturnPercent = 0.3  # 自动返航剩余飞行时间比例

# 自动攻击
AutoAttack = False

# 经纬度每度大概为 110000米
CoordinateFactor = 110000

# 单位attack打印的开关
PRINT_ATTACK = False

# 单位detect打印的开关
PRINT_DETECT = False

# weapon 的 hit 概率的开关
PRINT_HIT = False

# airport单位打印的开关
PRINT_AIRPORT = False

# 生成单位重合时，X，Y轴的随机因子
X_RANDOM = 10000
Y_RANDOM = 10000

# 预留的返航时间 单位s   总返航时间： 与返航位置距离/速度 + 预留的返航时间
RESERVE_TIME = 60

# 日志等级和日志路径，支持DEBUG/INFO/WARNING/ERROR/CRITICAL
LOG_PATH = None
LOG_LEVEL = "INFO"

# 是否加入导弹发射角度限定的逻辑
FIRE_ANGLE_LIMIT = True

# 是否加入飞机姿态pose的逻辑
USE_AIR_UNIT_POSE = True


class UnitDefaultValue:
    """默认值，对于不在配置中的int类型数据，默认值一律用-1表示"""

    Speed = 0.0
    Direction = [1, 0, 0]
    RunningTime = 3600 * 4  # 默认最大运行时间，单位s
    Altitude = 0.0
    Sensors = {}
    Weapons = {}
    Aircrafts = []
    Health = 1  # 用来填充武器的血量，仅限血量为1的单位
    FireChannel = 5  # 火力通道
    FireInterval = 20  # 导弹发射间隔,单位s
    RunwayNum = 4  # 跑道数量，默认航母4个弹射器，起飞仅和弹射器关联
    TakeOffInterval = 90  # 起飞间隔
    WeaponFlightTimeIncreaseFactor = 1.2  # 武器飞行时间增加被率
    BlastRadius = 100  # [DEV]: 武器爆炸半径，在这个区间的单位被毁


# 打开zc项目对环境的特定配置
ZCCustom = True

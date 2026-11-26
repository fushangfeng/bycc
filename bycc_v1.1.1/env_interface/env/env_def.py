
class Side:
    RED = 1
    BLUE = 2
    OTHERS = 0  # ATT为0的暂时归为中立单位


class EquipmentType:
    RADAR_STATION = '610_RADAR'  # 610A预警雷达
    HQ_9B_TTR = 'HQ-9B_TTR'  # HQ-9B火控雷达
    HQ_9B_LAUNCHER = 'HQ-9B_LAUNCHER'  # HQ-9B导弹发射车
    RCT321A_JAMMER_STATION = 'RCT321A_JAMMER_STATION'  # rct321a数据链GR设备
    TV_JAMMER_STATION = 'TV_JAMMER_STATION'  # tv jammer
    RCL671B_JAMMER_STATION = 'RCL671B_JAMMER_STATION'  # rcl671b电子对抗装备
    RCZ901_JAMMER_STATION = 'RCZ901_JAMMER_STATION'  # RCZ901高功率微波GR设备
    GPS_JAM_AIR = 'JAM_AIR'  # GPSGR站
    GPS_AIR = 'GPS_AIR'  # GPS卫星
    PROTECT_TARGET = 'PROTECT_TARGET'  # 保护目标
    EA_18G = 'EA-18G'  # EA-18G GR机
    E_2D = 'E-2D'
    F_35 = 'F-35'


"""
// 工作状态
enum Enum_WorkState {
    Enum_WorkState_0 = 0;// 关机
    Enum_WorkState_1 = 1;// 开机
    Enum_WorkState_2 = 2;// GR
    Enum_WorkState_3 = 3;// 搜索
    Enum_WorkState_4 = 4;// ZC
    Enum_WorkState_5 = 5;// 跟踪
    Enum_WorkState_6 = 6;// 静默
    Enum_WorkState_7 = 7;// 预留
    Enum_WorkState_8 = 8;// 预留
    Enum_WorkState_9 = 9;// 预留
    Enum_WorkState_255 = 255;// 无效值
}
"""


"""
//! 生存状态
enum Enum_SurvivalState 
{
    Enum_SurvivalState_0 = 0,	//! 正常
    Enum_SurvivalState_1 = 1,	//! 被摧毁
    Enum_SurvivalState_2 = 2,	//! 未知
    Enum_SurvivalState_3 = 3,	//! 预留
    Enum_SurvivalState_255 = 255,	//! 无效值
};
"""


"""
enum Enum_PlatType	
{
	//ePlatType_default = 0,
	//m_Airborne=1,      //机载
	//m_Shipboard,     //舰载
	//m_Groundboard,   //地面固定

	Enum_PlatType_0 = 0,//! 不明
	Enum_PlatType_1,    //! 地面固定
	Enum_PlatType_2,    //! 地面移动,火车
	Enum_PlatType_3,    //! 舰(船)载
	Enum_PlatType_4,    //! 潜艇载
	Enum_PlatType_5,    //! 弹载
	Enum_PlatType_6,    //! 飞机载
	Enum_PlatType_7,    //! 直升机载
	Enum_PlatType_8,    //! 无人机载
	Enum_PlatType_9,    //! 卫星载
	Enum_PlatType_10,   //! 气球载
	Enum_PlatType_11,   //! 车载
	Enum_PlatType_12,   //! 便携,背负
	Enum_PlatType_13,   //! 飞船载
	Enum_PlatType_14,   //! 浮标
	Enum_PlatType_15,   //! 飞艇
	Enum_PlatType_16,   //! 预留1
	Enum_PlatType_17,   //! 预留2
	Enum_PlatType_255 = 255,   //! 无效值
};
#endif //Enum_PlatType_DEF
"""


"""
enum Enum_SignalState 
{	// 信号活动情况
	Enum_SignalState_0 = 0,	// 未知
	Enum_SignalState_1 = 1,	// 信号消失
	Enum_SignalState_2 = 2,	// 信号出现
	Enum_SignalState_3 = 3,	// 信号跟踪中断
	Enum_SignalState_4 = 4,	// 预留
	Enum_SignalState_255 = 255,	// 无效值
};
"""


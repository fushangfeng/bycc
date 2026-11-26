/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.1		按照年(个数位)月日组合的方式	**
**版    本:	2015.04.01  zoubz修改											**
*************************************************************************/

#ifndef MEN_STRUCT_MACROS
#define MEN_STRUCT_MACROS

//////////////////////////////////////////////////////////////////////////
#ifndef SW_Delete
#define	SW_Delete(p)		{if(NULL != (p)){delete[] (p); (p) = NULL;}}
#endif
//////////////////////////////////////////////////////////////////////////
// windows and unix
#ifndef SW_Malloc_Char
#define	SW_Malloc_Char(pSrc,pDest)  { int nLen = 0; \
	if( NULL != pSrc && ( nLen = strlen(pSrc) ) > 0 ) \
	{ if (pDest) \
	{ delete [] pDest; \
      pDest = NULL;	} \
    pDest = new char[nLen+1];\
	memset(pDest,0,nLen+1);\
	memcpy(pDest,pSrc,sizeof(char) * (nLen + 1) );} }
#endif

#ifndef SW_Free_Char
#define	SW_Free_Char(p)	SW_Delete(p)
#endif

#ifndef SW_Malloc_Struct
#define SW_Malloc_Struct(T,pSrc,pDest,nSrcCount,nDestCount) {nDestCount = nSrcCount;\
	if(nDestCount > 0 && NULL != pSrc) \
	{if (pDest) \
	{ delete [] pDest; \
	pDest = NULL;	} \
    pDest = new T[nDestCount];\
	memset(pDest,0,sizeof(T)*nDestCount);\
	for (int i=0; i < nDestCount; i++) \
	{pDest[i] = pSrc[i];}}}
#endif

#ifndef SW_Malloc_Int
#define SW_Malloc_Int(pSrc,pDest,nSrcCount,nDestCount)  SW_Malloc_Struct(int,pSrc,pDest,nSrcCount,nDestCount)
#endif

#ifndef SW_Malloc_Float
#define SW_Malloc_Float(pSrc,pDest,nSrcCount,nDestCount)  SW_Malloc_Struct(float,pSrc,pDest,nSrcCount,nDestCount)
#endif



/*************************************************************
*                        枚举类型                            *
*************************************************************/
#pragma pack(1)

namespace DKDMS{//namespace DMS start zm20170912

#ifndef TYPEDEFINE
#define TYPEDEFINE
enum Enum_RegionSort {			// 区域应用类型（X67课题中定义）	
    Enum_RegionSort_0 = 0,		// 典型作战能力
	Enum_RegionSort_1 = 1,		// 部队集结区
	Enum_RegionSort_2 = 2,		// 部队部署区
	Enum_RegionSort_3 = 3,		// 机场
	Enum_RegionSort_4 = 4,		// 海区
	Enum_RegionSort_5 = 5,		// 阵地
	Enum_RegionSort_6 = 6,		// 区域
	Enum_RegionSort_7 = 7,		// 作战区域
	Enum_RegionSort_8 = 8,		// 任务分界
	Enum_RegionSort_9 = 9,		// 战斗分界线
	Enum_RegionSort_10 = 10,	// 任务分界线
	Enum_RegionSort_11 = 11,	// 警戒线
	Enum_RegionSort_12 = 12,	// 行动线
	Enum_RegionSort_13 = 13,	// 目标区域
	Enum_RegionSort_14 = 14,	// GR范围
	Enum_RegionSort_15 = 15,	// ZC范围
	Enum_RegionSort_16 = 16,	// 禁飞区域 colin add 2011-8-2
	Enum_RegionSort_17 = 17,	// 无人机任务飞行区 colin add 2011-8-2
	Enum_RegionSort_18 = 18,    // 飞行走廊 colin add 2011-8-10
	Enum_RegionSort_19 = 19,    // 保护区域 colin add 2011-8-10
	Enum_RegionSort_20 = 20,    // ZC区域 colin add 2011-8-10
	Enum_RegionSort_21 = 21,    // GR区域 colin add 2011-8-10
	Enum_RegionSort_22 = 22,    // 我方防空区域 colin add 2011-11-29
	Enum_RegionSort_23 = 23,    // 敌方防空区域 colin add 2011-11-29
	Enum_RegionSort_24 = 24,    // 对海TC区 colin add 2011-12-27
	Enum_RegionSort_25 = 25,    // 对空TC区 colin add 2011-12-27
	Enum_RegionSort_26 = 26,    // 对海攻击区 colin add 2011-12-27
	Enum_RegionSort_27 = 27,    // 对空攻击区 colin add 2011-12-27
	Enum_RegionSort_28 = 28,    // 预留1
	Enum_RegionSort_29 = 29,    // 预留2
	Enum_RegionSort_255 = 255,    // 无效值
};

enum Enum_RJamType 
{	// 雷达GR方式
	Enum_RJamType_0 = 0,	// 未知
	Enum_RJamType_1 = 1,	// 压制GR
	Enum_RJamType_2 = 2,	// 转发式欺骗GR
	Enum_RJamType_3 = 3,    // 密集假目标欺骗
	Enum_RJamType_4 = 4,	// 预留1
	Enum_RJamType_5 = 5,	// 预留2
	Enum_RJamType_255 = 255,	//无效值
};

enum Enum_JamMode 
{	    // GR样式
	Enum_JamMode_0 = 0,	//压制GR
	Enum_JamMode_1 = 1,	//欺骗GR，假目标
	Enum_JamMode_2 = 2,	//欺骗GR，交叉眼
	Enum_JamMode_3 = 3,	//欺骗GR，交叉极化
	Enum_JamMode_4 = 4,	//欺骗GR，弦外有源/空射诱饵
	Enum_JamMode_5 = 5,	//扩展用
	Enum_JamMode_6 = 6,	//扩展用
	Enum_JamMode_7 = 7,	//扩展用
	Enum_JamMode_255 = 255,	//无效值
};

enum Enum_RFT 
{	// 射频类型
	Enum_RFT_0 = 0,	// 未知
	Enum_RFT_1 = 1,	// 单一射频
	Enum_RFT_2 = 2,	// 射频可选择
	Enum_RFT_3 = 3,	// 频率分集
	Enum_RFT_4 = 4,	// 频率编码
	Enum_RFT_5 = 5,	// 射频捷变
	Enum_RFT_6 = 6,	// 射频参差
	Enum_RFT_7 = 7,	// 连续波频率调制
	Enum_RFT_8 = 8,	// 连续波编码调制
	Enum_RFT_9 = 9,	// 连续波噪声调制
	Enum_RFT_10 = 10,	// 脉内频率编码
	Enum_RFT_11 = 11,	// 预留1
	Enum_RFT_12 = 12,	// 预留2
	Enum_RFT_255 = 255,	// 无效值
};

enum Enum_PRIT 
{	// 脉冲重复间隔类型
	Enum_PRIT_0 = 0,	// 未知
	Enum_PRIT_1 = 1,	// 脉冲重复间隔固定
	Enum_PRIT_2 = 2,	// 脉冲重复间隔可选择
	Enum_PRIT_3 = 3,	// 脉冲重复间隔抖动
	Enum_PRIT_4 = 4,	// 脉冲重复间隔捷变
	Enum_PRIT_5 = 5,	// 脉冲重复间隔参差
	Enum_PRIT_6 = 6,	// 脉冲重复间隔编码
	Enum_PRIT_7 = 7,	// 脉冲重复间隔滑变
	Enum_PRIT_8 = 8,	// 预留1
	Enum_PRIT_255 = 255,	// 无效值
};

enum Enum_POT 
{	// 极化类型
	Enum_POT_0 = 0,	// 未知
	Enum_POT_1 = 1,	// 圆极化
	Enum_POT_2 = 2,	// 垂直极化
	Enum_POT_3 = 3,	// 水平极化
	Enum_POT_4 = 4,	// 斜极化
	Enum_POT_5 = 5,	// 极化可选择
	Enum_POT_6 = 6,	// 极化编码
	Enum_POT_7 = 7,	// 极化捷变
	Enum_POT_8 = 8,	// 预留1
	Enum_POT_9 = 9,	// 预留2
	Enum_POT_255 = 255,	//无效值
};

enum Enum_AreaType 
{	// 输入区域类型
	Enum_AreaType_0 = 0,	// 输入雷达位置变化区域
	Enum_AreaType_1 = 1,	// 输入目标位置变化区域
	Enum_AreaType_2 = 2,	// 输入GR机位置变化区域
	Enum_AreaType_3 = 3,	// 输入的位置既是GR机位置也是目标位置
	Enum_AreaType_4 = 4,	// 未知
	Enum_AreaType_5 = 5,	// 预留
	Enum_AreaType_255 = 255,//无效值
};


#ifndef Enum_ATT_DEF
#define Enum_ATT_DEF 
//! 敌我属性
enum Enum_ATT {	
	Enum_ATT_0 = 0,	//! 无报告
	Enum_ATT_1 = 1,	//! 我方 //red
	Enum_ATT_2 = 2,	//! 敌方 //blue
	Enum_ATT_3 = 3,	//! 友方
	Enum_ATT_4 = 4,	//! 中立
	Enum_ATT_5 = 5,	//! 敌方盟国
	Enum_ATT_6 = 6,	//! 敌方友邦
	Enum_ATT_7 = 7,	//! 不明
	Enum_ATT_8 = 8, //! 民用电台
	Enum_ATT_9 = 9, //! 预留1
	Enum_ATT_10 = 10,	//! 预留2
	Enum_ATT_255 = 255,	//! 无效值
};
#endif

#ifndef Enum_FlyPosType_DEF
#define Enum_FlyPosType_DEF 
//! 航迹点类型
enum Enum_FlyPosType 
{
	Enum_Out = 0,	//! 出航
	Enum_Cruise = 1,	//! 巡航
	Enum_Back = 2,	//! 返航
	Enum_FlyPosType_UnKnown = 3,//! 未知
	Enum_FlyPosType_NoUse = 255,//! 无效值
};
#endif

enum Enum_GroundTargetPlatType 
{	// 地面目标平台类型
	Enum_GroundTargetPlatType_0 = 0,	// 海军通信站
	Enum_GroundTargetPlatType_1 = 1,	// 预警机地面接收站
	Enum_GroundTargetPlatType_2 = 2,	// 飞机地面引导站
	Enum_GroundTargetPlatType_3 = 3,	// 地面雷达站
	Enum_GroundTargetPlatType_4 = 4,	// 机场
	Enum_GroundTargetPlatType_5 = 5,	// 建筑
	Enum_GroundTargetPlatType_6 = 6,	// 雷达阵地
	Enum_GroundTargetPlatType_7 = 7,	// 地导阵地
	Enum_GroundTargetPlatType_8 = 8,	// 指挥所
	Enum_GroundTargetPlatType_9 = 9,	// 未知
	Enum_GroundTargetPlatType_10 = 10,	// 预留1
	Enum_GroundTargetPlatType_11 = 11,	// 预留2
	Enum_GroundTargetPlatType_255 = 255,	// 无效值
};

enum Enum_GroundTgtType 
{	// 固定目标的类型
	Enum_GroundTgtType_0 = 0,
	Enum_GroundTgtType_1 = 1,	// 点目标
	Enum_GroundTgtType_2 = 2,	// 面目标
	Enum_GroundTgtType_3 = 3,	// 未知
	Enum_GroundTgtType_4 = 4,	// 预留1
	Enum_GroundTgtType_5 = 5,	// 预留2
	Enum_GroundTgtType_255 = 255,	// 无效值
};

enum Enum_JAMCtrl 
{	// GR控制
	Enum_JAMCtrl_0 = 0,	// 关
	Enum_JAMCtrl_1 = 1,	// 开
	Enum_JAMCtrl_2 = 2,	// 侦查
	Enum_JAMCtrl_3 = 3,	// 未知
	Enum_JAMCtrl_4 = 4,	// 预留
	Enum_JAMCtrl_255 = 255,	// 无效值
};


#ifndef Enum_manoeuverState_DEF
#define Enum_manoeuverState_DEF 
enum Enum_manoeuverState 
{	// 作战行动各阶段的状态
	Enum_manoeuverState_0 = 0,	// 起飞
	Enum_manoeuverState_1 = 1,	// 巡航
	Enum_manoeuverState_2 = 2,	// 返航
	Enum_manoeuverState_3 = 3,	// 待战
	Enum_manoeuverState_4 = 4,	// 空战
	Enum_manoeuverState_5 = 5,	// 毁损
	Enum_manoeuverState_6 = 6,	// 未起飞
	Enum_manoeuverState_7 = 7,	// 任务执行中
	Enum_manoeuverState_8 = 8,	// 盘旋
	Enum_manoeuverState_9 = 9,	// 护航
	Enum_manoeuverState_10 = 10,	// 未知
	Enum_manoeuverState_11 = 11,	// 预留
	Enum_manoeuverState_255 = 255,	// 无效值
};
#endif

#ifndef Enum_AircraftSort_DEF
#define Enum_AircraftSort_DEF

//! 飞机类型
enum Enum_AircraftSort 
{
	Enum_AircraftSort_0 = 0,	//! 歼击机
	Enum_AircraftSort_1 = 1,	//! 强击机
	Enum_AircraftSort_2 = 2,	//! 轰炸机
	Enum_AircraftSort_3 = 3,	//! 舰载机
	Enum_AircraftSort_4 = 4,	//! 预警机
	Enum_AircraftSort_5 = 5,	//! 电子战飞机
	Enum_AircraftSort_6 = 6,	//! 无人机载欺骗平台
	Enum_AircraftSort_7 = 7,	//! 未知
	Enum_AircraftSort_8 = 8,	//! 预留
	Enum_AircraftSort_9 = 9,	//! 预留
	Enum_AircraftSort_10 = 10,	//! 预留
	Enum_AircraftSort_11 = 11,	//! 预留
	//zm 20160728
	Enum_AircraftSort_20 = 20,  //! 导弹
};
#endif

#ifndef Enum_quitReason_DEF
#define Enum_quitReason_DEF 
enum Enum_quitReason 
{	// 退出战斗原因
	Enum_quitReasonDestroy = 0,	// 自毁
	Enum_quitReasonAA = 1,	// 空空拦截
	Enum_quitReasonGA = 2,	// 地空拦截
	Enum_quitReasonUnKnown = 3,	// 未知
	Enum_quitReasonNoUse = 255,	// 无效值
};
#endif

enum Enum_RadarSort 
{	// 雷达类别
	Enum_RadarSort_0 = 0,	// 警戒雷达
	Enum_RadarSort_1 = 1,	// （机载）预警雷达
	Enum_RadarSort_2 = 2,	// 防空制导雷达
	Enum_RadarSort_3 = 3,	// 火控雷达
	Enum_RadarSort_4 = 4,	// 合成孔径雷达
	Enum_RadarSort_5 = 5,	// 导引头
	Enum_RadarSort_6 = 6,	// 保留2
	Enum_RadarSort_255 = 255,	// 无效值
};

//截获方式
enum Enum_InterceptMode
{
	Enum_InterceptMode_Auto = 0,	//自动
	Enum_InterceptMode_Man,			//手动
};

#ifndef Enum_PCM_DEF
#define Enum_PCM_DEF 
enum Enum_PCM
{//脉内调制类型           //CJJ
	Enum_PCM_0 =0,  //未知
	Enum_PCM_1 =1,	// 固定数，无调制
	Enum_PCM_2 =2,	// 线性频率调制
	Enum_PCM_3 =3,	// 相位编码调制
	Enum_PCM_4 =4,	// 频率编码调制     （暂不用）
	Enum_PCM_5 =5,  // 噪声调制     ？？（暂不用） 
	Enum_PCM_6 = 6,	// 保留1
	Enum_PCM_7 = 7,	// 保留2
	Enum_PCM_255 = 255,	// 无效值
};
#endif

enum Enum_SignalState 
{	// 信号活动情况
	Enum_SignalState_0 = 0,	// 未知
	Enum_SignalState_1 = 1,	// 信号消失
	Enum_SignalState_2 = 2,	// 信号出现
	Enum_SignalState_3 = 3,	// 信号跟踪中断
	Enum_SignalState_4 = 4,	// 预留
	Enum_SignalState_255 = 255,	// 无效值
};

//! 生存状态
enum Enum_SurvivalState 
{
	Enum_SurvivalState_0 = 0,	//! 正常
	Enum_SurvivalState_1 = 1,	//! 被摧毁
	Enum_SurvivalState_2 = 2,	//! 未知
	Enum_SurvivalState_3 = 3,	//! 预留
	Enum_SurvivalState_255 = 255,	//! 无效值
};

#ifndef Enum_TaskType_DEF
#define Enum_TaskType_DEF 
enum Enum_TaskType {	// 航迹点任务类型
	Enum_TaskType_0 = 0,	// 未指定
	Enum_TaskType_1 = 1,	// 攻击
	Enum_TaskType_2 = 2,	// 预留
	Enum_TaskType_3 = 3,	// 预留
	Enum_TaskType_255 = 255,	// 无效值
};
#endif

//! 作战模式
enum Enum_WorkMode 
{
	Enum_WorkMode_0 = 0,	//! 受控
	Enum_WorkMode_1 = 1,	//! 自主
	Enum_WorkMode_2 = 2,	//! 未知
	Enum_WorkMode_3 = 3,	//! 预留
	Enum_WorkMode_255 = 255,	//! 无效值
};

//! 工作状态
enum Enum_WorkState 
{
	Enum_WorkState_0 = 0,	//! 关机
	Enum_WorkState_1 = 1,	//! 开机
	Enum_WorkState_2 = 2,	//! GR
	Enum_WorkState_3 = 3,	//! 搜索（反辐射导引头）/ZC
	Enum_WorkState_4 = 4,	//! 截获（雷达）/引爆（反辐射导引头）
	Enum_WorkState_5 = 5,	//! 跟踪（雷达）/静默
	Enum_WorkState_6 = 6,	//! 未知
	Enum_WorkState_7 = 7,	//! 预留
	Enum_WorkState_255 = 255,	//! 无效值
};

#ifndef Enum_WaveType_DEF
#define Enum_WaveType_DEF 
enum Enum_WaveType {	                // 目标起伏类型
	Enum_WaveType_0 = 0,	            // 不考虑起伏特性
	Enum_WaveType_1 = 1,	            // Swerling第一类起伏模型
	Enum_WaveType_2 = 2,	            // Swerling第二类起伏模型
	Enum_WaveType_3 = 3,                // Swerling第三类起伏模型
	Enum_WaveType_4 = 4,	            // Swerling第四类起伏模型
	Enum_WaveType_5 = 5,	// 未知
	Enum_WaveType_6 = 6,	// 预留
	Enum_WaveType_7 = 7,	// 预留
	Enum_WaveType_255 = 255,	// 无效值
};
#endif

enum Enum_AssCalcControl 
{   //辅助计算控制报文信息
	Enum_AssCalcControl_0 = 0,    //开始
	Enum_AssCalcControl_1 = 1,    //
	Enum_AssCalcControl_255 = 255,    //无效值
};

#endif

//重新定义 20170401 zm
#ifndef Enum_PlatType_DEF
#define Enum_PlatType_DEF 
//! 平台类型
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

enum Enum_WorkOnCtrl		// 开关机控制
{	
	Enum_WorkOnCtrl_0 = 0,	// 关机
	Enum_WorkOnCtrl_1 = 1,	// 开机
	Enum_WorkOnCtrl_2 = 2,	// 未知
	Enum_WorkOnCtrl_255 = 255,	// 无效值
};

#ifndef Enum_JamRlt_DEF
#define Enum_JamRlt_DEF 
enum Enum_JamRlt	// GR结果
{	
	Enum_JamRlt_0 = 0,	// GR无法工作
	Enum_JamRlt_1 = 1,	// GR但能工作
	Enum_JamRlt_2 = 2,	// 正常工作	
	Enum_JamRlt_3 = 3,	// 未知
	Enum_JamRlt_255 = 255,	// 无效值
};
#endif //Enum_JamRlt_DEF

enum Enum_SendRevType		// 发射机和接收机工作类型
{	    
	Enum_SendRevType_0 = 0,	// 即发射又接收
	Enum_SendRevType_1 = 1,	// 只发射
	Enum_SendRevType_2 = 2,	// 只接收
	Enum_SendRevType_3 = 3,	// 未知
	Enum_SendRevType_255 = 255,	// 无效值
};

#ifndef EEquipKind_DEF
#define EEquipKind_DEF 
enum EEquipKind
{
	et_Unknown=0,
	et_Radar=1,
	et_Radio,
	et_Plat,
	et_RadarJamer,
	et_RadioJamer,
	et_RadarScout,
	et_RadioScout,
	et_Weapon,
	et_CalcMode = 9,
};
#endif //EEquipKind_DEF

enum Enum_Priority			//保护优先级(0-9，9最高)	
{
	Enum_Priority_0 = 0,	//0级
	Enum_Priority_1,
	Enum_Priority_2,
	Enum_Priority_3,
	Enum_Priority_4,
	Enum_Priority_5,
	Enum_Priority_6,
	Enum_Priority_7,
	Enum_Priority_8,
	Enum_Priority_9,
	Enum_Priority_255 = 255,	// 无效值
};
//新增
//! 来源类型
enum Enum_EquipSrc
{
	Enum_EquipSrc_0 = 0,	//! 本地
	Enum_EquipSrc_1,		//! 航空兵
	Enum_EquipSrc_2,		//! 地防
	Enum_EquipSrc_3,		//! 电抗
	Enum_EquipSrc_4,			//! 雷达
	Enum_EquipSrc_5,   //! 预留1
	Enum_EquipSrc_6,   //! 预留2
	Enum_EquipSrc_255 = 255,   //! 无效值
};

#ifndef Enum_RegionType_DEF
#define Enum_RegionType_DEF
enum Enum_RegionType // 区域几何类型
{	
	Enum_RegionType_0 = 0,	// 扇形
	Enum_RegionType_1 = 1,	// 圆形
	Enum_RegionType_2 = 2,	// 多边形
	Enum_RegionType_3 = 3,	// 双扇型
	Enum_RegionType_4 = 4,		// 同心圆形
	Enum_RegionType_5 = 5,		// 腰字形
	Enum_RegionType_6 = 6,		// 椭圆
	Enum_RegionType_7 = 7,   //预留1
	Enum_RegionType_8 = 8,   //预留2
	Enum_RegionType_255 = 255,   //无效值
};
#endif //Enum_RegionType_DEF

#ifndef Enum_Evaluate_DEF
#define Enum_Evaluate_DEF
enum Enum_EvaluateItem	// 评估指标
{
	Enum_EvaluateItem_0	= 0,  // (战役级)对地面警戒雷达网目标压制率
	Enum_EvaluateItem_1,      // (战役级)对地面警戒雷达网有效压制时间率
	Enum_EvaluateItem_2,      // (战役级)对导弹制导雷达目标压制率
	Enum_EvaluateItem_3,      // (战役级)对导弹制导雷达有效压制时间率
	Enum_EvaluateItem_4,      // (战役级)预警机目标发现率
	Enum_EvaluateItem_5,      // (战役级)预警机目标发现率变化程度(离线)
	Enum_EvaluateItem_6,      // (战役级)掩护预警机预警时间
	Enum_EvaluateItem_7,      // (战役级)预警机预警时间变化程度(离线)
	Enum_EvaluateItem_8,      // (战役级)区域覆盖率
	Enum_EvaluateItem_9,      // (战役级)信号截获率
	Enum_EvaluateItem_10,     // (战役级)信号识别率
	Enum_EvaluateItem_11,     // (战役级)反辐射无人机突防成功率(离线)
	Enum_EvaluateItem_12,     // (战役级)反辐射攻击任务完成率(离线)
	Enum_EvaluateItem_13,     // (战役级)对机载预警雷达目标压制率
	Enum_EvaluateItem_14,     // (战役级)对机载预警雷达有效压制时间率
	Enum_EvaluateItem_15,     // (战役级)对机载火控雷达目标压制率
	Enum_EvaluateItem_16,     // (战役级)对机载火控雷达有效压制时间率
	Enum_EvaluateItem_17,     // (战役级)对机载成像雷达目标压制率
	Enum_EvaluateItem_18,     // (战役级)对机载成像雷达有效压制时间率
	Enum_EvaluateItem_19,     // (战术级)远距离支援GR目标压制率
	Enum_EvaluateItem_20,     // (战术级)远距离支援GR有效压制时间率
	Enum_EvaluateItem_21,     // (战术级)地面预警雷达网目标发现率
	Enum_EvaluateItem_22,     // (战术级)地面预警雷达网发现率变化程度(离线)
	Enum_EvaluateItem_23,     // (战术级)地面预警雷达网预警时间
	Enum_EvaluateItem_24,     // (战术级)地面预警雷达网预警时间变化程度(离线)
	Enum_EvaluateItem_25,     // (战术级)随队支援/自卫对导弹制导雷达目标压制率
	Enum_EvaluateItem_26,     // (战术级)随队支援/自卫对导弹制导雷达有效压制时间率
	Enum_EvaluateItem_27,     // (战术级)导弹制导雷达网目标发现率
	Enum_EvaluateItem_28,     // (战术级)反辐射攻击信号截获率
	Enum_EvaluateItem_29,     // (战术级)反辐射攻击持续压制时间(离线)
	Enum_EvaluateItem_30,     // (战术级)反辐射攻击命中率(离线)
	Enum_EvaluateItem_31,     // (战术级)反辐射攻击抗诱饵能力(离线)
	Enum_EvaluateItem_32,     // (战术级)对机载火控雷达目标压制率
	Enum_EvaluateItem_33,     // (战术级)对机载火控雷达有效压制时间率
	Enum_EvaluateItem_34,     // (战术级)对机载成像雷达目标压制率
	Enum_EvaluateItem_35,     // (战术级)对机载成像雷达有效压制时间率
	Enum_EvaluateItem_36,     // (战术级)对机载预警雷达目标压制率
	Enum_EvaluateItem_37,     // (战术级)对机载预警雷达有效压制时间率
	Enum_EvaluateItem_38,     // (战术级)预警机目标发现率
	Enum_EvaluateItem_39,     // (战术级)预警机目标发现率变化程度(离线)
	Enum_EvaluateItem_40,     // (战术级)预警机预警时间
	Enum_EvaluateItem_41,     // (战术级)预警机预警时间变化程度(离线)
	Enum_EvaluateItem_42,     // (战术级)地面电子对抗ZC区域覆盖率
	Enum_EvaluateItem_43,     // (战术级)地面电子对抗ZC信号截获率
	Enum_EvaluateItem_44,     // (战术级)地面电子对抗ZC测向精度
	Enum_EvaluateItem_45,     // (战术级)航空战略电子对抗ZC区域覆盖率
	Enum_EvaluateItem_46,     // (战术级)航空战略电子对抗ZC信号截获率
	Enum_EvaluateItem_47,     // (战术级)航空战略电子对抗ZC测向精度
	Enum_EvaluateItem_48,     // (战术级)航空战术电子对抗ZC区域覆盖率
	Enum_EvaluateItem_49,     // (战术级)航空战术电子对抗ZC信号截获率
	Enum_EvaluateItem_50,     // (战术级)航空战术电子对抗ZC测向精度
	Enum_EvaluateItem_51,     // (战术级)假目标的数量(离线)
	Enum_EvaluateItem_52,     // (战术级)假目标航迹的数量(离线)
	Enum_EvaluateItem_53,    // (团指)GPS最长压制时间
	Enum_EvaluateItem_54,    // (团指)通信GR时间压制率
	Enum_EvaluateItem_55,     //预留1
	Enum_EvaluateItem_56,    // 预留2
	Enum_EvaluateItem_255,    // 无效值
};

enum Enum_EquipUseType // 装备作战用途
{	
	Enum_EquipUseType_0 = 0,	// 地面预警机雷达GR（311、672C）
	Enum_EquipUseType_1,		// 地对空雷达GR(671A、672B)
	Enum_EquipUseType_2,		// 随队GR
	Enum_EquipUseType_3,		// 自卫GR
	Enum_EquipUseType_4,		// 远距离支援GR
	Enum_EquipUseType_5,		// 合成孔径雷达GR
	Enum_EquipUseType_6,		// 无人机载GR设备（假目标无人机）
	Enum_EquipUseType_7,		// 反辐射无人机
	Enum_EquipUseType_8,		// 机载雷达ZC（战略ZC、运八侦）
	Enum_EquipUseType_9,		// 地面电子对抗ZC（302、518ABC）
	Enum_EquipUseType_10,		// 机载电子ZC吊舱（战术ZC、KCDJ1）
	Enum_EquipUseType_11,		// 保留
	Enum_EquipUseType_12,		// 保留
	Enum_EquipUseType_255 = 255,    // 无效值
};
#endif //Enum_Evaluate_DEF

#ifndef ENUM_KEYPTTYPE_DEF
#define ENUM_KEYPTTYPE_DEF
//! 关键点类型
//关键点类型 zm 20170407
enum Enum_KeyPtType
{
	//Enum_KeyPt_Other      =   0,  //其它类型关键点
	//Enum_KeyPt_Anta       =   1,  //对抗关键点
	//Enum_KeyPt_Off		 =   2,  //关机关键点（面向所有装备）
	//Enum_KeyPt_OpenForWard=   3,  //前向开机（特指随队和自卫前后向GR装备）
	//Enum_KeyPt_OpenBack   =   4,  //后向开机（特指随队和自卫前后向GR装备）
	//Enum_KeyPt_OpenALL    =   5,  //全向开机（特指随队和自卫前后向GR装备）
	//Enum_KeyPt_Deploy	 =	 6,  //装备部署点（面向地面装备）
	//Enum_KeyPt_BeginWork	 =	 7,  //开机工作（面向地面装备和Y8G，该状态指装备加电完成，一切达到开机GR状态，具体GR事件相关存储在装备的频率信息）
	//Enum_KeyPt_FinishWork =	 8,  //结束工作（面向地面装备）

	Enum_KeyPt_Other       =   0,  //! 其它类型关键点
	Enum_KeyPt_On          =   1,  //! 加电准备

	Enum_KeyPt_ESM         =   2,    //! 转到仅ZC模式    所有GR设备均关辐射
	Enum_KeyPt_ESMForWard  =   201,  //! 前向ZC（特指机载前后向GR装备）
	Enum_KeyPt_ESMBack     =   202,  //! 后向ZC（特指机载前后向GR装备）
	Enum_KeyPt_ESMLeft     =   203,  //! 左向ZC（特指机载左右向GR装备）
	Enum_KeyPt_ESMRight    =   204,  //! 右向ZC（特指机载左右向GR装备）
	Enum_KeyPt_ESMALL      =   205,  //! 全向ZC（特指机载前后向GR装备）

	Enum_KeyPt_ECM         =   3,    //! 转到ZC+GR模式  所有GR设备均开辐射（930不含此模式）
	Enum_KeyPt_ECMForWard  =   301,  //! 前向GR（特指机载前后向GR装备）
	Enum_KeyPt_ECMBack     =   302,  //! 后向GR（特指机载前后向GR装备）
	Enum_KeyPt_ECMLeft     =   303,  //! 左向GR（特指机载左右向GR装备）
	Enum_KeyPt_ECMRight    =   304,  //! 右向GR（特指机载左右向GR装备）
	Enum_KeyPt_ECMALL      =   305,  //! 全向GR（特指机载GR装备）

	//多GR设备时的辐射控制 start  //2200                          //3000/3500             //930
	Enum_KeyPt_ECMMODE1    =   306,//! S关C开XKu前开XKu后开          //后向关前左开前右开	  // @Properties(description=后向关前左开前右开（自卫）)
	Enum_KeyPt_ECMMODE2    =   307,//! S开C关XKu前开XKu后开 		  //后向开前左关前右开	  // @Properties(description=后向开前左关前右开（自卫）)
	Enum_KeyPt_ECMMODE3    =   308,//! S开C开XKu前关XKu后开 		  //后向开前左开前右关	  // @Properties(description=后向开前左开前右关（自卫）)
	Enum_KeyPt_ECMMODE4    =   309,//! S开C开XKu前开XKu后关 		  //后向开前左关前右关	  // @Properties(description=后向开前左关前右关（自卫）)
	Enum_KeyPt_ECMMODE5    =   310,//! S关C关XKu前开XKu后开 		  //后向关前左关前右开	  // @Properties(description=后向关前左关前右开（自卫）)
	Enum_KeyPt_ECMMODE6    =   311,//! S关C开XKu前关XKu后开 		  //后向关前左开前右关	  // @Properties(description=后向关前左开前右关（自卫）)
	                                                                                      
	Enum_KeyPt_ECMMODE7    =   312,//! S关C开XKu前开XKu后关                                  // @Properties(description=后向开前左开前右开（自卫）) 
	Enum_KeyPt_ECMMODE8    =   313,//! S开C关XKu前关XKu后开                                  // @Properties(description=普通外挂支援GR)
	Enum_KeyPt_ECMMODE9    =   314,//! S开C关XKu前开XKu后关 
	Enum_KeyPt_ECMMODE10   =   315,//! S开C开XKu前关XKu后关 
	Enum_KeyPt_ECMMODE11   =   316,//! S关C关XKu前关XKu后开 
	Enum_KeyPt_ECMMODE12   =   317,//! S关C关XKu前开XKu后关 
	Enum_KeyPt_ECMMODE13   =   318,//! S关C开XKu前关XKu后关 
	Enum_KeyPt_ECMMODE14   =   319,//! S开C关XKu前关XKu后关 
	//多GR设备时的辐射控制 end
	Enum_KeyPt_HPECM       =   320,//! HPECM模式，其它GR关闭
	
	Enum_KeyPt_Off		   =   4,  //! 关机关键点（面向所有装备）
	Enum_KeyPt_NoUse	   =   5,  //! 无效值
};
#endif //Enum_Evaluate_DEF

//根据54提供的资料完善 zm 20170401
#ifndef Enum_CMD_DEF
#define Enum_CMD_DEF
//! 调制样式
enum Enum_CMD 
{
	Enum_CMD_0 = 0,	       //! 未知
	Enum_CMD_1 = 1,	       //! 载波CW
	Enum_CMD_2 = 2,	       //! 下边带LSB
	Enum_CMD_3 = 3,	       //! 上边带USB
	Enum_CMD_4 = 4,	       //! 幅度调制AM
	Enum_CMD_5 = 5,	       //! 频率调制FM
	Enum_CMD_6 = 6,	       //! 独立边带ISB
	Enum_CMD_7 = 7,	       //! 宽带频率调制WFM
	Enum_CMD_8 = 8,	       //! 移频键控FSK
	Enum_CMD_9 = 9,	       //! 幅度键控ASK
	Enum_CMD_10 = 10,	   //! 最小频移键控MSK
	Enum_CMD_11 = 11,	   //! 二相键控BPSK
	Enum_CMD_12 = 12,	   //! 四相键控QPSK
	Enum_CMD_13 = 13,	   //! VSB
	Enum_CMD_14 = 14,	   //! 噪声
	Enum_CMD_15 = 15,	   //! DSB
	Enum_CMD_16 = 16,	   //! 无效值

	//add zm 
	Enum_CMD_17 = 17,	   //! PSK
	Enum_CMD_18 = 18,	   //! QAM
	Enum_CMD_19 = 19,	   //! APSK
	Enum_CMD_20 = 20,	   //! 2FSK
	Enum_CMD_21 = 21,	   //! 4FSK
	Enum_CMD_22 = 22,	   //! 8FSK
	Enum_CMD_23 = 23,	   //! 16FSK
	Enum_CMD_24 = 24,	   //! 2ASK
	Enum_CMD_25 = 25,	   //! 4ASK
	Enum_CMD_26 = 26,	   //! 8PSK
	Enum_CMD_27 = 27,	   //! 16PSK
	Enum_CMD_28 = 28,	   //! 16QAM
	Enum_CMD_29 = 29,	   //! 32QAM
	Enum_CMD_30 = 30,	   //! 64QAM
	Enum_CMD_31 = 31,	   //! 128QAM
	Enum_CMD_32 = 32,	   //! 256QAM
	Enum_CMD_33 = 33,	   //! 512QAM
	Enum_CMD_34 = 34,	   //! 16APSK
	Enum_CMD_35 = 35,	   //! 32APSK
	Enum_CMD_36 = 36,	   //! FMStereo
	Enum_CMD_37 = 37,	   //! OQPSK
	Enum_CMD_38 = 38,	   //! GMSK
	Enum_CMD_39 = 39,	   //! FM/FSK
	Enum_CMD_40 = 40,	   //! OFDM
	Enum_CMD_99 = 99,	//! 预留1
	Enum_CMD_100 = 100,	//! 预留2
	Enum_CMD_255 = 255,	//! 预留3
};
#endif

#ifndef ENUM_INFOTYPE_DEF
#define ENUM_INFOTYPE_DEF
enum Enum_InfoType {	// 基带信息类型
	Enum_InfoType_0 = 0,	// 未 知
	Enum_InfoType_1 = 1,	// 噪 声
	Enum_InfoType_2 = 2,	// 明 话
	Enum_InfoType_3 = 3,	// 密 话
	Enum_InfoType_4 = 4,	// 手工报
	Enum_InfoType_5 = 5,	// 电传报
	Enum_InfoType_6 = 6,	// 数 据
	Enum_InfoType_7 = 7,	// 图 像
	Enum_InfoType_8 = 8,	// 电 视
	Enum_InfoType_9 = 9,	// 扩展用
	Enum_InfoType_11 = 11,	// Link 4
	Enum_InfoType_12 = 12,	// Link 4A
	Enum_InfoType_13 = 13,	// Link 11
	Enum_InfoType_14 = 14,	// Link 16
	Enum_InfoType_15 = 15,	// 扩展用
	Enum_InfoType_255 = 255,	// 无效值
};
#endif

#ifndef ENUM_LINKMODE_DEF
#define ENUM_LINKMODE_DEF
enum Enum_LinkMode {	// Enum_ LinkMode
	Enum_LinkMode_0 = 0,	// 非数据链信号
	Enum_LinkMode_1 = 1,	// Link-11
	Enum_LinkMode_2 = 2,	// Link-11A
	Enum_LinkMode_3 = 3,	// Link-11B
	Enum_LinkMode_4 = 4,	// Link-4
	Enum_LinkMode_5 = 5,	// Link-4A
	Enum_LinkMode_6 = 6,	// Link-14
	Enum_LinkMode_7 = 7,	// Link-16
	Enum_LinkMode_8 = 8,	// JTIDS
	Enum_LinkMode_9 = 9,	// MIDS
	Enum_LinkMode_10 = 10,	// Link-22
	Enum_LinkMode_11 = 11,	// 未知
	Enum_LinkMode_12 = 12,	// 预留
	Enum_LinkMode_255 = 255,	// 无效值
};
#endif

//与54协商修改：分两级区分信号样式，万位和千位代表大类，千百个位为该大类下的小类 zm20170331
//注意：描述的是信号而非用频方式！！！
#ifndef ENUM_SIGNALTYPE_DEF
#define ENUM_SIGNALTYPE_DEF
//! 信号类型
enum Enum_SignalType {	// Enum_SignalType
	Enum_SignalType_0 = 0,	//! 未知
	Enum_SignalType_1 = 1,	//! 常规定频信号
	Enum_SignalType_2 = 2,	//! 常规跳频信号
	Enum_SignalType_3 = 3,	//! 自适应信号
	Enum_SignalType_4 = 4,	//! JTIDS信号
	Enum_SignalType_5 = 5,	//! 数据链
	Enum_SignalType_6 = 6,	//! IFF
	Enum_SignalType_7 = 7,	//! 导航信号
	Enum_SignalType_8 = 8,	//! ALE
	Enum_SignalType_9 = 9,	//! 预留1
	Enum_SignalType_10 = 10,	//! 预留2
	Enum_SignalType_11 = 11,	//! 预留3
	Enum_SignalType_255 = 255,	//! 无效值
	//add zm start
	Enum_SignalType_1001 = 1001,	//! 模拟定频
	Enum_SignalType_1002 = 1002,	//! 数字定频

	Enum_SignalType_5001 = 5001,	//! Link-11
	Enum_SignalType_5002 = 5002,	//! Link-11A
	Enum_SignalType_5003 = 5003,	//! Link-11B
	Enum_SignalType_5004 = 5004,	//! Link-4
	Enum_SignalType_5005 = 5005,	//! Link-4A
	Enum_SignalType_5006 = 5006,	//! Link-4B
	Enum_SignalType_5007 = 5007,	//! Link-10
	Enum_SignalType_5008 = 5008,	//! Link-14
	Enum_SignalType_5009 = 5009,	//! Link-16
	Enum_SignalType_5010 = 5010,	//! MIDS
	Enum_SignalType_5011 = 5011,	//! Link-22
	Enum_SignalType_5012 = 5012,	//! ASN-150
	Enum_SignalType_5013 = 5013,	//! 预留1
	Enum_SignalType_5014 = 5014,	//! 预留2

	Enum_SignalType_6001 = 6001,	//! MARKV
	Enum_SignalType_6002 = 6002,	//! MARKVII
	Enum_SignalType_6003 = 6003,	//! S模式
	Enum_SignalType_6004 = 6004,	//! AC模式
	Enum_SignalType_6005 = 6005,	//! 预留1
	Enum_SignalType_6006 = 6006,	//! 预留2

	Enum_SignalType_7001 = 7001,	//! TACAN
	Enum_SignalType_7002 = 7002,	//! AIS
	Enum_SignalType_7003 = 7003,	//! ACARS
	Enum_SignalType_7004 = 7004,	//! ADS-B
	Enum_SignalType_7005 = 7005,	//! 预留1
	Enum_SignalType_7006 = 7006,	//! 预留2
	Enum_SignalType_7007 = 7007,	//! 预留3
	//add zm end

};
#endif


//zm modify 20170331
#ifndef ENUM_WAVETRANSTYPE_DEF
#define ENUM_WAVETRANSTYPE_DEF
enum Enum_WaveTransType {	// 电波传播方式
	Enum_WaveTransType_0 = 0,	// 天波
	Enum_WaveTransType_1 = 1,	// 直射波(视距传播)
	Enum_WaveTransType_2 = 2,	// 地波（海）
	Enum_WaveTransType_3 = 3,	// 地波（地）
	Enum_WaveTransType_4 = 4,	// 对流层散射
	Enum_WaveTransType_5 = 5,	// 预留1
	Enum_WaveTransType_6 = 6,	// 预留2
	Enum_WaveTransType_255 = 255,	// 无效值
};
#endif

#ifndef ENUM_CJMD_DEF
#define ENUM_CJMD_DEF
enum Enum_CJMD {	// 通信调制样式
	Enum_CJMD_0 = 0,	// 无调制（载波）
	Enum_CJMD_1 = 1,	// 调频
	Enum_CJMD_2 = 2,	// 调幅
	Enum_CJMD_3 = 3,	// 调相
	Enum_CJMD_4 = 4,	// 扩展用
	Enum_CJMD_255 = 255,	// 无效值
};
#endif

#ifndef ENUM_CJAMTYPE_DEF
#define ENUM_CJAMTYPE_DEF
enum Enum_CJamType {	// 通信GR方式
	Enum_CJamType_0 = 0,	// 未知
	Enum_CJamType_1 = 1,	// 瞄准GR
	Enum_CJamType_2 = 2,	// 强制GR
	Enum_CJamType_3 = 3,	// 连续谱拦阻GR
	Enum_CJamType_4 = 4,	// 梳状谱拦阻GR
	Enum_CJamType_5 = 5,	// 欺骗GR
	Enum_CJamType_6 = 6,	// 扩展用
	Enum_CJamType_255 = 255,	// 无效值
};
#endif

#ifndef ENUM_ANTENNATYPE_DEF
#define ENUM_ANTENNATYPE_DEF
//! 天线类型
enum Enum_AntennaType {
	Enum_AntennaType_0 = 0,	//! 天波-对数周期天线
	Enum_AntennaType_1 = 1,	//! 天波-倒V天线
	Enum_AntennaType_2 = 2,	//! 天波-宽带偶极天线
	Enum_AntennaType_3 = 3,	//! 地波-伞锥天线
	Enum_AntennaType_4 = 4,	//! 地波-半菱天线
	Enum_AntennaType_5 = 5,	//! 地波-单级天线
	Enum_AntennaType_6 = 6,	//! 地波-λ天线
	Enum_AntennaType_7 = 7,	//! 地波-垂直极化对周天线
	Enum_AntennaType_8 = 8,	//! 扩展用
	Enum_AntennaType_9 = 9,	//! 扩展用
	Enum_AntennaType_255 = 255,	//! 无效值
};
#endif

#ifndef ENUM_SATNAVITYPE_DEF
#define ENUM_SATNAVITYPE_DEF
enum Enum_ReceiverType {	// 接收机类型
	Enum_ReceiverType_1 = 0,	// 通道连续跟踪接收机
	Enum_ReceiverType_2 = 1,	// 时序接收机
	Enum_ReceiverType_3 = 2,	// 多路复用接收机
	Enum_ReceiverType_4 = 3,	// 扩展用
	Enum_ReceiverType_5 = 4,	// 扩展用
	Enum_ReceiverType_255 = 255,	// 无效值
};
#endif

enum Enum_CodeType {	// 导航定位扩频码码形
	Enum_CodeType_0 = 0,	// P(Y)码
	Enum_CodeType_1 = 1,	// C/A码
	Enum_CodeType_2 = 2,	// P码
	Enum_CodeType_3 = 3,	// 扩展用
	Enum_CodeType_4 = 4,	// 扩展用
	Enum_CodeType_255 = 255,	// 无效值
};

#ifndef Enum_AntennaMode_DEF
#define Enum_AntennaMode_DEF
enum Enum_AntennaMode {	// 天线模式
	Enum_AntennaMode_0 = 0,	// 全向
	Enum_AntennaMode_1 = 1,	// 定向
	Enum_AntennaMode_2 = 2,	// 扩展用
	Enum_AntennaMode_255 = 255,	// 无效值
};
#endif


#ifndef ENUM_DeviceType_DEF
#define ENUM_DeviceType_DEF
enum Enum_GPSJamDeviceType {	// 设备类型
	Enum_DeviceType_0 = 0,	// RCZ213车载GR站
	Enum_DeviceType_1 = 1,	// RCZ213背负GR站
	Enum_DeviceType_2 = 2,	// 其它，目前有901 zm20200623
	Enum_DeviceType_255 = 255,	// 无效值
};
#endif

#ifndef ENUM_MissileStateType_DEF
#define ENUM_MissileStateType_DEF
enum MISSILE_STATE
{
	//通用命令码
        MISSILE_WAIT  =	0,
        MISSILE_FIRSTDETECT  =	1,
        MISSILE_SECONDDETECT  =	2,
        MISSILE_HITTED  = 3,
        MISSILE_NOHITTED  = 4,
        MISSILE_INVALID  = 5,
};
#endif

#ifndef ENUM_WeatherType_DEF
#define ENUM_WeatherType_DEF
enum WeatherType
{
	WeatherType_None = 0,//不考虑气象
	WeatherType_Cloud  =	1,
	WeatherType_Rain  =	2,
	WeatherType_Fog  =	3,
	WeatherType_Snow  = 4,
	WeatherType_Res1  = 5,//预留1
	WeatherType_Res2  = 6,//预留2
};
#endif

}//namespace DMS end

#pragma pack()

#endif

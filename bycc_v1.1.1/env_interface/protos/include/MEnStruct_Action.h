
/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.09	按照年(个数位)月日组合的方式	**
**版    本:	2015.04.09  zoubz修改											**
*************************************************************************/
#include "MEnStruct_Macros.h"
#include "MEnStruct_Common.h"
#include "MEnStruct_RadarJam.h"
//#include "EO_COMMON.h"

#include <vector>
#include <map>
#define StoreNum  250


#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
	if (ptr != NULL ) \
{ \
	delete ptr; \
	ptr = NULL; \
}
#endif


#ifndef MEN_STRUCT_Action
#define MEN_STRUCT_Action

#pragma pack(1)
#ifndef Enum_Formation_DEF
#define Enum_Formation_DEF

enum Enum_Formation{
	Enum_Formatio_0 = 0,
	Enum_Formatio_1 = 1,
	Enum_Formatio_2 = 2,
	Enum_Formatio_255 = 255,
};
#endif

#ifndef Enum_TgtType_DEF
#define Enum_TgtType_DEF
enum Enum_TgtType
{	// 目标类型
	Enum_TgtType_0 = 0,	// 飞机平台
	Enum_TgtType_1 = 1,	// 导弹
	Enum_TgtType_2 = 2, //舰船
	Enum_TgtType_255 = 255,	//无效值
};
#endif
enum Enum_ActionOrderType
{	// 任务指令方向
	Enum_ActionOrderType_0 = 0,	// 编队内指令：长机发送给僚机的任务指令
	Enum_ActionOrderType_1 = 1,	// 编队内指令：僚机发送给长机的任务请求
	Enum_ActionOrderType_2 = 2, //编队间指令：长机发送给另一个编队长机的协同请求
	Enum_ActionOrderType_255 = 255,	//无效值
};




//编队/编组/组网信息
typedef struct _ModelBus_Formate
{
	int     FormateID;                  //编队ID
//	Enum_Formation     eFormation;      //编队队形
	int	    LeaderPlatID;	   					   //编队长机ID
	int     nFormatePlatNum;					  //编队内平台实际数量
	int*    pFormatePlatID;					  //编队内实际平台ID，第一个为长机，其他为僚机

	/*重载构造函数*/
	_ModelBus_Formate()
	{
		FormateID = 0;
//		eFormation = Enum_Formatio_255;
		LeaderPlatID = 0;
		nFormatePlatNum = 0;
		pFormatePlatID = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_Formate()
	{
		SW_Delete(pFormatePlatID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_Formate(const _ModelBus_Formate &theStruct)
	{
		pFormatePlatID = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_Formate& operator=(const _ModelBus_Formate& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		FormateID = theStruct.FormateID;
//		eFormation = theStruct.eFormation;
		LeaderPlatID = theStruct.LeaderPlatID;
		nFormatePlatNum		= theStruct.nFormatePlatNum;
		SW_Malloc_Int(theStruct.pFormatePlatID,pFormatePlatID,theStruct.nFormatePlatNum,nFormatePlatNum);
		return *this;

	}
}sFormateInfo;



//平台机动控制规则
typedef struct _ModelBus_PlatActRule
{
	bool bActive;          //有效标志
	//*****************平台机动通用规则*****************

	//*****************不同类型平台机动个性规则*****************
	DKDMS::Enum_PlatType   ePlatType;          //平台类型决定平台机动方式不同，不同类型利用不同字段数据
	////Enum_PlatType_1,    //地面固定
	////Enum_PlatType_2,    //地面移动,火车
	////Enum_PlatType_3,    //舰(船)载
	////Enum_PlatType_4,    //潜艇载
	////Enum_PlatType_5,    //弹载

	////Enum_PlatType_6,    //飞机载
	int		TrackNum;					//航迹点个数
	sPLAT_TRACK_DATA* TrackData;		//航迹数据

	////Enum_PlatType_7,    //直升机载
	////Enum_PlatType_8,    //无人机载
	////Enum_PlatType_9,    //卫星载
	////Enum_PlatType_10,   //气球载
	////Enum_PlatType_11,   //车载
	////Enum_PlatType_12,   //便携,背负
	////Enum_PlatType_13,   //飞船载
	////Enum_PlatType_14,   //浮标
	////Enum_PlatType_15,   //飞艇

	/*重载构造函数*/
	_ModelBus_PlatActRule()
	{
		bActive = false;
		ePlatType = DKDMS::Enum_PlatType_0;
		TrackNum = 0;
		TrackData = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_PlatActRule()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_PlatActRule(const _ModelBus_PlatActRule &theStruct)
	{
		TrackData = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_PlatActRule& operator=(const _ModelBus_PlatActRule& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		ePlatType = theStruct.ePlatType;
		TrackNum = theStruct.TrackNum;
		SW_Malloc_Struct(sPLAT_TRACK_DATA,theStruct.TrackData,TrackData,theStruct.TrackNum,TrackNum);
		return *this;
	}
}sPlatActRule;

//预警雷达控制规则
typedef struct _ModelBus_RadarActRule
{
	bool bActive;          //有效标志

	////初始目标分配
	//sTgtAllocation TgtAllocation;

	//雷达开机条件
	sPON_AREA   RadarOnPosition;  //触发事件1：指定位置开机
	float		fRadarOnTime;	   //触发事件2：开机时刻 单位：秒（s）
	float       fRadarOnInterval;   //开机间隔时间 单位：秒（s）
	float	    fRadarOnDuration;   //开机持续时间 单位：秒（s）
	//雷达波束方向控制




	/*重载构造函数*/
	_ModelBus_RadarActRule()
	{
		bActive = false;
		fRadarOnTime = -1;
		fRadarOnInterval = 0;
		fRadarOnDuration = 0;
	}

	/*重载析构函数*/
	~_ModelBus_RadarActRule()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarActRule(const _ModelBus_RadarActRule &theStruct)
	{

		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarActRule& operator=(const _ModelBus_RadarActRule& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		RadarOnPosition = theStruct.RadarOnPosition;
		fRadarOnTime = theStruct.fRadarOnTime;
		fRadarOnInterval = theStruct.fRadarOnInterval;
		fRadarOnDuration = theStruct.fRadarOnDuration;


		return *this;
	}
}sRadarActRule;

//
////制导雷达控制规则
//typedef struct _ModelBus_ZDRadarActRule
//{
//	bool bActive;          //有效标志
//
//	//初始目标分配
//	sTgtAllocation TgtAllocation;
//
//	//雷达开机条件
//	sPON_AREA   sRadarOnPosition;  //触发事件1：指定位置开机
//	float		fRadarOnTime;	   //触发事件2：开机时刻 单位：秒（s）
//
//	//雷达波束方向控制
//
//	/*重载构造函数*/
//	_ModelBus_ZDRadarActRule()
//	{
//	}
//
//	/*重载析构函数*/
//	~_ModelBus_ZDRadarActRule()
//	{
//
//	}
//
//	/*重载拷贝构造函数*/
//	_ModelBus_ZDRadarActRule(const _ModelBus_ZDRadarActRule &theStruct)
//	{
//
//		*this = theStruct;
//	}
//
//	/*重载=*/
//	_ModelBus_ZDRadarActRule& operator=(const _ModelBus_ZDRadarActRule& theStruct)
//	{
//		if (this == &theStruct)
//		{
//			return *this;
//		}
//
//		return *this;
//	}
//}sZDRadarActRule;


//雷达ZC机控制规则
typedef struct _ModelBus_RadarReconActRule
{
	bool			 bActive;					 //有效标志
	int				 nTgtNum;
	int*			 pTgtID;
	int		         iCenterPoint;		//ZC中心区域点个数
	sPON_AREA*       pCenterPoint;	//ZC中心区域点


	/*重载构造函数*/
	_ModelBus_RadarReconActRule()
	{
		bActive = false;
		nTgtNum = 0;
		pTgtID = NULL;
		iCenterPoint = 0;
		pCenterPoint = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_RadarReconActRule()
	{
		SW_Delete(pTgtID);
		SW_Delete(pCenterPoint);
	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarReconActRule(const _ModelBus_RadarReconActRule &theStruct)
	{
		pTgtID = NULL;
		pCenterPoint = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarReconActRule& operator=(const _ModelBus_RadarReconActRule& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		nTgtNum = theStruct.nTgtNum;
		SW_Malloc_Int(theStruct.pTgtID,pTgtID,theStruct.nTgtNum,nTgtNum);
		iCenterPoint = theStruct.iCenterPoint;
		SW_Malloc_Struct(sPON_AREA,theStruct.pCenterPoint,pCenterPoint,theStruct.iCenterPoint,iCenterPoint);
		return *this;
	}
}sRadarReconActRule;
//雷达GR机控制规则
typedef struct _ModelBus_RadarJammerActRule
{
	bool bActive;          //有效标志

	////初始目标分配
	//bool		bPresetTgt;		        //是否预设目标，地面GR装备和运八需要在场景中预设目标，空中GR装备根据ZC结果进行目标设置
	//sTgtAllocation TgtAllocation;		//优先级：导引头>火控雷达>预警雷达，


	//GR开机规则
	float		fJamOnTime;				 //开机触发事件1：开机时刻 单位：秒（s）
	sPON_AREA   JamOnPosition;			 //开机触发事件2：开机位置
	bool        bReconGuidJam;	         //开机触发事件3：ZC结果引导GR
	//GR关机规则
	float		fJamOffTime;			 //关机触发事件1：关机时刻 单位：秒（s）
	sPON_AREA   JamOffPosition;			 //关机触发事件2：关机位置

	//GR样式切换规则
	//<目标类型，GR样式>	            //Enum_RJamType  RadarJamType;//4为交叉极化GR，5为交叉眼GR

	/*重载构造函数*/
	_ModelBus_RadarJammerActRule()
	{
		bActive = false;
		bReconGuidJam = false;
		fJamOnTime = -1;
		fJamOffTime = -1;
	}

	/*重载析构函数*/
	~_ModelBus_RadarJammerActRule()
	{

	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarJammerActRule(const _ModelBus_RadarJammerActRule &theStruct)
	{

		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarJammerActRule& operator=(const _ModelBus_RadarJammerActRule& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		fJamOnTime = theStruct.fJamOnTime;
		JamOnPosition = theStruct.JamOnPosition;
		bReconGuidJam = theStruct.bReconGuidJam;
		fJamOffTime = theStruct.fJamOffTime;
		JamOffPosition = theStruct.JamOffPosition;
		return *this;
	}
}sRadarJammerActRule;

//导弹控制规则
typedef struct _ModelBus_MissileActRule
{
	bool bActive;          //有效标志
	//导弹发射条件
	float	    fMissileFireTime;				//触发事件1：发射时刻 秒（s）
	sPON_AREA   MissileFirePosition;            //触发事件2：发射位置
	int			iMissileFireAirPlaneMinDis;     //触发事件3：拦截飞机目标的最小发射距离
	int			iMissileFireMissileMinDis;      //触发事件4：拦截导弹目标的最小发射距离
	int			iMissileTerminalStateMinDis;     //触发事件5：导弹进入末端制导的最小距离

	/*重载构造函数*/
	_ModelBus_MissileActRule()
	{
		bActive = false;
		fMissileFireTime = -1;
		iMissileFireAirPlaneMinDis = 0;
		iMissileFireMissileMinDis = 0;
		iMissileTerminalStateMinDis = 0;
	}

	/*重载析构函数*/
	~_ModelBus_MissileActRule()
	{

	}

	/*重载拷贝构造函数*/
	_ModelBus_MissileActRule(const _ModelBus_MissileActRule &theStruct)
	{

		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_MissileActRule& operator=(const _ModelBus_MissileActRule& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = false;
		fMissileFireTime = theStruct.fMissileFireTime;
		MissileFirePosition = theStruct.MissileFirePosition;
		iMissileFireAirPlaneMinDis = theStruct.iMissileFireAirPlaneMinDis;
		iMissileFireMissileMinDis = theStruct.iMissileFireMissileMinDis;
		iMissileTerminalStateMinDis = theStruct.iMissileTerminalStateMinDis;

		return *this;
	}
}sMissileActRule;


//某平台的行为能力输入基本参数报
typedef struct _ModelBus_Action_Set_PARA
{
	//****************身份标识**************************
	char*	sRID;						//身份字符串
	int     ActionID;                     //本行为实例ID
	int		PlatID;						//所属平台ID或者装备ID
	int		TaskID;						 //所属任务类型ID（0为通用任务，1为远距离支援任务）由装备类型决定
	bool    bActive;				//所属任务激活状态
	//****************编成信息**************************
	//sFormateInfo   FormateInfo;			//所属任务平台编队/编组信息
	int     FormateID;						 //编队ID
	int	    LeaderPlatID;	   					   //编队长机ID
	int     nFormatePlatNum;					  //编队内平台实际数量
	int*    pFormatePlatID;					  //编队内实际平台ID，第一个为长机，其他为僚机


	//****************组件行为控制规则**************************
	//sPlatActRule         PlatActRule;         //平台机动规则
	//sRadarActRule	     RadarActRule;  	  //雷达行为控制规则
	//sRadarReconActRule   RadarReconActRule;    //雷达ZC装备行为控制规则
	//sRadarJammerActRule  RadarJammerActRule;  //雷达GR装备行为控制规则
	//sMissileActRule      MissileActRule;	  //导弹行为控制规则


	//ZC装备控制规则
	bool         bReconActive;
	int		     iCenterPoint;		//ZC中心区域点个数
	sPON_AREA*   pCenterPoint;	//ZC中心区域点

	//火控雷达控制规则
	bool        bRadarActive;
	sPON_AREA   RadarOnPosition;   //雷达开机触发事件1：指定位置开机
	float		fRadarOnTime;	   //雷达开机触发事件2：开机时刻 单位：秒（s）,开始设为-1则无效
	float       fRadarOnInterval;   //开机间隔时间 单位：秒（s）
	float	    fRadarOnDuration;   //开机持续时间 单位：秒（s）

	//GR装备控制规则
	bool        bJamActive;
	float		fJamOnTime;				 //开机触发事件1：开机时刻 单位：秒（s）
	sPON_AREA   JamOnPosition;			 //开机触发事件2：开机位置
	bool        bReconGuidJam;	         //开机触发事件3：ZC结果引导GR
	float		fJamOffTime;			 //关机触发事件1：关机时刻 单位：秒（s）
	sPON_AREA   JamOffPosition;			 //关机触发事件2：关机位置
	int         iJamTgtID;               //GR目标ID(平台)


	//导弹控制规则
	bool        bMissileActive;
	float	    fMissileFireTime;				//导弹平台设置：触发事件1：发射时刻 秒（s）
	sPON_AREA   MissileFirePosition;            //导弹平台设置：触发事件2：发射位置
	int			iMissileFirePlatMinDis;         //导弹平台设置：触发事件3：拦截飞机目标的最小发射距离
	int			iMissileFireMissileMinDis;      //导弹平台设置：触发事件4：拦截导弹目标的最小发射距离
	int			iMissileTerminalStateMinDis;    //导弹平台设置：触发事件5：导弹进入末端制导的最小距离
	int         iMissileFireTgtID;              //搭载平台设置：火力打击目标(平台)，若界面设置了则以界面设置的目标为主，没设置则接受火控雷达的引导
	int         iMissileFireNum;                //搭载平台设置：导弹齐发数量,对抗一个目标的导弹数量



	//平台机动控制规则
	//int        iPlatTurnMinDis;                 //平台转向触发条件：平台与目标最近距离


	/*重载构造函数*/
	_ModelBus_Action_Set_PARA()
	{
		sRID = NULL;
		ActionID = -1;
		PlatID = -1;
		TaskID = -1;
		bActive = false;
		FormateID = 0;
		LeaderPlatID = 0;
		nFormatePlatNum = 0;
		pFormatePlatID = NULL;
		//MainActionID = -2;

		bReconActive = false;
		iCenterPoint = 0;
		pCenterPoint = NULL;

		bRadarActive = false;
		fRadarOnTime = -1;
		fRadarOnInterval = 0;
		fRadarOnDuration = 0;

		bJamActive = false;
		fJamOnTime = -1;
		bReconGuidJam = false;
		fJamOffTime = -1;
		iJamTgtID = 0;

		bMissileActive = false;
		fMissileFireTime = -1;
		iMissileFirePlatMinDis = 0;
		iMissileFireMissileMinDis = 0;
		iMissileTerminalStateMinDis = 0;
		iMissileFireTgtID = 0;
		iMissileFireNum = 0;

		//iPlatTurnMinDis = 0;
	}

	/*重载析构函数*/
	~_ModelBus_Action_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(pFormatePlatID);

		SW_Delete(pCenterPoint);

	}

	/*重载拷贝构造函数*/
	_ModelBus_Action_Set_PARA(const _ModelBus_Action_Set_PARA &theStruct)
	{
		sRID = NULL;
		pFormatePlatID = NULL;

		pCenterPoint = NULL;

		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_Action_Set_PARA& operator=(const _ModelBus_Action_Set_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);
		ActionID  = theStruct.ActionID;
		PlatID	  = theStruct.PlatID;
		TaskID    = theStruct.TaskID;
		bActive   = theStruct.bActive;
		FormateID = theStruct.FormateID;
		LeaderPlatID = theStruct.LeaderPlatID;
		nFormatePlatNum		= theStruct.nFormatePlatNum;
		SW_Malloc_Int(theStruct.pFormatePlatID,pFormatePlatID,theStruct.nFormatePlatNum,nFormatePlatNum);

		//PlatActRule = theStruct.PlatActRule;
		//RadarActRule = theStruct.RadarActRule;
		//RadarReconActRule = theStruct.RadarReconActRule;
		//RadarJammerActRule = theStruct.RadarJammerActRule;
		//MissileActRule = theStruct.MissileActRule;
		//MainActionID  = theStruct.MainActionID;
		bReconActive = theStruct.bReconActive;
		iCenterPoint = theStruct.iCenterPoint;
		SW_Malloc_Struct(sPON_AREA,theStruct.pCenterPoint,pCenterPoint,theStruct.iCenterPoint,iCenterPoint);

		bRadarActive = theStruct.bRadarActive;
		fRadarOnTime = theStruct.fRadarOnTime;
		fRadarOnInterval = theStruct.fRadarOnInterval;
		fRadarOnDuration = theStruct.fRadarOnDuration;
		RadarOnPosition = theStruct.RadarOnPosition;

		bJamActive = theStruct.bJamActive;
		fJamOnTime = theStruct.fJamOnTime;
		JamOnPosition = theStruct.JamOnPosition;
		bReconGuidJam = theStruct.bReconGuidJam;
		fJamOffTime = theStruct.fJamOffTime;
		JamOffPosition = theStruct.JamOffPosition;
		iJamTgtID = theStruct.iJamTgtID;

		bMissileActive = theStruct.bMissileActive;
		fMissileFireTime = theStruct.fMissileFireTime;
		MissileFirePosition = theStruct.MissileFirePosition;
		iMissileFirePlatMinDis = theStruct.iMissileFirePlatMinDis;
		iMissileFireMissileMinDis = theStruct.iMissileFireMissileMinDis;
		iMissileTerminalStateMinDis = theStruct.iMissileTerminalStateMinDis;
		iMissileFireTgtID = theStruct.iMissileFireTgtID;
		iMissileFireNum = theStruct.iMissileFireNum;

		//iPlatTurnMinDis = theStruct.iPlatTurnMinDis;
		return *this;
	}
}sAction_Set_PARA;



//平台机动状态
typedef struct _ModelBus_PlatActState
{
	bool bActive;
	/*重载构造函数*/
	_ModelBus_PlatActState()
	{
		bActive = false;
	}

	/*重载析构函数*/
	~_ModelBus_PlatActState()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_PlatActState(const _ModelBus_PlatActState &theStruct)
	{
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_PlatActState& operator=(const _ModelBus_PlatActState& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		return *this;
	}
}sPlatActState;

//雷达行动执行状态
typedef struct _ModelBus_RadarActState
{
	bool bActive;

	/*重载构造函数*/
	_ModelBus_RadarActState()
	{
		bActive = false;

	}

	/*重载析构函数*/
	~_ModelBus_RadarActState()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarActState(const _ModelBus_RadarActState &theStruct)
	{
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarActState& operator=(const _ModelBus_RadarActState& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		return *this;
	}
}sRadarActState;

//typedef struct _ModelBus_RadarReconResult
//{
//	int   RadarID;           //被截获的目标雷达ID
//	int	  iReconNum;         //截获到该目标的ZC装备个数
//	int*  pReconID;
//	bool  bLocated;			 //目标当前是否被跟踪（两个及以上装备发现）//显示判断这个变量，决定是否开始显示航迹点
//	float fFirstLocatedTime;        //（！可以不要的字段）首次定位时间
//	sPON_AREA   RadarLocatedPoint;	//目标定位位置
//	/*重载构造函数*/
//	_ModelBus_RadarReconResult()
//	{
//		RadarID = 0;
//		iReconNum = 0;
//		pReconID = NULL;
//		bLocated = false;
//		fFirstLocatedTime = 0;
//	}
//
//	/*重载析构函数*/
//	~_ModelBus_RadarReconResult()
//	{
//		SW_Delete(pReconID);
//
//	}
//
//	/*重载拷贝构造函数*/
//	_ModelBus_RadarReconResult(const _ModelBus_RadarReconResult &theStruct)
//	{
//		pReconID = NULL;
//
//		*this = theStruct;
//	}
//
//	/*重载=*/
//	_ModelBus_RadarReconResult& operator=(const _ModelBus_RadarReconResult& theStruct)
//	{
//		if (this == &theStruct)
//		{
//			return *this;
//		}
//		RadarID = theStruct.RadarID;
//		iReconNum = theStruct.iReconNum;
//		SW_Malloc_Int(theStruct.pReconID,pReconID,theStruct.iReconNum,iReconNum);
//		bLocated = theStruct.bLocated;
//		fFirstLocatedTime = theStruct.fFirstLocatedTime;
//		RadarLocatedPoint = theStruct.RadarLocatedPoint;
//
//		return *this;
//	}
//
//}sRadarReconResult;


//雷达ZC行动执行状态
typedef struct _ModelBus_RadarReconActState
{
	bool bActive;
	int iReconNum;					//组网内ZC装备个数
	int*  pReconID;					  //编队内ZC装备ID，第一个为主站ID，其他为副站
	int  iTgtNum;			             //当前时刻截获的目标个数(只有主站上报整个ZC组网的结论，不只是当前平台的)
	sRECON_DATAFUSIONRESULT* pRadarReconResult;

	/*重载构造函数*/
	_ModelBus_RadarReconActState()
	{
		bActive = false;
		iReconNum = 0;
		pReconID = NULL;
		iTgtNum = 0;
		pRadarReconResult = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_RadarReconActState()
	{
		SW_Delete(pReconID);
		SW_Delete(pRadarReconResult);

	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarReconActState(const _ModelBus_RadarReconActState &theStruct)
	{
		pReconID = NULL;
		pRadarReconResult = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarReconActState& operator=(const _ModelBus_RadarReconActState& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		iReconNum		= theStruct.iReconNum;
		SW_Malloc_Int(theStruct.pReconID,pReconID,theStruct.iReconNum,iReconNum);
		iTgtNum = theStruct.iTgtNum;
		SW_Malloc_Struct(sRECON_DATAFUSIONRESULT,theStruct.pRadarReconResult,pRadarReconResult,theStruct.iTgtNum,iTgtNum);

		return *this;
	}
}sRadarReconActState;

//雷达GR行动执行状态
typedef struct _ModelBus_RadarJammerActState
{
	bool bActive;

	/*重载构造函数*/
	_ModelBus_RadarJammerActState()
	{
		bActive = false;

	}

	/*重载析构函数*/
	~_ModelBus_RadarJammerActState()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarJammerActState(const _ModelBus_RadarJammerActState &theStruct)
	{
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarJammerActState& operator=(const _ModelBus_RadarJammerActState& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		return *this;
	}
}sRadarJammerActState;

//导弹行动执行状态
typedef struct _ModelBus_MissileActState
{
	bool bActive;

	/*重载构造函数*/
	_ModelBus_MissileActState()
	{
		bActive = false;

	}

	/*重载析构函数*/
	~_ModelBus_MissileActState()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_MissileActState(const _ModelBus_MissileActState &theStruct)
	{
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_MissileActState& operator=(const _ModelBus_MissileActState& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		bActive = theStruct.bActive;
		return *this;
	}
}sMissileActState;

//行为能力输出基本参数报
typedef struct _ModelBus_Action_Get_PARA
{
	//身份标识
	char*	sRID;				      //身份字符串
	int		ActionID;				 //行为模型ID
	int		PlatID;                //当前平台ID
	int     TaskID;              //任务ID
	float	fTime;				//时间 单位：秒（s）
	bool    bActive;				//所属任务激活状态

	//****************协同信息**************************
	sFormateInfo   FormateInfo;			//所属任务平台编队/编组信息

	//****************组件行为状态**************************
	sPlatActState         PlatActState;         //平台机动状态
	sRadarActState		  RadarActState;  		//雷达行为控制状态
	//sZDRadarActState	  ZDRadarActState;	    //制导雷达行为控制状态
	sRadarReconActState  RadarReconActState;    //雷达ZC装备行为控制状态
	sRadarJammerActState  RadarJammerActState;  //雷达GR装备行为控制状态
	//sCommJammerActState  CommJammerActState;  //通信GR装备行为控制状态
	sMissileActState      MissileActState;		//导弹行为控制状态



	/*重载构造函数*/
	_ModelBus_Action_Get_PARA()
	{
		sRID            = NULL;
		ActionID        = 0;
		PlatID          =0;
		TaskID          = 0;
		fTime           = 0.;
		bActive         = false;
	}

	/*重载析构函数*/
	~_ModelBus_Action_Get_PARA()
	{
		SW_Free_Char(sRID);

	}

	/*重载拷贝构造函数*/
	_ModelBus_Action_Get_PARA(const _ModelBus_Action_Get_PARA &theStruct)
	{
		sRID  = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_Action_Get_PARA& operator=(const _ModelBus_Action_Get_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ActionID  = theStruct.ActionID;
		PlatID	  = theStruct.PlatID;
		TaskID    = theStruct.TaskID;
		fTime    = theStruct.fTime;
		bActive   = theStruct.bActive;
		FormateInfo   = theStruct.FormateInfo;
		PlatActState = theStruct.PlatActState;
		RadarActState = theStruct.RadarActState;
		RadarReconActState = theStruct.RadarReconActState;
		RadarJammerActState = theStruct.RadarJammerActState;
		MissileActState = theStruct.MissileActState;
		return *this;
	}
	/*
	void packToProto(string* &buf)
	{
		tutorial::sAction_Get_PARA ActionPara;

		if(this->sRID != NULL)

		{

			ActionPara.set_srid(this->sRID);

		}
		ActionPara.set_actionid(this->ActionID);

		ActionPara.set_platid(this->PlatID);

		ActionPara.set_taskid(this->TaskID);
		ActionPara.set_ftime(this->fTime);
		ActionPara.set_bactive(this->bActive);



		tutorial::sFormateInfo* tmpFormateInfo = ActionPara.mutable_formateinfo();
		tmpFormateInfo->set_formateid(this->FormateInfo.FormateID);
		tmpFormateInfo->set_leaderplatid(this->FormateInfo.LeaderPlatID);
		tmpFormateInfo->set_nformateplatnum(this->FormateInfo.nFormatePlatNum);
		for(int i=0; i < this->FormateInfo.nFormatePlatNum; i++)
		{
			tmpFormateInfo->add_pformateplatid(this->FormateInfo.pFormatePlatID[i]);
		}

		tutorial::sPlatActState* tmpPlatActState = ActionPara.mutable_platactstate();
		tmpPlatActState->set_bactive(this->PlatActState.bActive);

		tutorial::sRadarActState* tmpRadarActState = ActionPara.mutable_radaractstate();
		tmpRadarActState->set_bactive(this->RadarActState.bActive);

		tutorial::sRadarReconActState* tmpRadarReconActState = ActionPara.mutable_radarreconactstate();
		tmpRadarReconActState->set_bactive(this->RadarReconActState.bActive);
        tmpRadarReconActState->set_ireconnum(this->RadarReconActState.iReconNum);
		for(int i =0 ;i < this->RadarReconActState.iReconNum; i++)
        {
            tmpRadarReconActState->add_preconid(this->RadarReconActState.pReconID[i]);
        }
		tmpRadarReconActState->set_itgtnum(this->RadarReconActState.iTgtNum);
		for(int i =0 ;i < this->RadarReconActState.iTgtNum; i++)
        {
			tutorial::sRECON_DATAFUSIONRESULT *p = tmpRadarReconActState->add_pradarreconresult();
			p->set_radarid(this->RadarReconActState.pRadarReconResult[i].RadarID);
			p->set_radarplatid(this->RadarReconActState.pRadarReconResult[i].RadarPlatID);
			p->set_att(::enumDefine::Enum_ATT(this->RadarReconActState.pRadarReconResult[i].ATT));
			p->set_plattype(this->RadarReconActState.pRadarReconResult[i].PlatType);
			p->set_dangerclass(this->RadarReconActState.pRadarReconResult[i].DangerClass);
			p->set_recogpro(this->RadarReconActState.pRadarReconResult[i].RecogPro);

			tutorial::sReconLocateResult* w = p->mutable_locateresult();
			w->set_reconid(this->RadarReconActState.pRadarReconResult[i].LocateResult.ReconID);
			w->set_targetid(this->RadarReconActState.pRadarReconResult[i].LocateResult.TargetID);
			w->set_esmtype(this->RadarReconActState.pRadarReconResult[i].LocateResult.ESMType);
			w->set_blocatesucceed(this->RadarReconActState.pRadarReconResult[i].LocateResult.bLocateSucceed);
			w->set_frealtargetlon(this->RadarReconActState.pRadarReconResult[i].LocateResult.fRealTargetLon);
			w->set_frealtargetlat(this->RadarReconActState.pRadarReconResult[i].LocateResult.fRealTargetLat);
			w->set_frealtargetheight(this->RadarReconActState.pRadarReconResult[i].LocateResult.fRealTargetHeight);

			w->set_ftargetlon(this->RadarReconActState.pRadarReconResult[i].LocateResult.fTargetLon);
			w->set_ftargetlat(this->RadarReconActState.pRadarReconResult[i].LocateResult.fTargetLat);
			w->set_ftargetheight(this->RadarReconActState.pRadarReconResult[i].LocateResult.fTargetHeight);

			w->set_beepvalid(this->RadarReconActState.pRadarReconResult[i].LocateResult.bEEPValid);
			w->set_x(this->RadarReconActState.pRadarReconResult[i].LocateResult.X);
			w->set_y(this->RadarReconActState.pRadarReconResult[i].LocateResult.Y);
			w->set_a(this->RadarReconActState.pRadarReconResult[i].LocateResult.A);
			w->set_b(this->RadarReconActState.pRadarReconResult[i].LocateResult.B);
			w->set_theta(this->RadarReconActState.pRadarReconResult[i].LocateResult.theta);
			w->set_prob(this->RadarReconActState.pRadarReconResult[i].LocateResult.Prob);
			w->set_cep(this->RadarReconActState.pRadarReconResult[i].LocateResult.CEP);

			p->set_equiptotalnum(this->RadarReconActState.pRadarReconResult[i].equipTotalNum);
			for(int j =0 ;j < this->RadarReconActState.pRadarReconResult[i].equipTotalNum; j++)
			{
				tutorial::sReconPerfo *f = p->add_pequipperfo();
				f->set_reconid(this->RadarReconActState.pRadarReconResult[i].pEquipPerfo[j].ReconID);
				f->set_targetid(this->RadarReconActState.pRadarReconResult[i].pEquipPerfo[j].TargetID);

				f->set_bdoa(this->RadarReconActState.pRadarReconResult[i].pEquipPerfo[j].bDOA);
				f->set_doaerror(this->RadarReconActState.pRadarReconResult[i].pEquipPerfo[j].DOAError);

				f->set_bdtoa(this->RadarReconActState.pRadarReconResult[i].pEquipPerfo[j].bDTOA);
				f->set_dtoaerror(this->RadarReconActState.pRadarReconResult[i].pEquipPerfo[j].DTOAError);

				f->set_bdfoa(this->RadarReconActState.pRadarReconResult[i].pEquipPerfo[j].bDFOA);
				f->set_dfoaerror(this->RadarReconActState.pRadarReconResult[i].pEquipPerfo[j].DFOAError);
			}
		}
		tutorial::sRadarJammerActState* tmpRadarJammerActState = ActionPara.mutable_radarjammeractstate();
		tmpRadarJammerActState->set_bactive(this->RadarJammerActState.bActive);
		tutorial::sMissileActState* tmpMissileActState = ActionPara.mutable_missileactstate();
		tmpMissileActState->set_bactive(this->MissileActState.bActive);

		ActionPara.SerializeToString(buf);
	}
	*/

}sAction_Get_PARA;


//平台控制指令
typedef struct _ModelBus_PlatControlOrder
{
	char*	sRID;			//身份字符串
	int		ActionID;         //行为能力ID
	float	fTime;			//时间 单位：秒（s）
	int		PlatID;				//控制平台ID号
	float   fDir;           //转向的方位角
	/*重载构造函数*/
	_ModelBus_PlatControlOrder()
	{
		sRID               = NULL;
		ActionID             = 0;
		fTime         = 0.;
		PlatID			   = 0;
		fDir     =0;
	}

	/*重载析构函数*/
	~_ModelBus_PlatControlOrder()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_PlatControlOrder(const _ModelBus_PlatControlOrder &theStruct)
	{
		sRID            = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_PlatControlOrder& operator=(const _ModelBus_PlatControlOrder& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ActionID			   = theStruct.ActionID;
		fTime              = theStruct.fTime;
		PlatID			   = theStruct.PlatID;
		fDir            = theStruct.fDir;
		return *this;
	}
}sPlatControlOrder;
//雷达控制指令
typedef struct _ModelBus_RadarControlOrder
{
	char*	sRID;			//身份字符串
	int		ActionID;       //行为能力ID
	float 	fTime;			//时间 单位：秒（s）
	int		RadarID;	   //雷达装备ID
	DKDMS::Enum_WorkState	WorkState;	//工作状态

	/*重载构造函数*/
	_ModelBus_RadarControlOrder()
	{
		sRID             = NULL;
		ActionID          = 0;
		fTime            = 0.;
		RadarID	     = 0;
		WorkState        = DKDMS::Enum_WorkState_0;
	}

	/*重载析构函数*/
	~_ModelBus_RadarControlOrder()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarControlOrder(const _ModelBus_RadarControlOrder &theStruct)
	{
		sRID            = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarControlOrder& operator=(const _ModelBus_RadarControlOrder& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ActionID	   = theStruct.ActionID;
		fTime           = theStruct.fTime;
		RadarID  = theStruct.RadarID;
		WorkState  = theStruct.WorkState;
		//JamTgt = theStruct.JamTgt;
		return *this;
	}
}sRadarControlOrder;


//雷达ZC装备控制指令
typedef struct _ModelBus_RadarReconControlOrder
{
	char*	sRID;			//身份字符串
	int		ActionID;       //行为能力ID
	float 	fTime;			//时间 单位：秒（s）
	int		ReconID;	   //雷达ZC装备ID

	//重点目标/重点区域引导
	float		AZ;								//ZC方位，单位：度
	float		EL;								//ZC俯仰，单位：度


	/*重载构造函数*/
	_ModelBus_RadarReconControlOrder()
	{
		sRID             = NULL;
		ActionID          = 0;
		fTime            = 0.;
		ReconID	     = 0;
		AZ = 0.;
		EL = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_RadarReconControlOrder()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarReconControlOrder(const _ModelBus_RadarReconControlOrder &theStruct)
	{
		sRID            = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarReconControlOrder& operator=(const _ModelBus_RadarReconControlOrder& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ActionID    = theStruct.ActionID;
		fTime       = theStruct.fTime;
		ReconID		= theStruct.ReconID;
		AZ			= theStruct.AZ;
		EL			= theStruct.EL;
		return *this;
	}
}sRadarReconControlOrder;
//雷达GR装备控制指令
typedef struct _ModelBus_RadarJammerControlOrder
{
	char*	sRID;			//身份字符串
	int		ActionID;       //行为能力ID
	float 	fTime;			//时间 单位：秒（s）
	int		JammerID;	   //雷达GR装备ID
	DKDMS::Enum_WorkState	WorkState;	//工作状态
	DKDMS::Enum_RJamType	RJamState;	//GR样式


	//sTgtAllocation JamTgt;		//目标引导？？装备现在做不到被引导，只能接受具体控制参数
	//其他参数

	/*重载构造函数*/
	_ModelBus_RadarJammerControlOrder()
	{
		sRID             = NULL;
		ActionID          = 0;
		fTime            = 0.;
		JammerID	     = 0;
		WorkState        = DKDMS::Enum_WorkState_0;
		RJamState        = DKDMS::Enum_RJamType_0;
	}

	/*重载析构函数*/
	~_ModelBus_RadarJammerControlOrder()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarJammerControlOrder(const _ModelBus_RadarJammerControlOrder &theStruct)
	{
		sRID            = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_RadarJammerControlOrder& operator=(const _ModelBus_RadarJammerControlOrder& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ActionID	   = theStruct.ActionID;
		fTime           = theStruct.fTime;
		JammerID  = theStruct.JammerID;
		WorkState  = theStruct.WorkState;
		RJamState = theStruct.RJamState;
		//JamTgt = theStruct.JamTgt;
		return *this;
	}
}sRadarJammerControlOrder;



//导弹控制指令
typedef struct _ModelBus_MissileControlOrder
{
	char*	sRID;			//身份字符串
	int     ActionID;         //行为能力ID
	float   fTime;			//时间 单位：秒（s）
	int		MissileID;			//控制的武器ID
	DKDMS::MISSILE_STATE	 iMissileState;			//导弹的状态，WAIT为未发射，FIRSTDETECT为中制导，SECONDDETECT为末制导，HITTED为命中目标，NOHITTED为未命中目标,INVALID失效
	int		TgtID;
	float   fTgtLon;				      // 经度,单位:度
	float   fTgtLat;				      // 纬度,单位:度
	float   fTgtHeight;			      // 高度,单位:米(m)
	float	fTgtSpeed;			//运动速度 单位：米/秒（m/s）
	float	fTgtDir;			//运动方位角，单位：度
	float	fTgtPitch;			//横滚角度，单位：度
	float   fMeetTime;          //预测导弹与目标的相遇时间


	/*重载构造函数*/
	_ModelBus_MissileControlOrder()
	{
		sRID               = NULL;
		ActionID            = 0;
		fTime              = 0.;
		MissileID		   = 0;
		iMissileState	   = DKDMS::MISSILE_WAIT;
		TgtID       = 0;
		fTgtLon		= 0.;
		fTgtLat		= 0.;
		fTgtHeight     = 0.;
		fTgtSpeed = 0.;
		fTgtDir = 0.;
		fTgtPitch = 0.;
		fMeetTime = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_MissileControlOrder()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_MissileControlOrder(const _ModelBus_MissileControlOrder &theStruct)
	{
		sRID            = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_MissileControlOrder& operator=(const _ModelBus_MissileControlOrder& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ActionID			   = theStruct.ActionID;
		fTime           = theStruct.fTime;
		MissileID		   = theStruct.MissileID;
		iMissileState      = theStruct.iMissileState;
		TgtID       = theStruct.TgtID;
		fTgtLon		= theStruct.fTgtLon;
		fTgtLat		= theStruct.fTgtLat;
		fTgtHeight  = theStruct.fTgtHeight;
		fTgtSpeed = theStruct.fTgtSpeed;
		fTgtDir = theStruct.fTgtDir;
		fTgtPitch = theStruct.fTgtPitch;
		fMeetTime = theStruct.fMeetTime;
		return *this;
	}
}sMissileControlOrder;


typedef struct _ModelBus_TgtAllocation
{
	int     EquipPlatID;         //装备ID
	int		nTgtNum;        //目标数量
	sRadarDetectPlat*	pTgtInfo;         //目标信息
	/*重载构造函数*/
	_ModelBus_TgtAllocation()
	{
		EquipPlatID = 0;
		nTgtNum = 0;
		pTgtInfo = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_TgtAllocation()
	{
		SW_Delete(pTgtInfo);
	}

	/*重载拷贝构造函数*/
	_ModelBus_TgtAllocation(const _ModelBus_TgtAllocation &theStruct)
	{
		pTgtInfo = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_TgtAllocation& operator=(const _ModelBus_TgtAllocation& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		EquipPlatID = theStruct.EquipPlatID;
		nTgtNum = theStruct.nTgtNum;
		SW_Malloc_Struct(sRadarDetectPlat,theStruct.pTgtInfo,pTgtInfo,theStruct.nTgtNum,nTgtNum);
		return *this;
	}
}sTgtAllocation;

//人工干预/行为模型之间的控制指令
typedef struct _ModelBus_ActionOrder
{
	//身份标识
	char*	   sRID;			        //身份字符串
	int        ActionID;                 //行为模型ID
	int		   PlatID;						//所属平台ID或者装备ID
	int        TaskID;                //任务ID
//	int        FormateID;             //编队ID
	float	   fTime;			//时间 单位：秒（s）
	//****************协同信息**************************
	sFormateInfo   FormateInfo;			//所属任务平台编队/编组信息


	//平台机动控制
	bool              bPlatActive;

	//雷达控制
	bool              bRadarActive;
	bool              bRadarOn;				//僚机的雷达开机控制
	bool              bRadarOff;			//僚机的雷达关机控制

	//ZC装备控制
	bool              bReconActive;
	float             fTgtLat;
	float             fTgtLon;
	float             fTgtHeight;
	bool              bReconFollow;

	//GR装备控制
	bool			  bJamActive;
	bool              bJamOn;				//僚机的GR开机控制
	bool              bJamOff;				//僚机的GR关机控制

	//导弹控制
	bool			  bMissileActive;
	int				  ForceMissileFireTgtID;                //人工干预目标ID
	bool			  bForceMissileFire;                   //导弹发射控制
	int               nMissileNum;                         //导弹数量
	sTgtAllocation*   pMissileTgtAllocation;                //导弹目标分配



	/*重载构造函数*/
	_ModelBus_ActionOrder()
	{
		sRID = NULL;
		ActionID = 0;
		PlatID = 0;
		TaskID = 0;
//		FormateID = 0;
		fTime = 0;
		bPlatActive = false;
		bRadarActive = false;
		bRadarOn = false;
		bRadarOff = false;
		bReconActive = false;
		fTgtLon		= 0.;
		fTgtLat		= 0.;
		fTgtHeight     = 0.;
		bReconFollow = false;
		bJamActive = false;
		bJamOn = false;
		bJamOff = false;
		bMissileActive = false;
		ForceMissileFireTgtID = 0;
		bForceMissileFire = false;
		nMissileNum = 0;
		pMissileTgtAllocation = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_ActionOrder()
	{
		SW_Free_Char(sRID);
		SW_Delete(pMissileTgtAllocation);
	}

	/*重载拷贝构造函数*/
	_ModelBus_ActionOrder(const _ModelBus_ActionOrder &theStruct)
	{
		sRID = NULL;
		pMissileTgtAllocation = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_ActionOrder& operator=(const _ModelBus_ActionOrder& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ActionID = theStruct.ActionID;
		PlatID = theStruct.PlatID;
		TaskID      = theStruct.TaskID;
//		FormateID	= theStruct.FormateID;
		fTime       = theStruct.fTime;
		FormateInfo   = theStruct.FormateInfo;
		bPlatActive = theStruct.bPlatActive;
		bRadarActive = theStruct.bRadarActive;
		bRadarOn = theStruct.bRadarOn;
		bRadarOff = theStruct.bRadarOff;
		bReconActive = theStruct.bReconActive;
		fTgtLon		= theStruct.fTgtLon;
		fTgtLat		= theStruct.fTgtLat;
		fTgtHeight  = theStruct.fTgtHeight;
		bReconFollow = theStruct.bReconFollow;
		bJamActive = theStruct.bJamActive;
		bJamOn = theStruct.bJamOn;
		bJamOff = theStruct.bJamOff;
		bMissileActive = theStruct.bMissileActive;
		ForceMissileFireTgtID = theStruct.ForceMissileFireTgtID;
		bForceMissileFire = theStruct.bForceMissileFire;
		nMissileNum = theStruct.nMissileNum;
		SW_Malloc_Struct(sTgtAllocation,theStruct.pMissileTgtAllocation,pMissileTgtAllocation,theStruct.nMissileNum,nMissileNum);
		return *this;
	}
}sActionOrder;

//
//
////模型接口指令
//typedef struct _ModelBus_ControlOrder
//{
//	int iOrderFlag;//
//	char*   pData;
//	/*重载构造函数*/
//	_ModelBus_ControlOrder()
//	{
//		iOrderFlag = 0;
//		pData = NULL;
//	}
//
//	void Release()
//	{
//		if (iOrderFlag == 1)
//		{
//			sActionOrder* pTemp = (sActionOrder*)pData;
//			SAFE_DELETE(pTemp);
//		}
//		if (iOrderFlag == 2)
//		{
//			sPlatControlOrder* pTemp = (sPlatControlOrder*)pData;
//			SAFE_DELETE(pTemp);
//		}
//		if (iOrderFlag == 3)
//		{
//			sRadarControlOrder* pTemp = (sRadarControlOrder*)pData;
//			SAFE_DELETE(pTemp);
//		}
//		if (iOrderFlag == 4)
//		{
//			sRadarReconControlOrder* pTemp = (sRadarReconControlOrder*)pData;
//			SAFE_DELETE(pTemp);
//		}
//		if (iOrderFlag == 5)
//		{
//			sRadarJammerControlOrder* pTemp = (sRadarJammerControlOrder*)pData;
//			SAFE_DELETE(pTemp);
//		}
//		if (iOrderFlag == 6)
//		{
//			sMissileControlOrder* pTemp = (sMissileControlOrder*)pData;
//			SAFE_DELETE(pTemp);
//		}
//	}
//
//	/*重载析构函数*/
//	~_ModelBus_ControlOrder()
//	{
//		Release();
//	}
//
//	/*重载拷贝构造函数*/
//	_ModelBus_ControlOrder(const _ModelBus_ControlOrder &theStruct)
//	{
//		*this = theStruct;
//		pData = NULL;
//	}
//
//	/*重载=*/
//	_ModelBus_ControlOrder& operator=(const _ModelBus_ControlOrder& theStruct)
//	{
//		if (this == &theStruct)
//		{
//			return *this;
//		}
//		iOrderFlag = theStruct.iOrderFlag;
//		Release();
//		if (iOrderFlag == 1)
//		{
//			sActionOrder* pTemp = new sActionOrder;
//			sActionOrder* pTemptheStruct = (sActionOrder*)theStruct.pData;
//			*pTemp = *pTemptheStruct;
//			pData = (char*)pTemp;
//		}
//		if (iOrderFlag == 1)
//		{
//			sPlatControlOrder* pTemp = new sPlatControlOrder;
//			sPlatControlOrder* pTemptheStruct = (sPlatControlOrder*)theStruct.pData;
//			*pTemp = *pTemptheStruct;
//			pData = (char*)pTemp;
//		}
//		if (iOrderFlag == 1)
//		{
//			sRadarControlOrder* pTemp = new sRadarControlOrder;
//			sRadarControlOrder* pTemptheStruct = (sRadarControlOrder*)theStruct.pData;
//			*pTemp = *pTemptheStruct;
//			pData = (char*)pTemp;
//		}
//		if (iOrderFlag == 1)
//		{
//			sRadarReconControlOrder* pTemp = new sRadarReconControlOrder;
//			sRadarReconControlOrder* pTemptheStruct = (sRadarReconControlOrder*)theStruct.pData;
//			*pTemp = *pTemptheStruct;
//			pData = (char*)pTemp;
//		}
//		if (iOrderFlag == 1)
//		{
//			sRadarJammerControlOrder* pTemp = new sRadarJammerControlOrder;
//			sRadarJammerControlOrder* pTemptheStruct = (sRadarJammerControlOrder*)theStruct.pData;
//			*pTemp = *pTemptheStruct;
//			pData = (char*)pTemp;
//		}
//		if (iOrderFlag == 1)
//		{
//			sMissileControlOrder* pTemp = new sMissileControlOrder;
//			sMissileControlOrder* pTemptheStruct = (sMissileControlOrder*)theStruct.pData;
//			*pTemp = *pTemptheStruct;
//			pData = (char*)pTemp;
//		}
//		return *this;
//	}
//}sActionOrder,sPlatControlOrder,sRadarControlOrder,sRadarReconControlOrder,sRadarJammerControlOrder,sMissileControlOrder;



typedef struct _ModelBus_DATA_SAVE                  //
{
	double x[3][StoreNum];      //X,Y,H position
	double v[3][StoreNum];      //speed value

	unsigned long int  DataNum;   //measurement accept time number
	/*重载构造函数*/
	_ModelBus_DATA_SAVE()
	{
		for (int i = 0 ; i < 3; i++)
		{
			for (int j = 0 ; j < StoreNum; j++)
			{
				x[i][j] = 0;
			}
		}
		for (int i = 0 ; i < 3; i++)
		{
			for (int j = 0 ; j < StoreNum; j++)
			{
				v[i][j] = 0;
			}
		}
		DataNum = 0;
	}

	/*重载析构函数*/
	~_ModelBus_DATA_SAVE()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_DATA_SAVE(const _ModelBus_DATA_SAVE &theStruct)
	{
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_DATA_SAVE& operator=(const _ModelBus_DATA_SAVE& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		for (int i = 0 ; i < 3; i++)
		{
			for (int j = 0 ; j < StoreNum; j++)
			{
				x[i][j] = theStruct.x[i][j];
			}
		}
		for (int i = 0 ; i < 3; i++)
		{
			for (int j = 0 ; j < StoreNum; j++)
			{
				v[i][j] = theStruct.x[i][j];
			}
		}
		DataNum = theStruct.DataNum;
		return *this;

	}
}DATA_SAVE;



#pragma pack()

#endif

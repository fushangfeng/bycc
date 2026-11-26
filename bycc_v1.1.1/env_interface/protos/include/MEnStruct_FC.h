/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.1		按照年(个数位)月日组合的方式	**
**版    本:	2015.04.01  zoubz修改											**
*************************************************************************/

#include "MEnStruct_Macros.h"

#ifndef MEN_STRUCT_FC
#define MEN_STRUCT_FC

#include <string.h>
#pragma pack(1)

namespace DKDMS{//namespace DMS start zm20170912
enum Enum_MissileState
{
	Enum_MissileState_0	= 0,//预留
	Enum_MissileState_1	= 1,//挂载
	Enum_MissileState_2	= 2,//发射
	Enum_MissileState_3	= 3,//归零
	Enum_MissileState_4	= 4,//中制导
	Enum_MissileState_5	= 5,//中末交班
	Enum_MissileState_6	= 6,//自导引
	Enum_MissileState_7	= 7,//引战爆炸
	Enum_MissileState_8	= 8,//自毁
};

enum Enum_FireControlState
{
	Enum_FireControlState_0	= 0,//关机
	Enum_FireControlState_1	= 1,//准备状态
	Enum_FireControlState_2	= 2,//自动加载状态（加载稳定跟踪的最近目标）
	Enum_FireControlState_3	= 3,//引导状态
	Enum_FireControlState_4	= 4,//加载状态
	Enum_FireControlState_5	= 5,//预留
	Enum_FireControlState_6	= 6,//预留
	Enum_FireControlState_7	= 7,//预留
	Enum_FireControlState_8	= 8,//预留
};

typedef enum _eGndAirMSLType
{
	GA_MSL_UN = 0,							/*未知*/
	GA_MSL_GENERAL_CMD,				/*指令制导通用*/
	GA_MSL_GENERAL_COMBINED		/*复合制导通用*/
}eGndAirMSLType;

//dxp:添加导弹包线类型选择参数
//dxp:是否需要计算水平导弹杀伤包线
typedef enum _eGAMSLENVEHorizontal 
{
	GAMSL_ENVE_HORIZONTAL_NEED = 0,              /*选择计算水平导弹杀伤包线*/
	GAMSL_ENVE_HORIZONTAL_NOTNEED                /*不计算水平导弹杀伤包线*/

}eGAMSLENVEHorizontal;
//dxp:是否需要计算垂直导弹杀伤包线
typedef enum _eGAMSLENVEVertical 
{
	GAMSL_ENVE_VERTICAL_NEED = 0,              /*选择计算垂直导弹杀伤包线*/
	GAMSL_ENVE_VERTICAL_NOTNEED                /*不计算垂直导弹杀伤包线*/

}eGAMSLENVEVertical;
//dxp:是否需要计算3D导弹杀伤包线
typedef enum _eGAMSLENVE3D 
{
	GAMSL_ENVE_3D_NEED= 0,              /*选择计算3D导弹杀伤包线*/
	GAMSL_ENVE_3D_NOTNEED               /*不计算3D导弹杀伤包线*/
}eGAMSLENVE3D;

}

// 增加导弹和火控模型 2013.2.15 begin
typedef struct _ModelBus_sMISSILE_Set_PARA
{
	char*	sRID;			//身份字符串
	int		MissileID;		//导弹ID
	int		PlatID;			//平台ID号 
	char*	EquipmentName;	//装备名称
	char*	EquipmentType;	//装备类型
	DKDMS::Enum_ATT	ATT;		//敌我属性
	float	fLon;			//经度，单位：度
	float	fLat;			//纬度，单位：度
	float	fHeight;		//高度，单位：米（m）

	/*重载构造函数*/
	_ModelBus_sMISSILE_Set_PARA()
	{
		sRID          = NULL;
		MissileID	  = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sMISSILE_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sMISSILE_Set_PARA(const _ModelBus_sMISSILE_Set_PARA &theStruct)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sMISSILE_Set_PARA& operator=(const _ModelBus_sMISSILE_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		//SW_Free_Char(EquipmentType);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);

		MissileID	  = theStruct.MissileID;
		PlatID        = theStruct.PlatID;
		ATT           = theStruct.ATT;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		return *this;
	}
}sMISSILE_Set_PARA;

typedef struct _ModelBus_sMISSILE_Get_PARA
{
	char*	sRID;				//身份字符串
	int		MissileID;			//导弹ID
	int		PlatID;				//平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float	fTime;				//时间 单位：秒（s）
	DKDMS::Enum_ATT		ATT;		//敌我属性
	DKDMS::Enum_WorkState	WorkState;	//工作状态
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	float	fLon;				//经度，单位：度
	float	fLat;				//纬度，单位：度
	float	fHeight;			//高度，单位：米（m）
	DKDMS::Enum_MissileState	eMissileState;
	float	fSpeed;				//运动速度 单位：米/秒（m/s）
	float	fDir;				//运动方位角，单位：度
	float	fPitch;				//运动俯仰角，单位：度
	float	fRoll;				//横滚角度，单位：度

	/*重载构造函数*/
	_ModelBus_sMISSILE_Get_PARA()
	{
		sRID			= NULL;
		MissileID		= 0;
		PlatID			= 0;
		EquipmentName	= NULL;
		EquipmentType	= NULL;
		fTime			= 0.;
		ATT				= DKDMS::Enum_ATT_1;
		WorkState		= DKDMS::Enum_WorkState_0;
		SurvivalState	= DKDMS::Enum_SurvivalState_0;
		fLon			= 0.;
		fLat			= 0.;
		fHeight			= 0.;		
		eMissileState	= DKDMS::Enum_MissileState_0;
		fSpeed			= 0.;
		fDir			= 0.;
		fPitch			= 0.;
		fRoll			= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sMISSILE_Get_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sMISSILE_Get_PARA(const _ModelBus_sMISSILE_Get_PARA &theStruct)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sMISSILE_Get_PARA& operator=(const _ModelBus_sMISSILE_Get_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		//SW_Free_Char(EquipmentType);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);

		MissileID		= theStruct.MissileID;
		PlatID          = theStruct.PlatID;
		fTime			= theStruct.fTime;
		ATT				= theStruct.ATT;
		WorkState		= theStruct.WorkState;
		SurvivalState	= theStruct.SurvivalState;
		fLon			= theStruct.fLon;
		fLat			= theStruct.fLat;
		fHeight			= theStruct.fHeight;
		eMissileState	= theStruct.eMissileState;
		fSpeed			= theStruct.fSpeed;
		fDir			= theStruct.fDir;
		fPitch			= theStruct.fPitch;
		fRoll			= theStruct.fRoll;

		return *this;
	}
}sMISSILE_Get_PARA;

//导弹攻击命令交互报
typedef struct _ModelBus_sAttackCmd_PARA
{
	char*	sRID;			//身份字符串
	int		ReceiveID;		//接收ID   
	int		SendID;			//发送ID    
	float	fTime;			//时间
	int		nAttackTargetID;//攻击目标平台ID	
	float	fDMax1g;
	float	fDMax4g;
	float	fDMin1g;
	float	fDMin4g;
	float	fDistance;//敌我距离，<0表示空置未获取
	float	fOpenSeekerTime;//预留：导引头开机时间装订
	float	fOpenSeekerDist;//预留：导引头开机距离装订

	/*重载构造函数*/
	_ModelBus_sAttackCmd_PARA()
	{
		sRID			= NULL;
		ReceiveID		= 0;
		SendID			= 0;
		fTime			= 0.;
		nAttackTargetID	= 0;
		fDMax1g = 80000.;
		fDMax4g = 40000.;
		fDMin1g = 500.;
		fDMin4g = 500.;
		fDistance = -1;//敌我距离，<0表示空置未获取
		fOpenSeekerTime = 0.;//预留：导引头开机时间装订
		fOpenSeekerDist = 0.;//预留：导引头开机距离装订

	}

	/*重载析构函数*/
	~_ModelBus_sAttackCmd_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sAttackCmd_PARA(const _ModelBus_sAttackCmd_PARA &theStruct)
	{
		sRID = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sAttackCmd_PARA& operator=(const _ModelBus_sAttackCmd_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReceiveID		= theStruct.ReceiveID;
		SendID			= theStruct.SendID;
		fTime			= theStruct.fTime;
		nAttackTargetID	= theStruct.nAttackTargetID;
		fDMax1g = theStruct.fDMax1g;
		fDMax4g = theStruct.fDMax4g ;
		fDMin1g = theStruct.fDMin1g ;
		fDMin4g = theStruct.fDMin4g ;
		fDistance = theStruct.fDistance;//敌我距离，<0表示空置未获取
		fOpenSeekerTime = theStruct.fOpenSeekerTime;
		fOpenSeekerDist = theStruct.fOpenSeekerDist;
		return *this;
	}
}sAttackCmd;

//导弹引导信息交互报
typedef struct _ModelBus_sMissileGuideCmd_PARA
{
	char*	sRID;			//身份字符串
	int		ReceiveID;		//接收ID   
	int		SendID;			//发送ID    
	float	fTime;			//时间
	bool	bOpenSeeker;	//预留：导引头开始指令
	float	MessureTargetLon;	//deg	目标位置经度测量值
	float	MessureTargetLat;	//deg	目标位置纬度测量值
	float	MessureTargetAlt;	//m		目标位置高度测量值
	float	MessureTargetPsia;	//deg	目标航向测量值(滤波平滑值)
	float	MessureTargetTheta;	//deg	目标航向测量值(滤波平滑值)
	float	MessureTargetVel;	//m/s	目标速率测量值(滤波平滑值)	
	float	RealityTargetLon;	//deg	目标位置经度真实值
	float	RealityTargetLat;	//deg	目标位置纬度真实值
	float	RealityTargetAlt;	//m		目标位置高度真实值
	float	RealityTargetPsia;	//deg	目标航向真实值
	float	RealityTargetTheta;	//deg	目标航向真实值
	float	RealityTargetVel;	//m/s	目标速率真实值	
	float   DistanceError;      //m     测距误差
	float   DistanceVelError;   //m/s   测速误差
	float   AngleError;         //deg   测角误差
	float   AngleVelError;      //deg/s 侧角速度误差

	/*重载构造函数*/
	_ModelBus_sMissileGuideCmd_PARA()
	{
		sRID				= NULL;
		ReceiveID			= 0;
		SendID				= 0;
		fTime				= 0.;
		bOpenSeeker			= false;	//预留：导引头开始指令
		MessureTargetLon	= 0.;	
		MessureTargetLat	= 0.;	
		MessureTargetAlt	= 0.;	
		MessureTargetPsia	= 0.;	
		MessureTargetTheta	= 0.;	
		MessureTargetVel	= 0.;	
		RealityTargetLon = 0.;	//deg	目标位置经度真实值
		RealityTargetLat = 0.;	//deg	目标位置纬度真实值
		RealityTargetAlt = 0.;	//m		目标位置高度真实值
		RealityTargetPsia = 0.;	//deg	目标航向真实值
		RealityTargetTheta = 0.;	//deg	目标航向真实值
		RealityTargetVel = 0.;	//m/s	目标速率真实值	
		DistanceError = 0.;      //m     测距误差
		DistanceVelError = 0.;   //m/s   测速误差
		AngleError = 0.;         //deg   测角误差
		AngleVelError = 0.;      //deg/s 侧角速度误差
	}

	/*重载析构函数*/
	~_ModelBus_sMissileGuideCmd_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sMissileGuideCmd_PARA(const _ModelBus_sMissileGuideCmd_PARA &theStruct)
	{
		sRID = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sMissileGuideCmd_PARA& operator=(const _ModelBus_sMissileGuideCmd_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReceiveID			= theStruct.ReceiveID;
		SendID				= theStruct.SendID;
		fTime				= theStruct.fTime;
		bOpenSeeker			= theStruct.bOpenSeeker;
		MessureTargetLon	= theStruct.MessureTargetLon;	
		MessureTargetLat	= theStruct.MessureTargetLat;	
		MessureTargetAlt	= theStruct.MessureTargetAlt;	
		MessureTargetPsia	= theStruct.MessureTargetPsia;	
		MessureTargetTheta	= theStruct.MessureTargetTheta;	
		MessureTargetVel	= theStruct.MessureTargetVel;	
		RealityTargetLon = 0.;	//deg	目标位置经度真实值
		RealityTargetLat = 0.;	//deg	目标位置纬度真实值
		RealityTargetAlt = 0.;	//m		目标位置高度真实值
		RealityTargetPsia = 0.;	//deg	目标航向真实值
		RealityTargetTheta = 0.;	//deg	目标航向真实值
		RealityTargetVel = 0.;	//m/s	目标速率真实值	
		DistanceError = 0.;      //m     测距误差
		DistanceVelError = 0.;   //m/s   测速误差
		AngleError = 0.;         //deg   测角误差
		AngleVelError = 0.;      //deg/s 侧角速度误差
		return *this;
	}
}sMissileGuideCmd;

//导弹攻击结束交互报
typedef struct _ModelBus_sAttackEnd_PARA
{
	char*	sRID;			//身份字符串
	int		ReceiveID;		//接收ID   
	int		SendID;			//发送ID    
	float	fTime;			//时间
	bool	bHit;			//是否命中
	float	fMissDistance;	//脱靶量，单位：m

	/*重载构造函数*/
	_ModelBus_sAttackEnd_PARA()
	{
		sRID			= NULL;
		ReceiveID		= 0;
		SendID			= 0;
		fTime			= 0.;
		bHit			= false;
		fMissDistance	= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sAttackEnd_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sAttackEnd_PARA(const _ModelBus_sAttackEnd_PARA &theStruct)
	{
		sRID = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sAttackEnd_PARA& operator=(const _ModelBus_sAttackEnd_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReceiveID		= theStruct.ReceiveID;
		SendID			= theStruct.SendID;
		fTime			= theStruct.fTime;
		bHit			= theStruct.bHit;
		fMissDistance	= theStruct.fMissDistance;

		return *this;
	}
}sAttackEnd;

// 火控初始化输入
typedef struct _ModelBus_sFC_Set_PARA
{
	char*	sRID;			//身份字符串
	int		FCID;			//火控ID
	int		PlatID;			//平台ID号 
	char*	EquipmentName;	//装备名称
	char*	EquipmentType;	//装备类型
	DKDMS::Enum_ATT	ATT;		//敌我属性

	/*重载构造函数*/
	_ModelBus_sFC_Set_PARA()
	{
		sRID          = NULL;
		FCID		  = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
	}

	/*重载析构函数*/
	~_ModelBus_sFC_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sFC_Set_PARA(const _ModelBus_sFC_Set_PARA &theStruct)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sFC_Set_PARA& operator=(const _ModelBus_sFC_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		//SW_Free_Char(EquipmentType);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);

		FCID		  = theStruct.FCID;
		PlatID        = theStruct.PlatID;
		ATT           = theStruct.ATT;

		return *this;
	}
}sFC_Set_PARA;

// 火控对象类输出
typedef struct _ModelBus_sFC_Get_PARA
{
	char*	sRID;				//身份字符串
	int		FCID;				//火控ID
	int		PlatID;				//平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float	fTime;				//时间 单位：秒（s）
	DKDMS::Enum_ATT		ATT;		//敌我属性
	DKDMS::Enum_FireControlState	FCState;	//工作状态
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	int		TargetID;// <0表示空置
	int		MissileID;// <0表示空置
	float	fDMax1g;
	float	fDMax4g;
	float	fDMin1g;
	float	fDMin4g;
	float	fDistance;//敌我距离，<0表示空置未获取
	

	/*重载构造函数*/
	_ModelBus_sFC_Get_PARA()
	{
		sRID			= NULL;
		FCID			= 0;
		PlatID			= 0;
		EquipmentName	= NULL;
		EquipmentType	= NULL;
		fTime			= 0.;
		ATT				= DKDMS::Enum_ATT_1;
		FCState		= DKDMS::Enum_FireControlState_1;
		SurvivalState	= DKDMS::Enum_SurvivalState_0;
		TargetID = -1;// <0表示空置
		MissileID = -1;// <0表示空置
		fDMax1g = 80000.;
		fDMax4g = 40000.;
		fDMin1g = 500.;
		fDMin4g = 500.;
		fDistance = -1;//敌我距离，<0表示空置未获取
	}

	/*重载析构函数*/
	~_ModelBus_sFC_Get_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sFC_Get_PARA(const _ModelBus_sFC_Get_PARA &theStruct)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sFC_Get_PARA& operator=(const _ModelBus_sFC_Get_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		//SW_Free_Char(EquipmentType);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);

		FCID			= theStruct.FCID;
		PlatID          = theStruct.PlatID;
		fTime			= theStruct.fTime;
		ATT				= theStruct.ATT;
		FCState		= theStruct.FCState;
		SurvivalState	= theStruct.SurvivalState;
		TargetID = theStruct.TargetID;// <0表示空置
		MissileID = theStruct.MissileID ;// <0表示空置
		fDMax1g = theStruct.fDMax1g;
		fDMax4g = theStruct.fDMax4g ;
		fDMin1g = theStruct.fDMin1g ;
		fDMin4g = theStruct.fDMin4g ;
		fDistance = theStruct.fDistance;//敌我距离，<0表示空置未获取

		return *this;
	}
}sFC_Get_PARA;


//攻击区包络
typedef struct _ModelBus_sATTACK_RANGE
{
	char*	sRID;		//身份字符串
	int		ID;			//火控ID  
	int     TrgID;      //目标ID
	float	fTime;		//时间 单位：s
	float	fLon;       //中心（目标）经度
	float	fLat;		//中心（目标）纬度
	float	fHeight;	//中心（目标）高度
	int		nLayerCount;//包络层数
	int		nLayerPointCount;//每层包络点数
	int		nTotalPointCount;//包络点总数
	sPZone* ZonePoint;	//包络点

	/*重载构造函数*/
	_ModelBus_sATTACK_RANGE()
	{
		sRID          = NULL;
		ID			  = 0;
        TrgID		  = 0;
		fTime         = 0.;
		fLon		  = 0.;
		fLat		  = 0.;
		fHeight		  = 0.;
		nLayerCount	  = 0;
		nLayerPointCount = 36;
		nTotalPointCount = 0;
		ZonePoint     = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sATTACK_RANGE()
	{
		SW_Free_Char(sRID);
		SW_Delete(ZonePoint);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sATTACK_RANGE(const _ModelBus_sATTACK_RANGE &jam)
	{
		sRID = NULL;
		ZonePoint = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sATTACK_RANGE& operator=(const _ModelBus_sATTACK_RANGE& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Delete(ZonePoint);
		SW_Malloc_Struct(sPZone,theStruct.ZonePoint,ZonePoint,theStruct.nTotalPointCount, nTotalPointCount);

		ID				= theStruct.ID;
		TrgID			= theStruct.TrgID;
		fTime           = theStruct.fTime;
		fLon			= theStruct.fLon;
		fLat			= theStruct.fLat;
		fHeight			= theStruct.fHeight;
		nLayerCount		= theStruct.nLayerCount;
		nLayerPointCount		= theStruct.nLayerPointCount;
		nTotalPointCount		= theStruct.nTotalPointCount;

		return *this;
	}
}sATTACK_RANGE_Max1g,sATTACK_RANGE_Max4g,sATTACK_RANGE_Min1g,sATTACK_RANGE_Min4g;


// 增加导弹和火控模型 end

#define	GNDAIR_MSL_CMD_MAX_PNT_PER_SURFACE	(1024)

typedef struct _sGndAirMSLCfg
{
	char*	sRID;		//身份字符串
	DKDMS::eGndAirMSLType	m_MSLType;
	DKDMS::eGAMSLENVEHorizontal  m_EnvelopeHorizontal;    /*选择是否计算水平导弹杀伤包线*/
	DKDMS::eGAMSLENVEVertical m_EnvelopeVertical;        /*选择是否计算垂直导弹杀伤包线*/
	DKDMS::eGAMSLENVE3D  m_Envelope3D;     /*选择是否计算3D导弹杀伤包线*/
	float	m_HeightMax;			/*杀伤区高度上限，KM*/
	float	m_HeightMin;			/*杀伤区高度下限，KM*/
	float	m_AttackShortcutMax;	/*杀伤区最大航路捷径，KM*/
	float	m_AttackDistanceMax;	/*导弹最大射程，KM*/
	float	m_AttackDistanceMin;	/*导弹最小射程，KM*/
	float	m_ElpsilonMax;			/*地空导弹最大高低角，弧度*/
	float	m_QMax;					/*攻击区最大航路角，即目标相对于导弹指向的方位角，弧度*/
	float	m_HeightAntenna;		/*天线架设高度，KM*/
	float	m_TimeFanYing;			/*地空导弹系统反应时间，s*/
	float	m_TImeFeiXing;			/*导弹对应最大射程的飞行时间，s*/
	float	m_TimeGaoJiaoJie;		/*高交界时间，s*/

	float	m_HeightInterval;		/*高度离散化步长*/
	float	m_AttackShortcutInterval;	/*航路捷径离散化步长*/
	float	m_SValueInterval;		/*S坐标离散化步长*/

	/*构造函数*/
	_sGndAirMSLCfg()
	{
		Reset();
	}

	/*析构函数*/
	~_sGndAirMSLCfg()
	{
		SW_Free_Char(sRID);
		Reset();
	}

	/*拷贝构造函数*/
	_sGndAirMSLCfg(const _sGndAirMSLCfg &a_rRHS)
	{
		Reset();
		*this = a_rRHS;
	}

	/*=*/
	_sGndAirMSLCfg& operator=(const _sGndAirMSLCfg& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			//SW_Free_Char(sRID);
			SW_Malloc_Char(a_rRHS.sRID,sRID);

			m_MSLType = a_rRHS.m_MSLType;
			m_EnvelopeHorizontal = a_rRHS.m_EnvelopeHorizontal;
			m_EnvelopeVertical = a_rRHS.m_EnvelopeVertical;
			m_Envelope3D = a_rRHS.m_Envelope3D;
			m_HeightMax = a_rRHS.m_HeightMax;
			m_HeightMin = a_rRHS.m_HeightMin;
			m_AttackShortcutMax = a_rRHS.m_AttackShortcutMax;
			m_AttackDistanceMax = a_rRHS.m_AttackDistanceMax;
			m_AttackDistanceMin = a_rRHS.m_AttackDistanceMin;
			m_ElpsilonMax = a_rRHS.m_ElpsilonMax;
			m_QMax = a_rRHS.m_QMax;
			m_HeightAntenna = a_rRHS.m_HeightAntenna;
			m_TimeFanYing = a_rRHS.m_TimeFanYing;
			m_TImeFeiXing = a_rRHS.m_TImeFeiXing;
			m_TimeGaoJiaoJie = a_rRHS.m_TimeGaoJiaoJie;

			m_HeightInterval = a_rRHS.m_HeightInterval;
			m_AttackShortcutInterval = a_rRHS.m_AttackShortcutInterval;
			m_SValueInterval = a_rRHS.m_SValueInterval;
		}

		return *this;
	}

	void Reset()
	{
		sRID          = NULL;
		m_MSLType = DKDMS::GA_MSL_UN;
		m_EnvelopeHorizontal = DKDMS::GAMSL_ENVE_HORIZONTAL_NEED;
		m_EnvelopeVertical = DKDMS::GAMSL_ENVE_VERTICAL_NEED;
		m_Envelope3D = DKDMS::GAMSL_ENVE_3D_NEED;

		m_HeightMax = 0.0f;
		m_HeightMin = 0.0f;
		m_AttackShortcutMax = 0.0f;
		m_AttackDistanceMax = 0.0f;
		m_AttackDistanceMin = 0.0f;
		m_ElpsilonMax = 0.0f;
		m_QMax = 0.0f;
		m_HeightAntenna = 0.0f;
		m_TimeFanYing = 0.0f;
		m_TImeFeiXing = 0.0f;
		m_TimeGaoJiaoJie = 0.0f;

		m_HeightInterval = 0.0f;
		m_AttackShortcutInterval = 0.0f;
		m_SValueInterval = 0.0f;
	}
}sGndAirMSLCfg;

/*相对于制导站的坐标*/
typedef struct _sPosRelatToTracker 
{
	float	m_SValue;		/*S轴：水平面内与目标飞行航向相反方向上的距离*/
	float	m_Shortcut;		/*航路捷径轴，水平面内与目标航向垂直*/
	float	m_Height;		/*高度轴：垂直方向*/

	/*构造函数*/
	_sPosRelatToTracker()
	{
		Reset();
	}

	/*析构函数*/
	~_sPosRelatToTracker()
	{
		Reset();
	}

	/*拷贝构造函数*/
	_sPosRelatToTracker(const _sPosRelatToTracker &a_rRHS)
	{
		*this = a_rRHS;
	}

	/*=*/
	_sPosRelatToTracker& operator=(const _sPosRelatToTracker& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			m_SValue = a_rRHS.m_SValue;
			m_Shortcut = a_rRHS.m_Shortcut;
			m_Height = a_rRHS.m_Height;
		}

		return *this;
	}

	void Reset()
	{
		m_SValue = 0.0f;
		m_Shortcut = 0.0f;
		m_Height = 0.0f;
	}
}PosRelatToTracker;

/*三维曲面结构*/
typedef struct _sEnvelopeSurface
{
	unsigned int		m_ValidPntCnt;
	PosRelatToTracker	m_PointArray[1024];//GNDAIR_MSL_CMD_MAX_PNT_PER_SURFACE

	/*构造函数*/
	_sEnvelopeSurface()
	{
		Reset();
	}

	/*析构函数*/
	~_sEnvelopeSurface()
	{
		Reset();
	}

	/*拷贝构造函数*/
	_sEnvelopeSurface(const _sEnvelopeSurface &a_rRHS)
	{
		*this = a_rRHS;
	}

	/*=*/
	_sEnvelopeSurface& operator=(const _sEnvelopeSurface& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			m_ValidPntCnt = a_rRHS.m_ValidPntCnt;
			for (unsigned int t_Cnt=0; t_Cnt<GNDAIR_MSL_CMD_MAX_PNT_PER_SURFACE; t_Cnt++)
			{
				m_PointArray[t_Cnt] = a_rRHS.m_PointArray[t_Cnt];
			}
		}

		return *this;
	}

	_sEnvelopeSurface& operator+=(const _sEnvelopeSurface& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			for (unsigned int t_Cnt=0; t_Cnt<a_rRHS.m_ValidPntCnt; t_Cnt++)
			{
				if (m_ValidPntCnt < GNDAIR_MSL_CMD_MAX_PNT_PER_SURFACE)
				{
					m_PointArray[m_ValidPntCnt] = a_rRHS.m_PointArray[t_Cnt];
					m_ValidPntCnt++;
				}
				else
				{
					break;
				}
			}
		}

		return *this;
	}

	void Reset()
	{
		m_ValidPntCnt = 0;
		for (unsigned int t_Cnt=0; t_Cnt<GNDAIR_MSL_CMD_MAX_PNT_PER_SURFACE; t_Cnt++)
		{
			m_PointArray[t_Cnt].Reset();
		}
	}
}EnvelopeSurface;

/*水平导弹杀伤区*/
typedef struct _sMissileEnvelopeHorizontal
{
	EnvelopeSurface	m_NearSurfaceHorizontal;	/*近界曲面*/
	EnvelopeSurface	m_FarSurfaceHorizontal;	/*远界曲面*/
	EnvelopeSurface	m_UpperSurfaceHorizontal;	/*高界曲面*/
	EnvelopeSurface	m_LowerSurfaceHorizontal;	/*低界曲面*/

	/*构造函数*/
	_sMissileEnvelopeHorizontal()
	{
		Reset();
	}

	/*析构函数*/
	~_sMissileEnvelopeHorizontal()
	{
		Reset();
	}

	/*拷贝构造函数*/
	_sMissileEnvelopeHorizontal(const _sMissileEnvelopeHorizontal &a_rRHS)
	{
		Reset();
		*this = a_rRHS;
	}

	/*=*/
	_sMissileEnvelopeHorizontal& operator=(const _sMissileEnvelopeHorizontal& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			m_NearSurfaceHorizontal = a_rRHS.m_NearSurfaceHorizontal;
			m_FarSurfaceHorizontal = a_rRHS.m_FarSurfaceHorizontal;
			m_UpperSurfaceHorizontal = a_rRHS.m_UpperSurfaceHorizontal;
			m_LowerSurfaceHorizontal = a_rRHS.m_LowerSurfaceHorizontal;
		}
		return *this;
	}

	void Reset()
	{
		m_NearSurfaceHorizontal.Reset();
		m_FarSurfaceHorizontal.Reset();
		m_UpperSurfaceHorizontal.Reset();
		m_LowerSurfaceHorizontal.Reset();
	}
}MissileEnvelopeHorizontal;

/*垂直导弹杀伤区*/
typedef struct _sMissileEnvelopeVertical
{
	EnvelopeSurface	m_NearSurfaceVertical;	/*近界曲面*/
	EnvelopeSurface	m_FarSurfaceVertical;	/*远界曲面*/
	EnvelopeSurface	m_UpperSurfaceVertical;	/*高界曲面*/
	EnvelopeSurface	m_LowerSurfaceVertical;	/*低界曲面*/

	/*构造函数*/
	_sMissileEnvelopeVertical()
	{
		Reset();
	}

	/*析构函数*/
	~_sMissileEnvelopeVertical()
	{
		Reset();
	}

	/*拷贝构造函数*/
	_sMissileEnvelopeVertical(const _sMissileEnvelopeVertical &a_rRHS)
	{
		Reset();
		*this = a_rRHS;
	}

	/*=*/
	_sMissileEnvelopeVertical& operator=(const _sMissileEnvelopeVertical& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			m_NearSurfaceVertical = a_rRHS.m_NearSurfaceVertical;
			m_FarSurfaceVertical = a_rRHS.m_FarSurfaceVertical;
			m_UpperSurfaceVertical = a_rRHS.m_UpperSurfaceVertical;
			m_LowerSurfaceVertical = a_rRHS.m_LowerSurfaceVertical;
		}
		return *this;
	}

	void Reset()
	{
		m_NearSurfaceVertical.Reset();
		m_FarSurfaceVertical.Reset();
		m_UpperSurfaceVertical.Reset();
		m_LowerSurfaceVertical.Reset();
	}
}MissileEnvelopeVertical;


/*3D导弹杀伤区*/
typedef struct _sMissileEnvelope3D
{
	EnvelopeSurface	m_NearSurface3D;	/*近界曲面*/
	EnvelopeSurface	m_FarSurface3D;	    /*远界曲面*/
	EnvelopeSurface	m_UpperSurface3D;	/*高界曲面*/
	EnvelopeSurface	m_LowerSurface3D;	/*低界曲面*/

	/*构造函数*/
	_sMissileEnvelope3D()
	{
		Reset();
	}

	/*析构函数*/
	~_sMissileEnvelope3D()
	{
		Reset();
	}

	/*拷贝构造函数*/
	_sMissileEnvelope3D(const _sMissileEnvelope3D &a_rRHS)
	{
		Reset();
		*this = a_rRHS;
	}

	/*=*/
	_sMissileEnvelope3D& operator=(const _sMissileEnvelope3D& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			m_NearSurface3D = a_rRHS.m_NearSurface3D;
			m_FarSurface3D = a_rRHS.m_FarSurface3D;
			m_UpperSurface3D = a_rRHS.m_UpperSurface3D;
			m_LowerSurface3D = a_rRHS.m_LowerSurface3D;
		}

		return *this;
	}

	void Reset()
	{
		m_NearSurface3D.Reset();
		m_FarSurface3D.Reset();
		m_UpperSurface3D.Reset();
		m_LowerSurface3D.Reset();
	}
}MissileEnvelope3D;

/*导弹杀伤区*/
typedef struct _sMissileEnvelope
{
	char*	sRID;		//身份字符串
    int     ZdzhanID;               //制导站ID
	MissileEnvelopeHorizontal  m_MissEnveHorizontal;
	MissileEnvelopeVertical  m_MissEnveVertical;
	MissileEnvelope3D  m_MissEnve3D;

	/*构造函数*/
	_sMissileEnvelope()
	{
		Reset();
	}

	/*析构函数*/
	~_sMissileEnvelope()
	{
		SW_Free_Char(sRID);
		Reset();
	}

	/*拷贝构造函数*/
	_sMissileEnvelope(const _sMissileEnvelope &a_rRHS)
	{
		Reset();
		*this = a_rRHS;
	}

	/*=*/
	_sMissileEnvelope& operator=(const _sMissileEnvelope& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			//SW_Free_Char(sRID);
			SW_Malloc_Char(a_rRHS.sRID,sRID);
			ZdzhanID = a_rRHS.ZdzhanID;
			m_MissEnveHorizontal = a_rRHS.m_MissEnveHorizontal;
			m_MissEnveVertical = a_rRHS.m_MissEnveVertical;
			m_MissEnve3D = a_rRHS.m_MissEnve3D;
		}

		return *this;
	}

	void Reset()
	{
		sRID          = NULL;
		ZdzhanID      = 0;
		m_MissEnveHorizontal.Reset();
		m_MissEnveVertical.Reset();
		m_MissEnve3D.Reset();
	}
}MissileEnvelope;

/*目标RCS描述*/
typedef struct _sTARGETRCS
{
	float	fTime;			/*所属时刻*/
// 	float	fDir;			//运动方位角，单位：度
// 	float	fPitch;			//运动俯仰角，单位：度
// 	float	fRoll;			//横滚角度，单位：度
// 	float   fRF;			//频率，MHz
	float	fHeight;		/*目标当前高度*/
	float	fRCS;			/*回波面积，单位：平方米（m^2）*/

	/*构造函数*/
	_sTARGETRCS()
	{
		Reset();
	}

	/*析构函数*/
	~_sTARGETRCS()
	{
		Reset();
	}

	/*拷贝构造函数*/
	_sTARGETRCS(const _sTARGETRCS &a_rRHS)
	{
		*this = a_rRHS;
	}

	/*=*/
	_sTARGETRCS& operator=(const _sTARGETRCS& a_rRHS)
	{
		if (this != &a_rRHS)
		{
			fTime = a_rRHS.fTime;
// 			fDir = a_rRHS.fDir;
// 			fPitch = a_rRHS.fPitch;
// 			fRoll = a_rRHS.fRoll;
			fHeight = a_rRHS.fHeight;
			fRCS = a_rRHS.fRCS;
		}

		return *this;
	}

	void Reset()
	{
		fTime = 0.0f;
// 		fDir          = 0.;
// 		fPitch        = 0.;
// 		fRoll         = 0.;
		fHeight = 0.0f;
		fRCS = 0.0f;
	}
}TargetRCS;

/*目标RCS参数，目前只针对四代机任务规划*/
typedef struct _ModelBus_sTARGET_RCS_PARA
{
	int		TargetID;		//被TC目标ID号
	int     nRCSNum;        //RCS个数
	TargetRCS*	RCSArray;	//RCS参数（以时间为索引）

	/*重载构造函数*/
	_ModelBus_sTARGET_RCS_PARA()
	{
		TargetID      = -1;
		nRCSNum       = 0;
		RCSArray      = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sTARGET_RCS_PARA()
	{
		SW_Delete(RCSArray);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sTARGET_RCS_PARA(const _ModelBus_sTARGET_RCS_PARA &plat)
	{
		RCSArray = NULL;
		*this = plat;
	}

	/*重载=*/
	_ModelBus_sTARGET_RCS_PARA& operator=(const _ModelBus_sTARGET_RCS_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		//SW_Delete(RCSArray);
		SW_Malloc_Struct(TargetRCS,theStruct.RCSArray,RCSArray,theStruct.nRCSNum, nRCSNum);

		TargetID	  = theStruct.TargetID;
		nRCSNum       = theStruct.nRCSNum;
		return *this;
	}

}Target_RCS_Para;

//雷达TC目标RCS参数结构体定义，目前只针对四代机任务规划
typedef struct _ModelBus_sRADAR_TARGET_RCS
{
	char*	sRID;			//身份字符串
	int		RadarID;		//雷达ID号 
	int     nTargetNum;     //目标个数                           
	Target_RCS_Para*	TargetRCSArray;	//目标RCS参数

	/*重载构造函数*/
	_ModelBus_sRADAR_TARGET_RCS()
	{
		sRID          = NULL;
		RadarID       = 0;
		nTargetNum       = 0;
		TargetRCSArray      = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_TARGET_RCS()
	{
		SW_Free_Char(sRID);
		SW_Delete(TargetRCSArray);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_TARGET_RCS(const _ModelBus_sRADAR_TARGET_RCS &plat)
	{
		sRID = NULL;
		TargetRCSArray = NULL;
		*this = plat;
	}

	/*重载=*/
	_ModelBus_sRADAR_TARGET_RCS& operator=(const _ModelBus_sRADAR_TARGET_RCS& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Delete(TargetRCSArray);
		SW_Malloc_Struct(Target_RCS_Para,theStruct.TargetRCSArray,TargetRCSArray,theStruct.nTargetNum, nTargetNum);

		RadarID		  = theStruct.RadarID;
		nTargetNum       = theStruct.nTargetNum;
		return *this;
	}
}sRadar_Target_RCS;

#pragma pack()

#endif
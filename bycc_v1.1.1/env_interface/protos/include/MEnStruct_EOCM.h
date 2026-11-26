//MK36通用结构体
#include <stdlib.h>
#include "MEnStruct_Macros.h"
#include"MEnStruct_Common.h"
#include"MEnStruct_EO.h"
#pragma once
#pragma pack(push)
#pragma pack(1)

namespace DKDMS{
#ifndef Enum_MK36Pos_DEF
#define Enum_MK36Pos_DEF
enum Enum_MK36Pos {
	Enum_MK36Pos_LF = 0, //左前
	Enum_MK36Pos_RF = 1, //右前
	Enum_MK36Pos_LB = 2, //左后
	Enum_MK36Pos_RB = 3,
};
#endif
}

typedef struct _ModelBus_aEOTarget_Set_INI        //SimModelDataOut.proto
{
    char* sRID;//! @Properties(description=仿真id, alias=simuId, display=readonly)
    int DeviceID;//! @Properties(description=装备id, alias=modelId, display=readonly)
    int PlatID; //! @Properties(description=平台id, alias=platformId, display=readonly)
    DKDMS::Enum_PlatType platType;//! @Properties(description=平台类型, defaultValue=5)
    double dRadiancy; //! @Properties(description=目标红外辐射强度, unit=w/sr, defaultValue=100)
    double UltravioletRadiaIntensity;//! @Properties(description=目标紫外辐射强度, unit=w/sr, defaultValue=0.93)
    double PeakPower0;//! @Properties(description=激光器输出能量峰值P0, unit=w, defaultValue=10000000)
    double LaserPower;//! @Properties(description=激光能量功率, unit=w, defaultValue=30000000)
    double LaserAngle; //! @Properties(description=激光发散角, unit=弧度, defaultValue=0.001)
    _ModelBus_aEOTarget_Set_INI()
    {
        sRID           = NULL;
        DeviceID=0;
        PlatID=0;
        platType = DKDMS::Enum_PlatType_0;
        dRadiancy = 0.0;
        UltravioletRadiaIntensity = 0.0;
        PeakPower0 = 0.0;
        LaserPower = 0.0;
        LaserAngle = 0.0;

    }
    ~_ModelBus_aEOTarget_Set_INI()
    {
        SW_Free_Char(sRID);
    }
    _ModelBus_aEOTarget_Set_INI(const _ModelBus_aEOTarget_Set_INI& info)
    {
        sRID = NULL;
               *this = info;
    }
    _ModelBus_aEOTarget_Set_INI& operator=(const _ModelBus_aEOTarget_Set_INI& info)
    {
        if( this==&info )
        {
            return *this;
        }
        SW_Malloc_Char(info.sRID,sRID);
        DeviceID  = info.DeviceID;
        PlatID = info.PlatID;
        platType = info.platType;
        dRadiancy = info.dRadiancy;
        UltravioletRadiaIntensity = info.UltravioletRadiaIntensity;
        PeakPower0 = info.PeakPower0;
        LaserPower = info.LaserPower;
        LaserAngle = info.LaserAngle;

        return *this;
    }
}aEOTarget_Set_INI;//SimModelDataOut.proto
//! @Properties(description=光电目标, appType=init, id=29)
typedef struct _ModelBus_sEOTarget_Set_INI   //SimModelDataOut.proto
{
	char* sRID;//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int DeviceID;//! @Properties(description=装备id, alias=modelId, display=readonly)
	int PlatID;  //! @Properties(description=平台id, alias=platformId, display=readonly)
	DKDMS::Enum_PlatType platType;//! @Properties(description=平台类型, defaultValue=5)
	double dRadiancy; //! @Properties(description=目标红外辐射强度, unit=w/sr, defaultValue=100)
	double UltravioletRadiaIntensity;//! @Properties(description=目标紫外辐射强度, unit=w/sr, defaultValue=0.93)
	double PeakPower0;//! @Properties(description=激光器输出能量峰值P0, unit=w, defaultValue=10000000)
	double LaserPower;//! @Properties(description=激光能量功率, unit=w, defaultValue=30000000)
	double LaserAngle; //! @Properties(description=激光发散角, unit=弧度, defaultValue=0.001)

	_ModelBus_sEOTarget_Set_INI()
	{
		sRID           = NULL;
		DeviceID=0;
		PlatID=0;
		platType = DKDMS::Enum_PlatType_0;
		dRadiancy = 0.0;
		UltravioletRadiaIntensity = 0.0;
		PeakPower0 = 0.0;
		LaserPower = 0.0;
		LaserAngle = 0.0;

	}
	~_ModelBus_sEOTarget_Set_INI()
	{
		SW_Free_Char(sRID);
	}
	_ModelBus_sEOTarget_Set_INI(const _ModelBus_sEOTarget_Set_INI& info)
	{
		sRID = NULL;
		*this = info;
	}
	_ModelBus_sEOTarget_Set_INI& operator=(const _ModelBus_sEOTarget_Set_INI& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);
		DeviceID  = info.DeviceID;
		PlatID = info.PlatID;
		platType = info.platType;
		dRadiancy = info.dRadiancy;
		UltravioletRadiaIntensity = info.UltravioletRadiaIntensity;
		PeakPower0 = info.PeakPower0;
		LaserPower = info.LaserPower;
		LaserAngle = info.LaserAngle;

		return *this;
	}
}sEOTarget_Set_INI;//SimModelDataOut.proto
//	仿真场景数据
typedef struct _ModelBus_Set_ENV  //SimModelDataOut.proto
{
    char* sRID;
    int DeviceID;//实例ID
    double FX;//环境风向//正北为0度，北偏东为正
    double FS;//环境风速（单位：？）
    double FY;//风向俯仰
    double Airtrans_IR;//大气透过率红外（取值范围）
	double Airtrans_UV;//大气透过率紫外
	double Visibility;//能见度（米）
	/*重载构造函数*/
    _ModelBus_Set_ENV()
    {
        sRID           = NULL;
        DeviceID = 0;
        FX = 0.;
        FS = 0.;
        FY = 0.;
        Airtrans_IR = 0.;
		 Airtrans_UV=0.;
		Visibility=0.;
		
    }
	/*重载析构函数*/
    ~_ModelBus_Set_ENV()
    {
        SW_Free_Char(sRID);
       
    }
	/*重载拷贝构造函数*/
    _ModelBus_Set_ENV(const _ModelBus_Set_ENV& env)
    {
        sRID = NULL;
        *this = env;
    }
	/*重载=*/
    _ModelBus_Set_ENV& operator=(const _ModelBus_Set_ENV& env)
    {
        if( this==&env )
        {
            return *this;
        }
        SW_Malloc_Char(env.sRID,sRID);
        DeviceID = env.DeviceID;//实例ID
        FX = env.FX;//环境风向
        FS = env.FS;//环境风速
        FY = env.FY;//风向俯仰
        Airtrans_IR = env.Airtrans_IR;//大气透过率
		Airtrans_UV = env.Airtrans_UV;//大气透过率紫外
		Visibility=env.Visibility;//能见度（米）
        return *this;
    }
}Set_ENV;//SimModelDataOut.proto


//! @Properties(description=箔条, appType=init, id=28)
typedef struct _ModelBus_sCHAFF_Set_INI  //SimModelDataOut.proto
{
    char* sRID;//! @Properties(description=仿真id, alias=simuId, display=readonly)
    int DeviceID;//! @Properties(description=装备id, alias=modelId, display=readonly)
    int PlatID; 	//! @Properties(description=平台id, alias=platformId, display=readonly)
	  char*	EquipmentName;		//! @Properties(description=装备名称, alias=equipName)
	  char*	EquipmentType;			//! 装备类型
	  DKDMS::Enum_ATT		ATT;	//! @Properties(description=敌我属性, alias=iff, display=readonly)
	  DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作属性, defaultValue=1)
	  int ControlDeviceID;//! 引导发射箔条的ZC控制设备(如SLQ32)ID(自主引导则不填)
	  double vec;//！发射器速度（暂为：机载填写）
	  double az;//！投射器方位（暂为：机载填写）
	double el;//！投射器俯仰（暂为：机载填写）
	int LaunchMode; //! @Properties(description=投放方式（1自动；2半自动；3手动）, defaultValue=1)
	

    _ModelBus_sCHAFF_Set_INI()
    {
        sRID           = NULL;
		DeviceID=0;
		PlatID=0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT=DKDMS::Enum_ATT_1;
		WorkState=DKDMS::Enum_WorkState_1;	// 开机
		LaunchMode = 1;
		ControlDeviceID=0;
		vec=0;
		az=0;
		el=0;

    }
    ~_ModelBus_sCHAFF_Set_INI()
    {
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
    }
    _ModelBus_sCHAFF_Set_INI(const _ModelBus_sCHAFF_Set_INI& info)
    {
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
        *this = info;
    }
    _ModelBus_sCHAFF_Set_INI& operator=(const _ModelBus_sCHAFF_Set_INI& info)
    {
        if( this==&info )
        {
            return *this;
        }
        SW_Malloc_Char(info.sRID,sRID);
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);
        DeviceID  = info.DeviceID;
        PlatID = info.PlatID;
		ATT = info.ATT;
		WorkState = info.WorkState;
		LaunchMode = info.LaunchMode;
		ControlDeviceID = info.ControlDeviceID;
		vec = info.vec;
		az = info.az;
		el = info.el;

        return *this;
    }
}sCHAFF_Set_INI;//SimModelDataOut.proto


//箔条静态输出，包含所有箔条状态
typedef struct _ModelBus_ChaffOutAllCir{  
	int					chaffID;
	int					chaffLaunchStatus;
	DKDMS::Enum_MK36Pos chaffPos;
	// 默认构造函数
	_ModelBus_ChaffOutAllCir()
	{
		chaffID=0;
		chaffLaunchStatus=0;
		chaffPos=DKDMS::Enum_MK36Pos_LF;
	}
	~_ModelBus_ChaffOutAllCir()
	{

	}
	_ModelBus_ChaffOutAllCir(const _ModelBus_ChaffOutAllCir& info)
	{
		 *this = info;
	}
	_ModelBus_ChaffOutAllCir& operator=(const _ModelBus_ChaffOutAllCir& info)
	{
		if( this==&info )
        {
            return *this;
        }
		chaffID=info.chaffID;
		chaffLaunchStatus=info.chaffLaunchStatus;
		chaffPos=info.chaffPos;

	}
	
}ChaffOutAllCir;//SimModelDataOut.proto

//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sCHAFF_Get_STATUSAllCir{
	char* sRID;
	int DeviceID;//实例ID
	int PlatID;  //平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float fTime;
	int nAllChaffCount;
	ChaffOutAllCir  *pAllChaffOut;  //箔条输出信息

	_ModelBus_sCHAFF_Get_STATUSAllCir()
	{
		sRID = NULL;
		PlatID = 0;
		DeviceID = 0;
		fTime = 0.0;
		nAllChaffCount = 24;
		pAllChaffOut = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
	}
	~_ModelBus_sCHAFF_Get_STATUSAllCir()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		if(pAllChaffOut != NULL)
		{
			SW_Delete(pAllChaffOut);
			pAllChaffOut = NULL;
		}
	}
	_ModelBus_sCHAFF_Get_STATUSAllCir(const _ModelBus_sCHAFF_Get_STATUSAllCir& info)
	{
		sRID           = NULL;
		pAllChaffOut = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = info;
	}
	_ModelBus_sCHAFF_Get_STATUSAllCir& operator=(const _ModelBus_sCHAFF_Get_STATUSAllCir& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);
		DeviceID = info.DeviceID;
		PlatID = info.PlatID;
		fTime = info.fTime;
		nAllChaffCount = info.nAllChaffCount;
		SW_Malloc_Struct(ChaffOutAllCir,info.pAllChaffOut, pAllChaffOut, info.nAllChaffCount, nAllChaffCount);
		return *this;
	}
}sCHAFF_Get_STATUSAllCir;//SimModelDataOut.proto

//箔条云的状态
typedef struct _ModelBus_ChaffOutLaunch{  //SimModelDataOut.proto
	int chaffID;//箔条ID
	int chaffstatus;  //状态：1 发射 2 爆炸 3 结束 0 未发射
	double chaffX;  //发射位置地心系
	double chaffY;	//地心系
	double chaffZ;	//地心系
	double chaffBombX;
	double chaffBombY;	//地心系
	double chaffBombZ;	//地心系
	double chaffAz;//箔条方向 0~360
	double chaffEl;//箔条俯仰 0~90
	double RCS;       //箔条弹有效横截面积
	double t;		//导弹发射时刻
	double t1;		//记录GR弹爆照后的前一帧时间
	double bombT;//GR弹爆炸时刻
	double windAz; //风向
	double windV; //风速
	double originalQuota; // 初始RCS指标 1000㎡

	// 默认构造函数
   _ModelBus_ChaffOutLaunch()
	{
		chaffID=0;//箔条ID
		chaffstatus=0;  //状态：1 发射 2 爆炸 3 结束 0 未发射
		chaffX=0;  //发射位置地心系
		chaffY=0;	//地心系
		chaffZ=0;	//地心系

		chaffBombX=0;
		chaffBombY=0;	//地心系
		chaffBombZ=0;	//地心系

		chaffAz=0;//箔条方向 0~360
		chaffEl=0;//箔条俯仰 0~90

		RCS=0;       //箔条弹有效横截面积
		t=0;		//导弹发射时刻
		t1=0;		//记录GR弹爆照后的前一帧时间

		bombT=0;//GR弹爆炸时刻
		windAz=0; //风向
		windV=0; //风速
		originalQuota=0; // 初始RCS指标 1000㎡
		
	}
   /*重载析构函数*/
   ~_ModelBus_ChaffOutLaunch()
   {
	   
   }

	// 拷贝构造函数
     _ModelBus_ChaffOutLaunch(const _ModelBus_ChaffOutLaunch& chaff)
	{
		*this = chaff;
	}
	// 赋值操作符
    _ModelBus_ChaffOutLaunch& operator=(const _ModelBus_ChaffOutLaunch& theStruct)
	{
		//memcpy(this,&rv,sizeof(*this));
		if( this==&theStruct )
		{
			return *this;
		}
		chaffX = theStruct.chaffX;
		chaffY = theStruct.chaffY;
		chaffZ = theStruct.chaffZ;

		chaffBombX = theStruct.chaffBombX;
		chaffBombY = theStruct.chaffBombY;
		chaffBombZ = theStruct.chaffBombZ;

		chaffAz = theStruct.chaffAz;
		chaffEl = theStruct.chaffEl;

		RCS = theStruct.RCS;

		t = theStruct.t;
		t1 = theStruct.t1;

		bombT = theStruct.bombT;
		windAz = theStruct.windAz;
		windV = theStruct.windV;

		originalQuota = theStruct.originalQuota;
		chaffstatus = theStruct.chaffstatus;
		chaffID = theStruct.chaffID;
		return *this;
	}
} chaffOutLaunch;//SimModelDataOut.proto

	//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sCHAFF_Send_STATUSLAUNCH  //输出实际发射箔条的状态
{
	char* sRID;
	int DeviceID;//实例ID
	int PlatID;  //平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float fTime;
	int  chaffCount;  //默认24发
	chaffOutLaunch  *tempChaffOut;  //箔条输出信息
	_ModelBus_sCHAFF_Send_STATUSLAUNCH()
	{
		sRID           = NULL;
		DeviceID = 0;
		PlatID = 0;
		chaffCount = 0;
		fTime = 0.0;
		tempChaffOut = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		
	}
	~_ModelBus_sCHAFF_Send_STATUSLAUNCH()
	{
		SW_Free_Char(sRID);
		SW_Delete(tempChaffOut);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}
	_ModelBus_sCHAFF_Send_STATUSLAUNCH(const _ModelBus_sCHAFF_Send_STATUSLAUNCH& info)
	{
		sRID           = NULL;
		tempChaffOut = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = info;
	}
	_ModelBus_sCHAFF_Send_STATUSLAUNCH& operator=(const _ModelBus_sCHAFF_Send_STATUSLAUNCH& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);
		DeviceID = info.DeviceID;
		PlatID = info.PlatID;
		fTime = info.fTime;
		chaffCount = info.chaffCount;
		SW_Malloc_Struct(chaffOutLaunch,info.tempChaffOut, tempChaffOut, info.chaffCount, chaffCount);
		return *this;
	}
}sCHAFF_Send_STATUSLAUNCH;//SimModelDataOut.proto


//椭圆箔条
typedef struct _ModelBus_ChaffOutAllEll
{
	double 		simutimes;
	int         id;
	bool 		m_bActive;//   ["GR弹状态",Default=0]
	int		    m_Type;//    ["弹种",Default=0]

	double		m_Lon;//	["经度",Default=0]
	double 		m_Lat;//	["纬度",Default=0]
	double  	m_Height;//	["高度",Default=0]

	double		m_Speed;//	["速度",Default=0]
	double		m_SpeedRange;//	["速度范围",Default=0]

	double		m_Dir;//["航向",Default=0]
	double		m_Pitch;//["俯仰",Default=0]

	double		m_Rcs; //   ["箔条RCS",Default=0]
	double		m_RcsRange;//	["RCS范围",Default=0]
	double		m_Lr;  //  ["箔条扩散面积长轴",Default=0]
	double		m_Sr; //   ["箔条扩散面积短轴",Default=0]
	_ModelBus_ChaffOutAllEll()
	{
		simutimes=0.0;
		id = 0;
		m_bActive=false;
		m_Type=0;

		m_Lon=0;
		m_Lat=0;
		m_Height=0;

		m_Speed=0;
		m_SpeedRange=0;
		m_Dir=0;

		m_Pitch=0;
		m_Rcs=0;
		m_RcsRange=0;
		m_Lr=0;
		m_Sr=0;
	}
	/*重载析构函数*/
	~_ModelBus_ChaffOutAllEll()
	{
		
	}
	/*重载拷贝构造函数*/
	_ModelBus_ChaffOutAllEll(const _ModelBus_ChaffOutAllEll &src)
	{
		
		*this = src;
	}

	_ModelBus_ChaffOutAllEll& operator = (const _ModelBus_ChaffOutAllEll& src)
	{
		if( this==&src )
		{
			return *this;
		}
		simutimes=src.simutimes;
		id = src.id;
		m_bActive=src.m_bActive;
		m_Type=src.m_Type;
		m_Lon=src.m_Lon;
		m_Lat=src.m_Lat;
		m_Height=src.m_Height;
		m_Speed=src.m_Speed;
		m_SpeedRange=src.m_SpeedRange;
		m_Dir=src.m_Dir;
		m_Pitch=src.m_Pitch;
		m_Rcs=src.m_Rcs;
		m_RcsRange=src.m_RcsRange;
		m_Lr=src.m_Lr;
		m_Sr=src.m_Sr;
		return *this;
	};
}ChaffOutAllEll;//SimModelDataOut.proto

//按实际情况修改*****
//增加GR弹输出信息 机载2100A

//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sCHAFF_Get_STATUSAllEllMM
{
	char* sRID;
	int DeviceID;//实例ID
	int PlatID;  //平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float fTime;
	int  chaffCount;  //默认100发
	ChaffOutAllEll  *tempChaffOutMM;  //箔条输出信息
	
	_ModelBus_sCHAFF_Get_STATUSAllEllMM()
	{
		sRID           = NULL;
		PlatID = 0;
		DeviceID = 0;
		fTime=0;
		chaffCount=10;
		tempChaffOutMM=NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		
		//tempChaffOut=NULL;
	}
	~_ModelBus_sCHAFF_Get_STATUSAllEllMM()
	{
		SW_Free_Char(sRID);
		//SW_Delete(tempChaffOut);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		if(tempChaffOutMM!= NULL)
		{
			SW_Delete(tempChaffOutMM);
			
			tempChaffOutMM = NULL;
		}

	}
	_ModelBus_sCHAFF_Get_STATUSAllEllMM(const _ModelBus_sCHAFF_Get_STATUSAllEllMM& info)
	{
		sRID  = NULL;
		tempChaffOutMM=NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = info;
	}
	_ModelBus_sCHAFF_Get_STATUSAllEllMM& operator=(const _ModelBus_sCHAFF_Get_STATUSAllEllMM& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);
		//SW_Malloc_Struct(ChaffOutAllEll,info.tempChaffOutM,tempChaffOutM, info.chaffCount, chaffCount);
	    SW_Malloc_Struct(ChaffOutAllEll,info.tempChaffOutMM,tempChaffOutMM, info.chaffCount, chaffCount);
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);
		chaffCount=info.chaffCount;  //默认100发
		DeviceID = info.DeviceID;
		PlatID = info.PlatID;
		fTime = info.fTime;

		return *this;
	}
}sCHAFF_Get_STATUSAllEllMM;//SimModelDataOut.proto

// DAS告警结果数据（0x4011）
typedef struct _ModelBus_BASE_WARN_Body{		 //SimModelDataOut.proto   
	int		ObjID;			// 告警目标ID
	int     nType;          // 告警类型 0: 不告警 1：红外；2：激光；3：紫外

	double	AZ;				// 目标方位,[0，360),度
	double	EL;				// 目标仰角,[0，90),度

	double  Dst;            // 威胁距离 0：远距；1：中距；2：近距  // 20171118//单位？？
	int     nIndex;         // 激光告警探头编号

	int  	PlatID;		    // 搭载平台ID
	int     ThreatType;     // 威胁类型 0：导弹；1：飞机     // 20171118

	double  Ratio;          // 双色比
	double	Level;			// 置信度,[0,100]

	int	ThreatenLevel;  // 威胁等级,[1,5]
	float fTime;		// 发现目标时间
	//unsigned char	Date[4];		// 发现日期
	
	/*重载构造函数*/
	_ModelBus_BASE_WARN_Body()
	{
		ObjID  = 0;
		nType = 0;
		AZ = 0.0;
		EL = 0.0;
		Dst = 0.0;
		nIndex = 0;
		PlatID = 0;
		ThreatType = 0;
		Ratio = 0;
		Level = 0;
		ThreatenLevel = 0;
		fTime=0;

	}

	/*重载析构函数*/
	~_ModelBus_BASE_WARN_Body()
	{
		
	}

	/*重载拷贝构造函数*/
	_ModelBus_BASE_WARN_Body(const _ModelBus_BASE_WARN_Body &theStruct)
	{
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_BASE_WARN_Body& operator=(const _ModelBus_BASE_WARN_Body& theStruct)
	{
		ObjID  = theStruct.ObjID;
		nType = theStruct.nType;

		AZ = theStruct.AZ;
		EL = theStruct.EL;

		Dst = theStruct.Dst;
		nIndex = theStruct.nIndex;

		PlatID = theStruct.PlatID;
		ThreatType = theStruct.ThreatType;

		Ratio = theStruct.Ratio;
		Level = theStruct.Level;

		ThreatenLevel = theStruct.ThreatenLevel;
		fTime= theStruct.fTime;

		return *this;
	}
}Base_Warn_Body;//SimModelDataOut.proto

//动态告警输出
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sEOWARN_Get_INFO
{
	char*   sRID;
	int DeviceID;//实例ID
	int PlatID;  //平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型	
	float fTime;
	int     Warn_Count;
	Base_Warn_Body  *WarnInfo;
	DKDMS::Enum_WorkState WorkState;		//工作状态
	/*重载构造函数*/
	_ModelBus_sEOWARN_Get_INFO()
	{
		sRID           = NULL;
		Warn_Count  = 0;
		DeviceID   = 0;
		PlatID = 0;
		fTime=0;
		WarnInfo= NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		WorkState     = DKDMS::Enum_WorkState_0;
	}

	/*重载析构函数*/
	~_ModelBus_sEOWARN_Get_INFO()
	{
		SW_Free_Char(sRID);
		SW_Delete(WarnInfo);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		
	}

	/*重载拷贝构造函数*/
	_ModelBus_sEOWARN_Get_INFO(const _ModelBus_sEOWARN_Get_INFO &jam)
	{
		sRID = NULL;
		WarnInfo= NULL;	
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sEOWARN_Get_INFO& operator=(const _ModelBus_sEOWARN_Get_INFO& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		WorkState			= theStruct.WorkState;
		SW_Malloc_Struct(_ModelBus_BASE_WARN_Body,theStruct.WarnInfo, WarnInfo, theStruct.Warn_Count, Warn_Count);
		Warn_Count = theStruct.Warn_Count;
		DeviceID = theStruct.DeviceID;
		PlatID = theStruct.PlatID;
		fTime = theStruct.fTime;//q
		return *this;
	}
}sEOWARN_Get_INFO;//SimModelDataOut.proto

//动态告警设备初始化信息输入
//! @Properties(description=光电告警装备, appType=init, id=27)
typedef struct _ModelBus_sEOWARN_Set_INI
{
	char* sRID;//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int DeviceID;//! @Properties(description=装备id, alias=modelId, display=readonly)
	int PlatID;   //! @Properties(description=平台id, alias=platformId, display=readonly)
	char*	EquipmentName;		//! @Properties(description=装备名称, alias=equipName)
	char*	EquipmentType;		//! @Properties(description=装备类型, alias=equipType)
	DKDMS::Enum_ATT		ATT;	//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作属性, defaultValue=1)

//	Set_ENV  m_Env;//环境:大气透过率\可见度

	_ModelBus_sEOWARN_Set_INI()
	{
		sRID           = NULL;
		DeviceID = 0;
		PlatID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_1;
//		memset(&m_Env,0,sizeof(Set_ENV));
	}
	~_ModelBus_sEOWARN_Set_INI()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}
	_ModelBus_sEOWARN_Set_INI(const _ModelBus_sEOWARN_Set_INI& info)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = info;
	}
	_ModelBus_sEOWARN_Set_INI& operator=(const _ModelBus_sEOWARN_Set_INI& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);
		DeviceID = info.DeviceID;
		PlatID = info.PlatID;
		ATT = info.ATT;
		WorkState = info.WorkState;
	//	m_Env = info.m_Env;
		return *this;
	}
}sEOWARN_Set_INI;//SimModelDataOut.proto

//静态初始化相关参数(包含大气透过率，飞机航向角）
typedef struct _ModelBus_aEOWarn_Set_INI
{   
	char*   sRID;
	int     DeviceID;//实例ID
	int     PlatID;  //平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型

	DKDMS::Enum_ATT		ATT;		//敌我属性
	DKDMS::Enum_WorkState	WorkState;	//工作属性

	float	fLon;			////载机平台经度，单位：度
	float	fLat;			//载机平台纬度，单位：度
	float	fHeight;		//载机平台高度，单位：米（m）

	float	fSpeed;			//载机平台运动速度 单位：米/秒（m/s）
	float	fDir;			//载机平台运动方位角，单位：度
	float	fPitch;			//载机平台运动俯仰角，单位：度
	float	fRoll;			//载机平台横滚角度，单位：度

	Set_ENV  m_Env;//环境:大气透过率\可见度


	_ModelBus_aEOWarn_Set_INI()
	{
		sRID          = NULL;
		DeviceID  = 0;
		PlatID=0;
	

		EquipmentName = NULL;
		EquipmentType = NULL;

		fLon          = 0.;
		fLat          = 0.;
		ATT=DKDMS::Enum_ATT_1;
		WorkState=DKDMS::Enum_WorkState_1;
		fHeight       = 0.;

		fSpeed        = 0.;
		fDir          = 0.;

		fPitch        = 0.;
		fRoll         = 0.;
		memset(&m_Env,0,sizeof(Set_ENV));
	}
	~_ModelBus_aEOWarn_Set_INI()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}
	_ModelBus_aEOWarn_Set_INI(const _ModelBus_aEOWarn_Set_INI& lsinfo)
	{		
		sRID=NULL;
		EquipmentName=NULL;
		EquipmentType=NULL;
		*this = lsinfo;
	}
	_ModelBus_aEOWarn_Set_INI& operator=(const _ModelBus_aEOWarn_Set_INI& lsinfo)
	{
		if( this==&lsinfo )
		{
			return *this;
		}
		ATT=lsinfo.ATT;
		WorkState=lsinfo.WorkState;
		SW_Malloc_Char(lsinfo.sRID,sRID);
		SW_Malloc_Char(lsinfo.EquipmentName,EquipmentName);
		SW_Malloc_Char(lsinfo.EquipmentType,EquipmentType);
		fLon          = lsinfo.fLon;
		fLat          = lsinfo.fLat;
		fHeight       = lsinfo.fHeight;
		fSpeed        = lsinfo.fSpeed;
		fDir          = lsinfo.fDir;
		fPitch        = lsinfo.fPitch;
		fRoll         = lsinfo.fRoll;
		m_Env = lsinfo.m_Env;
		DeviceID=lsinfo.DeviceID;
		PlatID=lsinfo. PlatID;
		return *this;
	}

}aEOWarn_Set_INI;//SimModelDataOut.proto
//*************20210809qmh添加动态告警范围输出结构体********************//

//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sEOWarn_Range
{
	char*   sRID;
	int     DeviceID;   //设备ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float   fTime;
	int     WarnType;  // 告警类型 1：红外；2：激光；3：紫外
	double  WarnDst;//告警距离（单位：米）
	double  WarnStartAZ;//告警起始方位（单位：度）
	double  WarnEndAZ;//告警终止方位（单位：度）
	_ModelBus_sEOWarn_Range()
	{ 
		sRID=NULL;
		DeviceID  = 0;
		EquipmentName=NULL;
		EquipmentType=NULL;
		WarnType=0;  // 告警类型 1：红外；2：激光；3：紫外
		WarnDst=0.;//告警距离（单位：米）
		WarnStartAZ=0.;//告警起始方位（单位：度）
		WarnEndAZ=0.;//告警终止方位（单位：度）
		
	}
	~ _ModelBus_sEOWarn_Range()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}
	_ModelBus_sEOWarn_Range(const _ModelBus_sEOWarn_Range& saout)
	{
		sRID = NULL;
		EquipmentName=NULL;
		EquipmentType=NULL;
		*this = saout;
	}
	_ModelBus_sEOWarn_Range& operator=(const _ModelBus_sEOWarn_Range& saout)
	{
		if( this==&saout )
		{
			return *this;
		}

		SW_Malloc_Char(saout.sRID,sRID);
		SW_Malloc_Char(saout.EquipmentName,EquipmentName);
		SW_Malloc_Char(saout.EquipmentType,EquipmentType);
		WarnType=saout.WarnType;  // 告警类型 1：红外；2：激光；3：紫外
		WarnDst=saout.WarnDst;//告警距离（单位：米）
		WarnStartAZ=saout.WarnStartAZ;//告警起始方位（单位：度）
		WarnEndAZ=saout.WarnEndAZ;//告警终止方位（单位：度）
		DeviceID=saout.DeviceID;
		return *this;
	}

}sEOWarn_Range;//SimModelDataOut.proto
///////////////////////////
//*************qmh添加静态输出结构体20210810********************//
typedef struct _ModelBus_aEOWarn_Range
{
	char*   sRID;
	int     EuipID;
	//char*	EquipmentName;		//装备名称//20210810qmh修改
	//char*	EquipmentType;		//装备类型//20210810qmh修改
	int    WarnType;  // 告警类型 1：红外；2：激光；3：紫外
	double WarnDst;//告警距离（单位：米）
	double WarnStartAZ;//告警起始方位（单位：度）
	double WarnEndAZ;//告警终止方位（单位：度）
	_ModelBus_aEOWarn_Range()
	{ 
		sRID=NULL;
		EuipID = 0;
		//EquipmentName=NULL;//20210810qmh修改
		//EquipmentType=NULL;//20210810qmh修改
		WarnType=0;  // 告警类型 1：红外；2：激光；3：紫外
		WarnDst=0.;//告警距离（单位：米）
		WarnStartAZ=0.;//告警起始方位（单位：度）
		WarnEndAZ=0.;//告警终止方位（单位：度）
		
	}
	~ _ModelBus_aEOWarn_Range()
	{
		SW_Free_Char(sRID);
		//SW_Free_Char(EquipmentName);//20210810qmh修改
		//SW_Free_Char(EquipmentType);//20210810qmh修改
	}
	_ModelBus_aEOWarn_Range(const _ModelBus_aEOWarn_Range& saout)
	{
		sRID = NULL;
	//	EquipmentName=NULL;//20210810qmh修改
	//	EquipmentType=NULL;//20210810qmh修改
		*this = saout;
	}
	_ModelBus_aEOWarn_Range& operator=(const _ModelBus_aEOWarn_Range& saout)
	{
		if( this==&saout )
		{
			return *this;
		}

		SW_Malloc_Char(saout.sRID,sRID);
		EuipID = saout.EuipID;
	//	SW_Malloc_Char(saout.EquipmentName,EquipmentName);//20210810qmh修改
	//	SW_Malloc_Char(saout.EquipmentType,EquipmentType);//20210810qmh修改
		WarnType=saout.WarnType;  // 告警类型 1：红外；2：激光；3：紫外
		WarnDst=saout.WarnDst;//告警距离（单位：米）
		WarnStartAZ=saout.WarnStartAZ;//告警起始方位（单位：度）
		WarnEndAZ=saout.WarnEndAZ;//告警终止方位（单位：度）

		return *this;
	}

}aEOWarn_Range;//SimModelDataOut.proto
typedef struct _ModelBus_sWarnResult//SimModelDataOut.proto
{
	char*       sRID;
	int			WarnID;						//告警设备ID  
	int			TargetID;						//目标ID   
	int			WarnType;						//类型，告警类型 0: 不告警 1：红外；2：激光；3：紫外
	bool		bWarned;						//是否告警到
	int         ThreatType;     // 威胁类型 0：导弹；1：飞机     // 20171118

	float		AZ;								//目标方位，单位：度 
	float		EL;								//目标俯仰，单位：度
	float		DIS;							//目标距离，单位：Km


	/*重载构造函数*/
	_ModelBus_sWarnResult()
	{
		sRID=NULL;
		TargetID       = 0;
		WarnID      = 0;
		WarnType	 = 0;
		bWarned     = false;
		ThreatType=2;
		AZ = 0;
		EL = 0;
		DIS = 0;

	}

	/*重载析构函数*/
	~_ModelBus_sWarnResult()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sWarnResult(const _ModelBus_sWarnResult &jam)
	{
		sRID=NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sWarnResult& operator=(const _ModelBus_sWarnResult& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);
		TargetID       = theStruct.TargetID;
		WarnID         = theStruct.WarnID;
		WarnType		   = theStruct.WarnType;
		bWarned        = theStruct.bWarned;
		ThreatType=theStruct.ThreatType;
		AZ = theStruct.AZ;
		EL = theStruct.EL;
		DIS = theStruct.DIS;


		return *this;
	}
}sWarnResult;//SimModelDataOut.proto


//告警结果
typedef struct _ModelBus_aWARN_RESULT
{
	char*	sRID;								//身份字符串
//	char*	EquipmentName;		//装备名称//20210810qmh修改
//	char*	EquipmentType;		//装备类型//20210810qmh修改
	int		WarnID;						//告警设备ID  
	int		nResultNum;					//告警结论个数
	sWarnResult *pWarnResult;	//告警结论数据

	/*重载构造函数*/
	_ModelBus_aWARN_RESULT()
	{
		sRID          = NULL;	
//		EquipmentName=NULL;//20210810qmh修改
//		EquipmentType=NULL;//20210810qmh修改
		WarnID       = 0;
		nResultNum      = 0;	
		pWarnResult = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_aWARN_RESULT()
	{
		SW_Free_Char(sRID);
//		SW_Free_Char(EquipmentName);//20210810qmh修改
//		SW_Free_Char(EquipmentType);//20210810qmh修改
		SW_Delete(pWarnResult);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aWARN_RESULT(const _ModelBus_aWARN_RESULT &jam)
	{
		sRID = NULL;
//		EquipmentName=NULL;//20210810qmh修改
//		EquipmentType=NULL;//20210810qmh修改
		pWarnResult = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aWARN_RESULT& operator=(const _ModelBus_aWARN_RESULT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);//20210810qmh修改
		//SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);//20210810qmh修改
		WarnID= theStruct.WarnID;
		nResultNum= theStruct.nResultNum;
		//SW_Delete(pReconResult);
		SW_Malloc_Struct(sWarnResult,theStruct.pWarnResult,pWarnResult,theStruct.nResultNum,nResultNum);

		return *this;
	}
}aWARN_RESULT;//SimModelDataOut.proto
typedef struct _ModelBus_aEOTARGET_PARA
{
	char*	sRID;		//身份字符串
	int		ID;			//实体ID
	
	double dLonge;					//经度单位：度范围：-180-180 精度：.00001°，东经为正，西经为负。如东经°＇表示为.5°。
	double dLat;					//纬度单位：度范围：-90-90 精度：.00001°，表示南纬，表示北纬。
	
	float  fHeight;					//高度单位：m 范围：-10^9-10^9 精度：.01m，北纬为正，南纬为负。
	double dSpeed;					//速度大小单位: m/s
	
	double dCourse;					//航向单位：度范围：-360 精度：.1度，~360°,正北为0°
	double dPitch;					//运动俯仰角度 单位：度
	
	double dRoll;					//运动横滚角度 单位：度
	//DKDMS::MISSILE_STATE	 iMissileState;			//导弹的状态，WAIT为未发射，FIRSTDETECT为中制导，SECONDDETECT为末制导，HITTED为命中目标，NOHITTED为未命中目标,INVALID失效
	double dRadiancy; //目标红外辐射强度，单位 w/sr
	
	double UltravioletRadiaIntensity;//目标紫外辐射强度
	double PeakPower0;//激光器输出能量峰值P0
	//double LaserPowerDensity;//激光能量密度
	double LaserPower;//激光能量功率
	double LaserAngle; //激光发散角（弧度）

	/*重载构造函数*/
	_ModelBus_aEOTARGET_PARA()
	{
		sRID = NULL;
		ID = 0;
		
		dLonge   = 0;
		dLat     = 0;
		
		fHeight  = 0;
		dSpeed =0;
		
		dCourse  = 0;
		dPitch = 0;
		
		dRoll = 0;
		//iMissileState = DKDMS::MISSILE_WAIT;
		dRadiancy = 0;
		
		PeakPower0 = 0;
		LaserPower = 0;////激光功率
		
		LaserAngle = 0;
		UltravioletRadiaIntensity=0;
	}

	/*重载析构函数*/
	~_ModelBus_aEOTARGET_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aEOTARGET_PARA(const _ModelBus_aEOTARGET_PARA &radar)
	{
		sRID = NULL;
		*this = radar;
	}

	/*重载=*/
	_ModelBus_aEOTARGET_PARA& operator = (const _ModelBus_aEOTARGET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		ID     = theStruct.ID;
		dLonge		= theStruct.dLonge;
		dLat		= theStruct.dLat;
		fHeight  = theStruct.fHeight;
		dSpeed           = theStruct.dSpeed;
		dCourse		   = theStruct.dCourse;
		dPitch      = theStruct.dPitch;
		dRoll		= theStruct.dRoll;
		//iMissileState  = theStruct.iMissileState;
		dRadiancy = theStruct.dRadiancy;
		PeakPower0 = theStruct.PeakPower0;
		//LaserPowerDensity = theStruct.LaserPowerDensity;
		LaserPower=theStruct.LaserPower;
		LaserAngle = theStruct.LaserAngle;
		UltravioletRadiaIntensity=theStruct.UltravioletRadiaIntensity;

		return *this;
	}

}aEOTarget_Para;//SimModelDataOut.proto

//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sEOTARGET_PARA
{
	char*	sRID;		//身份字符串
	int		ID;			//实体ID
	DKDMS::Enum_PlatType platType;//qmh增加目标类型
	float	fTime;			//仿真时间	
	double dLonge;					//经度单位：度范围：-180-180 精度：.00001°，东经为正，西经为负。如东经°＇表示为.5°。
	double dLat;					//纬度单位：度范围：-90-90 精度：.00001°，表示南纬，表示北纬。
	float  fHeight;					//高度单位：m 范围：-10^9-10^9 精度：.01m，北纬为正，南纬为负。
	double dSpeed;					//速度大小单位: m/s
	double dCourse;					//航向单位：度范围：-360 精度：.1度，~360°,正北为0°
	double dPitch;					//运动俯仰角度 单位：度
	double dRoll;					//运动横滚角度 单位：度
	double dRadiancy; //目标红外辐射强度，单位 w/sr
	double UltravioletRadiaIntensity;//目标紫外辐射强度
	double PeakPower0;//激光器输出能量峰值P0
	double LaserPower;//激光能量功率
	double LaserAngle; //激光发散角（弧度）
	int    PlatID;//搭载平台ID

	/*重载构造函数*/
	_ModelBus_sEOTARGET_PARA()
	{
		sRID = NULL;
		platType=DKDMS::Enum_PlatType_6;
		ID = 0;
		fTime = 0.;
		dLonge   = 0;
		dLat     = 0;
		fHeight  = 0;
		dSpeed =0;
		dCourse  = 0;
		dPitch = 0;
		dRoll = 0;
		dRadiancy = 0;
		PeakPower0 = 0;
		LaserPower = 0;////激光功率
		LaserAngle = 0;
		UltravioletRadiaIntensity=0;
		PlatID=0;
	}

	/*重载析构函数*/
	~_ModelBus_sEOTARGET_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sEOTARGET_PARA(const _ModelBus_sEOTARGET_PARA &radar)
	{
		sRID = NULL;
		*this = radar;
	}

	/*重载=*/
	_ModelBus_sEOTARGET_PARA& operator = (const _ModelBus_sEOTARGET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		platType=theStruct.platType;
		ID     = theStruct.ID;
		fTime     = theStruct.fTime;
		dLonge		= theStruct.dLonge;
		dLat		= theStruct.dLat;
		fHeight  = theStruct.fHeight;
		dSpeed           = theStruct.dSpeed;
		dCourse		   = theStruct.dCourse;
		dPitch      = theStruct.dPitch;
		dRoll		= theStruct.dRoll;
		dRadiancy = theStruct.dRadiancy;
		PeakPower0 = theStruct.PeakPower0;
		LaserPower=theStruct.LaserPower;
		LaserAngle = theStruct.LaserAngle;
		UltravioletRadiaIntensity=theStruct.UltravioletRadiaIntensity;
		PlatID = theStruct.PlatID;

		return *this;
	}

}sEOTarget_Para;//SimModelDataOut.proto

//---------------------------------------------------------------------------------------------------//
//*************************20220728-----MEnStruct_EOCMNEW.h******************************************//
//---------------------------------------------------------------------------------------------------//
//! @Properties(description=光电设备, appType=init,id=30)
typedef struct _ModelBus_EOEquip_Set_INI//所有11型装备都用的初始化输入
{
	char* sRID;//! @Properties(description=身份字符串, alias=simuId, display=readonly)
	int EquipID;//! @Properties(description=装备id, alias=modelId, display=readonly)
	int PlatID; //! @Properties(description=平台id, alias=platformId, display=readonly)
	DKDMS::Enum_PlatType platType;//! @Properties(description=平台类型)
	char*	EquipmentName;		//! @Properties(description=装备名称)
	char*	EquipmentType;		//! @Properties(description=装备类型)
	DKDMS::Enum_ATT		ATT;		//! @Properties(description=敌我属性)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作状态)
	double	fLon;			//! @Properties(description=经度, alias=lon, unit=度)
	double	fLat;			//! @Properties(description=纬度, alias=lat, unit=度)
	double	fHeight;		//! @Properties(description=高度, alias=hei, unit=米)
	double  Start_AZ;//! @Properties(description=控守起始方位)
	double  End_AZ;//! @Properties(description=控守终止方位)
	int WarnEquipID;//! @Properties(description=告警设备ID)
	_ModelBus_EOEquip_Set_INI()
	{
		sRID           = NULL;
		EquipID=0;//设备ID
		PlatID=0;  //搭载平台ID
		platType=DKDMS::Enum_PlatType_1;//

		EquipmentName=NULL;		//装备名称
		EquipmentType=NULL;		//装备类型
		ATT=DKDMS::Enum_ATT_1 ;	////敌我属性 我方;		
		WorkState=DKDMS::Enum_WorkState_1;	//工作属性  默认开机
		fLon=0.0;			//部署位置经度，单位：度
		fLat=0.0;			//部署位置纬度，单位：度
		fHeight=0.0;		//部署位置高度，单位：米（m）
		Start_AZ=0;//控守起始方位
		End_AZ=180;//控守终止方位
		WarnEquipID=0;


	}
	~_ModelBus_EOEquip_Set_INI()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);

	}
	_ModelBus_EOEquip_Set_INI(const _ModelBus_EOEquip_Set_INI& info)
	{
		sRID = NULL;
		EquipmentName=NULL;		//装备名称
		EquipmentType=NULL;		//装备类型
		*this = info;
	}
	_ModelBus_EOEquip_Set_INI& operator=(const _ModelBus_EOEquip_Set_INI& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);

		EquipID=info.EquipID;//设备ID
		PlatID=info.PlatID;  //搭载平台ID
		platType=info.platType;//
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);

		ATT= info.ATT;	////敌我属性 我方;		
		WorkState=info.WorkState;	//工作属性  默认开机
		fLon=info.fLon;			//部署位置经度，单位：度
		fLat=info.fLat;			//部署位置纬度，单位：度
		fHeight=info.fHeight;		//部署位置高度，单位：米（m）
		Start_AZ=info.Start_AZ;//控守起始方位
		End_AZ=info.End_AZ;//控守终止方位
		WarnEquipID=info.WarnEquipID;


		return *this;
	}
}EOEquip_Set_INI;//所有11型装备都用的初始化输入GFS           //SimModelDataOut.proto
//! @Properties(description=P波段雷达输出, appType=modelOut)
typedef struct _ModelBus_PBandRadarEquip_Target_Para
{
	char*sRID;
	int  TargetID;
	double Azimuth;
	double Elevation;
	double Volecity;
	double	Lon;			//GR目标经度，单位：度
	double	Lat;			//GR目标纬度，单位：度
	double	Height;		//GR目标高度，单位：米（m）

	_ModelBus_PBandRadarEquip_Target_Para()
	{
		sRID           = NULL;
		TargetID=0;
		Azimuth=0.0;
		Elevation=0.0;
		Volecity=0.0;
		Lon=0.0;			//经度，单位：度
		Lat=0.0;			//纬度，单位：度
		Height=0.0;		//高度，单位：米（m）


	}
	~_ModelBus_PBandRadarEquip_Target_Para()
	{
		SW_Free_Char(sRID);


	}
	_ModelBus_PBandRadarEquip_Target_Para(const _ModelBus_PBandRadarEquip_Target_Para& info)
	{
		sRID = NULL;

		*this = info;
	}
	_ModelBus_PBandRadarEquip_Target_Para& operator=(const _ModelBus_PBandRadarEquip_Target_Para& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);


		TargetID=info.TargetID;
		Azimuth=info.Azimuth;
		Elevation=info.Elevation;
		Volecity=info.Volecity;
		Lon=info.Lon;			//经度，单位：度
		Lat=info.Lat;			//纬度，单位：度
		Height=info.Height;		//高度，单位：米（m）


		return *this;
	}
}PBandRadarEquip_Target_Para;//P波段雷达的输出GFS//SimModelDataOut.proto
//! @Properties(description=P波段雷达输出, appType=modelOut)
typedef struct _ModelBus_PBandRadarEquip_OUT_MSG//P波段雷达输出报文
{
	char* sRID;//身份字符串
	int EquipID;//设备ID
	int PlatID;  //搭载平台ID
	DKDMS::Enum_PlatType platType;//搭载平台类型
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float   fTime;              //仿真时间
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_WorkState	WorkState;	//工作状态
	double EquipPosLon;//部署位置信息
	double EquipPosLat;
	double EquipPosHeight;
	int   TargetNum;//导弹数量
	PBandRadarEquip_Target_Para*pBandRadarEquip_Target_Para;


	_ModelBus_PBandRadarEquip_OUT_MSG()
	{
		sRID           = NULL;
		EquipID=0;//设备ID
		PlatID=0;  //搭载平台ID
		platType=DKDMS::Enum_PlatType_1;//

		EquipmentName=NULL;		//装备名称
		EquipmentType=NULL;		//装备类型
		fTime=0.0;
		SurvivalState=DKDMS::Enum_SurvivalState_0 ; //正常;	//生存状态
		WorkState=DKDMS::Enum_WorkState_1;	//工作状态，开机
		EquipPosLon=0.0;//部署位置信息
		EquipPosLat=0.0;
		EquipPosHeight=0.0;
		TargetNum=0;
		pBandRadarEquip_Target_Para=NULL;



	}
	~_ModelBus_PBandRadarEquip_OUT_MSG()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		if(pBandRadarEquip_Target_Para != NULL)
		{
			SW_Delete(pBandRadarEquip_Target_Para);
			pBandRadarEquip_Target_Para = NULL;
		}	

	}
	_ModelBus_PBandRadarEquip_OUT_MSG(const _ModelBus_PBandRadarEquip_OUT_MSG& info)
	{
		sRID = NULL;
		EquipmentName=NULL;		//装备名称
		EquipmentType=NULL;		//装备类型
		pBandRadarEquip_Target_Para=NULL;
		*this = info;
	}
	_ModelBus_PBandRadarEquip_OUT_MSG& operator=(const _ModelBus_PBandRadarEquip_OUT_MSG& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);

		EquipID=info.EquipID;//设备ID
		PlatID=info.PlatID;  //搭载平台ID
		platType=info.platType;//
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);
		fTime=info.fTime;
		SurvivalState=info.SurvivalState ; //正常;	//生存状态
		WorkState=info.WorkState;	//工作状态，开机
		EquipPosLon=info.EquipPosLon;//部署位置信息
		EquipPosLat=info.EquipPosLat;
		EquipPosHeight=info.EquipPosHeight;
		TargetNum=info.TargetNum;
		SW_Malloc_Struct(PBandRadarEquip_Target_Para,info.pBandRadarEquip_Target_Para,pBandRadarEquip_Target_Para,info.TargetNum,TargetNum);	
		return *this;
	}
}PBandRadarEquip_OUT_MSG;//P波段雷达的输出GFS         //SimModelDataOut.proto
typedef struct _ModelBus_FalseTargetPara
{
	char*sRID;
	int     FalseTargetID;
	double  StartAzimuth;//保护区域范围起始方位
	double  EndAzimuth;//保护区域范围终止方位
	double  EffectRadius; //散射截获半径50/500米//qmh----20211006
	double	FalseTargetLon;			//假目标经度，单位：度
	double	FalseTargetLat;			//假目标纬度，单位：度
	double	FalseTargetHeight;		//假目标高度，单位：米（m）

	_ModelBus_FalseTargetPara()
	{
		sRID           = NULL;
		FalseTargetID=0;
		StartAzimuth=0.0;
		EndAzimuth=0.0;
		EffectRadius=0.0;
		FalseTargetLon=0.0;			//经度，单位：度
		FalseTargetLat=0.0;			//纬度，单位：度
		FalseTargetHeight=0.0;		//高度，单位：米（m）


	}
	~_ModelBus_FalseTargetPara()
	{
		SW_Free_Char(sRID);


	}
	_ModelBus_FalseTargetPara(const _ModelBus_FalseTargetPara& info)
	{
		sRID = NULL;

		*this = info;
	}
	_ModelBus_FalseTargetPara& operator=(const _ModelBus_FalseTargetPara& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);


		FalseTargetID=info.FalseTargetID;
		StartAzimuth=info.StartAzimuth;
		EndAzimuth=info.EndAzimuth;
		EffectRadius=info.EffectRadius;
		FalseTargetLon=info.FalseTargetLon;			//经度，单位：度
		FalseTargetLat=info.FalseTargetLat;			//纬度，单位：度
		FalseTargetHeight=info.FalseTargetHeight;		//高度，单位：米（m）


		return *this;
	}
}FalseTargetPara;                                             //SimModelDataOut.proto
//! @Properties(description=激光GR设备输出, appType=modelOut)
typedef struct _ModelBus_LaserJamEquip_OUT_MSG//激光GR设备输出报文
{
	char* sRID;//身份字符串
	int EquipID;//设备ID
	int PlatID;  //搭载平台ID
	DKDMS::Enum_PlatType platType;//搭载平台类型
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float fTime;//仿真时间
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_WorkState	WorkState;	//工作状态
	double EquipPosLon;//部署位置信息(出光打击位置信息）
	double EquipPosLat;
	double EquipPosHeight;
	double  LaserPower;								//! 激光功率=w)
	double  LaserAngle;	           					//! 激光束散角弧度)
	double  LaserWavelength;//激光波长
	double Azimuth;
	double Elevation;
	double WarnDis;//告警距离
	DKDMS::Enum_JamMode	JamMode;//GR样式
	int   FalseTargetNum;//假目标个数
	FalseTargetPara* pFalseTargetPara;//假目标GR信息
	//sPON_AREA* pFalseTargetPos;


	_ModelBus_LaserJamEquip_OUT_MSG()
	{
		sRID           = NULL;
		EquipID=0;//设备ID
		PlatID=0;  //搭载平台ID
		platType=DKDMS::Enum_PlatType_1;//

		EquipmentName=NULL;		//装备名称
		EquipmentType=NULL;		//装备类型
		fTime=0.0;
		SurvivalState=DKDMS::Enum_SurvivalState_0 ; //正常;	//生存状态
		WorkState=DKDMS::Enum_WorkState_1;	//工作状态，开机
		EquipPosLon=0.0;//部署位置信息(出光打击位置信息）
		EquipPosLat=0.0;
		EquipPosHeight=0.0;
		LaserPower=0.0;								//! 激光功率=w)
		LaserAngle=0.0;	           					//! 激光束散角弧度)
		LaserWavelength=0.0;//激光波长
		Azimuth=0.0;
		Elevation=0.0;
		WarnDis=0.0;//告警距离
		//Enum_JamMode_0 = 0,	//压制GR
		//Enum_JamMode_1 = 1,	//欺骗GR，假目标
		JamMode=DKDMS::Enum_JamMode_0 ;//GR样式
		FalseTargetNum=0;//假目标个数
		pFalseTargetPara=NULL;



	}
	~_ModelBus_LaserJamEquip_OUT_MSG()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		if(pFalseTargetPara != NULL)
		{

			SW_Delete(pFalseTargetPara);
			pFalseTargetPara = NULL;
		}

	}
	_ModelBus_LaserJamEquip_OUT_MSG(const _ModelBus_LaserJamEquip_OUT_MSG& info)
	{
		sRID = NULL;
		EquipmentName=NULL;		//装备名称
		EquipmentType=NULL;		//装备类型
		pFalseTargetPara = NULL;
		*this = info;
	}
	_ModelBus_LaserJamEquip_OUT_MSG& operator=(const _ModelBus_LaserJamEquip_OUT_MSG& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);

		EquipID=info.EquipID;//设备ID
		PlatID=info.PlatID;  //搭载平台ID
		platType=info.platType;//
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);
		fTime=info.fTime;
		SurvivalState=info.SurvivalState ; //正常;	//生存状态
		WorkState=info.WorkState;	//工作状态，开机

		EquipPosLon=info.EquipPosLon;//部署位置信息(出光打击位置信息）
		EquipPosLat=info.EquipPosLat;
		EquipPosHeight=info.EquipPosHeight;
		LaserPower=info.LaserPower;								//! 激光功率=w)
		LaserAngle=info.LaserAngle;	           					//! 激光束散角弧度)
		LaserWavelength=info.LaserWavelength;//激光波长
		Azimuth=info.Azimuth;
		Elevation=info.Elevation;
		WarnDis=info.WarnDis;//告警距离
		//Enum_JamMode_0 = 0,	//压制GR
		//Enum_JamMode_1 = 1,	//欺骗GR，假目标
		JamMode=info.JamMode;//GR样式
		FalseTargetNum=info.FalseTargetNum;//假目标个数
		//SW_Malloc_Struct(PBandRadarEquip_Target_Para,info.pBandRadarEquip_Target_Para,pBandRadarEquip_Target_Para,info.TargetNum,TargetNum);
		SW_Malloc_Struct(FalseTargetPara,info.pFalseTargetPara,pFalseTargetPara,info.FalseTargetNum,FalseTargetNum);


		return *this;
	}
}LaserJamEquip_OUT_MSG;//激光GR设备信息              //SimModelDataOut.proto
typedef struct _ModelBus_PassiveSmokeEquip_Para//无源GR设备输出报文
{
	char* sRID;//身份字符串
	int EquipUnitID;//设备单元ID
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_WorkState	WorkState;	//工作状态
	double SprayAZ;//喷洒指向方位
	double SprayEL;//喷洒指向俯仰
	sPON_AREA CebtralPoint;//烟墙中心点位置（抛射代表的是爆炸点位置）
	double  ProtectSize;//防护面积
	_ModelBus_PassiveSmokeEquip_Para()
	{
		sRID           = NULL;
		EquipUnitID=0;//设备ID
		SurvivalState=DKDMS::Enum_SurvivalState_0 ; //正常;	//生存状态
		WorkState=DKDMS::Enum_WorkState_1;	//工作状态，开机
		SprayAZ=0.0;//喷洒指向方位
		SprayEL=0.0;//喷洒指向俯仰
		CebtralPoint.LON=0.0;//烟墙中心点位置
		CebtralPoint.LAT=0.0;//烟墙中心点位置
		CebtralPoint.Height=0.0;//烟墙中心点位置
		ProtectSize=0.0;//防护面积
	}
	~_ModelBus_PassiveSmokeEquip_Para()
	{
		SW_Free_Char(sRID);



	}
	_ModelBus_PassiveSmokeEquip_Para(const _ModelBus_PassiveSmokeEquip_Para& info)
	{
		sRID = NULL;


		*this = info;
	}
	_ModelBus_PassiveSmokeEquip_Para& operator=(const _ModelBus_PassiveSmokeEquip_Para& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);

		EquipUnitID=info.EquipUnitID;//设备ID
		SurvivalState=info.SurvivalState; //正常;	//生存状态
		WorkState=info.WorkState;	//工作状态，开机
		SprayAZ=info.SprayAZ;//喷洒指向方位
		SprayEL=info.SprayEL;//喷洒指向俯仰
		CebtralPoint=info.CebtralPoint;//烟墙中心点位置
		ProtectSize=info.ProtectSize;//防护面积



		return *this;
	}
}PassiveSmokeEquip_Para;//无源烟幕GR设备信息        //SimModelDataOut.proto
//! @Properties(description=无源烟幕GR设备输出, appType=modelOut)
typedef struct _ModelBus_PassiveSmokeEquip_OUT_MSG//无源烟幕GR设备输出报文
{
	char* sRID;//身份字符串
	int EquipID;//设备ID
	int PlatID;  //搭载平台ID
	float fTime;//仿真时间
	DKDMS::Enum_PlatType platType;//搭载平台类型
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	double  EquipPosLon;//部署位置信息(喷烟位置信息）
	double  EquipPosLat;
	double  EquipPosHeight;
	int EquipUnitNum;//设备子单元数量
	PassiveSmokeEquip_Para*pSmokeEquip_Para;
	_ModelBus_PassiveSmokeEquip_OUT_MSG()
	{
		sRID=NULL;
		EquipID=0;
		PlatID=0;  //搭载平台ID
		fTime=0.0;//仿真时间
		platType=DKDMS::Enum_PlatType_1;//

		EquipmentName=NULL;		//装备名称
		EquipmentType=NULL;		//装备类型
		EquipPosLon=0.0;//部署位置信息(出光打击位置信息）
		EquipPosLat=0.0;
		EquipPosHeight=0.0;
		EquipUnitNum=0;
		pSmokeEquip_Para=NULL;
	}
	~_ModelBus_PassiveSmokeEquip_OUT_MSG()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		if(pSmokeEquip_Para != NULL)
		{
			SW_Delete(pSmokeEquip_Para);
			pSmokeEquip_Para = NULL;
		}		


	}
	_ModelBus_PassiveSmokeEquip_OUT_MSG(const _ModelBus_PassiveSmokeEquip_OUT_MSG& info)
	{
		sRID = NULL;
		EquipmentName=NULL;		//装备名称
		EquipmentType=NULL;		//装备类型
		pSmokeEquip_Para = NULL;

		*this = info;
	}
	_ModelBus_PassiveSmokeEquip_OUT_MSG& operator=(const _ModelBus_PassiveSmokeEquip_OUT_MSG& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);


		EquipID=info.EquipID;
		PlatID=info.PlatID;  //搭载平台ID
		platType=info.platType;//
		fTime=info.fTime;
		SW_Malloc_Char(info.EquipmentName,EquipmentName);
		SW_Malloc_Char(info.EquipmentType,EquipmentType);

		EquipPosLon=info.EquipPosLon;//部署位置信息(出光打击位置信息）
		EquipPosLat=info.EquipPosLat;
		EquipPosHeight=info.EquipPosHeight;
		EquipUnitNum=info.EquipUnitNum;
		SW_Malloc_Struct(PassiveSmokeEquip_Para,info.pSmokeEquip_Para,pSmokeEquip_Para,info.EquipUnitNum,EquipUnitNum);	
		return *this;
	}
}PassiveSmokeEquip_OUT_MSG;//无源烟幕GR设备输出//SimModelDataOut.proto

typedef struct _ModelBus_aEOJAM_Range//静态GR范围
{
	char*   sRID;
	int     EuipID;
//	char*	EquipmentName;		//装备名称//20210810qmh修改
//	char*	EquipmentType;		//装备类型//20210810qmh修改

	double JamDst;//GR作用距离（单位：米）
	double JamStartAZ;//GR起始方位（单位：度）
	double JamEndAZ;//GR终止方位（单位：度）
	double JamTarFreMin;//GR目标频率最小值
	double JamTarFreMax;//GR目标频率最小值
	_ModelBus_aEOJAM_Range()
	{ 
		sRID=NULL;
		EuipID = 0;
	//	EquipmentName=NULL;//20210810qmh修改
	//	EquipmentType=NULL;//20210810qmh修改
		JamDst=0.0;//GR作用距离（单位：米）
		JamStartAZ=0.0;//GR起始方位（单位：度）
		JamEndAZ=0.0;//GR终止方位（单位：度）
		JamTarFreMin=0.0;//GR目标频率最小值
		JamTarFreMax=0.0;//GR目标频率最小值

	}
	~ _ModelBus_aEOJAM_Range()
	{
		SW_Free_Char(sRID);
		//SW_Free_Char(EquipmentName);//20210810qmh修改
		//SW_Free_Char(EquipmentType);//20210810qmh修改
	}
	_ModelBus_aEOJAM_Range(const _ModelBus_aEOJAM_Range& saout)
	{
		sRID = NULL;
	//	EquipmentName=NULL;//20210810qmh修改
	//	EquipmentType=NULL;//20210810qmh修改
		*this = saout;
	}
	_ModelBus_aEOJAM_Range& operator=(const _ModelBus_aEOJAM_Range& saout)
	{
		if( this==&saout )
		{
			return *this;
		}

		SW_Malloc_Char(saout.sRID,sRID);
		EuipID = saout.EuipID;
	//	SW_Malloc_Char(saout.EquipmentName,EquipmentName);//20210810qmh修改
	//	SW_Malloc_Char(saout.EquipmentType,EquipmentType);//20210810qmh修改
		JamDst=saout.JamDst;//GR作用距离（单位：米）
		JamStartAZ=saout.JamStartAZ;//GR起始方位（单位：度）
		JamEndAZ=saout.JamEndAZ;//GR终止方位（单位：度）
		JamTarFreMin=saout.JamTarFreMin;//GR目标频率最小值
		JamTarFreMax=saout.JamTarFreMax;//GR目标频率最小值

		return *this;
	}

}aEOJAM_Range;//静态GR范围                //SimModelDataOut.proto
typedef struct _ModelBus_aJAMResult
{
	char*       sRID;
	int			TargetID;						//目标ID   
	bool		bJamed;						//是否GR  true:GR  false：未GR
	float		AZ;								//GR目标方位，单位：度
	float		EL;								//GR目标俯仰，单位：度
	float		DIS;							//GR目标距离，单位：Km
	/*重载构造函数*/
	_ModelBus_aJAMResult()
	{
		sRID=NULL;
		TargetID       = 0;
		bJamed     = false;
		AZ = 0;
		EL = 0;
		DIS = 0;

	}

	/*重载析构函数*/
	~_ModelBus_aJAMResult()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aJAMResult(const _ModelBus_aJAMResult &jam)
	{
		sRID=NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aJAMResult& operator=(const _ModelBus_aJAMResult& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);

		TargetID = theStruct.TargetID;
		bJamed = theStruct.bJamed;
		AZ = theStruct.AZ;
		EL = theStruct.EL;
		DIS = theStruct.DIS;


		return *this;
	}
}aJAMResult;                                 //SimModelDataOut.proto
typedef struct _ModelBus_aEOJAM_RESULT//静态GR结果结构体
{
	char*	sRID;						 //身份字符串
	//char*	EquipmentName;		         //装备名称//20210810qmh修改
	//char*	EquipmentType;		         //装备类型//20210810qmh修改
	int		EquipID;					 //GR设备ID
	int		nResultNum;					 //GR结论个数
	aJAMResult *pJAMResult;	             //GR结论数据

	/*重载构造函数*/
	_ModelBus_aEOJAM_RESULT()
	{
		sRID          = NULL;	
		//EquipmentName=NULL;//20210810qmh修改
		//EquipmentType=NULL;//20210810qmh修改
		EquipID      = 0;
		nResultNum      = 0;	
		pJAMResult = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_aEOJAM_RESULT()
	{
		SW_Free_Char(sRID);
		//SW_Free_Char(EquipmentName);//20210810qmh修改
		//SW_Free_Char(EquipmentType);//20210810qmh修改
		if(pJAMResult != NULL)
		{
			SW_Delete(pJAMResult);
			pJAMResult = NULL;
		}	
	}

	/*重载拷贝构造函数*/
	_ModelBus_aEOJAM_RESULT(const _ModelBus_aEOJAM_RESULT &jam)
	{
		sRID = NULL;
		//EquipmentName=NULL;//20210810qmh修改
		//EquipmentType=NULL;//20210810qmh修改
		pJAMResult = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aEOJAM_RESULT& operator=(const _ModelBus_aEOJAM_RESULT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);//20210810qmh修改
		//SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);//20210810qmh修改
		EquipID=theStruct.EquipID;					 //GR设备ID
		nResultNum=theStruct.nResultNum;					 //GR结论个数
		//aJAMResult *pJAMResult;	             //GR结论数据
		SW_Malloc_Struct(aJAMResult,theStruct.pJAMResult,pJAMResult,theStruct.nResultNum,nResultNum);

		return *this;
	}
}aEOJAM_RESULT;//静态GR结果             //SimModelDataOut.proto
//---------------------------------------------------------------------------------------------------//


//---------------------------------------------------------------------------------------------------//
//*************************20220728-----MEnStruct_EOModeCM.h******************************************//
//---------------------------------------------------------------------------------------------------//
enum Enum_EOWeaponType			//EnumDefine.proto		
{
	Enum_WeaponType_0=0,
	Enum_WeaponType_2=2,					//!	2-精确制导导弹
	Enum_WeaponType_3=3,					//!	3-巡航导弹
};

//!	???????
enum Enum_EOGuideType		//EnumDefine.proto					
{
	Enum_GuideType_0=0,
	Enum_GuideType_1=1,					//!	1-红外(ARGM)_AGM65
	Enum_GuideType_2=2,					//!	2-激光(Glider)_GBU-12
	Enum_GuideType_3=3,					//!	3-电视(ARGM)_AGM-130
	Enum_GuideType_4=4,					//!	4-GPS+INS(Glider)_JDAM
	Enum_GuideType_5=5,					//!	5-反辐射（雷达)(ARGM)_AARGM[被动寻的]
	Enum_GuideType_6=6,					//!	6-激光+红外(ARGM)_AGM-114D
	Enum_GuideType_7=7,					//!	7-GPS+INS+红外(Cruise)_战斧
	Enum_GuideType_8=8,					//!	8-毫米波雷达+红外(Cruise)_APTGD
	Enum_GuideType_9=9,					//!	9-GPS/INS+激光(Glider)_SDB
	Enum_GuideType_10=10,				//! 10-反辐射（雷达）ARGM_HARM[被动寻的]
	Enum_GuideType_11=11,				//! 11
	Enum_GuideType_12=12,				//! 12
	Enum_GuideType_13=13,			    //! 13
	Enum_GuideType_14=14,				//! 14

};

//!	????????????
typedef struct _ModelBus_EOWEAPON_IN_MSG
{
	Enum_EOWeaponType EOWeaponType;					//! @Properties(description=武器类型)
	Enum_EOGuideType  EOGuideType;					//! @Properties(description=制导类型)
	int     WeaponID;								//! @Properties(description=武器ID)
	char*   WeaponName;								//! @Properties(description=武器名称)
	int     WeaponMN;								//! @Properties(description=武器型号)
	DKDMS:: Enum_SurvivalState  EOWeaponSurvivalState;		//! @Properties(description=武器存活状态)
	DKDMS:: Enum_WorkState EOWeaponWorkState;				//! @Properties(description=武器工作状态)
	double  WeaponSpeed;							//! @Properties(description=速度, unit=m/s)
	int     AttackID;								//! @Properties(description=攻击目标ID)
	double  AttackLon;                              //! @Properties(description=攻击目标经度, unit=度, minimalValue=-180, maximalValue=180)
	double  AttackLat;                              //! @Properties(description=攻击目标纬度, unit=度, minimalValue=-90, maximalValue=90)
	double  AttackHeight;                           //! @Properties(description=攻击目标高度, unit=米)
	double  dRadiancy;								//! @Properties(description=红外辐射强度, unit=w/sr)
	double  UltravioletRadiaIntensity;				//! @Properties(description=紫外辐射强度, unit=w/sr)
	double  PeakPower0;								//! @Properties(description=激光器输出能量功率峰值P0, unit=w)
	double  LaserPower;								//! @Properties(description=激光能量功率, unit=w)
	double  LaserAngle;	           					//! @Properties(description=激光发散角, unit=rad)

	/*?????????*/
	_ModelBus_EOWEAPON_IN_MSG()
	{
		EOWeaponType=Enum_WeaponType_2;		
		EOGuideType=Enum_GuideType_3;			
		WeaponID=0;
		WeaponName=NULL;					 
		WeaponMN=0;							
		EOWeaponSurvivalState=DKDMS::Enum_SurvivalState_0;				
		EOWeaponWorkState=DKDMS::Enum_WorkState_1;					
		WeaponSpeed=0.0;					
		AttackID=0;								
		AttackLon=0.0;                              
		AttackLat=0.0;                              
		AttackHeight=0.0;                          	
		dRadiancy=0.0;						
		UltravioletRadiaIntensity=0.0;	
		PeakPower0=0.0;						
		LaserPower=0.0;						
		LaserAngle=0.0;						
	}

	/*????????????*/
	~_ModelBus_EOWEAPON_IN_MSG()
	{
		SW_Free_Char(WeaponName);

	}

	/*?????????????*/
	_ModelBus_EOWEAPON_IN_MSG(const _ModelBus_EOWEAPON_IN_MSG&EoTargetPara)
	{
		WeaponName = NULL;
		*this = EoTargetPara;
	}

	/*????=*/
	_ModelBus_EOWEAPON_IN_MSG& operator = (const _ModelBus_EOWEAPON_IN_MSG& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		EOWeaponType=theStruct.EOWeaponType;		
		EOGuideType=theStruct.EOGuideType;			 
		WeaponID=theStruct.WeaponID;
		SW_Malloc_Char(theStruct.WeaponName,WeaponName);					
		WeaponMN=theStruct.WeaponMN;							
		EOWeaponSurvivalState=theStruct.EOWeaponSurvivalState;			
		EOWeaponWorkState=theStruct.EOWeaponWorkState;					 
		WeaponSpeed=theStruct.WeaponSpeed;				
		AttackID=theStruct.AttackID;								
		AttackLon=theStruct.AttackLon;
		AttackLat=theStruct.AttackLat;                              
		AttackHeight=theStruct.AttackHeight;                       		
		dRadiancy=theStruct.dRadiancy;						 
		UltravioletRadiaIntensity=theStruct.UltravioletRadiaIntensity;		
		PeakPower0=theStruct.PeakPower0;						 
		LaserPower=theStruct.LaserPower;						
		LaserAngle=theStruct.LaserAngle;						

		return *this;
	}
}EOWeapon_IN_Msg; //SimModelDataOut.proto

//! @Properties(description=威胁目标信息输入, appType=init)
typedef struct _ModelBus_EOTARGET_SET_INI
{
	char*	sRID;									//! @Properties(description=身份字符串,display=readonly)
	int	equipId;									//! @Properties(description=装备id,alias=modelId,display=readonly)
	DKDMS::Enum_PlatType  PlatType;				//! @Properties(description=平台类型, display=readonly)
	int		PlatID;									//! @Properties(description=平台ID,alias=platformId, display=readonly)
	int     WeaponNum;                              //! @Properties(description=武器数量, display=readonly)
	EOWeapon_IN_Msg* pEOWeapon_IN_Msg;				//! @Properties(description=武器信息)

	_ModelBus_EOTARGET_SET_INI()
	{
		sRID=NULL;
		equipId = 0;	
		PlatType=DKDMS::Enum_PlatType_6;				
		PlatID=0;		
		WeaponNum=0;
		pEOWeapon_IN_Msg=NULL;

	}
	~_ModelBus_EOTARGET_SET_INI()
	{
		SW_Free_Char(sRID);
		if(pEOWeapon_IN_Msg != NULL)
		{

			SW_Delete(pEOWeapon_IN_Msg);
			pEOWeapon_IN_Msg = NULL;
		}

	}
	_ModelBus_EOTARGET_SET_INI(const _ModelBus_EOTARGET_SET_INI& info)
	{
		sRID=NULL;
		pEOWeapon_IN_Msg = NULL;
		*this = info;
	}
	_ModelBus_EOTARGET_SET_INI& operator=(const _ModelBus_EOTARGET_SET_INI& info)
	{
		if( this==&info )
		{
			return *this;
		}
		SW_Malloc_Char(info.sRID,sRID);
		equipId = info.equipId;
		PlatType=info.PlatType;				
		PlatID=info.PlatID;
		WeaponNum=info.WeaponNum;
		SW_Malloc_Struct(EOWeapon_IN_Msg,info.pEOWeapon_IN_Msg, pEOWeapon_IN_Msg, info.WeaponNum,  WeaponNum);

		return *this;
	}
}EOTarget_Set_INI;//SimModelDataOut.proto
//! ???????????????????
typedef struct _ModelBus_EOWEAPON_OUT_MSG
{
	Enum_EOWeaponType EOWeaponType;					         //! 武器类型
	Enum_EOGuideType  EOGuideType;					         //! 制导类型：
	int     WeaponID;								          //! 武器ID
	char*   WeaponName;							              //! 武器名称
	int     WeaponMN;										  //! 武器型号
	DKDMS::Enum_SurvivalState  EOWeaponSurvivalState;		//! 武器存活状态  
	DKDMS::Enum_WorkState EOWeaponWorkState;				//! 武器工作状态   
	bool    JamState;                               //! 是否被GR
	double  WeaponSpeed;							//! 武器速度大小    
	double  WeaponLon;                              //! 武器经度
	double  WeaponLat;                               //! 武器纬度
	double  WeaponHeight;                           //! 武器高度
	int     AttackID;								//! 攻击目标ID
	double  AttackLon;                               //! 攻击目标经度
	double  AttackLat;                              //! 攻击目标纬度
	double  AttackHeight;                           //! 攻击目标高度
	double  LockDis;								//! 锁定目标距离 
	double  AttackDis;							    //! 攻击目标距离  
	double  dRadiancy;							    //! 武器红外辐射强度
	double  UltravioletRadiaIntensity;			     //! 武器紫外辐射强度
	double  PeakPower0;							    //! 激光器输出能量峰值P0
	double  LaserPower;							     //! 激光能量功率
	double  LaserAngle;							    //! 激光发散角
	double	MissleLaunchLON;						//!  发射点经度
	double	MissleLaunchLAT;						//!  发射点纬度
	float	MissleLaunchHeight;						//!  发射点高度
	double	MissleExplodeLON;		                //!  爆炸点经度
	double	MissleExplodeLAT;						//!  爆炸点纬度
	double	MissleExplodeHeight;					//!  爆炸点高度
	double	MissleExplodeDst;						//! 脱靶量
	int		LaunchFlag;								// 是否已发射  0:未发射  1：发射
	double  Heading;								// 航向
	_ModelBus_EOWEAPON_OUT_MSG()
	{

		EOWeaponType=Enum_WeaponType_2;			
		EOGuideType=Enum_GuideType_1;			
		WeaponID=0;								
		WeaponName=NULL;						
		WeaponMN=0;								
		EOWeaponSurvivalState=DKDMS::Enum_SurvivalState_0;		  
		EOWeaponWorkState=DKDMS::Enum_WorkState_0;				  
		JamState=0;                            
		WeaponSpeed=0;							
		WeaponLon=0.0;                         
		WeaponLat=0.0;                         
		WeaponHeight=0.0;                      
		AttackID=0;								
		AttackLon=0.0;                         
		AttackLat=0.0;                         
		AttackHeight=0.0;                      
		LockDis=0.0;							
		AttackDis=0.0;							
		dRadiancy=0.0;							
		UltravioletRadiaIntensity=0.0;			
		PeakPower0=0.0;							
		LaserPower=0.0;							
		LaserAngle=0.0;							
		MissleLaunchLON=0.0;					
		MissleLaunchLAT=0.0;					
		MissleLaunchHeight=0.0;					
		MissleExplodeLON=0.0;		           
		MissleExplodeLAT=0.0;					
		MissleExplodeHeight=0.0;				
		MissleExplodeDst=-1.0;					
		LaunchFlag = 0;
		Heading = 0.0;
	}
	~_ModelBus_EOWEAPON_OUT_MSG()
	{
		SW_Free_Char(WeaponName);


	}
	_ModelBus_EOWEAPON_OUT_MSG(const _ModelBus_EOWEAPON_OUT_MSG& info)
	{
		WeaponName = NULL;
		*this = info;
	}
	_ModelBus_EOWEAPON_OUT_MSG& operator=(const _ModelBus_EOWEAPON_OUT_MSG& info)
	{
		if( this==&info )
		{
			return *this;
		}
		EOWeaponType=info.EOWeaponType;					
		EOGuideType=info.EOGuideType;					
		WeaponID=info.WeaponID;							
		SW_Malloc_Char(info.WeaponName,WeaponName);		
		WeaponMN=info.WeaponMN;							
		EOWeaponSurvivalState=info.EOWeaponSurvivalState;	
		EOWeaponWorkState=info.EOWeaponWorkState;			
		JamState=info.JamState;                             
		WeaponSpeed=info.WeaponSpeed;						
		WeaponLon=info.WeaponLon;                           
		WeaponLat=info.WeaponLat;                           
		WeaponHeight=info.WeaponHeight;                     
		AttackID=info.AttackID;								
		AttackLon=info.AttackLon;                           
		AttackLat=info.AttackLat;                           
		AttackHeight=info.AttackHeight;                     
		LockDis=info.LockDis;								
		AttackDis=info.AttackDis;							
		dRadiancy=info.dRadiancy;							
		UltravioletRadiaIntensity=info.UltravioletRadiaIntensity;			    
		PeakPower0=info.PeakPower0;							    
		LaserPower=info.LaserPower;							    
		LaserAngle=info.LaserAngle;							    
		MissleLaunchLON=info.MissleLaunchLON;					
		MissleLaunchLAT=info.MissleLaunchLAT;					
		MissleLaunchHeight=info.MissleLaunchHeight;				
		MissleExplodeLON=info.MissleExplodeLON;		            
		MissleExplodeLAT=info.MissleExplodeLAT;					
		MissleExplodeHeight=info.MissleExplodeHeight;			
		MissleExplodeDst=info.MissleExplodeDst;	
		LaunchFlag = info.LaunchFlag;
		Heading = info.LaunchFlag;				

		return *this;
	}

}EOWeapon_OUT_Msg;//SimModelDataOut.proto
//! @Properties(description=光电目标信息, appType=modelOut)
typedef struct _ModelBus_EOTARGET_PARA
{
	char*	sRID;									//! 身份字符串
	int equipId;									//模型ID
	float	fTime;									//! 仿真时间
	DKDMS:: Enum_PlatType  PlatType;				//! 平台类型 
	int		PlatID;									//! 平台ID 
	DKDMS:: Enum_ATT   ATT;							//! 敌我属性
	char*    PlatName;								//! 平台名称
	int      PlatMN;								//! 平台型号 
	DKDMS:: Enum_SurvivalState  PlatSurvivalState;	//! 平台存活状态 
	DKDMS:: Enum_WorkState PlatWorkState;			//! 平台工作状态
	double  PlatLon;								//! 经度
	double  PlatLat;								//! 纬度。
	double  PlatHeight;								//! 高度
	double  AZ;									     //! 运动方位角度 
	double  EL;									     //! 运动俯仰角度
	double  Roll;									//! 运动横滚角度 
	double  PlatSpeed;							    //! 平台速度	
	int     WeaponNum;                              //! 武器数量
	EOWeapon_OUT_Msg* pEOWeapon_OUT_Msg;			//! 武器输出参数

	/*?????????*/
	_ModelBus_EOTARGET_PARA()
	{
		sRID=NULL;			
		equipId = 0;					
		fTime=0.;								
		PlatType=DKDMS:: Enum_PlatType_6;				
		PlatID=0;								
		ATT=DKDMS:: Enum_ATT_1;				
		PlatName=NULL;				           
		PlatMN=0;								
		PlatSurvivalState=DKDMS:: Enum_SurvivalState_0;					
		PlatWorkState=DKDMS:: Enum_WorkState_1;						
		PlatLon=0.;								
		PlatLat=0.;								
		PlatHeight=0.;					
		AZ=0.;							
		EL=0.;							
		Roll=0.;						
		PlatSpeed=0.;					
		WeaponNum=0;
		pEOWeapon_OUT_Msg=NULL;
	}

	/*????????????*/
	~_ModelBus_EOTARGET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(PlatName);

		if(pEOWeapon_OUT_Msg != NULL)
		{
			SW_Delete(pEOWeapon_OUT_Msg);
			pEOWeapon_OUT_Msg = NULL;
		}		
	}

	/*?????????????*/
	_ModelBus_EOTARGET_PARA(const _ModelBus_EOTARGET_PARA &EoTargetPara)
	{
		sRID = NULL;
		PlatName=NULL;
		pEOWeapon_OUT_Msg=NULL;
		*this = EoTargetPara;
	}

	/*????=*/
	_ModelBus_EOTARGET_PARA& operator = (const _ModelBus_EOTARGET_PARA &theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);
		equipId = theStruct.equipId;
		fTime=theStruct.fTime;								
		PlatType=theStruct.PlatType;						
		PlatID=theStruct.PlatID;							
		ATT=theStruct.ATT;									
		SW_Malloc_Char(theStruct.PlatName,PlatName);		
		PlatMN=theStruct.PlatMN;							
		PlatSurvivalState=theStruct.PlatSurvivalState;		
		PlatWorkState=theStruct.PlatWorkState;				
		PlatLon=theStruct.PlatLon;							
		PlatLat=theStruct.PlatLat;							
		PlatHeight=theStruct.PlatHeight;					
		AZ=theStruct.AZ;									
		EL=theStruct.EL;									
		Roll=theStruct.Roll;								
		PlatSpeed=theStruct.PlatSpeed;						
		WeaponNum=theStruct.WeaponNum;
		SW_Malloc_Struct(EOWeapon_OUT_Msg,theStruct.pEOWeapon_OUT_Msg,pEOWeapon_OUT_Msg,theStruct.WeaponNum,WeaponNum);	

		return *this;
	}

}EOTarget_Para;//GSF红方Set输入结构体//SimModelDataOut.proto
//! ???????????
typedef struct _ModelBus_JamObj
{
	int MissleID;		//! ????ID
	bool JamStatus;		//! ??????
	/*?????????*/
	_ModelBus_JamObj()
	{
		MissleID = 0;
		JamStatus = 0;
	}

	/*????????????*/
	~_ModelBus_JamObj()
	{

	}

	/*?????????????*/
	_ModelBus_JamObj(const _ModelBus_JamObj &info)
	{
		*this = info;
	}

	/*????=*/
	_ModelBus_JamObj& operator = (const _ModelBus_JamObj &theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		MissleID = theStruct.MissleID;
		JamStatus = theStruct.JamStatus;

		return *this;
	}
}JamObj;//SimModelDataOut.proto
//! ???????????
typedef struct _ModelBus_JamResult
{
	int EquipID;		//! ?豸ID
	int WeaponNum;		//! ????????
	JamObj* jamObj;		//! ???????????
	/*?????????*/
	_ModelBus_JamResult()
	{
		EquipID = 0;
		WeaponNum = 0;
		jamObj = NULL;
	}

	/*????????????*/
	~_ModelBus_JamResult()
	{

		if(jamObj != NULL)
		{
			SW_Delete(jamObj);
			jamObj = NULL;
		}
	}

	/*?????????????*/
	_ModelBus_JamResult(const _ModelBus_JamResult &info)
	{
		jamObj=NULL;
		*this = info;
	}

	/*????=*/
	_ModelBus_JamResult& operator = (const _ModelBus_JamResult &theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		EquipID = theStruct.EquipID;

		WeaponNum = theStruct.WeaponNum;

		SW_Malloc_Struct(JamObj,theStruct.jamObj,jamObj,theStruct.WeaponNum,WeaponNum);


		return *this;
	}
}JamResult;//SimModelDataOut.proto
//---------------------------------------------------------------------------------------------------//
//*************************20220728-----MEnStruct_EOModeJAM.h******************************************//
//---------------------------------------------------------------------------------------------------//

//! @Properties(description=?????????, appType=modelOut)
typedef struct _ModelBus_EOTJAMOUT_PARA
{
	char*	sRID;									//! ????????
	int equipId;

	int typelength;									//! ???????????
	unsigned char* type;							//! ????????????
	int datalength;									//! ???????????
	unsigned char* data;							//! ????????

	/*?????????*/
	_ModelBus_EOTJAMOUT_PARA()
	{
		sRID = NULL;
		equipId = 0;
		typelength = 0;
		type = NULL;
		datalength = 0;
		data = NULL;
	}

	/*????????????*/
	~_ModelBus_EOTJAMOUT_PARA()
	{
		SW_Free_Char(sRID);
		if (type != NULL)
		{
			SW_Delete(type);
			type = NULL;
		}
		if (data != NULL)
		{
			SW_Delete(data);
			data = NULL;
		}
		//SW_Free_Char(type);
		//SW_Free_Char(data);
	}

	/*?????????????*/
	_ModelBus_EOTJAMOUT_PARA(const _ModelBus_EOTJAMOUT_PARA &EoJAMOUTPara)
	{
		sRID = NULL;
		type = NULL;
		data = NULL;
		*this = EoJAMOUTPara;
	}

	/*????=*/
	_ModelBus_EOTJAMOUT_PARA& operator = (const _ModelBus_EOTJAMOUT_PARA &EoJAMOUTPara)
	{
		if( this==&EoJAMOUTPara )
		{
			return *this;
		}
		SW_Malloc_Char(EoJAMOUTPara.sRID,sRID);
		equipId = EoJAMOUTPara.equipId;

		if (EoJAMOUTPara.type != NULL && EoJAMOUTPara.typelength > 0)
		{
			if (type)
			{
				delete [] type;
				type = NULL;
			}
			type = new unsigned char[EoJAMOUTPara.typelength];
			memcpy(type, EoJAMOUTPara.type, EoJAMOUTPara.typelength);
		}
		typelength = EoJAMOUTPara.typelength;

		if (EoJAMOUTPara.data != NULL && EoJAMOUTPara.datalength > 0)
		{
			if (data)
			{
				delete [] data;
				data = NULL;
			}
			data = new unsigned char[EoJAMOUTPara.datalength];
			memcpy(data, EoJAMOUTPara.data, EoJAMOUTPara.datalength);
		}
		datalength = EoJAMOUTPara.datalength;
		return *this;
	}

}EOTJAMOUT_PARA;//SimModelDataOut.proto
typedef struct _ModelBus_EOGuideMissile_Msg
{
	char*	sRID;				      // 身份字符串
	int		ID;					      // 实体ID
	int		PlatID;				      // 搭载平台ID
	char*	EquipmentName;		      // 设备名称
	char*	EquipmentType;		      // 设备型号
	DKDMS::Enum_ATT ATT;			          // 敌我属性
	float   fLon;				      // 经度,单位:度
	float   fLat;				      // 纬度,单位:度
	float   fHeight;			      // 高度,单位:米(m)
	float   fTime;			          // 时间,单位:秒(s)
	float   radi;					  //辐射强度
	bool    bDASWarned;                        //是否被DAS告警
	double  dWarnDur;                           //DAS告警持续时间
	double  PeakPower0;							    //! qmh激光器输出能量峰值P0
	double  LaserPower;							     //! qmh激光能量功率
	double  LaserAngle;							    //! qmh激光发散角
	DKDMS::Enum_SurvivalState SurvivalState; // 生存状态
	DKDMS::Enum_WorkState  WorkState;		  // 工作状态
	DKDMS::Enum_EGuideMode EGuideMode;		  // 光电制导方式

	/*重载构造函数*/
	_ModelBus_EOGuideMissile_Msg()
	{
		sRID		= NULL;
		ID			= 0;
		PlatID      = 0;
		ATT			= DKDMS::Enum_ATT_1;
		fLon		= 0.;
		fLat		= 0.;
		fHeight     = 0.;
		fTime		= 0.;
		radi=0.;
		EquipmentName	 =  NULL;
		EquipmentType	 =  NULL;
		bDASWarned      = false;
		dWarnDur        =0.0;
		PeakPower0=0.0;							    //! qmh激光器输出能量峰值P0
		LaserPower=0.0;							     //! qmh激光能量功率
		LaserAngle=0.0;							    //! qmh激光发散角
		SurvivalState	 = DKDMS::Enum_SurvivalState_0;
		WorkState		 = DKDMS::Enum_WorkState_0;
		EGuideMode       = DKDMS::Enum_EGuideMode_0;
	}

	/*重载析构函数*/
	~_ModelBus_EOGuideMissile_Msg()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EOGuideMissile_Msg(const _ModelBus_EOGuideMissile_Msg &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_EOGuideMissile_Msg& operator=(const _ModelBus_EOGuideMissile_Msg& theStruct)
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

		ID			= theStruct.ID;
		PlatID      = theStruct.PlatID;
		ATT			= theStruct.ATT;
		fLon		= theStruct.fLon;
		fLat        = theStruct.fLat;
		fHeight     = theStruct.fHeight;
		fTime	    = theStruct.fTime;
		radi=       theStruct.radi;
		SurvivalState =  theStruct.SurvivalState;
		WorkState	=  theStruct.WorkState;
		EGuideMode  =  theStruct.EGuideMode;
		bDASWarned  =  theStruct.bDASWarned;
		dWarnDur    =  theStruct.dWarnDur;
		PeakPower0  =  theStruct.PeakPower0;							    //! qmh激光器输出能量峰值P0
		LaserPower  =  theStruct.LaserPower;							     //! qmh激光能量功率
		LaserAngle  =  theStruct.LaserAngle;							    //! qmh激光发散角
		return *this;
	}

}sEOGuideMissile_Msg;//SimModelDataOut.proto
typedef struct _ModelBus_sEOPLAT_PARA
{
	char*	sRID;			//????????
	int		PlatID;			//??????ID?? 
	char*	EquipmentName;	//???????
	char*	EquipmentType;	//???????
	DKDMS::Enum_ATT	ATT;		//????????
	float	fTime;			//??? ??λ????s??
	float	fLon;			//???????λ????
	float	fLat;			//γ?????λ????
	float	fHeight;		//??????λ?????m??
	float	fSpeed;			//?????? ??λ????/??m/s??
	float	fDir;			//?????λ?????λ????
	float	fPitch;			//????????????λ????
	float	fRoll;			//?????????λ????
	bool    bDASWarned;                        //是否被DAS告警
	double  dWarnDur;                           //DAS告警持续时间
	int   nBatch;  // 批次;
	int		iActiveFlag;	//?????(0-?????1????)
	int     nRCSNum;        //RCS????           modify by liuk 20130122

	DKDMS::Enum_FlyPosType	FlyPosType;	//??·?????? 0-???? 1-??? 2-????
	DKDMS::Enum_manoeuverState	manoeuverState;	//????ж?????ε???

	/*?????????*/
	_ModelBus_sEOPLAT_PARA()
	{
		sRID          = NULL;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		fTime         = 0.;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		fSpeed        = 0.;
		fDir          = 0.;
		fPitch        = 0.;
		fRoll         = 0.;
		bDASWarned=false;
		dWarnDur=0.0;
		nBatch=0;  // 批次;
		iActiveFlag   = 0;
		nRCSNum       = 0;

		FlyPosType    = DKDMS::Enum_Out;		
		manoeuverState     = DKDMS::Enum_manoeuverState_0;
	}

	/*????????????*/
	~_ModelBus_sEOPLAT_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);

	}

	/*?????????????*/
	_ModelBus_sEOPLAT_PARA(const _ModelBus_sEOPLAT_PARA &plat)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;

		*this = plat;
	}

	/*????=*/
	_ModelBus_sEOPLAT_PARA& operator=(const _ModelBus_sEOPLAT_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		//SW_Free_Char(EquipmentType);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);

		//SW_Delete(RCSArray);


		PlatID        = theStruct.PlatID;
		ATT           = theStruct.ATT;
		fTime         = theStruct.fTime;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		fSpeed        = theStruct.fSpeed;
		fDir          = theStruct.fDir;
		fPitch        = theStruct.fPitch;
		fRoll         = theStruct.fRoll;
		bDASWarned=theStruct.bDASWarned;
		dWarnDur=theStruct.dWarnDur;
		nBatch=theStruct.nBatch;  // 批次;;  // 批次;
		iActiveFlag   = theStruct.iActiveFlag;
		nRCSNum       = theStruct.nRCSNum;
		FlyPosType    = theStruct.FlyPosType;
		manoeuverState     = theStruct.manoeuverState;
		return *this;
	}
}sEOPLAT_PARA;//SimModelDataOut.proto


#pragma pack(pop)


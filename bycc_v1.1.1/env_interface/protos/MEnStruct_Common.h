/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.1		按照年(个数位)月日组合的方式	**
**版    本:	2015.04.01  zoubz修改											**
*************************************************************************/


#ifndef MEN_STRUCT_COMMON
#define MEN_STRUCT_COMMON

#include <string.h>
#include "MEnStruct_Macros.h"

using namespace std;
#pragma pack(1)

/*************************************************************
*                    模型计算交换类                          *
*************************************************************/
//二维位置
typedef struct _ModelBus_sPON_AGG
{
	float LON;	//经度，单位：度
	float LAT;	//维度，单位：度

	/*重载构造函数*/
	_ModelBus_sPON_AGG()
	{
		LON      = 0;
		LAT      = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sPON_AGG()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sPON_AGG(const _ModelBus_sPON_AGG &jam)
	{
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sPON_AGG& operator=(const _ModelBus_sPON_AGG& theStruct)
	{
		LON      = theStruct.LON;
		LAT      = theStruct.LAT;

		return *this;
	}
}sPON_AGG;

//! 三维位置
typedef struct _ModelBus_sPON_AREA
{
	float LON;		//! @Properties(description=经度, unit=度)
	float LAT;		//! @Properties(description=纬度, unit=度)
	float Height;	//! @Properties(description=高度, unit=米)

	/*重载构造函数*/
	_ModelBus_sPON_AREA()
	{
		LON      = 0;
		LAT      = 0;
		Height   = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sPON_AREA()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sPON_AREA(const _ModelBus_sPON_AREA &jam)
	{
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sPON_AREA& operator=(const _ModelBus_sPON_AREA& theStruct)
	{
		LON      = theStruct.LON;
		LAT      = theStruct.LAT;
		Height   = theStruct.Height;

		return *this;
	}
}sPON_AREA;

//! 平台航迹结构体
typedef struct _ModelBus_sPLAT_TRACK_DATA
{
	float fLon;			//! @Properties(description=经度, unit=度)
	float fLat;			//! @Properties(description=纬度, unit=度)
	float fHeight;		//! @Properties(description=高度, unit=米, defaultValue=5000)
	float fSpeed;		//! @Properties(description=运动速度, unit=米/秒, defaultValue=300)
	float fReachTime;	//! @Properties(description=到达时间, unit=秒, defaultValue=0)
	float fDir;			//! @Properties(description=运动方位角, unit=度)
	float fPitch;		//! @Properties(description=运动俯仰角, unit=度)
	DKDMS::Enum_FlyPosType	FlyPosType;	//! @Properties(description=航路点类型, defaultValue=1)

	/*重载构造函数*/
	_ModelBus_sPLAT_TRACK_DATA()
	{
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		fSpeed        = 0.;
		fReachTime    = 0.;
		fDir          = 0.;
		fPitch        = 0.;
		FlyPosType    = DKDMS::Enum_Out;
	}

	/*重载析构函数*/
	~_ModelBus_sPLAT_TRACK_DATA()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sPLAT_TRACK_DATA(const _ModelBus_sPLAT_TRACK_DATA &plat)
	{
		*this = plat;
	}

	/*重载=*/
	_ModelBus_sPLAT_TRACK_DATA& operator=(const _ModelBus_sPLAT_TRACK_DATA& theStruct)
	{
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		fSpeed        = theStruct.fSpeed;
		fReachTime    = theStruct.fReachTime;
		fDir          = theStruct.fDir;
		fPitch        = theStruct.fPitch;
		FlyPosType    = theStruct.FlyPosType;
		return *this;
	}

}sPLAT_TRACK_DATA;

//! 平台RCS参数
typedef struct _ModelBus_RCS_PARA
{
	// 雷达相对于平台正向的角度(平台RCS个数大于1时有效,0~360，若为固定RCS平台则默认为-1)，顺时针，单位：度
	float fAz;			//! @Properties(description=角度, unit=度, defaultValue=0)
	// 该角度对应的RCS，平方米
	float fRCS;         //! @Properties(description=RCS, unit=平方米, defaultValue=5)
	

	/*重载构造函数*/
	_ModelBus_RCS_PARA()
	{
		fAz          = -1;
		fRCS         = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_RCS_PARA()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_RCS_PARA(const _ModelBus_RCS_PARA &plat)
	{
		*this = plat;
	}

	/*重载=*/
	_ModelBus_RCS_PARA& operator=(const _ModelBus_RCS_PARA& theStruct)
	{
		fRCS          = theStruct.fRCS;
		fAz           = theStruct.fAz;
		return *this;
	}
}RCS_PARA;

//! @Properties(description=平台, appType=init, id=3)
typedef struct _ModelBus_KdPlat
{
	char*	sRID;					//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int		PlatID;					//! @Properties(description=平台id, alias=platformId, display=readonly)
	char*	EquipmentName;			//! @Properties(description=平台名称, alias=equipName)
	char*	EquipmentType;			//! @Properties(description=平台类型, alias=platformType, display=readonly)
	float   fStartTime;				//! @Properties(description=平台运动初始时间, alias=platformStartTime, display=readonly, defaultValue=0)
	DKDMS::Enum_ATT	ATT;				//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_EquipSrc SRCType;			//! 来源
	DKDMS::Enum_AircraftSort	AircraftSort;	//! 飞机类别
	int		TrackNum;					//! @Properties(description=航迹点个数, display=readonly)
	sPLAT_TRACK_DATA* TrackData;		//! @Properties(description=航迹点列表, alias=line, display=readonly)
	int     nRCSNum;                    //! @Properties(description=RCS个数, display=readonly, defaultValue=1)
	RCS_PARA*	RCSArray;	            //! @Properties(description=RCS列表, defaultValue=1)

	/*重载构造函数*/
	_ModelBus_KdPlat()
	{
		sRID          = NULL;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		SRCType       = DKDMS::Enum_EquipSrc_0;
		AircraftSort  = DKDMS::Enum_AircraftSort_0;
		TrackNum      = 0;
		TrackData     = NULL;
		fStartTime	  = 0.f;
		nRCSNum       = 1;
		RCSArray      = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_KdPlat()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(TrackData);
        SW_Delete(RCSArray);
	}

	/*重载拷贝构造函数*/
	_ModelBus_KdPlat(const _ModelBus_KdPlat &plat)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		TrackData = NULL;
		RCSArray = NULL;
		*this = plat;
	}

	/*重载=*/
	_ModelBus_KdPlat& operator=(const _ModelBus_KdPlat& theStruct)
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

		//SW_Delete(TrackData);
		SW_Malloc_Struct(sPLAT_TRACK_DATA,theStruct.TrackData,TrackData,theStruct.TrackNum,TrackNum);

		PlatID        = theStruct.PlatID;
		ATT           = theStruct.ATT;
		SRCType       =theStruct.SRCType;
		AircraftSort  = theStruct.AircraftSort;
		TrackNum      = theStruct.TrackNum;
		fStartTime    = theStruct.fStartTime;
		nRCSNum       = theStruct.nRCSNum;
		//SW_Delete(RCSArray);
		SW_Malloc_Struct(RCS_PARA,theStruct.RCSArray, RCSArray, theStruct.nRCSNum, nRCSNum);

		return *this;
	}
}sPLAT_Set_PARA;

//! @Properties(description=平台输出, appType=modelOut)
typedef struct _ModelBus_sPLAT_PARA
{
	char*	sRID;			//身份字符串
	int		PlatID;			//仿真平台ID号 
	char*	EquipmentName;	//装备名称
	char*	EquipmentType;	//装备类型
	DKDMS::Enum_ATT	ATT;		//敌我属性
	float	fTime;			//时间 单位：秒（s）
	float	fLon;			//经度，单位：度
	float	fLat;			//纬度，单位：度
	float	fHeight;		//高度，单位：米（m）
	float	fSpeed;			//运动速度 单位：米/秒（m/s）
	float	fDir;			//运动方位角，单位：度
	float	fPitch;			//运动俯仰角，单位：度
	float	fRoll;			//横滚角度，单位：度
	int		iActiveFlag;	//活动标识(0-消失，1－活动)
	int     nRCSNum;        //RCS个数           modify by liuk 20130122
	RCS_PARA*	RCSArray;	//回波面积组        modify by zm 20150630
	DKDMS::Enum_FlyPosType	FlyPosType;	//航路点类型 0-出航 1-巡航 2-返航
	DKDMS::Enum_manoeuverState	manoeuverState;	//作战行动各阶段的状态

	/*重载构造函数*/
	_ModelBus_sPLAT_PARA()
	{
		sRID          = "null";
		PlatID        = 0;
		EquipmentName = "null";
		EquipmentType = "null";
		ATT           = DKDMS::Enum_ATT_1;
		fTime         = 0.;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		fSpeed        = 0.;
		fDir          = 0.;
		fPitch        = 0.;
		fRoll         = 0.;
		iActiveFlag   = 0;
		nRCSNum       = 0;
		RCSArray      = NULL;
		FlyPosType    = DKDMS::Enum_Out;		
		manoeuverState     = DKDMS::Enum_manoeuverState_0;
	}

	/*重载析构函数*/
	~_ModelBus_sPLAT_PARA()
	{
		//SW_Free_Char(sRID);
		//SW_Free_Char(EquipmentName);
		//SW_Free_Char(EquipmentType);
		//SW_Delete(RCSArray);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sPLAT_PARA(const _ModelBus_sPLAT_PARA &plat)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		RCSArray      = NULL;
		*this = plat;
	}

	/*重载=*/
	_ModelBus_sPLAT_PARA& operator=(const _ModelBus_sPLAT_PARA& theStruct)
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
		SW_Malloc_Struct(RCS_PARA,theStruct.RCSArray, RCSArray, theStruct.nRCSNum, nRCSNum);

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
		iActiveFlag   = theStruct.iActiveFlag;
		nRCSNum       = theStruct.nRCSNum;
		FlyPosType    = theStruct.FlyPosType;
		manoeuverState     = theStruct.manoeuverState;
		return *this;
	}
}sPLAT_PARA;

//平台交互信息
typedef struct _ModelBus_aPLAT_PARA
{
	char*		sRID;		//身份字符串
	int			ID;			//平台ID
	float		LON;		//经度，单位：度
	float		LAT;		//纬度，单位：度
	float		Height;		//高度，单位：米（m）
	float		fSpeed;	    //运动速度 单位：米/秒（m/s）
	float		fDir;		//运动方位角，单位：度
	int         nRCSNum;    //RCS个数                          
	RCS_PARA*	RCSArray;	//回波面积组 
	float		Radius;		//半径，单位：米（m）

	/*重载构造函数*/
	_ModelBus_aPLAT_PARA()
	{
		sRID        = NULL;
		ID          = 0;
		LON         = 0;
		LAT         = 0;
		Height      = 0;
		fSpeed      = 0.0f;
		fDir        = 0.0f;
		nRCSNum       = 0;
		RCSArray      = NULL;
		Radius = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aPLAT_PARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(RCSArray);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aPLAT_PARA(const _ModelBus_aPLAT_PARA &plat)
	{
		sRID = NULL;
		RCSArray = NULL;
		*this = plat;
	}

	/*重载=*/
	_ModelBus_aPLAT_PARA& operator = (const _ModelBus_aPLAT_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ID     = theStruct.ID;
		LON    = theStruct.LON;
		LAT    = theStruct.LAT;
		Height = theStruct.Height;
		fSpeed = theStruct.fSpeed;
		fDir   = theStruct.fDir;
		Radius = theStruct.Radius;
		nRCSNum  = theStruct.nRCSNum;
		//SW_Delete(RCSArray);
		SW_Malloc_Struct(RCS_PARA,theStruct.RCSArray, RCSArray, theStruct.nRCSNum, nRCSNum);

		return *this;
	}
}aPLAT_PARA;

//! 关键点
typedef struct _ModelBus_sKeyPoint
{
	int iTime;					//! @Properties(description=关键点时间, defaultValue=0)
	DKDMS::Enum_KeyPtType	KeyPtType;	//! @Properties(description=关键点类型, defaultValue=3)

	/*重载构造函数*/
	_ModelBus_sKeyPoint()
	{
		iTime = 0;
		KeyPtType    = DKDMS::Enum_KeyPt_On;
	}

	/*重载析构函数*/
	~_ModelBus_sKeyPoint()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sKeyPoint(const _ModelBus_sKeyPoint &plat)
	{
		*this = plat;
	}

	/*重载=*/
	_ModelBus_sKeyPoint& operator=(const _ModelBus_sKeyPoint& theStruct)
	{
		iTime		 = theStruct.iTime;
		KeyPtType    = theStruct.KeyPtType;
		return *this;
	}

}sKeyPoint;

//重要事件信息
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sIMPORT_EVENT_REPORT
{
	char* sRID;				//身份字符串
	int	ReceiveID;			//发送方ID 
	int	SendID;				//接收方ID 
	float fTime;			//时间 单位：秒（s）
	char* StrImportReport;	//事件信息

	/*重载构造函数*/
	_ModelBus_sIMPORT_EVENT_REPORT()
	{
		sRID           = NULL;
		ReceiveID      = 0;
		SendID         = 0;
		fTime          = 0.;
		StrImportReport= NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sIMPORT_EVENT_REPORT()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(StrImportReport);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sIMPORT_EVENT_REPORT(const _ModelBus_sIMPORT_EVENT_REPORT &jam)
	{
		sRID = NULL;
		StrImportReport = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sIMPORT_EVENT_REPORT& operator=(const _ModelBus_sIMPORT_EVENT_REPORT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(StrImportReport);
		SW_Malloc_Char(theStruct.StrImportReport,StrImportReport);

		ReceiveID         = theStruct.ReceiveID;
		SendID            = theStruct.SendID;
		fTime             = theStruct.fTime;

		return *this;
	}

}eIMPORT_EVENT_REPORT;

//评估模型输入基本参数报
typedef struct _ModelBus_sEVALUATING_Set_PARA
{
	char*	sRID;				//身份字符串
	int		ID;					//模型ID
	int		nItemCount;			//评估指标数量
	int*	pItem;				//评估指标

	/*重载构造函数*/
	_ModelBus_sEVALUATING_Set_PARA()
	{
		sRID		= NULL;
		ID			= 0;			
		nItemCount	= 0;	
		pItem		= NULL;	
	}

	/*重载析构函数*/
	~_ModelBus_sEVALUATING_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(pItem);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sEVALUATING_Set_PARA(const _ModelBus_sEVALUATING_Set_PARA &jam)
	{
		sRID = NULL;
		pItem  = NULL; 
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sEVALUATING_Set_PARA& operator=(const _ModelBus_sEVALUATING_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID			= theStruct.ID;
		nItemCount	= theStruct.nItemCount;

		//SW_Delete(pItem);
		SW_Malloc_Int(theStruct.pItem,pItem,theStruct.nItemCount,nItemCount);

		return *this;
	}
}sEVALUATING_Set_PARA;

//评估数据项
typedef struct _ModelBus_sEvaluateItem
{
	int		nItemIndex;		//评估数据项
	float	fItemValue;		//评估数据值

	/*重载构造函数*/
	_ModelBus_sEvaluateItem()
	{
		nItemIndex	= 0;
		fItemValue	= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sEvaluateItem()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sEvaluateItem(const _ModelBus_sEvaluateItem &theStruct)
	{
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sEvaluateItem& operator=(const _ModelBus_sEvaluateItem& theStruct)
	{
		nItemIndex		= theStruct.nItemIndex;
		fItemValue      = theStruct.fItemValue;
		return *this;
	}
}sEvaluateItem;

//评估模型输出基本参数报
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sEVALUATING_Get_PARA
{
	char*	sRID;				//身份字符串
	int		ID;					//模型ID
	int		nItemCount;			//评估指标数量
	sEvaluateItem*	pItem;		//评估指标

	/*重载构造函数*/
	_ModelBus_sEVALUATING_Get_PARA()
	{
		sRID		= NULL;
		ID			= 0;			
		nItemCount	= 0;	
		pItem		= NULL;	
	}

	/*重载析构函数*/
	~_ModelBus_sEVALUATING_Get_PARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(pItem);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sEVALUATING_Get_PARA(const _ModelBus_sEVALUATING_Get_PARA &jam)
	{
		sRID = NULL;
		pItem  = NULL; 
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sEVALUATING_Get_PARA& operator=(const _ModelBus_sEVALUATING_Get_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID			= theStruct.ID;
		nItemCount	= theStruct.nItemCount;

		//SW_Delete(pItem);
		SW_Malloc_Struct(sEvaluateItem, theStruct.pItem,pItem,theStruct.nItemCount,nItemCount);

		return *this;
	}
}sEVALUATING_Get_PARA;


//! 时间
typedef struct _ModelBus_sTIME 
{
	int iYear;  //! 年
	int iMon;   //! 月
	int iDay;   //! 日
	int iHour;  //! 时
	int iMin;   //! 分
	int iSec;   //! 秒

	/*重载构造函数*/
	_ModelBus_sTIME()
	{
		iYear = 0;
		iMon  = 0;
		iDay  = 0;
		iHour = 0;
		iMin  = 0;
		iSec  = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sTIME()
	{

	}

	/*重载拷贝构造函数*/
	_ModelBus_sTIME(const _ModelBus_sTIME &sTime)
	{
		*this = sTime;
	}

	/*重载=*/
	_ModelBus_sTIME& operator=(const _ModelBus_sTIME& theStruct)
	{
		iYear = theStruct.iYear;
		iMon  = theStruct.iMon;
		iDay  = theStruct.iDay;
		iHour = theStruct.iHour;
		iMin  = theStruct.iMin;
		iSec  = theStruct.iSec;
		return *this;
	}

}sTIME;

#pragma pack()

#endif

/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.09	按照年(个数位)月日组合的方式	**
**版    本:	2015.04.09  zoubz修改											**
*************************************************************************/

#include "MEnStruct_Common.h"
#include <iostream>
#include <stdio.h>
#ifndef MEN_STRUCT_RADARJAM
#define MEN_STRUCT_RADARJAM

#pragma pack(1)
using namespace std;
namespace DKDMS{//namespace DMS start zm20170912
enum Enum_K2300ESMMode
{	// ZC装备工作模式，不限制为2300
	Enum_K2300ESMMode_RWR	= 0, // 关ESM，只保留威胁告警
	Enum_K2300ESMMode_ESM	= 1, // RW + ESM  （528：干涉仪测向天线ZC系统）
	Enum_K2300ESMMode_HGESM = 2, // RW + HGESM （528：GR引导天线ZC系统）
};

enum Enum_K2300ECMMode
{	// K2300ECM工作模式
	Enum_K2300ECMMode_OFF	= 0, // 关GR
	Enum_K2300ECMMode_ECM   = 1, // ECM  （528：支援GR）
	Enum_K2300ECMMode_HPECM = 2, // HPECM  （528：自卫GR）
};

//! 雷达工作模式
enum Enum_RadarWorkMode
{
	Enum_RadarWorkMode_0 = 0, //! VS
	Enum_RadarWorkMode_1 = 1, //! RWR
	Enum_RadarWorkMode_2 = 2, //! VSR
	Enum_RadarWorkMode_3 = 3, //! STT(不能作为起始工作模式)

	Enum_RadarWorkMode_4 = 4, //! 普查模式，SAR专用
	Enum_RadarWorkMode_5 = 5, //! 详查模式一，SAR专用
	Enum_RadarWorkMode_6 = 6, //! 详查模式二，SAR专用
	Enum_RadarWorkMode_7 = 7, //! 聚束模式，SAR专用
	Enum_RadarWorkMode_8 = 8, //! GMTI
	Enum_RadarWorkMode_9 = 9, //! 红外
	Enum_RadarWorkMode_10 = 10, //! 可见光
	Enum_RadarWorkMode_11 = 11, //! 对空模式
	Enum_RadarWorkMode_12 = 12, //! 对海模式
	Enum_RadarWorkMode_13 = 13, //! 对地模式
	Enum_RadarWorkMode_14 = 14, //! 预留
	Enum_RadarWorkMode_15 = 15, //! 预留
	Enum_RadarWorkMode_16 = 16, //! 预留
};

//add zm 20161018 方向控制，目前暂用于描述SAR波束
enum Enum_DirCtrl
{	
	Enum_DirCtrl_0 = 0,		// 前向
	Enum_DirCtrl_1 ,		// 后向
	Enum_DirCtrl_2 ,		// 下视
	Enum_DirCtrl_3 ,		// 左向
	Enum_DirCtrl_4 ,		// 右向
	Enum_DirCtrl_5 ,		// 预留
	Enum_DirCtrl_6 ,		// 预留
	Enum_DirCtrl_7 ,		// 预留
	Enum_DirCtrl_8 ,		// 预留
};

enum Enum_RadarJamDirCtrl
{	// 雷达GR方向控制
	Enum_RadarJamDirCtrl_0 = 0,		// 前向：固定侦收前向信号，并固定前向发出GR
	Enum_RadarJamDirCtrl_1 = 1,		// 后向：固定侦收后向信号，并固定后向发出GR
	Enum_RadarJamDirCtrl_2 = 2,		// 自动：自动侦收前/后/左/右向信号，并根据接收到的信号方位发出前向/后/左/右向GR
	Enum_RadarJamDirCtrl_3 = 3,		// 左向：固定侦收左向信号，并固定前向发出GR
	Enum_RadarJamDirCtrl_4 = 4,		// 右向：固定侦收右向信号，并固定后向发出GR
};
}

//default

//struct  sPON_AREA
//{
//	int   ptr;
//};
//
//struct sKeyPoint
//{
//	int ptr;
//};

//GR波束
typedef struct _ModelBus_sJAM_POINT
{
	float JamPointAZ;	//GR波束方位指向，单位：度
	float JamPointEL;	//GR波束俯仰指向，单位：度
	float HBeamWidth;	//GR天线水平波束宽度，单位：度（o）
	float VBeamWidth;	//GR天线垂直波束宽度，单位：度（o）
	float BeamDis;		//波束长度，单位：千米（Km）
	int   nJamTrgNum;   //真实GR目标数
	int*  JamTrgID;     //GR的目标ID


	/*重载构造函数*/
	_ModelBus_sJAM_POINT()
	{
		JamPointAZ        = 0;
		JamPointEL        = 0;
		HBeamWidth        = 0;
		VBeamWidth        = 0;
		BeamDis           = 0;
		nJamTrgNum        = 0;
        JamTrgID          = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sJAM_POINT()
	{
		SW_Delete(JamTrgID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sJAM_POINT(const _ModelBus_sJAM_POINT &jam)
	{
		JamTrgID          = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sJAM_POINT& operator=(const _ModelBus_sJAM_POINT& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		JamPointAZ        = theStruct.JamPointAZ;
		JamPointEL        = theStruct.JamPointEL;
		HBeamWidth        = theStruct.HBeamWidth;
		VBeamWidth        = theStruct.VBeamWidth;
		BeamDis           = theStruct.BeamDis;
        nJamTrgNum        = theStruct.nJamTrgNum;
		//SW_Delete(JamTrgID);
		SW_Malloc_Int(theStruct.JamTrgID,JamTrgID,theStruct.nJamTrgNum,nJamTrgNum);
		return *this;
	}
}sJAM_POINT;

//ZC/GR能力区域
typedef struct _ModelBus_sJAM_POWERPOINT
{
	float fStartAZ;    //起始方位角 单位：度 范围：0~360
	float fEndAZ;      //终止方位角 单位：度 范围：0~360
	float fMaxDis;     //最大作用距离 单位：米
	float fMinDis;     //最小作用距离 单位：米
	float fStartEL;    //起始俯仰角 单位：度 范围：-90~90
	float fEndEL;      //终止俯仰角 单位：度 范围：-90~90

	/*重载构造函数*/
	_ModelBus_sJAM_POWERPOINT()
	{
		fStartAZ = 0.;
		fEndAZ   = 0.;
		fMaxDis  = 0.;
		fMinDis  = 0.;
		fStartEL = 0.;
		fEndEL   = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sJAM_POWERPOINT()
	{
	}


	/*重载拷贝构造函数*/
	_ModelBus_sJAM_POWERPOINT(const _ModelBus_sJAM_POWERPOINT &jam)
	{
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sJAM_POWERPOINT& operator=(const _ModelBus_sJAM_POWERPOINT& theStruct)
	{
		fStartAZ = theStruct.fStartAZ;
		fEndAZ   = theStruct.fEndAZ;
		fMaxDis  = theStruct.fMaxDis;
		fMinDis  = theStruct.fMinDis;
		fStartEL = theStruct.fStartEL;
		fEndEL	 = theStruct.fEndEL;

		return *this;
	}
}sJAM_POWERPOINT;
typedef sJAM_POWERPOINT sRECON_POWERPOINT;
typedef sJAM_POWERPOINT sCOVER_RANGE;

//GR机GR交互基本参数报
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sJAM_PARA
{
	char*	sRID;			//身份字符串
	int		JammerID;		//GR机ID
	int		RadarID;		//雷达ID    
	char*	EquipmentName;	//装备名称
	char*	EquipmentType;	//装备类型
	float	fTime;			//时间 单位：秒（s）
	DKDMS::Enum_ATT	ATT;		//敌我属性
	DKDMS::Enum_WorkState		WorkState;		//工作状态
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	float	fLon;			//经度，单位：度（o）
	float	fLat;			//纬度，单位：度（o）
	float	fHeight;		//高度，单位：米（m）
	int		PlatID;			//GR机所在平台ID
	float	fRF;			//工作频率 单位：MHz
	DKDMS::Enum_JamMode	JamMode;//GR样式
	float	fPt;			//GR机功率 单位：瓦（w）
	float	fGt;			//GR机天线主瓣增益 单位：分贝（dB）
	float	fSLGain;		//GR机天线平均旁瓣增益 单位：分贝（dB）
	float	fLoss;			//GR机综合发射损失 单位：分贝（dB）
	int		iFalseTrgNum;	//假目标个数(欺骗GR有效)  //by zoujw
	float	JamPointAZ;		//GR波束方位指向，单位：度
	float	JamPointEL;		//GR波束俯仰指向，单位：度
	float	fJamSigBW;		//GR信号带宽（噪声GR时有效） 单位：KHz
	float	fBeamWidth;		//GR天线波束宽度，单位：度

	/*重载构造函数*/
	_ModelBus_sJAM_PARA()
	{
		sRID          = "null";
		JammerID      = 0;
		RadarID       = 0;
		EquipmentName = "null";
		EquipmentType = "null";
		fTime         = 0.;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		PlatID        = 0;
		fRF           = 0.;
		JamMode       = DKDMS::Enum_JamMode_0;
		fPt           = 0.;
		fGt           = 0.;
		fSLGain       = 0.;
		fLoss         = 0.;
		iFalseTrgNum  = 0;
		JamPointAZ	 = 0.;
		JamPointEL  = 0;
		fJamSigBW     = 0.;
		fBeamWidth     = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sJAM_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sJAM_PARA(const _ModelBus_sJAM_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sJAM_PARA& operator=(const _ModelBus_sJAM_PARA& theStruct)
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

		JammerID        = theStruct.JammerID;
		RadarID         = theStruct.RadarID;
		fTime         = theStruct.fTime;
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		SurvivalState = theStruct.SurvivalState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		PlatID        = theStruct.PlatID;
		fRF           = theStruct.fRF;
		JamMode       = theStruct.JamMode;
		fPt           = theStruct.fPt;
		fGt           = theStruct.fGt;
		fSLGain       = theStruct.fSLGain;
		fLoss         = theStruct.fLoss;
		iFalseTrgNum  = theStruct.iFalseTrgNum;
		JamPointAZ  = theStruct.JamPointAZ;
		JamPointEL  = theStruct.JamPointEL;
		fJamSigBW     = theStruct.fJamSigBW;
		fBeamWidth     = theStruct.fBeamWidth;
		return *this;
	}
}sJAM_PARA;
typedef sJAM_PARA sJAM_PARA_INTERACTIVE;


//! @Properties(description=雷达GR装备, appType=init, id=4)
typedef struct _ModelBus_sJAM_Set_PARA
{
	char*	sRID;				//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int		JammerID;			//! @Properties(description=装备id, alias=modelId, display=readonly)
	int		PlatID;				//! @Properties(description=平台id, alias=platformId, display=readonly)
	char*	EquipmentName;		//! @Properties(description=装备名称, alias=equipName)
	char*	EquipmentType;		//! 装备类型
	DKDMS::Enum_ATT		ATT;		//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作属性, defaultValue=1)
	float	fLon;				//! @Properties(description=经度, alias=lon, unit=度)
	float	fLat;				//! @Properties(description=纬度, alias=lat, unit=度)
	float	fHeight;			//! @Properties(description=高度, alias=hei, unit=米)
	// 控守起始方位，单位：度（地面装备有效）
	float	fStartAZ;           //! @Properties(description=控守起始方位, unit=度, defaultValue=0)
	// 控守终止方位，单位：度（地面装备有效）
	float   fEndAZ;			    //! @Properties(description=控守终止方位, unit=度, defaultValue=360)
	int		iTrgNum;			//! @Properties(description=被对抗的雷达个数, display=readonly)
	int*	lTrgVal;			//! @Properties(description=被对抗的雷达列表, alias=gis-sRADAR_Set_PARA)
	// 目前仅对运八GR机有效
	int		iCenterPoint;		//! @Properties(description=中心区域点个数, display=readonly)
	sPON_AREA *pCenterPoint;	//! 中心区域点列表
	int		iKeyPtNum;			//! @Properties(description=关键点个数, display=readonly, defaultValue=1)
	sKeyPoint *pKeyPt;			//! @Properties(description=关键点列表, defaultValue=1)

	/*重载构造函数*/
	_ModelBus_sJAM_Set_PARA()
	{
		sRID          = nullptr;
		JammerID      = 0;
		PlatID        = 0;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_1;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		iTrgNum       = 0;
		lTrgVal       = nullptr;
		iCenterPoint  = 0;
		pCenterPoint  = nullptr;
		fStartAZ      = 0.;
		fEndAZ        = 360.;
		iKeyPtNum	  = 0;
		pKeyPt		  = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sJAM_Set_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);

		SW_Delete(lTrgVal);
		SW_Delete(pCenterPoint);
		SW_Delete(pKeyPt);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sJAM_Set_PARA(const _ModelBus_sJAM_Set_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		lTrgVal = nullptr;
		pCenterPoint  = nullptr; 
		pKeyPt		  = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sJAM_Set_PARA& operator=(const _ModelBus_sJAM_Set_PARA& theStruct)
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
		iTrgNum=theStruct.iTrgNum;
		//SW_Delete(lTrgVal);
		SW_Malloc_Int(theStruct.lTrgVal,lTrgVal,theStruct.iTrgNum,iTrgNum);
		iCenterPoint=theStruct.iCenterPoint;
		//SW_Delete(pCenterPoint);
		SW_Malloc_Struct(sPON_AREA,theStruct.pCenterPoint,pCenterPoint,theStruct.iCenterPoint,iCenterPoint);

		iKeyPtNum=theStruct.iKeyPtNum;
		//SW_Delete(pKeyPt);
		SW_Malloc_Struct(sKeyPoint,theStruct.pKeyPt,pKeyPt,theStruct.iKeyPtNum,iKeyPtNum);

		JammerID        = theStruct.JammerID;
		PlatID          = theStruct.PlatID;
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		iTrgNum       = theStruct.iTrgNum;
		fStartAZ      = theStruct.fStartAZ;
		fEndAZ        = theStruct.fEndAZ;

		return *this;
	}
}sJAM_Set_PARA;


//GR机输出基本参数报
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sJAM_Get_PARA
{
	char*	sRID;				//身份字符串
	int		JammerID;			//GR机ID
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
	int		JamPointAmount;		//GR波束个数
	sJAM_POINT* JamPointVar;	//GR波束值
	DKDMS::Enum_EquipUseType EquipUseType; // 装备作战用途
	int		iTrgNum;			//对抗目标个数  
	int*	lTrgVal;			//对抗目标ID
	int		iJamedTrgNum;		//被GR的目标个数
	int*	lJamedTrgVal;		//被GR的目标ID

	/*重载构造函数*/
	_ModelBus_sJAM_Get_PARA()
	{
		sRID          = "null";
		JammerID      = 0;
		PlatID        = 0;
		EquipmentName = "null";
		EquipmentType = "null";
		fTime         = 0.;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		JamPointAmount= 0;
		JamPointVar   = nullptr;
		iTrgNum       = 0;
		lTrgVal       = 0;
		EquipUseType = DKDMS::Enum_EquipUseType_0;
		iJamedTrgNum = 0;
		lJamedTrgVal = 0;

	}

	/*重载析构函数*/
	~_ModelBus_sJAM_Get_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);

		SW_Delete(JamPointVar);
		SW_Delete(lTrgVal);
		SW_Delete(lJamedTrgVal);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sJAM_Get_PARA(const _ModelBus_sJAM_Get_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		JamPointVar = nullptr;
		lTrgVal = nullptr;
		lJamedTrgVal = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sJAM_Get_PARA& operator=(const _ModelBus_sJAM_Get_PARA& theStruct)
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

		iTrgNum=theStruct.iTrgNum;
		//SW_Delete(lTrgVal);
		SW_Malloc_Int(theStruct.lTrgVal,lTrgVal,theStruct.iTrgNum,iTrgNum);

		iJamedTrgNum=theStruct.iJamedTrgNum;
		//SW_Delete(lJamedTrgVal);
		SW_Malloc_Int(theStruct.lJamedTrgVal,lJamedTrgVal,theStruct.iJamedTrgNum,iJamedTrgNum);

		JammerID        = theStruct.JammerID;
		PlatID          = theStruct.PlatID;
		fTime         = theStruct.fTime;
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		SurvivalState = theStruct.SurvivalState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		JamPointAmount= theStruct.JamPointAmount;
		EquipUseType = theStruct.EquipUseType;
		//SW_Delete(JamPointVar);

		SW_Malloc_Struct(sJAM_POINT,theStruct.JamPointVar,JamPointVar,theStruct.JamPointAmount,JamPointAmount);

		return *this;
	}
}sJAM_Get_PARA;

//GR能力范围信息
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sJAM_JAMRANGE 
{
	char*	sRID;			//身份字符串
	int		JammerID;		//GR机ID
	int		TargetID;
	float   fTime;          //时间 单位：秒
	float	fCenterLon;	    //经度，单位：度（o）
	float	fCenterLat;		//纬度，单位：度（o）
	float	fCenterHeight;	//高度，单位：米（m）
	int     nJamRangeNum;   //GR能力区域个数
	sJAM_POWERPOINT* PowerRange;  //GR能力区域

	/*重载构造函数*/
	_ModelBus_sJAM_JAMRANGE()
	{
		sRID          = nullptr;
		JammerID      = 0;
		TargetID	  = 0;
		fTime         = 0.;
		fCenterLon    = 0.;
		fCenterLat    = 0.;
		fCenterHeight = 0.;
		nJamRangeNum  = 0;
		PowerRange    = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sJAM_JAMRANGE()
	{
		SW_Free_Char(sRID);
		SW_Delete(PowerRange);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sJAM_JAMRANGE(const _ModelBus_sJAM_JAMRANGE &jam)
	{
		sRID  = nullptr;
		PowerRange = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sJAM_JAMRANGE& operator=(const _ModelBus_sJAM_JAMRANGE& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		JammerID        = theStruct.JammerID;
		TargetID	=	theStruct.TargetID;
		fTime           = theStruct.fTime;
		fCenterLon      = theStruct.fCenterLon;
		fCenterLat      = theStruct.fCenterLat;
		fCenterHeight   = theStruct.fCenterHeight;
		nJamRangeNum    = theStruct.nJamRangeNum;

		//SW_Delete(PowerRange);
		SW_Malloc_Struct(sJAM_POWERPOINT,theStruct.PowerRange,PowerRange,theStruct.nJamRangeNum,nJamRangeNum);

		return *this;
	}

}sJAM_JAMRANGE;
typedef sJAM_JAMRANGE sEQUIP_POWER_AREA;

//GR机动态分配目标
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sJAM_Set_TARGET
{
	char*	sRID;		//身份字符串
	int		JammerID;	//GR机ID
	int		iTrgNum;	//对抗目标个数  
	int*	lTrgVal;	//对抗目标ID

	/*重载构造函数*/
	_ModelBus_sJAM_Set_TARGET()
	{
		sRID          = nullptr;
		JammerID      = 0;
		iTrgNum       = 0;
		lTrgVal       = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sJAM_Set_TARGET()
	{
		SW_Free_Char(sRID);
		SW_Delete(lTrgVal);

	}

	/*重载拷贝构造函数*/
	_ModelBus_sJAM_Set_TARGET(const _ModelBus_sJAM_Set_TARGET &jam)
	{
		sRID = nullptr;
		lTrgVal = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sJAM_Set_TARGET& operator=(const _ModelBus_sJAM_Set_TARGET& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		JammerID      = theStruct.JammerID;
		iTrgNum       = theStruct.iTrgNum;

		//SW_Delete(lTrgVal);

		SW_Malloc_Int(theStruct.lTrgVal,lTrgVal,theStruct.iTrgNum,iTrgNum);

		return *this;	
	}
}sJAM_Set_TARGET;

//! @Properties(description=雷达, appType=init, id=1)
typedef struct _ModelBus_sRADAR_POS
{
	char*	sRID;				//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int		RadarID;			//! @Properties(description=目标id, alias=modelId, display=readonly)
	int		PlatID;				//! @Properties(description=平台id, alias=platformId, display=readonly)
	float	fLon;				//! @Properties(description=经度, alias=lon, unit=度)
	float	fLat;				//! @Properties(description=纬度, alias=lat, unit=度)
	float	fHeight;			//! @Properties(description=高度, alias=hei, unit=米)
	char*	EquipmentName;		//! @Properties(description=装备名称, alias=equipName)
	char*	EquipmentType;		//! 装备类型
	float   fStartTime;			//! 仿真开始时间
	DKDMS::Enum_ATT		ATT;		//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作状态, defaultValue=1)
	DKDMS::Enum_SurvivalState	SurvivalState;	//! @Properties(description=生存状态, defaultValue=0)
	int		RIEV;				//! 雷达接收机处理模式
	int		DivType;			//! @Properties(description=捷变方式（1-自动，2-手动）, defaultValue=1)
	float	DivFre;				//! 捷变频率（自动时该值无效，手动时该值表示频率）
	int		iMonitorType;		//! 雷达显示器类型(1-P显，2-B显)

	float	fSRCS;				//! @Properties(description=标称目标雷达截面积, unit=平方米, defaultValue=5)
	float	fSHeight;			//! @Properties(description=标称目标高度, unit=米, defaultValue=2000)
	// 指定标称RCS平台ID，如果为空则使用标称fSRCS和fSHeight
	int		StdRCSPlatID;		//! @Properties(description=标称RCS平台ID, defaultValue=-1)
	// 目前仅对相控阵雷达有效
	float	fAntAngle;			//! @Properties(description=天线法向, unit=度)

	DKDMS::Enum_RadarWorkMode RadarWorkMode;  //! @Properties(description=雷达工作模式, defaultValue=1)

	//以下字段SAR雷达有效,用于确定扫描范围、经纬划分网格的数量
	float fStartLon;//! fStartLon
	float fEndLon;//! fEndLon
	int   iLonDivNum;//! iLonDivNum
	float fStartLat;//! fStartLat
	float fEndLat;//! fEndLat
	int   iLatDivNum;//! iLatDivNum
	//SAR add end

	/*重载构造函数*/
	_ModelBus_sRADAR_POS()
	{
		sRID          = nullptr;
		RadarID       = 0;
		PlatID        = 0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		fStartTime    = 0;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		RIEV          = 0;
		DivType       = 0;
		DivFre        = 0.;
		iMonitorType  = 0;

		fSRCS= 0.;
		fSHeight= 0.;
		fAntAngle= 0.;
		RadarWorkMode = DKDMS::Enum_RadarWorkMode_1;
		StdRCSPlatID = -1;

		fStartLon  = 0;
		fEndLon    = 0;
		iLonDivNum = 0;
		fStartLat  = 0;
		fEndLat    = 0;
		iLatDivNum = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_POS()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_POS(const _ModelBus_sRADAR_POS &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRADAR_POS& operator=(const _ModelBus_sRADAR_POS& theStruct)
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

		RadarID         	= theStruct.RadarID;
		PlatID          	= theStruct.PlatID;
		fLon            	= theStruct.fLon;
		fLat            	= theStruct.fLat;
		fHeight         	= theStruct.fHeight;
		ATT					= theStruct.ATT;
		WorkState			= theStruct.WorkState;
		SurvivalState		= theStruct.SurvivalState;
		RIEV				= theStruct.RIEV;
		DivType				= theStruct.DivType;
		DivFre				= theStruct.DivFre;
		iMonitorType        = theStruct.iMonitorType;

		fSRCS               = theStruct.fSRCS;
		fSHeight            = theStruct.fSHeight;
		fAntAngle           = theStruct.fAntAngle;
		fStartTime = theStruct.fStartTime;
		RadarWorkMode       = theStruct.RadarWorkMode;
		StdRCSPlatID		= theStruct.StdRCSPlatID;

		fStartLon  = theStruct.fStartLon ;
		fEndLon    = theStruct.fEndLon   ;
		iLonDivNum = theStruct.iLonDivNum;
		fStartLat  = theStruct.fStartLat ;
		fEndLat    = theStruct.fEndLat   ;
		iLatDivNum = theStruct.iLatDivNum;

		return *this;
	}

}sRADAR_Set_PARA;

//雷达工作参数报
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRADAR_PARA
{
	char*	sRID;			//身份字符串
	int		RadarID;		//雷达ID号  
	char*	EquipmentName;	//装备名称
	char*	EquipmentType;	//装备类型
	int		PlatID;			//仿真平台ID号 
	float	fTime;			//时间 单位：秒（s）
	DKDMS::Enum_ATT	ATT;		//敌我属性
	DKDMS::Enum_WorkState		WorkState;		//工作状态
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_RadarSort		eRadarSort;		//雷达功能用途
	DKDMS::Enum_RadarWorkMode  eRadarWorkMode; //雷达工作模式
	float	fLon;			//经度，单位：度
	float	fLat;			//纬度，单位：度
	float	fHeight;		//高度，单位：米（m）
	float	fRF;			//雷达工作频率 单位：MHz
	float   fRFMax;         //最大频率范围 单位：MHz  2013.01.22 add by liuk
	float   fRFMin;         //最小频率范围 单位: MHz  2013.01.22 add by liuk
	float	fPt;			//雷达发射功率 单位：w
	float	fLt;			//发射损失 单位：分贝（dB）
	float	fGt;			//雷达天线主瓣增益 单位：分贝（dB）
	float	fAzBeamWidth;	//雷达天线主瓣水平波束宽度，单位：度
	float	fElBeamWidth;	//雷达天线主瓣俯仰波束宽度，单位：度
	float	AntAZ;			//天线方位指向，单位：度
	float	AntEl;			//天线俯仰指向，单位：度
	float	fAziMax;		//方位扫描最大值，单位：度
	float	fAziMin;		//方位扫描最小值，单位：度
	float   fElMax;         //俯仰扫描最大值，单位：度 2013.01.25 add by liuk
	float   fElMin;         //俯仰扫描最小值，单位：度 2013.01.25 add by liuk
	float   ScanCycle;	    //天线扫描周期，单位：s
	DKDMS::Enum_PCM    PCM;        //脉内调制类型
	DKDMS::Enum_RFT	RFT;		//射频类型
	float		PRI;		//PRI 单位：us
	DKDMS::Enum_PRIT	PRIT;		//PRI类型
	float		PW;			//脉宽 单位：us
	float		RBand;		//雷达接收机带宽 单位：MHz
	DKDMS::Enum_POT	POT;		//极化类型
	float		iMonitorType;//雷达显示器类型(1-P显，2-B显)
	float       AutoTrackDistance; //自动跟踪距离 单位：米  2013.01.22 add by liuk
	float	    fSlmGt;			//雷达天线平均旁瓣增益 单位：分贝（dB）
	float		fSL1Gt;		    //天线第一旁瓣增益，单位：dB
	DKDMS::Enum_PlatType  ePlatType;   //搭载平台类型


	/*重载构造函数*/
	_ModelBus_sRADAR_PARA()
	{
		sRID          = "null";
		RadarID       = 0;
		EquipmentName = "null";
		EquipmentType = "null";
		PlatID        = 0;
		fTime         = 0.;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		eRadarSort	  = DKDMS::Enum_RadarSort_0;
		eRadarWorkMode = DKDMS::Enum_RadarWorkMode_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		fRF           = 0;
		fRFMax        = 0.;
		fRFMin        = 0.;
		fPt           = 0;
		fLt           = 0.;
		fGt           = 0;
		fAzBeamWidth  = 0;
		fElBeamWidth  = 0;
		AntAZ         = 0;
		AntEl         = 0;
		fAziMax       = 0;
		fAziMin       = 0;
		fElMax        = 0;
		fElMin        = 0;
		ScanCycle     = 0.;
		PCM           = DKDMS::Enum_PCM_1;
		RFT           = DKDMS::Enum_RFT_0;
		PRI           = 0;
		PRIT          = DKDMS::Enum_PRIT_0;
		PW            = 0;
		RBand         = 0;
		POT           = DKDMS::Enum_POT_0;
		iMonitorType  = 0;
		AutoTrackDistance = 0;
		fSlmGt		  = 0;
		fSL1Gt        = 0;
		ePlatType     = DKDMS::Enum_PlatType_255;
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_PARA()
	{
		//SW_Free_Char(sRID);

		//SW_Free_Char(EquipmentName);

		//SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_PARA(const _ModelBus_sRADAR_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRADAR_PARA& operator=(const _ModelBus_sRADAR_PARA& theStruct)
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

		RadarID				= theStruct.RadarID;
		PlatID				= theStruct.PlatID;
		fTime				= theStruct.fTime;
		ATT					= theStruct.ATT;
		WorkState			= theStruct.WorkState;
		SurvivalState       = theStruct.SurvivalState;
		eRadarSort			= theStruct.eRadarSort;
		eRadarWorkMode      = theStruct.eRadarWorkMode;
		fLon				= theStruct.fLon;
		fLat				= theStruct.fLat;
		fHeight				= theStruct.fHeight;
		fRF          		= theStruct.fRF;
		fRFMax              = theStruct.fRFMax;
		fRFMin              = theStruct.fRFMin;
		fPt          		= theStruct.fPt;
		fLt          		= theStruct.fLt;
		fGt          		= theStruct.fGt;
		fAzBeamWidth        = theStruct.fAzBeamWidth;
		fAzBeamWidth        = theStruct.fAzBeamWidth;
		fElBeamWidth        = theStruct.fElBeamWidth;
		AntAZ          		= theStruct.AntAZ;
		AntEl          		= theStruct.AntEl;
		fAziMax          	= theStruct.fAziMax;
		fAziMin          	= theStruct.fAziMin;
		fElMax              = theStruct.fElMax;
		fElMin              = theStruct.fElMin;
		ScanCycle           = theStruct.ScanCycle;
		PCM                 = theStruct.PCM;
		RFT          		= theStruct.RFT;
		PRI          		= theStruct.PRI;
		PRIT				= theStruct.PRIT;
		PW					= theStruct.PW;
		RBand				= theStruct.RBand;
		POT					= theStruct.POT;
		iMonitorType		= theStruct.iMonitorType;
		AutoTrackDistance   = theStruct.AutoTrackDistance;
		fSlmGt				= theStruct.fSlmGt;
		fSL1Gt              = theStruct.fSL1Gt;
		ePlatType           = theStruct.ePlatType;

		return *this;
	}
}sRADAR_PARA;
typedef sRADAR_PARA sRADAR_PARA_FC;

//雷达TC包罗数据结构定义（新）
typedef struct _ModelBus_sRectZone
{
	float fLon;		//经度，单位：度
	float fLat;		//纬度，单位：度

	/*重载构造函数*/
	_ModelBus_sRectZone()
	{
		fLon       = 0;
		fLat       = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sRectZone()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRectZone(const _ModelBus_sRectZone &jam)
	{
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRectZone& operator=(const _ModelBus_sRectZone& theStruct)
	{
		fLon       = theStruct.fLon;
		fLat       = theStruct.fLat;

		return *this;
	}

}sRectZone;

//雷达TC范围报（新）
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRADAR_RANGE
{
	char*	sRID;			//身份字符串
	int		RadarID;		//雷达ID  
	int     TargetID;       //目标ID
	float	fTime;			//时间 单位：秒（s）
	int     nRangeSort;     //范围类型，1代表TC，2代表跟踪
	int		iDetectZoneNum;	//点数量  
	sRectZone* ZonePoint;	//包络点
	float   fTrgHeight;      //实际TC目标高度，单位：米（m）//zm 20150627
	float	fSHeight;		//标称目标高度，单位：米（m）//zoubz 20130810
	float   fRangeJamRatio; //距离压制系数（噪声GR有效，GR方向上），0-1，0表示无压制，1表示全压制

	/*重载构造函数*/
	_ModelBus_sRADAR_RANGE()
	{
		sRID          = "null";
		RadarID       = 0;
		TargetID      = 0;
		fTime         = 0.;
		nRangeSort    = 0;
		iDetectZoneNum= 0;
		ZonePoint     = nullptr;
		fTrgHeight     = 0.;
		fSHeight	  = 0.;
		fRangeJamRatio= 0.;
	}


	///*重载析构函数*/
	//~_ModelBus_sRADAR_RANGE()
	//{
	//	SW_Free_Char(sRID);
	//	SW_Delete(ZonePoint);
	//}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_RANGE(const _ModelBus_sRADAR_RANGE &jam)
	{
		sRID = nullptr;
		ZonePoint = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRADAR_RANGE& operator=(const _ModelBus_sRADAR_RANGE& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Delete(ZonePoint);
		SW_Malloc_Struct(sRectZone,theStruct.ZonePoint,ZonePoint,theStruct.iDetectZoneNum,iDetectZoneNum);

		RadarID         = theStruct.RadarID;
		TargetID        = theStruct.TargetID;
		fTime           = theStruct.fTime;
		nRangeSort      = theStruct.nRangeSort;
		iDetectZoneNum  = theStruct.iDetectZoneNum;
		fSHeight	    = theStruct.fSHeight;
		fTrgHeight       = theStruct.fTrgHeight;
		fRangeJamRatio	= theStruct.fRangeJamRatio;

		return *this;
	}
}sRADAR_RANGE;

//单点雷达TC距离
typedef struct _ModelBus_RADAR_DistNode
{		
	double  DetectDist;     //雷达TC距离,m
	float	Prob;			//TC概率0~1

	/*重载构造函数*/
	_ModelBus_RADAR_DistNode()
	{
		DetectDist    = 0;
		Prob          = 0;
	}

	/*重载析构函数*/
	~_ModelBus_RADAR_DistNode()
	{		
	}

	/*重载拷贝构造函数*/
	_ModelBus_RADAR_DistNode(const _ModelBus_RADAR_DistNode &jam)
	{
		*this = jam;
	}

	/*重载=*/
	_ModelBus_RADAR_DistNode& operator=(const _ModelBus_RADAR_DistNode& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		DetectDist      = theStruct.DetectDist;
		Prob            = theStruct.Prob;
		return *this;
	}
}RADAR_DistNode;

//对某一目标的TC距离计算结果
typedef struct _ModelBus_DectDistRlt
{  
	int		TargetID;		      //目标ID 
	float   fTrgHeight;           //目标高度
	int     DetcDistNum;          //距离数目
	RADAR_DistNode*  RadDetcDist; //雷达TC距离

	void Init()
	{
		TargetID      = 0;
		fTrgHeight    = 0.;
		DetcDistNum   = 0;
		RadDetcDist   = nullptr;
	}

	void Release()
	{
		SW_Delete(RadDetcDist);
	}

	/*重载构造函数*/
	_ModelBus_DectDistRlt()
	{
		Init();
	}

	/*重载析构函数*/
	~_ModelBus_DectDistRlt()
	{
		Release();
	}

	/*重载拷贝构造函数*/
	_ModelBus_DectDistRlt(const _ModelBus_DectDistRlt &jam)
	{
		RadDetcDist = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_DectDistRlt& operator=(const _ModelBus_DectDistRlt& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		TargetID        = theStruct.TargetID;
		fTrgHeight      = theStruct.fTrgHeight;
		DetcDistNum     = theStruct.DetcDistNum;

		//SW_Delete(RadDetcDist);
		SW_Malloc_Struct(RADAR_DistNode,theStruct.RadDetcDist,RadDetcDist,theStruct.DetcDistNum,DetcDistNum);	

		return *this;
	}
}DectDistRlt;

//雷达TC距离结论报，静态计算
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aRADAR_DIST
{
	char*	sRID;			      //身份字符串
	int		RadarID;		      //雷达ID   
	DectDistRlt DetectDistRlt;    //TC距离

	void Init()
	{
		sRID          = nullptr;
		RadarID       = 0;
		DetectDistRlt.Init();
	}

	void Release()
	{
		SW_Free_Char(sRID);
	}

	/*重载构造函数*/
	_ModelBus_aRADAR_DIST()
	{
		Init();
	}

	/*重载析构函数*/
	~_ModelBus_aRADAR_DIST()
	{
		Release();
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRADAR_DIST(const _ModelBus_aRADAR_DIST &jam)
	{
		sRID  = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aRADAR_DIST& operator=(const _ModelBus_aRADAR_DIST& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		RadarID         = theStruct.RadarID;
		DetectDistRlt   = theStruct.DetectDistRlt;
		return *this;
	}
}aRADAR_DIST;

//雷达TC距离，推演
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRADAR_DIST
{
	char*	sRID;			      //身份字符串
	int		RadarID;		      //雷达ID
	float   fTime;                //时间 单位：秒
	DectDistRlt DectDist;         //TC距离

	/*重载构造函数*/
	_ModelBus_sRADAR_DIST()
	{
		sRID          = nullptr;
		RadarID       = 0;
		fTime         = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_DIST()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_DIST(const _ModelBus_sRADAR_DIST &jam)
	{
		sRID          = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRADAR_DIST& operator=(const _ModelBus_sRADAR_DIST& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		RadarID         = theStruct.RadarID;
		fTime           = theStruct.fTime;

		return *this;
	}
}sRADAR_DIST;

//P显数据点
typedef struct _ModelBus_sPZone
{
	float fAzi;	//方位角，单位：度
	float fDis;	//斜距，单位：m
	float fIntensity; //强度

	/*重载构造函数*/
	_ModelBus_sPZone()
	{
		fAzi       = 0.;
		fDis       = 0.;
		fIntensity = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sPZone()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sPZone(const _ModelBus_sPZone &pzone)
	{
		*this = pzone;
	}

	/*重载=*/
	_ModelBus_sPZone& operator=(const _ModelBus_sPZone& theStruct)
	{
		fAzi       = theStruct.fAzi;
		fDis       = theStruct.fDis;
		fIntensity = theStruct.fIntensity;

		return *this;
	}
}sPZone;

//雷达P显数据
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRADAR_P_RANGE
{
	char*	sRID;		//身份字符串
	int		RadarID;	//雷达ID  
	float	fTime;		//时间 单位：s
	int		iZoneNum;	//点数量  
	sPZone* ZonePoint;	//包络点

	/*重载构造函数*/
	_ModelBus_sRADAR_P_RANGE()
	{
		sRID          = nullptr;
		RadarID       = 0;
		fTime         = 0.;
		iZoneNum      = 0;
		ZonePoint     = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_P_RANGE()
	{
		SW_Free_Char(sRID);
		SW_Delete(ZonePoint);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_P_RANGE(const _ModelBus_sRADAR_P_RANGE &jam)
	{
		sRID = nullptr;
		ZonePoint = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRADAR_P_RANGE& operator=(const _ModelBus_sRADAR_P_RANGE& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Delete(ZonePoint);
		SW_Malloc_Struct(sPZone,theStruct.ZonePoint,ZonePoint,theStruct.iZoneNum,iZoneNum);

		RadarID         = theStruct.RadarID;
		fTime           = theStruct.fTime;
		iZoneNum        = theStruct.iZoneNum;

		return *this;
	}
}sRADAR_P_RANGE;

//目标可TC范围信息
typedef struct _ModelBus_sRADAR_TARGET_VIEWRANGE 
{
	char*	sRID;			//身份字符串
	int		RadarID;		//雷达ID
	int     TargetID;       //目标ID
	float   fTime;          //时间 单位：秒
	int     iDetectZoneNum; //点数量
	sRectZone* ZonePoint;   //包络点

	/*重载构造函数*/
	_ModelBus_sRADAR_TARGET_VIEWRANGE()
	{
		sRID          = nullptr;
		RadarID		  = 0;
		TargetID      = 0;
		fTime         = 0.;
		iDetectZoneNum= 0;
		ZonePoint     = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_TARGET_VIEWRANGE()
	{
		SW_Free_Char(sRID);
		SW_Delete(ZonePoint);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_TARGET_VIEWRANGE(const _ModelBus_sRADAR_TARGET_VIEWRANGE &jam)
	{
		sRID = nullptr;
		ZonePoint = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRADAR_TARGET_VIEWRANGE& operator=(const _ModelBus_sRADAR_TARGET_VIEWRANGE& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Delete(ZonePoint);
		SW_Malloc_Struct(sRectZone,theStruct.ZonePoint,ZonePoint,theStruct.iDetectZoneNum,iDetectZoneNum);

		RadarID			= theStruct.RadarID;
		TargetID        = theStruct.TargetID;
		fTime           = theStruct.fTime;
		iDetectZoneNum  = theStruct.iDetectZoneNum;

		return *this;
	}

}sRADAR_TARGET_VIEWRANGE;

//未TC平台信息
typedef struct _ModelBus_sRadarNoneDetectPlat 
{
	int PlatID;                //平台ID（不在TC能力范围内的平台）
	float fLon;                //经度
	float fLat;                //纬度
	float fHeight;             //高度
	float fSpeed;              //速度
	float fAbilityDetectDis;   //能力可TC最大距离

	/*重载构造函数*/
	_ModelBus_sRadarNoneDetectPlat()
	{
		PlatID = 0;
		fLon = 0;
		fLat = 0;
		fHeight = 0;
		fSpeed = 0;
		fAbilityDetectDis = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sRadarNoneDetectPlat()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRadarNoneDetectPlat(const _ModelBus_sRadarNoneDetectPlat &plat)
	{
		*this = plat;
	}

	/*重载=*/
	_ModelBus_sRadarNoneDetectPlat& operator=(const _ModelBus_sRadarNoneDetectPlat& theStruct)
	{
		PlatID            = theStruct.PlatID;
		fLon              = theStruct.fLon;
		fLat              = theStruct.fLat;
		fHeight           = theStruct.fHeight;
		fSpeed            = theStruct.fSpeed;
		fAbilityDetectDis = theStruct.fAbilityDetectDis;
		return *this;
	}

}sRadarNoneDetectPlat;

//雷达未TC目标信息
typedef struct _ModelBus_sRADAR_NONEDECTECTPLAT 
{
	char*	sRID;			//身份字符串
	int		RadarID;		//雷达ID
	float   fTime;          //时间 单位：秒
	int     nNonePlatNum;   //未TC平台数
	sRadarNoneDetectPlat* NoneDetectPlat; //未TC平台信息

	/*重载构造函数*/
	_ModelBus_sRADAR_NONEDECTECTPLAT()
	{
		sRID           = nullptr;
		RadarID        = 0;
		fTime          = 0.;
		nNonePlatNum   = 0;
		NoneDetectPlat = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_NONEDECTECTPLAT()
	{
		SW_Free_Char(sRID);
		SW_Delete(NoneDetectPlat);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_NONEDECTECTPLAT(const _ModelBus_sRADAR_NONEDECTECTPLAT &radar)
	{
		sRID = nullptr;
		NoneDetectPlat = nullptr;
		*this = radar;
	}

	/*重载=*/
	_ModelBus_sRADAR_NONEDECTECTPLAT& operator=(const _ModelBus_sRADAR_NONEDECTECTPLAT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Delete(NoneDetectPlat);
		SW_Malloc_Struct(sRadarNoneDetectPlat,theStruct.NoneDetectPlat,NoneDetectPlat,theStruct.nNonePlatNum,nNonePlatNum);

		RadarID        = theStruct.RadarID;
		fTime          = theStruct.fTime;
		nNonePlatNum   = theStruct.nNonePlatNum;

		return *this;
	}

}sRADAR_NONEDECTECTPLAT;

//雷达TC指定目标结论报
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aRADAR_RESULT
{
	char*	sRID;			//身份字符串
	int		RadarID;		//雷达ID   
	int		TargetID;		//目标ID  
	bool	bDetected;		//是否TC到
	float	Prob;			//TC概率0~1
	float	DetectError;	//TC误差，单位：m
	float   DetectRangeMax;	//雷达最大作用距离，不考虑GR，单位：m
	bool    bDecepJammed;   //是否受欺骗GR

	/*重载构造函数*/
	_ModelBus_aRADAR_RESULT()
	{
		sRID          = nullptr;
		RadarID       = 0;
		TargetID      = 0;
		bDetected     = false;
		Prob          = 0;
		DetectError   = 0;
		DetectRangeMax= 0;
		bDecepJammed  = false;
	}

	/*重载析构函数*/
	~_ModelBus_aRADAR_RESULT()
	{
		SW_Free_Char(sRID);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aRADAR_RESULT(const _ModelBus_aRADAR_RESULT &jam)
	{
		sRID = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aRADAR_RESULT& operator=(const _ModelBus_aRADAR_RESULT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		RadarID         = theStruct.RadarID;
		TargetID        = theStruct.TargetID;
		bDetected       = theStruct.bDetected;
		Prob            = theStruct.Prob;
		DetectError     = theStruct.DetectError;
		DetectRangeMax  = theStruct.DetectRangeMax;
		bDecepJammed    = theStruct.bDecepJammed;

		return *this;
	}
}aRADAR_RESULT;

struct SingleDectRlt
{
	int		TargetID;		//目标ID  
	bool	bDetected;		//是否TC到
	float	Prob;			//TC概率0~1
	float	DetectError;	//TC误差，单位：m
	float   DetectRangeMax;	//雷达最大作用距离，不考虑GR，单位：m
	bool    bDecepJammed;   //是否受欺骗GR

	SingleDectRlt()
	{
		//memset(this,0x00,sizeof(SingleDectRlt));
		TargetID = 0;		
		bDetected = false;		
		Prob = 0;			
		DetectError = 0;	
		DetectRangeMax = 0;	
		bDecepJammed = false;   
	}
};

//雷达TC指定目标结论报
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aRADAR_RESULTEX
{
	char*	sRID;			//身份字符串
	int		RadarID;		//雷达ID 
	int     nRltNum;        //TC结果数目
	SingleDectRlt* MultiDectRlt;//TC结果
	
	/*重载构造函数*/
	_ModelBus_aRADAR_RESULTEX()
	{
		sRID          = nullptr;
		RadarID       = 0;
		nRltNum       = 0;
		MultiDectRlt  = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aRADAR_RESULTEX()
	{
		SW_Free_Char(sRID);
		SW_Delete(MultiDectRlt);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRADAR_RESULTEX(const _ModelBus_aRADAR_RESULTEX &jam)
	{
		sRID = nullptr;
		MultiDectRlt = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aRADAR_RESULTEX& operator=(const _ModelBus_aRADAR_RESULTEX& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);

		RadarID         = theStruct.RadarID;
		nRltNum         = theStruct.nRltNum;
		SW_Malloc_Struct(SingleDectRlt,theStruct.MultiDectRlt,MultiDectRlt,theStruct.nRltNum,nRltNum);

		return *this;
	}
}aRADAR_RESULTEX;

//ZC/GR设备对雷达的ZC性能误差
typedef struct _ModelBus_sReconPerfo
{
	int			ReconID;						//ZC/GR设备ID
	int			TargetID;						//目标ID

	bool		bDOA;							//是否具备测向能力
	float		DOAError;						//侧向精度，单位：度，ZC到有效

	bool		bDTOA;
	float       DTOAError;						//时差精度us

	bool		bDFOA;
	float       DFOAError;						//频差精度Hz

	
	/*重载构造函数*/
	_ModelBus_sReconPerfo()
	{
		ReconID		= 0;					
		TargetID	= 0;						

		bDOA		= false;						
		DOAError	= -1;						

		bDTOA		= false;
		DTOAError	= -1;						

		bDFOA		= false;
		DFOAError	= -1;	
		
	}

}sReconPerfo;


//ZC/GR设备对雷达的定位结果,zoubz20200408
typedef struct _ModelBus_sReconLocateResult
{
	int			ReconID;						//ZC/GR设备ID
	int			TargetID;						//目标ID
	int			ESMType;						//类型,1-交叉定位，2-时差定位，3-交叉+时差定位
	bool		bLocateSucceed;					//定位成功标志

	float		fRealTargetLon;					//真实位置X，单位：度
	float		fRealTargetLat;					//当次定位，单位：度
	float		fRealTargetHeight;				//当次定位，单位：m

	float		fTargetLon;						//当次定位假想X，单位：度
	float		fTargetLat;						//当次定位，单位：度
	float		fTargetHeight;					//当次定位，单位：m

	bool		bEEPValid;						//定位误差椭圆是否有效
	//float		XLon;							//定位性能误差椭圆中心X经度，单位：度
	//float		YLat;							//定位性能误差椭圆中心Y纬度，单位：度
	float		X;								//定位性能误差椭圆中心X，单位：km
	float		Y;								//定位性能误差椭圆中心Y，单位：km
	float       A;									//定位性能误差椭圆X轴，单位：km
	float       B;									//定位性能误差椭圆Y轴，单位：km
	float       theta;								//定位性能误差椭圆长轴相对X角度，0-180单位：度

	float		Prob;						//概率
	float       CEP;                        //CEP0.5,km

	/*重载构造函数*/
	_ModelBus_sReconLocateResult()
	{
		ReconID=0;			
		TargetID=0;			
		ESMType=0;			
		bLocateSucceed=false;			

		fRealTargetLon=0;		
		fRealTargetLat=0;		
		fRealTargetHeight=0;	

		fTargetLon=0;			
		fTargetLat=0;			
		fTargetHeight=0;		

		bEEPValid=false;
		X=-1;
		Y=-1;
		A=-1;					
		B=-1;					
		theta=-1;				

		Prob=-1;				
		CEP=-1;
	}

}sReconLocateResult;


//ZC/GR设备对雷达的ZC结果,zoubz20150318
typedef struct _ModelBus_sReconResult
{
	int			ReconID;						//ZC/GR设备ID
	int			TargetID;						//目标ID   
	int			ESMType;						//类型，RWR/ESM/HGESM，或者是接收机类型
	bool		bReconed;						//是否ZC到

	bool		bIsInFrequenceRange;			//是否满足频段要求
	bool		bIsInAzVision;					//是否满足方位视场
	bool		bIsInELVision;					//是否满足俯仰视场，bUseOTH为false时有效
	bool		bIsInLOS;						//是否满足视距视场，bUseOTH为false时有效
	bool		bIsTerrainVisible;				//是否满足地形通视
	bool		bIsInSensity;					//是否满足灵敏度要求
	bool		bIsSignalRecognise;				//信号能否识别

	float		AZ;								//目标方位，单位：度 
	float		EL;								//目标俯仰，单位：度
	float		DIS;							//目标距离，单位：Km
	float		ReconMaxRange;					//对目标最大ZC距离，单位：Km

	float		DOAError;						//侧向误差，单位：度，ZC到有效
	float		LocationError;					//定位误差，单位：Km，有定位功能且ZC到有效
	float		CaptureProb;					//截获概率，范围：0~1，本截获概率仅指方位搜索时对脉冲雷达信号的截获概率

	float       fVisDist;                       //视距，km
	bool        bUseOTH;                        //是否是超视距计算
	float       fDectProb;                      //检测概率，bUseOTH为true时有效
	float       fOTHDistMin;                    //超视距近界，km，bUseOTH为true时有效
	
	int         equipTotalNum;					//从站时为1，只报自己的ZC结果参数
	sReconPerfo *pEquipPerfo;					//第一个参数为本站的

	bool		bLocate;						//是否具备定位能力
	sReconLocateResult LocateResult;			//chenzh  

	/*重载构造函数*/
	_ModelBus_sReconResult()
	{
		TargetID       = 0;
		ReconID      = 0;
		ESMType	 = -1;
		bReconed     = false;

		bIsInFrequenceRange = false;
		bIsInAzVision = false;
		bIsInELVision = false;
		bIsInSensity = false;
		bIsInLOS = false;
		bIsTerrainVisible = false;
		bIsSignalRecognise = false;

		AZ = 0;
		EL = 0;
		DIS = 0;
		ReconMaxRange = 0;
		DOAError = 0;
		LocationError = 0;
		CaptureProb	=	0;
		equipTotalNum	= 0;
		pEquipPerfo = nullptr;
		bLocate		= false;
		fVisDist  = 0.f;
		bUseOTH   = false;
		fDectProb = 0.9;
		fOTHDistMin = 0.f;
	}

	/*重载析构函数*/
	~_ModelBus_sReconResult()
	{
		SW_Delete(pEquipPerfo);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sReconResult(const _ModelBus_sReconResult &jam)
	{
		pEquipPerfo = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sReconResult& operator=(const _ModelBus_sReconResult& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		TargetID        = theStruct.TargetID;
		ReconID         = theStruct.ReconID;
		ESMType		    = theStruct.ESMType;
		bReconed        = theStruct.bReconed;

		bIsInFrequenceRange = theStruct.bIsInFrequenceRange;
		bIsInAzVision = theStruct.bIsInAzVision;
		bIsInELVision = theStruct.bIsInELVision;
		bIsInSensity = theStruct.bIsInSensity;
		bIsInLOS = theStruct.bIsInLOS;
		bIsTerrainVisible = theStruct.bIsTerrainVisible;
		bIsSignalRecognise = theStruct.bIsSignalRecognise;

		AZ = theStruct.AZ;
		EL = theStruct.EL;
		DIS = theStruct.DIS;
		ReconMaxRange = theStruct.ReconMaxRange;
		DOAError = theStruct.DOAError;
		LocationError = theStruct.LocationError;
		CaptureProb = theStruct.CaptureProb;

		bUseOTH       = theStruct.bUseOTH;
		fDectProb     = theStruct.fDectProb;
		fVisDist      = theStruct.fVisDist;
		fOTHDistMin   = theStruct.fOTHDistMin;

		equipTotalNum	= theStruct.equipTotalNum;
		bLocate		= theStruct.bLocate;
		LocateResult	= theStruct.LocateResult;

		SW_Malloc_Struct(sReconPerfo,theStruct.pEquipPerfo,pEquipPerfo,theStruct.equipTotalNum,equipTotalNum);
		return *this;
	}
}sReconResult;

// GR计算结果
typedef struct _ModelBus_RJamCalcResult
{
	int			TargetID;
	bool		bCanJam;					//是否能够GR

	// 侦查结果
	//sReconResult ReconResult;

	// GR能力结果
	bool        bCanRecon;                  //能否ZC到
	bool		bIsInJamRFRange;			//是否满足频段要求
	bool		bIsInJamAzVision;			//是否满足方位视场
	bool		bIsInJamELVision;			//是否满足俯仰视场
	bool		bIsInJamRange;				//是否在GR距离内
	bool		bIsInJamMaxNum;				//是否在多目标GR能力内

	// GR距离能力
	float		JamMaxRange;				//对目标最大GR距离，单位：Km，满足频段要求有效
	float		JamMinRange;				//对目标最小GR距离，单位：Km

	// GR区域能力
	int			nPowerRangeNum;					//GR能力区域个数
	sJAM_POWERPOINT* PowerRange;			//GR能力区域

	// GR参数
	DKDMS::Enum_RJamType	RJamType;				//GR类型
	float		ERP;						//等效辐射功率，单位：W
	float		RF;							//GR中心频率，单位：MHz
	float		RJamBandWidth;				//GR信号带宽，单位：KHz
	int			FalseTrgNum;					//假目标个数

	//GR波束
	sJAM_POINT JamPointVar;	//GR波束范围

	/*重载构造函数*/
	_ModelBus_RJamCalcResult()
	{
		TargetID     = 0;
		bCanJam      = false;
		bCanRecon        = false;
		bIsInJamRFRange  = false;
		bIsInJamAzVision = false;
		bIsInJamELVision = false;
		bIsInJamRange    = false;
		bIsInJamMaxNum   = false;
		JamMaxRange      = 0;
		JamMinRange      = 0;
		nPowerRangeNum   = 0;
		PowerRange       = nullptr;
		RJamType         = DKDMS::Enum_RJamType_1;
		ERP              = 0;
		RF	             = 0;
		RJamBandWidth    = 0;
		FalseTrgNum      = 0;
	}

	/*重载析构函数*/
	~_ModelBus_RJamCalcResult()
	{
		SW_Delete(PowerRange);
	}

	/*重载拷贝构造函数*/
	_ModelBus_RJamCalcResult(const _ModelBus_RJamCalcResult &jam)
	{
        PowerRange       = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_RJamCalcResult& operator=(const _ModelBus_RJamCalcResult& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		TargetID     = theStruct.TargetID;
		bCanJam      = theStruct.bCanJam;
		bCanRecon        = theStruct.bCanRecon;
		bIsInJamRFRange  = theStruct.bIsInJamRFRange;
		bIsInJamAzVision = theStruct.bIsInJamAzVision;
		bIsInJamELVision = theStruct.bIsInJamELVision;
		bIsInJamRange    = theStruct.bIsInJamRange;
		bIsInJamMaxNum   = theStruct.bIsInJamMaxNum;
		JamMaxRange      = theStruct.JamMaxRange;
		JamMinRange      = theStruct.JamMinRange;
		nPowerRangeNum   = theStruct.nPowerRangeNum;
		//ReconResult      = theStruct.ReconResult;
		RJamType         = theStruct.RJamType;
		ERP              = theStruct.ERP;
		RF	             = theStruct.RF;
		RJamBandWidth    = theStruct.RJamBandWidth;
		FalseTrgNum      = theStruct.FalseTrgNum;
		JamPointVar      = theStruct.JamPointVar;
		//SW_Delete(PowerRange);
		SW_Malloc_Struct(sJAM_POWERPOINT,theStruct.PowerRange,PowerRange,theStruct.nPowerRangeNum,nPowerRangeNum);

		return *this;
	}
}RJamCalcResult;

//GR结论
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aJAM_RESULT
{
	char*	sRID;						//身份字符串
	int		ID;							//GR装备ID；
	float	LON;						//GR装备经度，单位：度
	float	LAT;						//GR装备纬度，单位：度
	float	Height;						//GR装备高度，单位：米（m）

	int		nResultNum;					//GR结论个数
	RJamCalcResult *pJamResult;			//GR结论数据

	/*重载构造函数*/
	_ModelBus_aJAM_RESULT()
	{
		sRID          = nullptr;	
		ID       = 0;
		LON      = 0;	
		LAT      = 0;
		Height   = 0;
		nResultNum = 0;
		pJamResult = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aJAM_RESULT()
	{
		SW_Free_Char(sRID);
		SW_Delete(pJamResult);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aJAM_RESULT(const _ModelBus_aJAM_RESULT &jam)
	{
		sRID = nullptr;
		pJamResult = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aJAM_RESULT& operator=(const _ModelBus_aJAM_RESULT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID         = theStruct.ID;
		LON        = theStruct.LON;
		LAT        = theStruct.LAT;
		Height     = theStruct.Height;

		nResultNum = theStruct.nResultNum;
		//SW_Delete(pJamResult);
		SW_Malloc_Struct(RJamCalcResult,theStruct.pJamResult,pJamResult,theStruct.nResultNum,nResultNum);

		return *this;
	}

}aJAM_RESULT;

//ZC/GR设备对雷达的ZC结果,zoubz20150318
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aRECON_RESULT
{
	char*	sRID;								//身份字符串
	int		ReconID;						//ZC/GR设备ID

	int		nResultNum;					//ZC结论个数
	sReconResult *pReconResult;	//ZC结论数据

	/*重载构造函数*/
	_ModelBus_aRECON_RESULT()
	{
		sRID          = nullptr;	
		ReconID       = 0;
		nResultNum      = 0;	
		pReconResult = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aRECON_RESULT()
	{
		SW_Free_Char(sRID);
		SW_Delete(pReconResult);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRECON_RESULT(const _ModelBus_aRECON_RESULT &jam)
	{
		sRID = nullptr;
		pReconResult = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aRECON_RESULT& operator=(const _ModelBus_aRECON_RESULT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReconID         = theStruct.ReconID;

		nResultNum         = theStruct.nResultNum;
		//SW_Delete(pReconResult);
		SW_Malloc_Struct(sReconResult,theStruct.pReconResult,pReconResult,theStruct.nResultNum,nResultNum);

		return *this;
	}
}aRECON_RESULT;

//地面目标输入
typedef struct _ModelBus_sTARGET_Set_PARA
{
	char*	sRID;			//身份字符串
	int		ID;				//实体ID
	DKDMS::Enum_GroundTgtType	GroundTgtType;	//固定目标类型
	DKDMS::Enum_ATT			ATT;			//敌我属性
	DKDMS::Enum_GroundTargetPlatType	GroundTargetPlatType;	//地面目标平台类型
	float	LON;			//经度，单位：度
	float	LAT;			//纬度，单位：度
	float	Height;			//高度，单位：米（m）
	char*	EquipmentName;	//设备名称
	int		PlatID;			//搭载平台ID 
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_WorkState	WorkState;			//工作状态
	float	TargetRadius;				//目标半径，单位：米（m）

	/*重载构造函数*/
	_ModelBus_sTARGET_Set_PARA()
	{
		sRID          = nullptr;
		ID            = 0;
		GroundTgtType = DKDMS::Enum_GroundTgtType_1;
		ATT           = DKDMS::Enum_ATT_1;
		GroundTargetPlatType       = DKDMS::Enum_GroundTargetPlatType_0;
		LON           = 0.;
		LAT           = 0.;
		Height        = 0.;
		EquipmentName = nullptr;
		PlatID        = 0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		WorkState     = DKDMS::Enum_WorkState_0;
		TargetRadius       = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sTARGET_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sTARGET_Set_PARA(const _ModelBus_sTARGET_Set_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sTARGET_Set_PARA& operator=(const _ModelBus_sTARGET_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID            = theStruct.ID;
		GroundTgtType = theStruct.GroundTgtType;
		ATT           = theStruct.ATT;
		GroundTargetPlatType       = theStruct.GroundTargetPlatType;
		LON           = theStruct.LON;
		LAT           = theStruct.LAT;
		Height        = theStruct.Height;

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		PlatID        = theStruct.PlatID;
		SurvivalState = theStruct.SurvivalState;
		WorkState     = theStruct.WorkState;
		TargetRadius  = theStruct.TargetRadius;
		return *this;
	}

}sTARGET_Set_PARA;

//地面目标输出
typedef struct _ModelBus_sTARGET_Get_PARA
{
	char*	sRID;		//身份字符串
	int		ID;			//实体ID  
	float	SimuTime;	//仿真时间
	int		OwnerID;	//隶属关系 
	DKDMS::Enum_GroundTgtType	GroundTgtType;	//固定目标类型
	DKDMS::Enum_ATT		ATT;	//敌我属性
	DKDMS::Enum_GroundTargetPlatType	GroundTargetPlatType;	//地面目标平台类型
	char*	EquipmentType;	//设备类型
	float	LON;		//经度，单位：度
	float	LAT;		//纬度，单位：度
	float	Height;		//高度，单位：米（m）
	char*	EquipmentName;	//设备名称
	int		PlatID;		//搭载平台ID  
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_WorkState	WorkState;	//工作状态
	float	TargetRadius;		//目标半径，单位：米（m）
	float	RCS[3];				//雷达回波面积，单位：平方米（m^2）

	/*重载构造函数*/
	_ModelBus_sTARGET_Get_PARA()
	{
		sRID          = nullptr;
		ID            = 0;
		SimuTime      = 0;
		OwnerID       = 0;
		GroundTgtType = DKDMS::Enum_GroundTgtType_1;
		ATT           = DKDMS::Enum_ATT_1;
		GroundTargetPlatType           = DKDMS::Enum_GroundTargetPlatType_0;
		EquipmentType = nullptr;
		LON           = 0.;
		LAT           = 0.;
		Height        = 0.;
		EquipmentName = nullptr;
		PlatID        = 0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		WorkState     = DKDMS::Enum_WorkState_0;
		TargetRadius  = 0;
		for (int i=0;i<3;i++)
		{
			RCS[i] = 0;
		}
	}

	/*重载析构函数*/
	~_ModelBus_sTARGET_Get_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sTARGET_Get_PARA(const _ModelBus_sTARGET_Get_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sTARGET_Get_PARA& operator=(const _ModelBus_sTARGET_Get_PARA& theStruct)
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

		ID            = theStruct.ID;
		SimuTime      = theStruct.SimuTime;
		OwnerID       = theStruct.OwnerID;
		GroundTgtType = theStruct.GroundTgtType;
		ATT           = theStruct.ATT;
		GroundTargetPlatType           = theStruct.GroundTargetPlatType;
		LON           = theStruct.LON;
		LAT           = theStruct.LAT;
		Height        = theStruct.Height;
		PlatID        = theStruct.PlatID;
		SurvivalState = theStruct.SurvivalState;
		WorkState     = theStruct.WorkState;
		TargetRadius     = theStruct.TargetRadius;
		for (int i=0;i<3;i++)
		{
			RCS[i] = theStruct.RCS[i];
		}

		return *this;
	}
}sTARGET_Get_PARA;

//! 控守范围
typedef struct _ModelBus_sCoverRange
{
	// 地面装备有效，0-360
	float	    fStartAZ;       //! @Properties(description=控守水平起始方向, unit=度)
	// 0-360
	float       fEndAZ;			//! @Properties(description=控守水平终止方向, unit=度)
	// -90~90
	float       fStartEL;		//! @Properties(description=控守垂直起始方向, unit=度)
	// -90~90
	float       fEndEL;			//! @Properties(description=控守垂直终止方向, unit=度)
}sHideCoverRange;

//! @Properties(description=雷达ZC装备, appType=init, id=6)
typedef struct _ModelBus_sRECON_Set_PARA
{
	char*		sRID;			//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int			ReconID;		//! @Properties(description=装备id, alias=modelId, display=readonly)
	int			PlatID;			//! @Properties(description=平台id, alias=platformId, display=readonly)
	char*		EquipmentName;	//! @Properties(description=装备名称, alias=equipName)
	DKDMS::Enum_ATT	ATT;			//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作属性, defaultValue=1)
	float		fLon;			//! @Properties(description=经度, alias=lon, unit=度)
	float		fLat;			//! @Properties(description=纬度, alias=lat, unit=度)
	float		fHeight;		//! @Properties(description=高度, alias=hei, unit=米)
	// 地面装备有效
	float	    fStartAZ;       //! @Properties(description=控守起始方位, unit=度)
	// 地面装备有效
	float       fEndAZ;			//! @Properties(description=控守终止方位, unit=度)
	// 目前仅对302有效
	int			SlaveNum;		//! @Properties(description=副站个数, display=readonly)
	sPON_AREA*	PonAreaData;	//! 副站列表
	
	int			nJamCount;		//! @Properties(description=下属GR机/ZC站个数, display=readonly)
	int*		pJamID;			//! 下属GR机/ZC站ID列表
	int			iKeyPtNum;		//! @Properties(description=关键点个数, display=readonly)
	sKeyPoint	*pKeyPt;		//! 关键点列表

	float		fOperatorAbility;//! @Properties(description=操作员水平0~1, defaultValue=1)
	float		fEnviorAdaptability;//! @Properties(description=环境适应性, defaultValue=1)

	int			nHideRangeNum; //! @Properties(description=遮蔽角个数, display=readonly)
	sHideCoverRange* pHideRangeData;//! 遮蔽角列表

	/*重载构造函数*/
	_ModelBus_sRECON_Set_PARA()
	{
		sRID          = nullptr;
		ReconID       = 0;
		PlatID        = 0;
		EquipmentName = nullptr;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		SlaveNum      = 0;
		PonAreaData   = nullptr;
		nJamCount=0;
		pJamID= nullptr;
		fStartAZ = 0.;
		fEndAZ = 360.;
		iKeyPtNum	  = 0;
		pKeyPt		  = nullptr;
		fOperatorAbility = 1;
		fEnviorAdaptability = 1;
		nHideRangeNum = 0;
		pHideRangeData = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sRECON_Set_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Delete(PonAreaData);

		SW_Delete(pJamID);

		SW_Delete(pKeyPt);

		SW_Delete(pHideRangeData);

	}

	/*重载拷贝构造函数*/
	_ModelBus_sRECON_Set_PARA(const _ModelBus_sRECON_Set_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		PonAreaData = nullptr;
		pJamID=nullptr;
		pKeyPt	= nullptr;
		pHideRangeData	= nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRECON_Set_PARA& operator=(const _ModelBus_sRECON_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		ReconID       = theStruct.ReconID;
		PlatID        = theStruct.PlatID;
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		SlaveNum      = theStruct.SlaveNum;
		fStartAZ      = theStruct.fStartAZ;
		fEndAZ        = theStruct.fEndAZ;

		fOperatorAbility = theStruct.fOperatorAbility;
		fEnviorAdaptability = theStruct.fEnviorAdaptability;

		//SW_Delete(PonAreaData);
		SW_Malloc_Struct(sPON_AREA,theStruct.PonAreaData,PonAreaData,theStruct.SlaveNum,SlaveNum);

		nJamCount      = theStruct.nJamCount;

		//SW_Delete(pJamID);
		SW_Malloc_Int(theStruct.pJamID,pJamID,theStruct.nJamCount,nJamCount);

		iKeyPtNum=theStruct.iKeyPtNum;
		//SW_Delete(pKeyPt);
		SW_Malloc_Struct(sKeyPoint,theStruct.pKeyPt,pKeyPt,theStruct.iKeyPtNum,iKeyPtNum);

		nHideRangeNum=theStruct.nHideRangeNum;
		SW_Malloc_Struct(sHideCoverRange,theStruct.pHideRangeData,pHideRangeData,theStruct.nHideRangeNum,nHideRangeNum);
		 
		return *this;
	}
}sRECON_Set_PARA;

//雷达对抗ZC状态报
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRECON_Get_PARA
{
	char*		sRID;			//身份字符串
	int			ReconID;		//实体ID 
	DKDMS::Enum_ATT	ATT;			//敌我属性
	float		EndAZ;			//终止方位，单位：度
	float		EndRF;			//终止频率，单位：MHz
	char*		EquipmentName;	//设备名称
	char*		EquipmentType;	//设备型号
	float		fHeight;		//高度，单位：米（m）
	float		fLon;			//纬度，单位：度
	float		fLat;			//经度，单位：度
	int			PlatID;			//搭载平台ID
	float		fRecDis;		//ZC距离，单位：千米（Km）
	float		fTime;			//仿真时间，单位：秒（s）
	float		StartAZ;		//起始方位，单位：度
	float		StartRF;		//起始频率，单位：MHz
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_WorkState		WorkState;		//工作状态
	DKDMS::Enum_EquipUseType EquipUseType; // 装备作战用途


	/*重载构造函数*/
	_ModelBus_sRECON_Get_PARA()
	{
		sRID          = "null";
		ReconID       = 0;
		ATT           = DKDMS::Enum_ATT_1;
		EndAZ         = 0;
		EndRF         = 0;
		EquipmentName = "null";
		EquipmentType = "null";
		fHeight       = 0.;
		fLon          = 0.;
		fLat          = 0.;
		PlatID        = 0;
		fRecDis       = 0;
		fTime         = 0.;
		StartAZ       = 0;
		StartRF       = 0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		WorkState     = DKDMS::Enum_WorkState_0;
		EquipUseType = DKDMS::Enum_EquipUseType_0;
	}

	/*重载析构函数*/
	~_ModelBus_sRECON_Get_PARA()
	{
		/*SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);*/
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRECON_Get_PARA(const _ModelBus_sRECON_Get_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRECON_Get_PARA& operator=(const _ModelBus_sRECON_Get_PARA& theStruct)
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

		ReconID       = theStruct.ReconID;
		ATT           = theStruct.ATT;
		EndAZ         = theStruct.EndAZ;
		EndRF         = theStruct.EndRF;
		fHeight       = theStruct.fHeight;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		PlatID        = theStruct.PlatID;
		fRecDis       = theStruct.fRecDis;
		fTime         = theStruct.fTime;
		StartAZ       = theStruct.StartAZ;
		StartRF       = theStruct.StartRF;
		SurvivalState = theStruct.SurvivalState;
		WorkState     = theStruct.WorkState;
		EquipUseType = theStruct.EquipUseType;
		return *this;
	}
}sRECON_Get_PARA;

//TC定位区域信息
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRECON_AREA
{
	char*		sRID;			//身份字符串
	int			ReconID;		//实体ID  
	float		fTime;			//仿真时间	
	DKDMS::Enum_RegionSort	RegionSort;	//ZC区域类型
	float		fHeight;		//高度，单位：米（m）
	DKDMS::Enum_RegionType	RegionType;	//区域几何类型
	int			PtNum;			//区域点数 
	sPON_AGG*	PonAggData;		//区域

	int		TargetID;
	float	fCenterLon;			//经度，单位：度（o）
	float	fCenterLat;			//纬度，单位：度（o）
	float	fCenterHeight;		//高度，单位：米（m）
	int     nRangeNum;			//ZC/GR能力区域个数
	sRECON_POWERPOINT* PowerRange;  //ZC/GR能力区域

	/*重载构造函数*/
	_ModelBus_sRECON_AREA()
	{
		sRID          = "null";
		ReconID       = 0;
		fTime         = 0.;
		RegionSort    = DKDMS::Enum_RegionSort_1;
		fHeight       = 0.;
		RegionType    = DKDMS::Enum_RegionType_0;
		PtNum         = 0;
		PonAggData    = nullptr;

		TargetID	  = 0;
		fCenterLon    = 0.;
		fCenterLat    = 0.;
		fCenterHeight = 0.;
		nRangeNum     = 0;
		PowerRange    = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sRECON_AREA()
	{
		SW_Free_Char(sRID);
		SW_Delete(PonAggData);
		SW_Delete(PowerRange);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRECON_AREA(const _ModelBus_sRECON_AREA &jam)
	{
		sRID = nullptr;
		PonAggData = nullptr;
		PowerRange    = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRECON_AREA& operator=(const _ModelBus_sRECON_AREA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReconID       = theStruct.ReconID;
		fTime         = theStruct.fTime;
		RegionSort    = theStruct.RegionSort;
		fHeight       = theStruct.fHeight;
		RegionType    = theStruct.RegionType;
		PtNum         = theStruct.PtNum;

		//SW_Delete(PonAggData);
		SW_Malloc_Struct(sPON_AGG,theStruct.PonAggData,PonAggData,theStruct.PtNum,PtNum);

		TargetID	  = theStruct.TargetID;
		fCenterLon    = theStruct.fCenterLon;
		fCenterLat    = theStruct.fCenterLat;
		fCenterHeight = theStruct.fCenterHeight;
		nRangeNum    = theStruct.nRangeNum;

		//SW_Delete(PowerRange);
		SW_Malloc_Struct(sRECON_POWERPOINT,theStruct.PowerRange,PowerRange,theStruct.nRangeNum,nRangeNum);

		return *this;
	}
}sRECON_AREA;
typedef sRECON_AREA sRECON_POWER_AREA;

//无人机航迹点信息
typedef struct _ModelBus_sTRACK_POINT
{
	DKDMS::Enum_FlyPosType	FlyPosType;	//航路点类型 0-出航 1-巡航 2-返航
	float PlatformSpeed;		//平台航速
	float LON;					//平台经度，单位：度
	float LAT;					//平台纬度，单位：度
	float Height;				//平台高度，单位：米（m）
	float ReachTime;			//到达时间，单位：秒（s）
	float Psia;					//航向角，单位：度，0~360
	float Slope;				//坡度，单位：度，-90~90
	DKDMS::Enum_TaskType	PointTaskType;	//航迹点任务类型
	float DamageProbability;	//毁伤概率0~1

	/*重载构造函数*/
	_ModelBus_sTRACK_POINT()
	{
		FlyPosType          = DKDMS::Enum_Out;
		PlatformSpeed       = 0;
		LON                 = 0;
		LAT                 = 0;
		Height              = 0;
		ReachTime           = 0;
		Psia                = 0;
		Slope               = 0;
		PointTaskType       = DKDMS::Enum_TaskType_0;
		DamageProbability   = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sTRACK_POINT()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sTRACK_POINT(const _ModelBus_sTRACK_POINT &jam)
	{
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sTRACK_POINT& operator=(const _ModelBus_sTRACK_POINT& theStruct)
	{
		FlyPosType          = theStruct.FlyPosType;
		PlatformSpeed       = theStruct.PlatformSpeed;
		LON                 = theStruct.LON;
		LAT                 = theStruct.LAT;
		Height              = theStruct.Height;
		ReachTime           = theStruct.ReachTime;
		Psia                = theStruct.Psia;
		Slope               = theStruct.Slope;
		PointTaskType       = theStruct.PointTaskType;
		DamageProbability   = theStruct.DamageProbability;

		return *this;
	}
}sTRACK_POINT;

//无人机输入参数
typedef struct _ModelBus_sUAV_Set_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID 
	int			PlatID;			//搭载平台ID 
	DKDMS::Enum_ATT	ATT;			//敌我属性
	char*		EquipmentName;	//设备名称
	float       fStartTime;		//仿真开始时间
	float		LON;			//经度，单位：度
	float		LAT;			//纬度，单位：度
	float		Height;			//高度，单位：米（m）
	int			TargetNum;		//目标数 
	int*		TargetID;		//目标ID
	int			PosNum;			//航迹点数
	sTRACK_POINT* CombatTracklist;	//航迹点

	/*重载构造函数*/
	_ModelBus_sUAV_Set_PARA()
	{
		sRID          = nullptr;
		ID            = 0;
		PlatID        = 0;
		ATT           = DKDMS::Enum_ATT_1;
		EquipmentName = nullptr;
		LON           = 0.;
		LAT           = 0.;
		Height        = 0.;
		TargetNum     = 0;
		TargetID      = nullptr;
		PosNum        = 0;
		CombatTracklist = nullptr;
		fStartTime     = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sUAV_Set_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Delete(TargetID);

		SW_Delete(CombatTracklist);

	}

	/*重载拷贝构造函数*/
	_ModelBus_sUAV_Set_PARA(const _ModelBus_sUAV_Set_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		TargetID = nullptr;
		CombatTracklist = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sUAV_Set_PARA& operator=(const _ModelBus_sUAV_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID            = theStruct.ID;
		PlatID        = theStruct.PlatID;
		ATT           = theStruct.ATT;

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		LON           = theStruct.LON;
		LAT           = theStruct.LAT;
		Height        = theStruct.Height;
		TargetNum     = theStruct.TargetNum;
		fStartTime     = theStruct.fStartTime;

		//SW_Delete(TargetID);
		SW_Malloc_Int(theStruct.TargetID,TargetID,theStruct.TargetNum,TargetNum);

		//SW_Delete(CombatTracklist);
		SW_Malloc_Struct(sTRACK_POINT,theStruct.CombatTracklist,CombatTracklist,theStruct.PosNum,PosNum);

		return *this;
	}  
}sUAV_Set_PARA;

//辅助计算应答报
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aUAVSkyway 
{
	char* sRID;	//身份字符串(用户标识)
	int ID;
	int RadarID;	//
	bool IsCourseOK;    //
	bool IsTimeOK;    //

	/*重载构造函数*/
	_ModelBus_aUAVSkyway()
	{
		sRID = nullptr;
		ID   = 0;
		RadarID = 0;
		IsCourseOK = false;
		IsTimeOK = false;
	}

	/*重载析构函数*/
	~_ModelBus_aUAVSkyway()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aUAVSkyway(const _ModelBus_aUAVSkyway& auavskyway)
	{
		sRID = nullptr;
		ID   = 0;
		RadarID = 0;
		*this = auavskyway;
	}

	/*重载=*/
	_ModelBus_aUAVSkyway& operator=(const _ModelBus_aUAVSkyway& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID = theStruct.ID;
		RadarID = theStruct.RadarID;

		IsCourseOK = theStruct.IsCourseOK;
		IsTimeOK = theStruct.IsTimeOK;

		return *this;
	}

}aUAVSkyway;

//无人机输出参数
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sUAV_Get_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID 
	int			PlatID;			//搭载平台ID  
	float		fTime;			//时间 单位：秒（s）
	char*		EquipmentName;	//设备名称
	char*		EquipmentType;	//设备型号
	float		LON;			//经度，单位：度
	float		LAT;			//纬度，单位：度
	float		Height;			//高度，单位：米（m）
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_WorkState	WorkState;	//工作状态
	DKDMS::Enum_ATT	ATT;			//敌我属性
	float		RCS[3];			//雷达回波面积，单位：平方米（m^2）
	float		Theta;			//俯仰角，单位：度
	float		Psia;			//航向角，单位：度
	float		Phie;			//滚转角，单位：度
	float		Xdote;			//x轴速度分量，单位：米/秒（m/s）
	float		Ydote;			//y轴速度分量，单位：米/秒（m/s）
	float		Zdote;			//z轴速度分量，单位：米/秒（m/s）
	float		flightTime;		//飞行时间,单位：秒（s
	float		Velocity;		//真空速，单位：米/秒（m/s）
	DKDMS::Enum_FlyPosType		FlyPosType;		//航路点类型
	DKDMS::Enum_manoeuverState	manoeuverState;	//作战行动各阶段的状态
	float				DamageDegree;	//毁伤程度
	DKDMS::Enum_AircraftSort	AircraftSort;	//平台类别

	/*重载构造函数*/
	_ModelBus_sUAV_Get_PARA()
	{
		sRID               = nullptr;
		ID                 = 0;
		PlatID             = 0;
		fTime              = 0;
		EquipmentName      = nullptr;
		EquipmentType      = nullptr;
		LON                = 0.;
		LAT                = 0.;
		Height             = 0.;
		WorkState          = DKDMS::Enum_WorkState_0;
		SurvivalState      = DKDMS::Enum_SurvivalState_0;
		ATT                = DKDMS::Enum_ATT_1;

		for (int i=0;i<3;i++)
		{
			RCS[i] = 0;
		}

		Theta              = 0;
		Psia               = 0.;
		Phie               = 0;
		Xdote              = 0.;
		Ydote              = 0;
		Zdote              = 0;
		flightTime         = 0;
		Velocity           = 0;
		FlyPosType         = DKDMS::Enum_Out;
		manoeuverState     = DKDMS::Enum_manoeuverState_0;
		DamageDegree       = 0;
		AircraftSort       = DKDMS::Enum_AircraftSort_0;
	}

	/*重载析构函数*/
	~_ModelBus_sUAV_Get_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sUAV_Get_PARA(const _ModelBus_sUAV_Get_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		EquipmentType = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sUAV_Get_PARA& operator=(const _ModelBus_sUAV_Get_PARA& theStruct)
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

		ID                 = theStruct.ID;
		PlatID             = theStruct.PlatID;
		fTime              = theStruct.fTime;
		LON                = theStruct.LON;
		LAT                = theStruct.LAT;
		Height             = theStruct.Height;
		WorkState          = theStruct.WorkState;
		SurvivalState      = theStruct.SurvivalState;
		ATT                = theStruct.ATT;

		for (int i=0;i<3;i++)
		{
			RCS[i] = theStruct.RCS[i];
		}

		Theta              = theStruct.Theta;
		Psia               = theStruct.Psia;
		Phie               = theStruct.Phie;
		Xdote              = theStruct.Xdote;
		Ydote              = theStruct.Ydote;
		Zdote              = theStruct.Zdote;
		flightTime         = theStruct.flightTime;
		Velocity           = theStruct.Velocity;
		FlyPosType         = theStruct.FlyPosType;
		manoeuverState     = theStruct.manoeuverState;
		DamageDegree       = theStruct.DamageDegree;
		AircraftSort       = theStruct.AircraftSort;

		return *this;
	}
}sUAV_Get_PARA;

//无人机攻击参数交互类
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sUAV_ATTRACK_PARA
{
	char*	sRID;		//身份字符串
	int		TargetID;	//目标ID 
	int		UAVID;		//无人机ID 
	float	fTime;		//时间 单位：秒（s）
	float	KillProb;	//毁伤概率0~1

	/*重载构造函数*/
	_ModelBus_sUAV_ATTRACK_PARA()
	{
		sRID          = nullptr;
		TargetID      = 0;
		UAVID         = 0;
		fTime         = 0.;
		KillProb      = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sUAV_ATTRACK_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sUAV_ATTRACK_PARA(const _ModelBus_sUAV_ATTRACK_PARA &jam)
	{
		sRID = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sUAV_ATTRACK_PARA& operator=(const _ModelBus_sUAV_ATTRACK_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		TargetID         = theStruct.TargetID;
		UAVID            = theStruct.UAVID;
		fTime            = theStruct.fTime;
		KillProb         = theStruct.KillProb;

		return *this;
	}
}sUAV_ATTRACK_PARA;

//反辐射攻击告警交互类
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sUAV_ALAM_PARA
{
	char*	sRID;		//身份字符串
	int		TargetID;	//目标ID  
	int		UAVID;		//无人机ID   
	float	fTime;		//时间 单位：秒（s）
	bool	IsLocked;	//是否锁定目标

	/*重载构造函数*/
	_ModelBus_sUAV_ALAM_PARA()
	{
		sRID          = nullptr;
		TargetID      = 0;
		UAVID         = 0;
		fTime         = 0.;
		IsLocked      = true;
	}

	/*重载析构函数*/
	~_ModelBus_sUAV_ALAM_PARA()
	{
		SW_Free_Char(sRID);

	}

	/*重载拷贝构造函数*/
	_ModelBus_sUAV_ALAM_PARA(const _ModelBus_sUAV_ALAM_PARA &jam)
	{
		sRID = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sUAV_ALAM_PARA& operator=(const _ModelBus_sUAV_ALAM_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		TargetID         = theStruct.TargetID;
		UAVID            = theStruct.UAVID;
		fTime            = theStruct.fTime;
		IsLocked         = theStruct.IsLocked;

		return *this;
	}

}sUAV_ALAM_PARA;

typedef struct _ModelBus_aUAV_Set_Skyway
{
	char* sRID;    //身份字符串
	char*	ID;	//实体ID
	float RadarLON;
	float RadarLAT;
	float RadarHeight;

	/*重载构造函数*/
	_ModelBus_aUAV_Set_Skyway()
	{
		sRID = nullptr;
		ID = nullptr;
		RadarLON = 0.f;
		RadarLAT = 0.f;
		RadarHeight = 0.f;
	}

	/*重载析构函数*/
	~_ModelBus_aUAV_Set_Skyway()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(ID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aUAV_Set_Skyway(const _ModelBus_aUAV_Set_Skyway &skyway)
	{
		sRID = nullptr;
		ID = nullptr;
		*this = skyway;
	}

	/*重载=*/
	_ModelBus_aUAV_Set_Skyway& operator = (const _ModelBus_aUAV_Set_Skyway& theStruct)
	{
	    if( this==&theStruct )
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(ID);
		SW_Malloc_Char(theStruct.ID,ID);

		RadarLON	   = theStruct.RadarLON;
		RadarLAT	   = theStruct.RadarLAT;
		RadarHeight	   = theStruct.RadarHeight;

		return *this;
	}

}aUAV_Set_Skyway;

//雷达GR初始化信息
typedef struct _ModelBus_aJAM_Set_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	DKDMS::Enum_ATT	ATT;			//敌我属性
	char*		EquipmentName;	//设备名称
	float		LON;			//经度，单位：度
	float		LAT;			//纬度，单位：度
	float		Height;			//高度，单位：米（m）
	int		    TargetNum;		//目标数量
	int*		TargetID;		//目标ID
	int		    iCenterPoint;	//中心区域点个数(目前仅对运八干有效) 
	sPON_AREA *	pCenterPoint;	//中心区域点
	DKDMS::Enum_WorkMode	WorkMode;	//作战模式
	int		ESMMode;			//无源ZC模式，0-告警RWR，1-3500:测距测向；其它：ESM，2-HGESM
	                            //对528:1-干涉仪天线ZC；2-GR引导天线ZC
	int		ECMMode;		    //有源GR模式，1-ECM，2-HPESM；
	                            //对GPSGR站：10-车载全向，11-车载定向，12-背负全向，13-背负定向
	                            //对528:1-支援GR；2-自卫GR
								/*对2200:0x0000-全部关辐射          0x1111-全部开辐射           0x0111-S关C开XKu前开XKu后开  0x1011-S开C关XKu前开XKu后开
										0x1101-S开C开XKu前关XKu后开 0x1110-S开C开XKu前开XKu后关 0x0011-S关C关XKu前开XKu后开  0x0101-S关C开XKu前关XKu后开
										0x0110-S关C开XKu前开XKu后关 0x1001-S开C关XKu前关XKu后开 0x1010-S开C关XKu前开XKu后关  0x1100-S开C开XKu前关XKu后关
										0x0001-S关C关XKu前关XKu后开 0x0010-S关C关XKu前开XKu后关 0x0100-S关C开XKu前关XKu后关  0x1000-S开C关XKu前关XKu后关*/
								/*对3000:0x000-全部关辐射         0x111-全部开辐射         0x1-后向关前左关前右开    0x10-后向关前左开前右关
									     0x11-后向关前左开前右开  0x100-后向开前左关前右关  0x101-后向开前左关前右开  0x110-后向开前开关前右*/
	                            /*对3500:0x000-全部关辐射         0x111-全部开辐射         0x1-后向关前左关前右开    0x10-后向关前左开前右关
									     0x11-后向关前左开前右开  0x100-后向开前左关前右关  0x101-后向开前左关前右开  0x110-后向开前开关前右 2-HPECM*/
	bool    bJamTypeCtrl;       //是否使用外部设置的GR样式，否则用模型默认值
	DKDMS::Enum_RJamType eJamType;     //GR样式,bJamTypeCtrl为true时有效
	float		Psia;					//航向角，单位：度（仅对空中GR设备有效）
	DKDMS::Enum_RadarJamDirCtrl     eWorkDir;  //工作方位指向（仅部分空中装备有效）
	float		StartAZ;				//起始方位（度）
	float		EndAZ;				//终止方位（度）
	float		RCS;					//被保护目标RCS
	bool		bUseEye;		   //是否调用地形遮蔽

	/*重载构造函数*/
	_ModelBus_aJAM_Set_PARA()
	{
		sRID          = nullptr;
		ID            = 0;
		ATT           = DKDMS::Enum_ATT_3;
		EquipmentName = nullptr;
		LON           = 0;
		LAT           = 0;
		Height        = 0;
		TargetNum     = 0;
		TargetID      = nullptr;
		iCenterPoint  = 0;
		pCenterPoint  = nullptr;
		WorkMode      = DKDMS::Enum_WorkMode_1;
		Psia          = 0;
		eWorkDir      = DKDMS::Enum_RadarJamDirCtrl_2;
		StartAZ		  = 0;
		EndAZ		  = 360;
		bUseEye		  = false;
		ESMMode = -1;
		ECMMode = -1;
		bJamTypeCtrl  = false;
		eJamType = DKDMS::Enum_RJamType_1;
		RCS = 5;
	}

	/*重载析构函数*/
	~_ModelBus_aJAM_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Delete(TargetID);
		SW_Delete(pCenterPoint);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aJAM_Set_PARA(const _ModelBus_aJAM_Set_PARA& jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		TargetID = nullptr;
		pCenterPoint  = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aJAM_Set_PARA& operator = (const _ModelBus_aJAM_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		ID            = theStruct.ID;
		ATT           = theStruct.ATT;
		LON           = theStruct.LON;
		LAT           = theStruct.LAT;
		Height        = theStruct.Height;
		TargetNum     = theStruct.TargetNum;

		//SW_Delete(TargetID);
		SW_Malloc_Int(theStruct.TargetID,TargetID,theStruct.TargetNum,TargetNum);

		//SW_Delete(pCenterPoint);
		SW_Malloc_Struct(sPON_AREA,theStruct.pCenterPoint,pCenterPoint,theStruct.iCenterPoint,iCenterPoint);

		WorkMode      = theStruct.WorkMode;
		Psia          = theStruct.Psia;
		eWorkDir        = theStruct.eWorkDir;
		StartAZ			= theStruct.StartAZ;
		EndAZ			= theStruct.EndAZ;
		bUseEye			= theStruct.bUseEye;
		ESMMode = theStruct.ESMMode;
		ECMMode = theStruct.ECMMode;
		bJamTypeCtrl = theStruct.bJamTypeCtrl;
		eJamType = theStruct.eJamType;
		RCS = theStruct.RCS;
		return *this;
	}
}aJAM_Set_PARA;

//雷达初始化信息
typedef struct _ModelBus_aRADAR_Set_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	DKDMS::Enum_ATT	ATT;			//敌我属性
	char*		EquipmentName;	//设备名称
	float		LON;			//经度，单位：度
	float		LAT;			//纬度，单位：度
	float		Height;			//高度，单位：米（m）
	int			RadarBaitNum;	//雷达诱饵数量
	int*		RadarBaitID;	//雷达诱饵ID
	float		PointAZ;		//雷达阵面方位指向，单位：度（仅对相控阵雷达有效）
	float		Psia;			//航向角，单位：度（仅对空中雷达有效）
	float		fPd;            //检测概率
	bool		bUseEye;		   //是否调用地形遮蔽	

	DKDMS::Enum_RadarWorkMode  eWorkMode; //工作模式
	//add zm 20161018  外所SAR、GMTI、光学模型复用雷达接口时使用
	DKDMS::Enum_DirCtrl        eWorkDir;  //SAR波束方位
	float               fPitch;    //SAR搭载平台俯仰角，单位：（±90）度（方位角复用fPsia）
	float               fRoll;     //SAR搭载平台横滚角，单位：度
	//add end 20161018

	//步长数据只在计算三维TC包络时使用，建议在0~3之间
	float       fAzStep;//方位步长，度
	float       fElStep;//俯仰步长，度

	bool bReconCalc;
	bool bJamCalc;  

	/*重载构造函数*/
	_ModelBus_aRADAR_Set_PARA()
	{
		sRID          = nullptr;
		ID            = 0;
		ATT           = DKDMS::Enum_ATT_3;
		EquipmentName = nullptr;
		LON           = 0;
		LAT           = 0;
		Height        = 0;
		RadarBaitNum  = 0;
		RadarBaitID  = nullptr;
		PointAZ       = 0;
		Psia          = 0;
		fPd           = 0.9;
		bUseEye		  =false;
		eWorkMode     = DKDMS::Enum_RadarWorkMode_4; 
		eWorkDir      = DKDMS::Enum_DirCtrl_3;  
		fPitch        = 0;    
		fRoll         = 0; 
		fAzStep       = 1;
		fElStep       = 1;
		bReconCalc = true;
		bJamCalc   = true;
	}

	/*重载析构函数*/
	~_ModelBus_aRADAR_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Delete(RadarBaitID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRADAR_Set_PARA(const _ModelBus_aRADAR_Set_PARA &radar)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		RadarBaitID = nullptr;
		*this = radar;
	}

	/*重载=*/
	_ModelBus_aRADAR_Set_PARA& operator = (const _ModelBus_aRADAR_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		ID            = theStruct.ID;	
		ATT           = theStruct.ATT;
		LON           = theStruct.LON;
		LAT           = theStruct.LAT;
		Height        = theStruct.Height;

		RadarBaitNum  = theStruct.RadarBaitNum;
		//SW_Delete(RadarBaitID);
		SW_Malloc_Int(theStruct.RadarBaitID,RadarBaitID,theStruct.RadarBaitNum,RadarBaitNum);

		PointAZ       = theStruct.PointAZ;
		Psia          = theStruct.Psia;
		fPd           = theStruct.fPd;
		bUseEye		  = theStruct.bUseEye;
		eWorkMode     = theStruct.eWorkMode; 
		eWorkDir      = theStruct.eWorkDir;   
		fPitch        = theStruct.fPitch;    
		fRoll         = theStruct.fRoll; 
		fAzStep       = theStruct.fAzStep;
		fElStep       = theStruct.fElStep;
		bReconCalc    = theStruct.bReconCalc;
		bJamCalc      = theStruct.bJamCalc;
		return *this;
	}
}aRADAR_Set_PARA;

//雷达ZC设备初始化信息
typedef struct _ModelBus_aRECON_Set_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	DKDMS::Enum_ATT	ATT;			//敌我属性
	char*		EquipmentName;	//设备名称
	float		LON;			//经度，单位：度
	float		LAT;			//纬度，单位：度
	float		Height;			//高度，单位：米（m）
	float		Psia;			//航向角（仅对空中ZC设备有效）/控守方位中心（9X9有效），单位：度
	float		StartAZ;		//起始方位（度）
	float		EndAZ;			//终止方位（度）
	bool        bUseEye;		//是否调用地形遮蔽

	int         WorkMode;       //工作模式：0、1、2仅308B有效，3、4、5仅302A有效
	                            //0-RWR(全向TC子系统，1.2GHz～18GHz),1-ESM(精测向定位子系统，0.05GHz～18GHz)，2-HGESM(高增益TC子系统，2GHz～12GHz)；
	                            //3-测向交绘系统（0.8~18G），4-时差定位系统（0.38~0.48G，0.8~18G），5-超视距系统（0.8~6G）
	bool        bUseOTH;        //是否计算超视距能力，true:是，false:否，通视距离
	float       fProb;          //fProb时间不超过的路径损耗，取值范围：0~1，超视距时有效
	bool        bUseRelatRecon; //是否采用相关检测（9X9有效），默认常规
	                            //true：相关检测，灵敏度阈值低，ZC距离远，参数测量精度低
	                            //false:常规检测，灵敏度阈值相对相关检测高，参数测量精度高

	float		fOperatorAbility;//操作员水平0~1,默认为1
	float		fEnviorAdaptability;//环境适应性

	int			nHideRangeNum; //遮蔽角信息
	sHideCoverRange* pHideRangeData;

	/*重载构造函数*/
	_ModelBus_aRECON_Set_PARA()
	{
		sRID          = nullptr;
		ID            = 0;
		ATT           = DKDMS::Enum_ATT_1;
		EquipmentName = nullptr;
		LON           = 0;
		LAT           = 0;
		Height        = 0;
		Psia          = 0;
		StartAZ		  = 0;
		EndAZ		  = 360;
		bUseEye		  = false;
		WorkMode      = -1;
		bUseOTH       = false;
		fProb         = 0.9;
		bUseRelatRecon = false;
		fOperatorAbility = 1;
		fEnviorAdaptability = 1;
		nHideRangeNum = 0;
		pHideRangeData = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aRECON_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Delete(pHideRangeData);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRECON_Set_PARA(const _ModelBus_aRECON_Set_PARA &recon)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		pHideRangeData = nullptr;
		*this = recon;
	}

	/*重载=*/
	_ModelBus_aRECON_Set_PARA& operator = (const _ModelBus_aRECON_Set_PARA& theStruct) 
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		ID             = theStruct.ID;
		ATT            = theStruct.ATT;
		LON             = theStruct.LON;
		LAT             = theStruct.LAT;
		Height          = theStruct.Height;
		Psia            = theStruct.Psia;
		StartAZ			= theStruct.StartAZ;
		EndAZ			= theStruct.EndAZ;
		bUseEye			= theStruct.bUseEye;
		WorkMode        = theStruct.WorkMode;
		bUseOTH         = theStruct.bUseOTH;
		fProb           = theStruct.fProb;
		bUseRelatRecon  = theStruct.bUseRelatRecon;
		fOperatorAbility = theStruct.fOperatorAbility;
		fEnviorAdaptability = theStruct.fEnviorAdaptability;


		nHideRangeNum=theStruct.nHideRangeNum;
		SW_Malloc_Struct(sHideCoverRange,theStruct.pHideRangeData,pHideRangeData,theStruct.nHideRangeNum,nHideRangeNum);
		return *this;
	}
}aRECON_Set_PARA;

//目标平台初始化信息
typedef struct _ModelBus_aPLAT_Set_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	DKDMS::Enum_ATT	ATT;			//敌我属性
	char*		EquipmentName;	//设备名称
	float		LON;			//经度，单位：度
	float		LAT;			//纬度，单位：度
	float		Height;			//高度，单位：米（m）
	DKDMS::Enum_GroundTgtType GroundTgtType;					//固定目标类型
	DKDMS::Enum_GroundTargetPlatType GroundTargetPlatType;    //地面目标平台类型
	float		TargetRadius;   //目标半径，单位：米（m）
	int         nRCSNum;    //RCS个数                          
	RCS_PARA*	RCSArray;	//回波面积组(多RCS平台有效)，单位：平方米（m^2）

	/*重载构造函数*/
	_ModelBus_aPLAT_Set_PARA()
	{
		sRID          = nullptr;
		ID            = 0;
		ATT           = DKDMS::Enum_ATT_3;
		EquipmentName = nullptr;
		LON           = 0;
		LAT           = 0;
		Height        = 0;
		GroundTgtType = DKDMS::Enum_GroundTgtType_1;
		GroundTargetPlatType = DKDMS::Enum_GroundTargetPlatType_0;
		TargetRadius  = 0;
		nRCSNum       = 1;
		RCSArray      = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aPLAT_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Delete(RCSArray);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aPLAT_Set_PARA(const _ModelBus_aPLAT_Set_PARA &plat)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		RCSArray      = nullptr;
		*this = plat;
	}

	/*重载=*/
	_ModelBus_aPLAT_Set_PARA& operator = (const _ModelBus_aPLAT_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		ID            = theStruct.ID;
		ATT           = theStruct.ATT;
		LON           = theStruct.LON;
		LAT           = theStruct.LAT;
		Height        = theStruct.Height;
		GroundTgtType = theStruct.GroundTgtType;
		GroundTargetPlatType  = theStruct.GroundTargetPlatType;
		TargetRadius  = theStruct.TargetRadius;
		nRCSNum       = theStruct.nRCSNum;
		//SW_Delete(RCSArray);
		SW_Malloc_Struct(RCS_PARA,theStruct.RCSArray, RCSArray, theStruct.nRCSNum, nRCSNum);

		return *this;
	}
}aPLAT_Set_PARA;

//雷达GR交互信息
typedef struct _ModelBus_aJAM_Get_PARA
{
	char*		sRID;		//身份字符串
	int			ID;			//实体ID
	float		LON;		//经度，单位：度
	float		LAT;		//纬度，单位：度
	float		Height;		//高度，单位：米（m）
	DKDMS::Enum_RFT	RFT;		//射频类型
	float		RF[64];		//射频值，单位：MHz
	int			QRF;		//射频值数量
	float		PW;			//脉冲宽度，单位：us
	float		RBand;		//接收机带宽，单位：MHz
	float		Power;		//功率，单位：w
	float		Gt;			//天线接收增益，单位：分贝（dB）
	float		HBeamWidth;	//水平波束宽度，单位：度
	float		VBeamWidth;	//垂直波束宽度，单位：度
	float		StartAZ;	//起始角，单位：度
	float		EndAZ;		//终止角，单位：度

	/*重载构造函数*/
	_ModelBus_aJAM_Get_PARA()
	{
		sRID = nullptr;
		ID = 0;
		LON = 0;
		LAT = 0;
		Height = 0;
		RFT = DKDMS::Enum_RFT_0;
		for (int i=0; i<64; i++)
		{
			RF[i] = 0;
		}
		QRF = 0;
		PW = 0;
		RBand = 0;
		Power = 0;
		Gt = 0;
		HBeamWidth = 0;
		VBeamWidth = 0;
		StartAZ = 0;
		EndAZ = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aJAM_Get_PARA()
	{
		SW_Free_Char(sRID);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aJAM_Get_PARA(const _ModelBus_aJAM_Get_PARA &radar)
	{
		sRID = nullptr;
		*this = radar;
	}

	/*重载=*/
	_ModelBus_aJAM_Get_PARA& operator = (const _ModelBus_aJAM_Get_PARA& theStruct)
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
		RFT    = theStruct.RFT;
		for (int i=0; i<64; i++)
		{
			RF[i] = theStruct.RF[i];
		}
		QRF    = theStruct.QRF;
		PW     = theStruct.PW;
		RBand  = theStruct.RBand;
		Power  = theStruct.Power;
		Gt     = theStruct.Gt;
		HBeamWidth = theStruct.HBeamWidth;
		VBeamWidth = theStruct.VBeamWidth;
		StartAZ    = theStruct.StartAZ;
		EndAZ      = theStruct.EndAZ;

		return *this;
	}

}aJAM_Get_PARA;

//雷达交互信息
typedef struct _ModelBus_aRADAR_PARA
{
	char*		sRID;		//身份字符串
	int			ID;			//实体ID
	float		LON;		//经度，单位：度
	float		LAT;		//纬度，单位：度
	float		Height;		//高度，单位：米（m）
	DKDMS::Enum_RFT	RFT;		//射频类型
	float		RF[64];		//射频值，单位：MHz
	int			QRF;		//射频值数量
	float		PW;			//脉冲宽度，单位：us
	float		RBand;		//接收机带宽，单位：MHz
	float		Power;		//功率，单位：w
	float		Gt;			//天线接收增益，单位：分贝（dB）
	float		HBeamWidth;	//水平波束宽度，单位：度
	float		VBeamWidth;	//垂直波束宽度，单位：度
	float		StartAZ;	//起始角，单位：度
	float		EndAZ;		//终止角，单位：度
	float		ScanCycle;	//天线扫描周期，单位：s
	float		fGtSL1;		//天线第一旁瓣增益，单位：dB
	float		fGtSLm;		//天线平均旁瓣增益，单位：dB
	DKDMS::Enum_RadarSort eRadarSort;  //雷达功能用途
	DKDMS::Enum_PlatType  ePlatType;   //搭载平台类型

	bool        bReconCalc;
	bool        bJamCalc;

	/*重载构造函数*/
	_ModelBus_aRADAR_PARA()
	{
		sRID = nullptr;
		ID = 0;
		LON = 0;
		LAT = 0;
		Height = 0;
		RFT = DKDMS::Enum_RFT_0;
		for (int i=0; i<64; i++)
		{
			RF[i] = 0;
		}
		QRF = 0;
		PW = 0;
		RBand = 0;
		Power = 0;
		Gt = 0;
		ScanCycle  = 0.;
		HBeamWidth = 0;
		VBeamWidth = 0;
		StartAZ = 0;
		EndAZ = 0;
		fGtSL1 = 0;
		fGtSLm = 0;
		eRadarSort = DKDMS::Enum_RadarSort_255;
		ePlatType  = DKDMS::Enum_PlatType_255;

		bReconCalc = true;
		bJamCalc   = true;
	}

	/*重载析构函数*/
	~_ModelBus_aRADAR_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRADAR_PARA(const _ModelBus_aRADAR_PARA &radar)
	{
		sRID = nullptr;
		*this = radar;
	}

	/*重载=*/
	_ModelBus_aRADAR_PARA& operator = (const _ModelBus_aRADAR_PARA& theStruct)
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
		RFT    = theStruct.RFT;
		for (int i=0; i<64; i++)
		{
			RF[i] = theStruct.RF[i];
		}
		QRF    = theStruct.QRF;
		PW     = theStruct.PW;
		RBand  = theStruct.RBand;
		Power  = theStruct.Power;
		Gt     = theStruct.Gt;
		HBeamWidth = theStruct.HBeamWidth;
		VBeamWidth = theStruct.VBeamWidth;
		StartAZ    = theStruct.StartAZ;
		EndAZ      = theStruct.EndAZ;		
		ScanCycle  = theStruct.ScanCycle;
		fGtSL1 = theStruct.fGtSL1;
		fGtSLm = theStruct.fGtSLm;
		eRadarSort = theStruct.eRadarSort;
		ePlatType  = theStruct.ePlatType;

		bReconCalc = theStruct.bReconCalc;
		bJamCalc   = theStruct.bJamCalc;
		return *this;
	}

}aRADAR_PARA;

//GR交互信息
typedef struct _ModelBus_aJAM_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	int			RadarID;		//目标雷达ID
	float		LON;			//经度，单位：度
	float		LAT;			//纬度，单位：度
	float		Height;			//高度，单位，米（m）
	float		ERP;			//等效辐射功率，单位：分贝（dB）
	float		RF[64];			//射频值，单位：MHz
	int			QRF;			//射频值数量
	float		RJamBandWidth;	//接收机带宽，单位：KHz
	DKDMS::Enum_RJamType	RJamType;	//GR类型
	float		QDecoyTarget;	//假目标个数
	float		DecoyTargetInterval;	//假目标间隔时间，单位：us

	/*重载构造函数*/
	_ModelBus_aJAM_PARA()
	{
		sRID = nullptr;
		ID   = 0;
		RadarID = 0;
		LON  = 0;
		LAT  = 0;
		Height = 0;
		ERP  = 0;
		for (int i=0; i<64; i++)
		{
			RF[i] = 0;
		}
		QRF = 0;
		RJamBandWidth = 0;
		RJamType = DKDMS::Enum_RJamType_1;
		QDecoyTarget = 0;
		DecoyTargetInterval = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aJAM_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aJAM_PARA(const _ModelBus_aJAM_PARA &jam)
	{
		sRID = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aJAM_PARA& operator = (const _ModelBus_aJAM_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID      = theStruct.ID;
		RadarID = theStruct.RadarID;
		LON     = theStruct.LON;
		LAT     = theStruct.LAT;
		Height  = theStruct.Height;
		ERP     = theStruct.ERP;
		for (int i=0; i<64; i++)
		{
			RF[i] = theStruct.RF[i];
		}
		QRF     = theStruct.QRF;
		RJamBandWidth = theStruct.RJamBandWidth;
		RJamType      = theStruct.RJamType;
		QDecoyTarget  = theStruct.QDecoyTarget;
		DecoyTargetInterval = theStruct.DecoyTargetInterval;

		return *this;
	}

}aJAM_PARA;


//雷达二维TC范围输出结果信息
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aRadarRange
{
	char*			sRID;		//身份字符串
	int				ID;			//雷达ID
	int				PlatID;		//平台ID
	DKDMS::Enum_RegionSort	RegionSort;	//区域类型
	DKDMS::Enum_RegionType	RegionType;	//几何类型
	float			LON;		//经度，单位：度
	float			LAT;		//纬度，单位：度
	float			Height;		//高度
	int				PtNum;		//边界点个数
	sPON_AGG*		Position;	//边界点
	float           fTrgHeight; //TC目标高度
	float           fRangeJamRatio;   //距离压制系数（噪声GR有效，GR方向上），0-1，0表示无压制，1表示全压制

	/*重载构造函数*/
	_ModelBus_aRadarRange()
	{
		sRID = nullptr;
		ID = 0;
		PlatID = 0;
		fTrgHeight = 0.;
		RegionSort = DKDMS::Enum_RegionSort_1;
		RegionType = DKDMS::Enum_RegionType_0;
		LON = 0.0;
		LAT = 0.0;
		Height = 0.0;
		PtNum = 0;
		Position = nullptr;
		fRangeJamRatio = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aRadarRange()
	{
		SW_Free_Char(sRID);
		SW_Delete(Position);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRadarRange(const _ModelBus_aRadarRange &range)
	{
		sRID = nullptr;
		Position = nullptr;
		*this = range;
	}

	/*重载=*/
	_ModelBus_aRadarRange& operator = (const _ModelBus_aRadarRange& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID = theStruct.ID;
		PlatID = theStruct.PlatID;
		fTrgHeight = theStruct.fTrgHeight;
		RegionSort = theStruct.RegionSort;
		RegionType = theStruct.RegionType;
		LON = theStruct.LON;
		LAT = theStruct.LAT;
		Height = theStruct.Height;
		fRangeJamRatio = theStruct.fRangeJamRatio;
		PtNum = theStruct.PtNum;
		//SW_Delete(Position);
		SW_Malloc_Struct(sPON_AGG,theStruct.Position,Position,theStruct.PtNum,PtNum);

		return *this;
	}

}aRadarRange;

//一个方位切面的包络信息 zm add 20161228
typedef struct _ModelBus_OneAzPoly
{
	float			fAz;		//方位值，度
	int				nPosNum;	//包络点数目
	sPON_AREA*		Position;	//边界点，顺序：原点+各俯仰对应的包络点（俯仰从下界遍历至上届）

	/*重载构造函数*/
	_ModelBus_OneAzPoly()
	{
		fAz      = 0.0;
		nPosNum  = 0;
		Position = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_OneAzPoly()
	{
		SW_Delete(Position);
	}

	/*重载拷贝构造函数*/
	_ModelBus_OneAzPoly(const _ModelBus_OneAzPoly &range)
	{
		Position = nullptr;
		*this = range;
	}

	/*重载=*/
	_ModelBus_OneAzPoly& operator = (const _ModelBus_OneAzPoly& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		fAz = theStruct.fAz;
		nPosNum = theStruct.nPosNum;
		//SW_Delete(Position);
		SW_Malloc_Struct(sPON_AREA,theStruct.Position,Position,theStruct.nPosNum,nPosNum);

		return *this;
	}
}OneAzPoly;

//雷达三维TC范围输出结果信息  zm add 20161228
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_RadarRange3D
{
	char*			sRID;		//身份字符串
	int				ID;			//本模型实体ID
	int				TrgID;		//目标ID
	float			fLon;		//雷达经度，单位：度
	float			fLat;		//雷达纬度，单位：度
	float			fHeight;	//雷达高度，米
	int				nAzNum;		//方位面数目
	OneAzPoly*		Poly;	    //每个方位面的包络
	float           fTime;      //推演计算时有效

	/*重载构造函数*/
	_ModelBus_RadarRange3D()
	{
		sRID    = nullptr;
		ID      = 0;
		TrgID   = 0;
		fLon    = 0.0;
		fLat    = 0.0;
		fHeight = 0.0;
		nAzNum  = 0;
		Poly    = nullptr;
		fTime   = 0;
	}

	/*重载析构函数*/
	~_ModelBus_RadarRange3D()
	{
		SW_Free_Char(sRID);
		SW_Delete(Poly);
	}

	/*重载拷贝构造函数*/
	_ModelBus_RadarRange3D(const _ModelBus_RadarRange3D &range)
	{
		sRID = nullptr;
		Poly = nullptr;
		*this = range;
	}

	/*重载=*/
	_ModelBus_RadarRange3D& operator = (const _ModelBus_RadarRange3D& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID = theStruct.ID;
		TrgID = theStruct.TrgID;
		fLon  = theStruct.fLon;
		fLat  = theStruct.fLat;
		fHeight = theStruct.fHeight;
		nAzNum  = theStruct.nAzNum;
		fTime   = theStruct.fTime;
		//SW_Delete(Poly);
		SW_Malloc_Struct(OneAzPoly,theStruct.Poly,Poly,theStruct.nAzNum,nAzNum);

		return *this;
	}
}RadarRange3D;

//计算检测概率的单个位置点参数
typedef struct _ModelBus_aPD_REGION_POINT
{
	int             ID;         //点ID
	sPON_AREA		Position;	//点位置
	float           RCS;        //点对应RCS

	/*重载构造函数*/
	_ModelBus_aPD_REGION_POINT()
	{
		ID  = 0;
		RCS = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_aPD_REGION_POINT()
	{

	}

	/*重载拷贝构造函数*/
	_ModelBus_aPD_REGION_POINT(const _ModelBus_aPD_REGION_POINT &range)
	{
		*this = range;
	}

	/*重载=*/
	_ModelBus_aPD_REGION_POINT& operator = (const _ModelBus_aPD_REGION_POINT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		ID       = theStruct.ID;
		Position = theStruct.Position;
		RCS      = theStruct.RCS;

		return *this;
	}
}aPD_REGION_POINT;

//计算检测概率的区域设置 modify zm 20171208 位置点由同一平面改为可适应不同平面
typedef struct _ModelBus_aPD_REGION
{
	char*		    sRID;		//身份字符串
	//float			Height;		//高度,单位：米（m）
	int				PtNum;		//位置点个数
	aPD_REGION_POINT*	RegionPoint;	//各位置点

	/*重载构造函数*/
	_ModelBus_aPD_REGION()
	{
		sRID = nullptr;
		//Height = 0;
		PtNum = 0;
		RegionPoint = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aPD_REGION()
	{
		SW_Free_Char(sRID);
		SW_Delete(RegionPoint);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aPD_REGION(const _ModelBus_aPD_REGION &range)
	{
		sRID = nullptr;
		RegionPoint = nullptr;
		*this = range;
	}

	/*重载=*/
	_ModelBus_aPD_REGION& operator = (const _ModelBus_aPD_REGION& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//Height = theStruct.Height;
		PtNum = theStruct.PtNum;
		//SW_Delete(RegionPoint);
		SW_Malloc_Struct(aPD_REGION_POINT,theStruct.RegionPoint,RegionPoint,theStruct.PtNum,PtNum);
		return *this;
	}
}aPD_REGION;


//某个位置点的TC概率
typedef struct _ModelBus_sPOS_PT_PD
{
	int      ID;        //点ID
	sPON_AREA Position;	//点位置
	float    Pd;	    //TC概率

	/*重载构造函数*/
	_ModelBus_sPOS_PT_PD()
	{
		ID = 0;
		Pd = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sPOS_PT_PD()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sPOS_PT_PD(const _ModelBus_sPOS_PT_PD &range)
	{
		*this = range;
	}

	/*重载=*/
	_ModelBus_sPOS_PT_PD& operator = (const _ModelBus_sPOS_PT_PD& theStruct)
	{
		ID       = theStruct.ID;
		Position = theStruct.Position;
		Pd       = theStruct.Pd;
		return *this;
	}
}POS_PT_PD;

//雷达区域TC概率输出结果信息
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aRADAR_REGION_PD
{
	char*			sRID;		//身份字符串
	int				RadarID;	//雷达ID
	int				TargetID;	//目标平台ID
	//float			Height;		//目标高度
	int				PtNum;		//位置点个数
	POS_PT_PD*		PosPtPD;	//各位置点的TC概率

	/*重载构造函数*/
	_ModelBus_aRADAR_REGION_PD()
	{
		sRID = nullptr;
		RadarID = 0;
		TargetID = 0;
		//Height = 0;
		PtNum = 0;
		PosPtPD = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aRADAR_REGION_PD()
	{
		SW_Free_Char(sRID);
		SW_Delete(PosPtPD);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRADAR_REGION_PD(const _ModelBus_aRADAR_REGION_PD &other)
	{
		sRID = nullptr;
		PosPtPD = nullptr;
		*this = other;
	}

	/*重载=*/
	_ModelBus_aRADAR_REGION_PD& operator = (const _ModelBus_aRADAR_REGION_PD& other)
	{
		if( this==&other )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(other.sRID,sRID);

		RadarID = other.RadarID;
		TargetID = other.TargetID;
		//Height = other.Height;
		PtNum = other.PtNum;
		//SW_Delete(PosPtPD);
		SW_Malloc_Struct(POS_PT_PD,other.PosPtPD,PosPtPD,other.PtNum,PtNum);

		return *this;
	}

}aRADAR_REGION_PD;

//GR机ZC范围输出结果信息
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aReconRange
{
	char*			sRID;		//身份字符串
	int				ID;			//GR机ID
	int				RadarID;	//雷达ID
	sReconResult ReconResult;
	DKDMS::Enum_RegionSort	RegionSort;	//区域类型
	DKDMS::Enum_RegionType	RegionType;	//几何类型
	float			Height;		//高度
	int				PtNum;		//边界点个数
	sPON_AGG*		Position;	//边界点

	int		TargetID;
	float	fCenterLon;			//经度，单位：度（o）
	float	fCenterLat;			//纬度，单位：度（o）
	float	fCenterHeight;		//高度，单位：米（m）
	int     nRangeNum;			//ZC/GR能力区域个数
	sRECON_POWERPOINT* PowerRange;  //ZC/GR能力区域
	bool    bUsePosRng;         //true：使用点迹（PtNum、Position）表征ZC范围，false：使用nRangeNum、PowerRange
	
	bool    bUseOTH;            //是否是超视距计算
	float   fDectProb;          //检测概率，超视距时有效

	/*重载构造函数*/
	_ModelBus_aReconRange()
	{
		sRID = nullptr;
		ID = 0;
		RadarID = 0;
		RegionSort = DKDMS::Enum_RegionSort_1;
		RegionType = DKDMS::Enum_RegionType_0;
		Height = 0;
		PtNum = 0;
		Position = nullptr;
		nRangeNum = 0;
		PowerRange = nullptr;
		TargetID = 0;
		fCenterLon = 0.f;
		fCenterLat = 0.f;
		fCenterHeight = 0.f;
		bUseOTH = false;
		fDectProb     = 0.9;
		bUsePosRng = true;
	}

	/*重载析构函数*/
	~_ModelBus_aReconRange()
	{
		SW_Free_Char(sRID);
		SW_Delete(Position);
		SW_Delete(PowerRange);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aReconRange(const _ModelBus_aReconRange &range)
	{
		sRID = nullptr;
		Position = nullptr;
		PowerRange = nullptr;
		*this = range;
	}

	/*重载=*/
	_ModelBus_aReconRange& operator = (const _ModelBus_aReconRange& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID = theStruct.ID;
		RadarID = theStruct.RadarID;
		RegionSort = theStruct.RegionSort;
		RegionType = theStruct.RegionType;
		Height = theStruct.Height;
		PtNum = theStruct.PtNum;
		//SW_Delete(Position);
		SW_Malloc_Struct(sPON_AGG,theStruct.Position,Position,theStruct.PtNum,PtNum);

		ReconResult = theStruct.ReconResult;

		TargetID	  = theStruct.TargetID;
		fCenterLon    = theStruct.fCenterLon;
		fCenterLat    = theStruct.fCenterLat;
		fCenterHeight = theStruct.fCenterHeight;
		nRangeNum     = theStruct.nRangeNum;

		//SW_Delete(PowerRange);
		SW_Malloc_Struct(sRECON_POWERPOINT,theStruct.PowerRange,PowerRange,theStruct.nRangeNum,nRangeNum);

		bUsePosRng    = theStruct.bUsePosRng;
		bUseOTH       = theStruct.bUseOTH;
		fDectProb     = theStruct.fDectProb;

		return *this;
	}
}aReconRange;

//GR机暴露区计算输出结果
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aDiscoverableArea
{
	char*			sRID;		//身份字符串
	int				ID;			//GR机ID
	int				RadarID;	//雷达ID
	DKDMS::Enum_RegionSort	RegionSort;	//区域类型
	DKDMS::Enum_RegionType	RegionType;	//几何类型
	int				PtNum;		//边界点个数
	sPON_AGG*		Position;	//边界点

	/*重载构造函数*/
	_ModelBus_aDiscoverableArea()
	{
		sRID = nullptr;
		ID = 0;
		RadarID = 0;
		RegionSort = DKDMS::Enum_RegionSort_1;
		RegionType = DKDMS::Enum_RegionType_0;
		PtNum = 0;
		Position = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aDiscoverableArea()
	{
		SW_Free_Char(sRID);
		SW_Delete(Position);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aDiscoverableArea(const _ModelBus_aDiscoverableArea &range)
	{
		sRID = nullptr;
		Position = nullptr;
		*this = range;
	}

	/*重载=*/
	_ModelBus_aDiscoverableArea& operator = (const _ModelBus_aDiscoverableArea& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID = theStruct.ID;
		RadarID = theStruct.RadarID;
		RegionSort = theStruct.RegionSort;
		RegionType = theStruct.RegionType;
		PtNum = theStruct.PtNum;

		//SW_Delete(Position);
		SW_Malloc_Struct(sPON_AGG,theStruct.Position,Position,theStruct.PtNum,PtNum);

		return *this;
	}

}aDiscoverableArea;


//GR波束计算输出结果
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aJamPointVar
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	int			JamPointAmount;	//GR波束数
	sJAM_POINT* JamPointVar;	//GR波束信息

	/*重载构造函数*/
	_ModelBus_aJamPointVar()
	{
		sRID = nullptr;
		ID = 0;
		JamPointAmount = 0;
		JamPointVar = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aJamPointVar()
	{
		SW_Free_Char(sRID);
		SW_Delete(JamPointVar);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aJamPointVar(const _ModelBus_aJamPointVar &jamvar)
	{
		sRID = nullptr;
		JamPointVar = nullptr;
		*this = jamvar;
	}

	/*重载=*/
	_ModelBus_aJamPointVar& operator = (const _ModelBus_aJamPointVar& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID             = theStruct.ID;
		JamPointAmount = theStruct.JamPointAmount;

		//SW_Delete(JamPointVar);
		SW_Malloc_Struct(sJAM_POINT,theStruct.JamPointVar,JamPointVar,theStruct.JamPointAmount,JamPointAmount);

		return *this;
	}

}aJamPointVar;

//雷达ZC辐射源工作特征参数
typedef struct _ModelBus_sRECON_DETECTRADAR
{
	int			ReconID;					// 实体ID  
	int			RadarID;					// 雷达ID	

	// 平台相关信息
	int			RadarPlatID;				// 雷达搭载平台ID
	DKDMS::Enum_ATT	ATT;						// 敌我属性	
	int			PlatType;					// 平台类型
	int			DangerClass;				// 威胁等级	

	DKDMS::Enum_SignalState SignalState;	// 信号活动情况
	sReconResult ReconResult;				// ZC计算结果

	int			JamState;					//GR标识,0=未GR;1=有源GR(ECM);2=无源GR(CFDS);3=有源GR+无源GR(ECM+CFDS);4=HPECM。
	DKDMS::Enum_RJamType		JamType;			// GR方式

	/*重载构造函数*/
	_ModelBus_sRECON_DETECTRADAR()
	{
		ReconID       = 0;
		RadarID		  = 0;
		RadarPlatID	  = 0;
		ATT			  = DKDMS::Enum_ATT_0;
		PlatType	  = 0;
		DangerClass	  = 0;
		SignalState   = DKDMS::Enum_SignalState_0;
		JamState	  = 0;
		JamType	      = DKDMS::Enum_RJamType_1;
	}	

}sRECON_DETECTRADAR;

//雷达ZC数据融合结果
typedef struct _ModelBus_sRECON_DATAFUSIONRESULT
{
	int			RadarID;					// 雷达ID

	// 平台相关信息
	int			RadarPlatID;				// 雷达搭载平台ID
	DKDMS::Enum_ATT	ATT;					// 敌我属性
	int			PlatType;					// 平台类型
	int			DangerClass;				// 威胁等级
	float         RecogPro;					//识别准确率

	int         equipTotalNum;					//所有发现该目标的ZC站个数
	sReconPerfo  *pEquipPerfo;					//ZC性能参数
 
	sReconLocateResult LocateResult;			//融合定位结果

	/*重载构造函数*/
	_ModelBus_sRECON_DATAFUSIONRESULT()
	{
		RadarID		  = 0;
		RadarPlatID	  = 0;
		ATT			  = DKDMS::Enum_ATT_0;
		PlatType	  = 0;
		DangerClass	  = 0;
		RecogPro	  = 0;
		equipTotalNum = 0;
		pEquipPerfo   = nullptr;
		/*memset(&ReconResult,0,sizeof(ReconResult));*/
	}
	/*重载析构函数*/
	~_ModelBus_sRECON_DATAFUSIONRESULT()
	{
		SW_Delete(pEquipPerfo);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRECON_DATAFUSIONRESULT(const _ModelBus_sRECON_DATAFUSIONRESULT &jam)
	{
		pEquipPerfo = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRECON_DATAFUSIONRESULT& operator=(const _ModelBus_sRECON_DATAFUSIONRESULT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		RadarID       = theStruct.RadarID;
		RadarPlatID   = theStruct.RadarPlatID;

		ATT			  = theStruct.ATT;
		PlatType	  = theStruct.PlatType;
		DangerClass	  = theStruct.DangerClass;
		RecogPro	  = theStruct.RecogPro;

		equipTotalNum = theStruct.equipTotalNum;
		SW_Malloc_Struct(sReconPerfo, theStruct.pEquipPerfo,pEquipPerfo,theStruct.equipTotalNum,equipTotalNum);
		LocateResult  = theStruct.LocateResult;

		return *this;
	}

}sRECON_DATAFUSIONRESULT;
//雷达ZC数据融合特征参数
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRECON_DATAFUSIONPARA
{
	char*		sRID;							//身份字符串
	int			ReconID;						// 实体ID
	int			PlatID;							//当前平台ID
	int			TaskID;							//任务ID
	float		fTime;							// 仿真时间
	bool		bMainNode;						//主节点融合中心标识，true为主节点
	int			iReconNum;						//组网内ZC装备个数
	int*		pReconID;						//组网内ZC装备个数
	int			iTgtNum;			            //当前时刻截获的目标个数
	sRECON_DATAFUSIONRESULT* pRadarReconFusionResult;		//ZC融合结果：（参数结果+定位结果）


	/*重载构造函数*/
	_ModelBus_sRECON_DATAFUSIONPARA()
	{
		sRID          = nullptr;
		ReconID       = 0;
		PlatID		  = 0;
		TaskID        = 0;
		fTime         = 0.;
		bMainNode	  = false;
		iReconNum	  = 0;
		pReconID	  = nullptr;
		iTgtNum       = 0;
		pRadarReconFusionResult = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sRECON_DATAFUSIONPARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(pReconID);
		SW_Delete(pRadarReconFusionResult);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRECON_DATAFUSIONPARA(const _ModelBus_sRECON_DATAFUSIONPARA &jam)
	{
		sRID = nullptr;
		pReconID= nullptr;
		pRadarReconFusionResult =nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRECON_DATAFUSIONPARA& operator=(const _ModelBus_sRECON_DATAFUSIONPARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReconID       = theStruct.ReconID;
		PlatID		  = theStruct.PlatID;
		TaskID        = theStruct.TaskID;
		fTime         = theStruct.fTime;
		bMainNode	  = theStruct.bMainNode;
		iReconNum	  = theStruct.iReconNum;

		SW_Malloc_Int(theStruct.pReconID,pReconID,theStruct.iReconNum,iReconNum);

		iTgtNum       = theStruct.iTgtNum;

		//SW_Delete(ReconRadarPara);
		SW_Malloc_Struct(sRECON_DATAFUSIONRESULT, theStruct.pRadarReconFusionResult,pRadarReconFusionResult,theStruct.iTgtNum,iTgtNum);

		return *this;
	}

}sRECON_DATAFUSIONPARA;

//typedef struct _ModelBus_sRECON_GROUPINFOR
//{
//
//	int		ActionID;				 //行为模型ID
//	int		PlatID;                //当前平台ID
//	int     TaskID;              //任务ID
//	float	fTime;				//时间 单位：秒（s）
//	bool    bActive;				//所属任务激活状态
//	int		iReconNum;			//组网内ZC装备个数
//	map<int,int>   m_GroupInforMap;	//编队内ZC装备ID
//
//	/*重载构造函数*/
//	_ModelBus_sRECON_RADARPARA()
//	{
//		sRID          = nullptr;
//		ReconID       = 0;
//		fTime         = 0.;
//		RadarNum	  = 0;
//		bmaster		  = false;
//		ReconRadarPara= nullptr;
//	}
//
//}sRECON_GROUPINFOR;
//雷达ZC辐射源工作特征参数
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRECON_RADARPARA
{
	char*		sRID;							//身份字符串
	int			ReconID;						// 实体ID  
	float		fTime;							// 仿真时间
	//add by chenzh20200416
	bool		bmaster;						//区分一下结果是主站报出还是从站报出，上层数据融合时只融合主站报出的数据，true为主站
	int			RadarNum;						//雷达数量
	sRECON_DETECTRADAR *ReconRadarPara;

	/*重载构造函数*/
	_ModelBus_sRECON_RADARPARA()
	{
		sRID          = "null";
		ReconID       = 0;
		fTime         = 0.;
		RadarNum	  = 0;
		bmaster		  = false;
		ReconRadarPara= nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sRECON_RADARPARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(ReconRadarPara);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRECON_RADARPARA(const _ModelBus_sRECON_RADARPARA &jam)
	{
		sRID = nullptr;
		ReconRadarPara= nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sRECON_RADARPARA& operator=(const _ModelBus_sRECON_RADARPARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReconID       = theStruct.ReconID;
		fTime         = theStruct.fTime;
		RadarNum	= theStruct.RadarNum;
		bmaster		= theStruct.bmaster;

		//SW_Delete(ReconRadarPara);
		SW_Malloc_Struct(sRECON_DETECTRADAR, theStruct.ReconRadarPara,ReconRadarPara,theStruct.RadarNum,RadarNum);

		return *this;
	}
}sRECON_RADARPARA;

typedef struct _ModelBus_sRADARDETECTPLAT
{
	int		PlatID;		//平台ID号
	DKDMS::Enum_ATT	ATT;		//敌我属性
	DKDMS::Enum_AircraftSort AircraftSort; 

	float	fLon;			//经度，单位：度
	float	fLat;			//纬度，单位：度
	float	fHeight;		//高度，单位：米（m）
	float	fSpeed;			//运动速度 单位：米/秒（m/s）
	float	fDir;			//运动方位角，单位：度

	float DetectError;      //TC误差
	bool  bDecepJammed;     //是否受欺骗GR

	/*重载构造函数*/
	_ModelBus_sRADARDETECTPLAT()
	{
		PlatID = 0;
		ATT = DKDMS::Enum_ATT_1;
		AircraftSort = DKDMS::Enum_AircraftSort_0; 
		fLon = 0.;
		fLat = 0.;
		fHeight = 0.;
		fSpeed = 0.;
		fDir = 0.;
		DetectError = 0.;
		bDecepJammed = false;
	}
	_ModelBus_sRADARDETECTPLAT(const _ModelBus_sRADARDETECTPLAT & info){
	
		PlatID = info.PlatID;
		ATT = info.ATT;
		AircraftSort =info.AircraftSort;
		fLon = info.fLon;
		fLat = info.fLat;
		fHeight = info.fHeight;
		fSpeed = info.fSpeed;
		fDir = info.fDir;
		DetectError = info.DetectError;
		bDecepJammed = info.bDecepJammed;
	
	}

}sRadarDetectPlat;

//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRADAR_DETECTINFO
{
	char*	sRID;		//身份字符串
	int		RadarID;	//雷达ID  
	DKDMS::Enum_RadarSort	eRadarSort;		//雷达类别	
	float	fTime;		//时间 单位：s
	int iTargetNum; 
	sRadarDetectPlat* RadarDetectPlat;

	/*重载构造函数*/
	_ModelBus_sRADAR_DETECTINFO()
	{
		sRID		= "null";
		RadarID		= 0;
		eRadarSort	= DKDMS::Enum_RadarSort_0;
		fTime		= 0;
		iTargetNum	= 0;	
		//RadarDetectPlat	= nullptr;	
		RadarDetectPlat = new sRadarDetectPlat();
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_DETECTINFO()
	{
		delete RadarDetectPlat;
		//SW_Free_Char(sRID);
		//SW_Delete(RadarDetectPlat);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_DETECTINFO(const _ModelBus_sRADAR_DETECTINFO &detectInfo)
	{
		sRID = nullptr;
		RadarDetectPlat  = nullptr; 
		*this = detectInfo;
	}

	/*重载=*/
	_ModelBus_sRADAR_DETECTINFO& operator=(const _ModelBus_sRADAR_DETECTINFO& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		RadarID			= theStruct.RadarID;
		eRadarSort		= theStruct.eRadarSort;
		fTime	= theStruct.fTime;
		iTargetNum	= theStruct.iTargetNum;
		RadarDetectPlat = new sRadarDetectPlat();
		RadarDetectPlat = theStruct.RadarDetectPlat;

		//SW_Delete(RadarDetectPlat);
		//SW_Malloc_Struct(sRadarDetectPlat, theStruct.RadarDetectPlat,RadarDetectPlat,theStruct.iTargetNum,iTargetNum);

		return *this;
	}

}sRadar_DetectInfo;

typedef struct _ModelBus_sIMAGE_ZONE
{
	float fImageDefinition;	//	成像清晰度, 取值0～1之间，数值越大，成像清晰度越高
	int	iPtNum;		//点数量  //by zoujw
	sRectZone* ZonePoint;	//包络点
	/*重载构造函数*/
	_ModelBus_sIMAGE_ZONE()
	{
		fImageDefinition= 0.;
		iPtNum			= 0;
		ZonePoint		= nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sIMAGE_ZONE()
	{
		SW_Delete(ZonePoint);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sIMAGE_ZONE(const _ModelBus_sIMAGE_ZONE &theStruct)
	{
		ZonePoint = nullptr;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sIMAGE_ZONE& operator=(const _ModelBus_sIMAGE_ZONE& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		fImageDefinition= theStruct.fImageDefinition;
		iPtNum  = theStruct.iPtNum;

		//SW_Delete(ZonePoint);
		SW_Malloc_Struct(sRectZone,theStruct.ZonePoint,ZonePoint,theStruct.iPtNum,iPtNum);
		return *this;
	}
}sIMAGE_ZONE;

//雷达成像区域报（新）
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sRADAR_IMAGE_AREA
{
	char* sRID;	//身份字符串
	int	RadarID;	//雷达ID  //by zoujw
	float fTime;	//时间 单位：s
	int iImageZoneNum;
	sIMAGE_ZONE* ImageZone;

	/*重载构造函数*/
	_ModelBus_sRADAR_IMAGE_AREA()
	{
		sRID          = nullptr;
		RadarID       = 0;
		fTime         = 0.;
		iImageZoneNum= 0;
		ImageZone     = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sRADAR_IMAGE_AREA()
	{
		SW_Free_Char(sRID);
		SW_Delete(ImageZone);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sRADAR_IMAGE_AREA(const _ModelBus_sRADAR_IMAGE_AREA &theStruct)
	{
		sRID          = nullptr;
		ImageZone     = nullptr;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sRADAR_IMAGE_AREA& operator=(const _ModelBus_sRADAR_IMAGE_AREA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		RadarID         = theStruct.RadarID;
		fTime           = theStruct.fTime;

		iImageZoneNum  = theStruct.iImageZoneNum;
		//SW_Delete(ImageZone);
		SW_Malloc_Struct(sIMAGE_ZONE,theStruct.ImageZone,ImageZone,theStruct.iImageZoneNum,iImageZoneNum);
		return *this;
	}
}sRADAR_IMAGE_AREA;

//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aRADAR_IMAGE_AREA
{
	char* sRID;	//身份字符串
	int	RadarID;	//雷达ID  //by zoujw
	int iImageZoneNum;
	sIMAGE_ZONE* ImageZone;

	/*重载构造函数*/
	_ModelBus_aRADAR_IMAGE_AREA()
	{
		sRID          = nullptr;
		RadarID       = 0;
		iImageZoneNum= 0;
		ImageZone     = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aRADAR_IMAGE_AREA()
	{
		SW_Free_Char(sRID);
		SW_Delete(ImageZone);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRADAR_IMAGE_AREA(const _ModelBus_aRADAR_IMAGE_AREA &theStruct)
	{
		sRID          = nullptr;
		ImageZone     = nullptr;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_aRADAR_IMAGE_AREA& operator=(const _ModelBus_aRADAR_IMAGE_AREA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		RadarID         = theStruct.RadarID;
		iImageZoneNum  = theStruct.iImageZoneNum;
		SW_Malloc_Struct(sIMAGE_ZONE,theStruct.ImageZone,ImageZone,theStruct.iImageZoneNum,iImageZoneNum);

		return *this;
	}
}aRADAR_IMAGE_AREA;


//无人机静态输入参数
typedef struct _ModelBus_aUAV_Set_PARA
{
	char*		sRID;			   	    			//身份字符串
	int			ID;								//实体ID 
	DKDMS::Enum_ATT	ATT;							//敌我属性
	char*		EquipmentName;				//设备名称
	float		LON;								//经度，单位：度
	float		LAT;								//纬度，单位：度
	float		Height;							//高度，单位：米（m）
	int			TargetNum;					//目标数 
	int*		TargetID;						//目标ID
	int			PosNum;						//航迹点数
	sTRACK_POINT* CombatTracklist;	//航迹点
	int			BombPointNum;				//炸点设置

	/*重载构造函数*/
	_ModelBus_aUAV_Set_PARA()
	{
		sRID          = nullptr;
		ID            = 0;
		ATT           = DKDMS::Enum_ATT_1;
		EquipmentName = nullptr;
		LON           = 0.;
		LAT           = 0.;
		Height        = 0.;
		TargetNum     = 0;
		TargetID      = nullptr;
		PosNum        = 0;
		CombatTracklist = nullptr;
		BombPointNum  = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aUAV_Set_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Delete(TargetID);

		SW_Delete(CombatTracklist);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aUAV_Set_PARA(const _ModelBus_aUAV_Set_PARA &jam)
	{
		sRID = nullptr;
		EquipmentName = nullptr;
		TargetID = nullptr;
		CombatTracklist = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aUAV_Set_PARA& operator=(const _ModelBus_aUAV_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID            = theStruct.ID;
		ATT           = theStruct.ATT;

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		LON           = theStruct.LON;
		LAT           = theStruct.LAT;
		Height        = theStruct.Height;
		TargetNum     = theStruct.TargetNum;

		//SW_Delete(TargetID);
		SW_Malloc_Int(theStruct.TargetID,TargetID,theStruct.TargetNum,TargetNum);

		//SW_Delete(CombatTracklist);
		SW_Malloc_Struct(sTRACK_POINT,theStruct.CombatTracklist,CombatTracklist,theStruct.PosNum,PosNum);
		BombPointNum = theStruct.BombPointNum;
		return *this;
	}  
}aUAV_Set_PARA;

//无人机炸点静态计算输出参数
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aUAV_BombPos
{
	char* sRID;                //身份字符串
	int     ID;					//实体ID
	int     RadarID;			//雷达ID
	float  RadarLON;			//雷达所在位置经度
	float  RadarLAT;			//雷达所在位置纬度
	float  RadarHeight;		    //雷达所在位置高度
	int    BombPointNum;		//落点数量
	sPON_AREA *BombPointVar;    //落点位置
	float AveLON;				//平均经度
	float AveLAT;				//平均纬度
	float AveHeight;			//平均高度
	float ErrorValue;

	/*重载构造函数*/
	_ModelBus_aUAV_BombPos()
	{
		sRID          = nullptr;
		ID            = 0;
		RadarID = 0;
		RadarLON = 0;
		RadarLAT = 0;
		RadarHeight = 0;
		BombPointVar = nullptr;
		BombPointNum = 0;
		AveLON = 0;
		AveLAT = 0;
		AveHeight = 0;
		ErrorValue = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aUAV_BombPos()
	{
		SW_Free_Char(sRID);
		SW_Delete(BombPointVar);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aUAV_BombPos(const _ModelBus_aUAV_BombPos &aUAVBomb)
	{
		sRID = nullptr;
		BombPointVar = nullptr;
		*this = aUAVBomb;
	}

	/*重载=*/
	_ModelBus_aUAV_BombPos& operator=(const _ModelBus_aUAV_BombPos& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		RadarID = theStruct.RadarID;
		ID            = theStruct.ID;
		RadarLON = theStruct.RadarLON;
		RadarLAT = theStruct.RadarLAT;
		RadarHeight = theStruct.RadarHeight;

		BombPointNum = theStruct.BombPointNum;
		//SW_Delete(BombPointVar);
		SW_Malloc_Struct(sPON_AREA,theStruct.BombPointVar,BombPointVar,theStruct.BombPointNum,BombPointNum);

		AveLON = theStruct.AveLON;
		AveLAT = theStruct.AveLAT;
		AveHeight = theStruct.AveHeight;
		ErrorValue = theStruct.ErrorValue;
		return *this;
	} 
}aUAV_BombPos;

//无人机杀伤概率静态计算输出参数
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aUAV_KillProb
{
	char* sRID;                //身份字符串
	int     ID;					//实体ID
	int     RadarID;			//雷达ID
	char* MID;
	float  fKillProb;			//杀伤概率

	/*重载构造函数*/
	_ModelBus_aUAV_KillProb()
	{
		sRID          = nullptr;
		ID             = 0;
		RadarID     = 0;
		MID           = nullptr;
		fKillProb     = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aUAV_KillProb()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(MID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aUAV_KillProb(const _ModelBus_aUAV_KillProb &aUAVKill)
	{
		sRID = nullptr;
		MID = nullptr;
		*this = aUAVKill;
	}

	/*重载=*/
	_ModelBus_aUAV_KillProb& operator=(const _ModelBus_aUAV_KillProb& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		RadarID = theStruct.RadarID;
		ID            = theStruct.ID;

		//SW_Free_Char(MID);
		SW_Malloc_Char(theStruct.MID,MID);

		fKillProb = theStruct.fKillProb;
		return *this;
	} 
}aUAV_KillProb;

//雷达仿真参数
typedef struct _ModelBus_RADAR_CFG_PARAM
{
	double		fPt;				//雷达发射功率，单位：w
	double		fGt;				//雷达天线增益，单位：dB
	double		fGtSL1;				//天线第一旁瓣增益，单位：dB
	double		fGtSLm;				//天线平均旁瓣增益，单位：dB
	double		fAzBW;				//方位面主瓣波束宽度，单位：度
	double		fElBW;				//俯仰面主瓣波束宽度，单位：度
	double		fBWSL1;				//天线第一旁瓣波束宽度，单位：度
	int			eScanType;			//天线扫描类型,0,圆扫;1,扇扫;2,相控阵;3,固定;
	double		fAzScanRate;		//天线方位向扫描速度，单位：度/s
	double		fSettleTime;		//波束驻留时间，单位：s(相控阵雷达有效)
	double		fAziMax;			//方位角最大值，单位：度
	double		fAziMin;			//方位角最小值，单位：度
	double		fEleMax;			//俯仰角最大值，单位：度
	double		fEleMin;			//俯仰角最小值，单位：度
	double		fPw;				//脉宽，单位：s
	double		fBw;				//信号带宽，单位：Hz
	int	ePRIT;				//PRI类型,参见DKDMS::Enum_PRIT
	double		fPRI;				//脉冲重复间隔，单位：s
	int	eRFT;				//射频类型，参见DKDMS::Enum_RFT
	int			iRFNum;				//载频个数
	double		fRF[64];			//雷达工作频率，单位：Hz
	int			iPulseNum;			//积累脉冲数
	int	ePOT;				//极化类型，参见DKDMS::Enum_POT
	double		fD0;				//检测因子（最小可检测信噪比），单位：dB
	double		fLt;				//发射损失，单位：dB
	double		fLr;				//接收损失，单位：dB
	double		fLs;				//其它损耗，单位：dB
	double		fFn;				//噪声系数，单位: dB

	int  eRadarSort;          //雷达功能用途，参见DKDMS::Enum_RadarSort
	int  ePlatType;           //搭载平台类型，参见DKDMS::Enum_PlatType

	/*重载构造函数*/
	_ModelBus_RADAR_CFG_PARAM()
	{
		fPt = -1; //负数无效
		fGt = -1;
		fGtSL1 = 0; //旁瓣增益是相对主瓣增益的值，应为负数
		fGtSLm = 0; //旁瓣增益是相对主瓣增益的值，应为负数
		fAzBW = -1;
		fElBW = -1;
		fBWSL1 = -1;
		eScanType = -1;
		fAzScanRate = -1;
		fSettleTime = -1;
		fAziMax = -1;
		fAziMin = -1;
		fEleMax = -1;
		fEleMin = -1;
		fPw = -1;
		fBw = -1;
		ePRIT = -1;
		fPRI = -1;
		eRFT = -1;
		iRFNum = -1;
		memset(fRF, -1, sizeof(double) * 64);	
		iPulseNum = -1;
		ePOT = -1;
		fD0 = -1;
		fLt = -1;
		fLr = -1;
		fLs = -1;
		fFn = -1;
		eRadarSort = 255;
		ePlatType  = 255;
	}

}RadarCfgPara;

typedef struct _ModelBus_aRadarCfgPara
{
	char* sRID;	//身份字符串
	int	RadarID;	//雷达ID
	RadarCfgPara CfgPara;

	/*重载构造函数*/
	_ModelBus_aRadarCfgPara()
	{
		sRID          = nullptr;
		RadarID       = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aRadarCfgPara()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRadarCfgPara(const _ModelBus_aRadarCfgPara &theStruct)
	{
		sRID = nullptr;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_aRadarCfgPara& operator=(const _ModelBus_aRadarCfgPara& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		RadarID = theStruct.RadarID;

		return *this;
	}
}aRadarCfgPara;

//// 天线频率特性
//struct AntennaRFParam
//{
//	float	RF;						// 工作频率
//	float	Sensity;						// 天线增益
//};
//
//typedef struct _ModelBus_RadarReconBandPara
//{
//	float	MaxRF;							// 工作频段上限 MHz
//	float	MinRF;							// 工作频段下限 MHz
//	float Sensity;							// 接收机灵敏度（如果是系统灵敏度，则天线增益无效）单位：dBW
//	float Gr;									// 天线增益，单位：dB
//	float	HBeamWidth;				// 天线水平波束宽度，单位：度
//	float	VBeamWidth;				// 天线垂直波束宽度，单位：度
//	float MeasureAzPrecision;	// 测向精度，单位：度
//	float MeasureRFPrecision;	// 测频精度，单位：MHz
//	float LocationPrecision;		// 定位精度
//
//	float	MaxPW;							// "脉冲宽度测量上限" 单位="us"
//	float	MinPW;							// "脉冲宽度测量下限" 单位="us"
//	float	MaxPRF;							// "脉冲重复频率测量上限" 单位="Hz"
//	float	MinPRF;							// "脉冲重复频率测量下限" 单位="Hz"
//	float	MaxASP;							// "天线扫描周期测量上限" 单位="s"
//	float	MinASP;							// "天线扫描周期测量下限" 单位="s"
//
//	bool bUseSingleSensity;     //是否使用唯一灵敏度，是则采用Sensity、Gr组合，否则使用SensityArr中具体分段的系统灵敏度
//	int    SensityNum;
//	AntennaRFParam SensityArr[100];//频率由小变大，对应每个子频段的上限值
//
//	//空域覆盖能力，地面系统一般为单一覆盖范围；机载系统可能有多个覆盖范围
//	int 	CoverRangeNum;			// 覆盖空域数目
//	sCOVER_RANGE CRange[6];
//
//	_ModelBus_RadarReconBandPara()
//	{
//		MaxRF = -1;
//		MinRF = -1;
//		Sensity = 0;
//		Gr = -1;
//		HBeamWidth = -1;
//		VBeamWidth = -1;
//		MeasureAzPrecision = -1;
//		MeasureRFPrecision = -1;
//		LocationPrecision = -1;
//		CoverRangeNum = 0;
//	}
//
//}RadarReconBandPara;

// 频率-灵敏度特性
struct AntennaRFParam
{
	float	RF;						// 子频段上限值，MHz
	float	Sensity;				// 子频段对应的常规检测系统灵敏度，dBW
	float	RelatSensity;           // 子频段对应的相关检测系统灵敏度，dBW
};

struct CoverRange
{
	int		Flag;		// 空域标识：0-前向，1-后向，3-左，4-右，其他-未知；
	float	MaxAz;		// 方位覆盖范围，最大方位角 单位：度 范围：0~360
	float	MinAz;			// 最小方位角 单位：度
	float	MaxEl;			// 俯仰覆盖范围，最大俯仰角 单位：度 范围：-90~90
	float	MinEl;			// 最小俯仰角 单位：度
	float MaxDis;		// 最大作用距离 单位：千米 （修改单位为km，zm 20170515）
	float MinDis;		// 最小作用距离 单位：千米 （修改单位为km，zm 20170515）
};

struct RadarScoutBandParam
{
	float	MaxRF;							// 工作频段上限 MHz
	float	MinRF;							// 工作频段下限 MHz
	float	Sensity;						// 接收机灵敏度（如果是系统灵敏度，则天线增益无效）单位：dBW
	float	Gr;								// 天线增益 dB
	float	Lr;								// 接收损耗 dB
	float	HBeamWidth;						// 天线水平波束宽度，单位：度
	float	VBeamWidth;						// 天线垂直波束宽度，单位：度
	float	MeasureAzPrecision;				// 测向精度，单位：度
	float	MeasureRFPrecision;				// 测频精度，单位：MHz
	//add by chenzh20200416
	int		Loc_mode;						//作为主站时的定位体制：0-无定位,-1-不进行定位计算,1-测向交叉定位,2-时差定位,3-交叉+时差定位
	int		Doa_mode;						// 测向的体制，-1-直接读取，0-比幅测向，1-干涉仪测向
	float	MeacureDisPrecision;			// 测距精度，单位：%R
	float	MeasureDTOAPrecision;			// 测时差精度，单位：us
	float	MeasureDFOAPrecision;			// 测频差精度，单位：Hz
	
	float	LocationPrecision;				// 定位精度

	float	MaxPW;							// "脉冲宽度测量上限" 单位="us"
	float	MinPW;							// "脉冲宽度测量下限" 单位="us"
	float	MaxPRF;							// "脉冲重复频率测量上限" 单位="Hz"
	float	MinPRF;							// "脉冲重复频率测量下限" 单位="Hz"
	float	MaxASP;							// "天线扫描周期测量上限" 单位="s"
	float	MinASP;							// "天线扫描周期测量下限" 单位="s"

	int bUseSingleSensity; //1-使用唯一灵敏度，是则采用Sensity/RelatSensity、Gr组合；0-使用SensityArr中具体分段的系统灵敏度
	int SensityNum;
	AntennaRFParam SensityArr[100];//注意：分段区间需在MinRF~MaxRF

	//空域覆盖能力，地面系统一般为单一覆盖范围；机载系统可能有多个覆盖范围
	int 	CoverRangeNum;			// 覆盖空域数目 <=6
	CoverRange CRange[6];

    float	SLGain;							// 天线平均旁瓣增益 dB
	float	RelatSensity;				    // 接收机相关检测灵敏度（如果是系统灵敏度，则天线增益无效）单位：dBW
	bool    bOTHAbility;                    //是否有超视距ZC能力
	int     RadarLOSNum;                    //仅能视距ZC的雷达种类数目
	int     RadarLOS[64];                   //仅能视距ZC的雷达，bOTHAbility为true时有效，搭载平台类型*1000+雷达类型
	bool    bCalcRadarSlm;                  //是否对副瓣ZC,是：通视条件下计算对副瓣的ZC能力

    RadarScoutBandParam()
	{
		//memset(this,0,sizeof(RadarScoutBandParam));	//memset在unix下遇到崩溃问题，不解啊	zm20180716

		MaxRF = 0;
		MinRF = 0;
		Sensity = 0;
		Gr = 0;
		Lr = 0;
		HBeamWidth = 0;
		VBeamWidth = 0;
		MeasureAzPrecision = 0;
		MeasureRFPrecision = 0;
		Loc_mode=-1;
		MeacureDisPrecision = 0;	
		MeasureDTOAPrecision = 0;	
		MeasureDFOAPrecision = 0;

 		LocationPrecision = 0;
		MaxPW = 0;
		MinPW = 0;
		MaxPRF = 0;
		MinPRF = 0;
		MaxASP = 0;
		MinASP = 0;

		bUseSingleSensity = false;
		SensityNum = 0;
		CoverRangeNum = 0;

		SLGain = 0;			
		RelatSensity = 0;	
		bOTHAbility = false;    
		RadarLOSNum = 0;    
		memset(RadarLOS, 0x00, sizeof(int) * 64);   
		bCalcRadarSlm = false; 
		Doa_mode = -1;
	} 
};

typedef struct _ModelBus_RadarReconCfgPara
{
	int			PlatType;					// 名称="平台类型" 描述="0,未知;1,机载;2,舰载;3,地面固定"
	int		   ScanType;			// 天线扫描类型,0,圆扫;1,扇扫;2,相控阵;3,固定;
	float		   AzScanRate;		// 天线方位向扫描速度，单位：度/s
	float		   PulseNum;			// 方位快速可靠搜索：要求收到最少脉冲个数为n
	int		   POT;				   // 极化类型

	int           ReconType;          //2300用，ZC类型，0：威胁告警，1：ESM，2：HGESM
	int		   RFBandNum;		   // 工作频段个数  <=10
	RadarScoutBandParam ReconBandParam[10];	

	_ModelBus_RadarReconCfgPara()
	{
		PlatType = -1;
		ScanType = -1;
		AzScanRate = -1;
		PulseNum = 0;
		POT = -1;
		RFBandNum = 0;
		ReconType = -1;
	}
}RadarReconCfgPara;

typedef struct _ModelBus_aRadarReconCfgPara
{
	char* sRID;	//身份字符串
	int	ID;		//装备ID
	RadarReconCfgPara CfgPara;

	/*重载构造函数*/
	_ModelBus_aRadarReconCfgPara()
	{
		ID    = 0;
		sRID  = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aRadarReconCfgPara()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRadarReconCfgPara(const _ModelBus_aRadarReconCfgPara &theStruct)
	{
		sRID = nullptr;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_aRadarReconCfgPara& operator=(const _ModelBus_aRadarReconCfgPara& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ID = theStruct.ID;

		return *this;
	}
}aRadarReconCfgPara;

typedef struct _ModelBus_RadarJamBandPara
{
	float	MaxRF;					// 工作频段上限 MHz
	float	MinRF;					// 工作频段下限 MHz
	float	HBeamWidth;				// 天线水平波束宽度
	float	VBeamWidth;				// 天线垂直波束宽度	
	float   JamMaxRange;				// 最大GR距离 单位：米
	float   JamMinRange;				// 最小GR距离 单位：米
	int	    JamMaxNum;					// GR最大目标数

	//空域覆盖能力，地面系统一般为单一覆盖范围；机载系统可能有多个覆盖范围
	int 	CoverRangeNum;			// 覆盖空域数目
	sCOVER_RANGE CRange[6];

	_ModelBus_RadarJamBandPara()
	{
		MaxRF = -1;
		MinRF = -1;
		HBeamWidth = -1;
		VBeamWidth = -1;
		JamMaxRange = -1;
		JamMinRange = -1;
		JamMaxNum = -1;
		CoverRangeNum = 0;
	}
}RadarJamBandPara;

typedef struct _ModelBus_RadarJamCfgPara
{
	int              ECMMode;       //2300用，ECM工作模式，0：关机，1：ECM，2：HPECM
	int              JamMax;        //最大GR数目
	int			     RFBandNum;		// 工作频段个数  
	RadarJamBandPara JamBandParam[10];	

	_ModelBus_RadarJamCfgPara()
	{
		JamMax    = -1;
		ECMMode   = -1;
		RFBandNum = 0;
	}
}RadarJamCfgPara;

typedef struct _ModelBus_aRadarJamCfgPara
{
	char* sRID;	//身份字符串
	int	ID;		//装备ID
	RadarJamCfgPara CfgPara;

	/*重载构造函数*/
	_ModelBus_aRadarJamCfgPara()
	{
		ID            = 0;
		sRID          = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_aRadarJamCfgPara()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aRadarJamCfgPara(const _ModelBus_aRadarJamCfgPara &theStruct)
	{
		sRID          = nullptr;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_aRadarJamCfgPara& operator=(const _ModelBus_aRadarJamCfgPara& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		ID = theStruct.ID;

		return *this;
	}
}aRadarJamCfgPara;

//GR交互信息，有无发出GR均会输出，而aJAM_PARA只有发出GR时才会输出
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_aJAM_OUT_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	int			RadarID;		//目标雷达ID
	float		LON;			//经度，单位：度
	float		LAT;			//纬度，单位：度
	float		Height;			//高度，单位，米（m）
	float		ERP;			//等效辐射功率，单位：W
	float		fRFMin;			//射频值，单位：MHz
	float		fRFMax;			//射频值，单位：MHz

	/*重载构造函数*/
	_ModelBus_aJAM_OUT_PARA()
	{
		sRID    = nullptr;
		ID      = 0;
		RadarID = 0;
		LON     = 0;
		LAT     = 0;
		Height  = 0;
		ERP     = 0;
		fRFMin  = 0;
		fRFMax  = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aJAM_OUT_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aJAM_OUT_PARA(const _ModelBus_aJAM_OUT_PARA &jam)
	{
		sRID = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aJAM_OUT_PARA& operator = (const _ModelBus_aJAM_OUT_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID      = theStruct.ID;
		RadarID = theStruct.RadarID;
		LON     = theStruct.LON;
		LAT     = theStruct.LAT;
		Height  = theStruct.Height;
		ERP     = theStruct.ERP;
		fRFMin  = theStruct.fRFMin;
		fRFMax  = theStruct.fRFMax;

		return *this;
	}

}aJAM_OUT_PARA;

//对导弹的TC结果(子集)
typedef struct _ModelBus_sMissile_Detect_Rlt
{
	int    iTrgID;  //导弹ID
	char*  sTrgName;//导弹名称
	double dbTrgRCS;//假设的导弹RCS
	double dbDist;  //TC距离，unit:m

	/*重载构造函数*/
	_ModelBus_sMissile_Detect_Rlt()
	{
		sTrgName = nullptr;
		iTrgID   = 0;
		dbTrgRCS = 0;
		dbDist   = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sMissile_Detect_Rlt()
	{
		SW_Free_Char(sTrgName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sMissile_Detect_Rlt(const _ModelBus_sMissile_Detect_Rlt &rlt)
	{
		sTrgName = nullptr;
		*this = rlt;
	}

	/*重载=*/
	_ModelBus_sMissile_Detect_Rlt& operator=(const _ModelBus_sMissile_Detect_Rlt& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sTrgName);
		SW_Malloc_Char(theStruct.sTrgName,sTrgName);

		iTrgID    = theStruct.iTrgID;
		dbTrgRCS  = theStruct.dbTrgRCS;
		dbDist    = theStruct.dbDist;

		return *this;
	}
}sMissile_Detect_Rlt;

//对导弹的TC结果(总集)
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sMissile_Detect_Multi_Rlt
{
	char*				 sRID;		    //身份字符串
	double               dbSimuTime;    //仿真时间，s
	int					 RadarID;	    //实体ID 
	int					 TargetNum;	    //目标数 
	sMissile_Detect_Rlt* TargetDectInfo;//目标ID

	/*重载构造函数*/
	_ModelBus_sMissile_Detect_Multi_Rlt()
	{
		sRID           = nullptr;
		dbSimuTime = 0;
		RadarID        = 0;
		TargetNum      = 0;
		TargetDectInfo = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sMissile_Detect_Multi_Rlt()
	{
		SW_Free_Char(sRID);
		SW_Delete(TargetDectInfo);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sMissile_Detect_Multi_Rlt(const _ModelBus_sMissile_Detect_Multi_Rlt &rlt)
	{
		sRID = nullptr;
		TargetDectInfo = nullptr;
		*this = rlt;
	}

	/*重载=*/
	_ModelBus_sMissile_Detect_Multi_Rlt& operator=(const _ModelBus_sMissile_Detect_Multi_Rlt& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		RadarID       = theStruct.RadarID;
		TargetNum     = theStruct.TargetNum;
		dbSimuTime    = theStruct.dbSimuTime;

		//SW_Delete(TargetDectInfo);
		SW_Malloc_Struct(sMissile_Detect_Rlt,theStruct.TargetDectInfo,TargetDectInfo,theStruct.TargetNum,TargetNum);

		return *this;
	}  
}sMissile_Detect_Multi_Rlt;

//add 20160822 begin
typedef struct _ModelBus_JamSrc
{
	int			nEquipID;			//GR装备编号
	char*		szEquipType;		//GR装备型号

	/*重载构造函数*/
	_ModelBus_JamSrc()
	{
		nEquipID	= 0;
		szEquipType = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_JamSrc()
	{
		SW_Free_Char(szEquipType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_JamSrc(const _ModelBus_JamSrc &jamSrc)
	{
		szEquipType = nullptr;
		*this = jamSrc;
	}

	/*重载=*/
	_ModelBus_JamSrc& operator = (const _ModelBus_JamSrc& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		nEquipID = theStruct.nEquipID;

		//SW_Free_Char(szEquipType);
		SW_Malloc_Char(theStruct.szEquipType, szEquipType);

		return *this;
	}
}sJamSrc;

//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_EquipJamed
{
	char*		sRID;				//身份字符串
	int			nEquipID;		    //雷达编号
	char*		szEquipType;		//雷达型号
	float		fStartJamedFreq;	//受扰起始频率
	float		fEndJamedFreq;		//受扰终止频率
	int			nJamSrcNum;			//GR源数量
	sJamSrc*	pJamSrc;			//GR结果

		/*重载构造函数*/
	_ModelBus_EquipJamed()
	{
		sRID		= nullptr;
		nEquipID    = 0;
		szEquipType = nullptr;
		fStartJamedFreq	= 0.f;
		fEndJamedFreq	= 0.f;
		nJamSrcNum		= 0;
		pJamSrc			= nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_EquipJamed()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(szEquipType);

		SW_Delete(pJamSrc);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EquipJamed(const _ModelBus_EquipJamed &jam)
	{
		sRID		= nullptr;
		szEquipType	= nullptr;
		pJamSrc		= nullptr;

		*this = jam;
	}

	/*重载=*/
	_ModelBus_EquipJamed& operator = (const _ModelBus_EquipJamed& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID, sRID);

		nEquipID      = theStruct.nEquipID;

		//SW_Free_Char(szEquipType);
		SW_Malloc_Char(theStruct.szEquipType, szEquipType);

		fStartJamedFreq	= theStruct.fStartJamedFreq;
		fEndJamedFreq   = theStruct.fEndJamedFreq;
		nJamSrcNum		= theStruct.nJamSrcNum;
		
		//SW_Delete(pJamSrc);
		SW_Malloc_Struct(sJamSrc, theStruct.pJamSrc, pJamSrc, theStruct.nJamSrcNum, nJamSrcNum);

		return *this;
	}
}aRadarJamed;
// add 20160822 end

// 783  add struct sIFFJAM_Set_Para
typedef struct _ModelBus_sIFFJAM_Set_Para   
{
	char* sRID;	//身份字符串
	int	ID;		//装备ID
	int PlatID; //平台ID
	DKDMS::Enum_ATT	ATT;							//敌我属性
	char*		EquipmentName;	//设备名称
	char*		EquipmentType;	//设备型号
	float	fSiteLon;		//本站经度，单位：度（o）
	float	fSiteLat;		//本站纬度，单位：度（o）
	float   fHeight;        // 本站 高度  单位: 米
	float	fAntTurnStartAngle;		//地面站GR站天线 扇扫起始角  单位：度
	float   fAntTurnEndAngle;           //地面站GR站天线 扇扫结束角  单位：度
	//bool    bJamSite;     // GR站类型   true-地面GR站   false-无人机GR站
	int     iSignal_size;           // 信号强度  1-典型 2-强
	float   sWave_Direction;         // 波束指向 
	int     iSiteState;              // 本站状态 0-关机 1-开机  2-GR
	int     iAntWorkStyle;           // 天线工作方式  固定方位   扇扫  默认 固定方位
	int     iSiteWorkStyle;          // 本站工作样式 ： 伪装 灵巧
	int     iSiteWorkMode;           // 本站工作模式    1-M1 2-M2 3-M3/a 4-M4 5-Mc  6-常规  7-保密 8-混合
	// 灵巧工作方式下，模式有  常规  保密  混合
	// 伪装工作方式下  模式有  1 2 3/a c 4  混合

	/*重载构造函数*/
	_ModelBus_sIFFJAM_Set_Para()
	{
		ID            = 0;
		PlatID        = 0;
		sRID          = nullptr;
		ATT           = DKDMS::Enum_ATT_1;		//敌我属性
		EquipmentName = nullptr;	//设备名称
		EquipmentType = nullptr;
		fSiteLon = 0.0;		//本站经度，单位：度（o）
		fSiteLat = 0.0;		//本站纬度，单位：度（o）
		fHeight = 0.0;      // 本站 高度  单位: 米
		fAntTurnStartAngle = 0.0;		//地面站GR站天线 扇扫起始角  单位：度
		fAntTurnEndAngle = 0.0;           //地面站GR站天线 扇扫结束角  单位：度
		//bJamSite = true;    // 默认 地面GR站
		iSignal_size = 1;           // 信号强度  1 典型 2 强 默认典型
		sWave_Direction = 0;       // 波束指向  默认指向正北
		iSiteState = 2;              // 本站状态 0-关机 1-开机  2-GR
		iAntWorkStyle = 1;           // 天线工作方式  固定方位   扇扫  默认固定方位 
		iSiteWorkStyle = 1;          // 本站工作样式 ： 伪装 灵巧  默认 伪装
		iSiteWorkMode = 1;           // 本站工作模式    1-M1 2-M2 3-M3/a 4-M4 5-Mc  6-常规  7-保密 8-混合
	}

	/*重载析构函数*/
	~_ModelBus_sIFFJAM_Set_Para()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sIFFJAM_Set_Para(const _ModelBus_sIFFJAM_Set_Para &theStruct)
	{
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sIFFJAM_Set_Para& operator=(const _ModelBus_sIFFJAM_Set_Para& theStruct)
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

		ID = theStruct.ID;
		PlatID = theStruct.PlatID;
		ATT = theStruct.ATT;

		fSiteLon = theStruct.fSiteLon;		//本站经度，单位：度（o）
		fSiteLat = theStruct.fSiteLat;		//本站纬度，单位：度（o）
		fHeight = theStruct.fHeight;      // 本站 高度  单位: 米
		fAntTurnStartAngle = theStruct.fAntTurnStartAngle;
		fAntTurnEndAngle = theStruct.fAntTurnEndAngle;
		//bJamSite = theStruct.bJamSite;    // GR站类型   true-地面GR站   false-无人机GR站
		iSignal_size = theStruct.iSignal_size;           // 信号强度  1 典型 2 强 默认典型
		sWave_Direction = theStruct.sWave_Direction;       // 波束指向 
		iSiteState = theStruct.iSiteState;              // 本站状态 开机  待机  工作 撤收  默认待机
		iAntWorkStyle = theStruct.iAntWorkStyle;           // 天线工作方式  固定方位   扇扫  默认固定方位 
		iSiteWorkStyle = theStruct.iSiteWorkStyle;          // 本站工作样式 ： 伪装 灵巧  默认 伪装
		iSiteWorkMode = theStruct.iSiteWorkMode;           // 本站工作模式    1-M1 2-M2 3-M3/a 4-M4 5-Mc  6-常规  7-保密 8-混合

		return *this;
	}
}sIFFJAM_Set_Para;


// 783  add struct sIFFJAM_Get_Para
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sIFFJAM_Get_Para   
{
	char* sRID;	//身份字符串
	int	ID;		//装备ID
	int PlatID; //平台ID
	DKDMS::Enum_ATT	ATT;							//敌我属性
	char*		EquipmentName;	//设备名称
	char*		EquipmentType;	//设备型号
	float	fSiteLon;		//本站经度，单位：度（o）
	float	fSiteLat;		//本站纬度，单位：度（o）
	float   fHeight;        // 本站 高度  单位: 米
	float	fAntTurnStartAngle;		//地面站GR站天线 扇扫起始角  单位：度
	float   fAntTurnEndAngle;           //地面站GR站天线 扇扫结束角  单位：度
	//bool    bJamSite;     // GR站类型   true-地面GR站   false-无人机GR站
	int     iSignal_size;           // 信号强度  0 典型 1 强
	float   sWave_Direction;         // 波束指向 
	int     iSiteState;              // 本站状态 开机  待机  工作 撤收
	int     iAntWorkStyle;           // 天线工作方式  固定方位   扇扫  默认 固定方位
	int     iSiteWorkStyle;          // 本站工作样式 ： 伪装 灵巧
	int     iSiteWorkMode;           // 本站工作模式    1-M1 2-M2 3-M3/a 4-M4 5-Mc  6-常规  7-保密 8-混合
	// 灵巧工作方式下，模式有  常规  保密  混合
	// 伪装工作方式下  模式有  1 2 3/a c 4  混合

	/*重载构造函数*/
	_ModelBus_sIFFJAM_Get_Para()
	{
		ID            = 0;
		PlatID        = 0;
		sRID          = nullptr;
		ATT           = DKDMS::Enum_ATT_1;							//敌我属性
		EquipmentName = nullptr;	//设备名称
		EquipmentType = nullptr;	//设备型号
		fSiteLon = 0.0;		//本站经度，单位：度（o）
		fSiteLat = 0.0;		//本站纬度，单位：度（o）
		fHeight = 0.0;      // 本站 高度  单位: 米
		fAntTurnStartAngle = 0.0;
		fAntTurnEndAngle = 0.0;
		iSignal_size = 1;           // 信号强度  1 典型 2 强 默认典型
		sWave_Direction = 0;       // 波束指向  默认指向正北
		iSiteState = 2;              // 本站状态 开机  待机  工作 撤收  默认待机
		iAntWorkStyle = 1;           // 天线工作方式  固定方位   扇扫  默认固定方位 
		iSiteWorkStyle = 1;          // 本站工作样式 ： 伪装 灵巧  默认 伪装
		iSiteWorkMode = 1;           // 本站工作模式    1-M1 2-M2 3-M3/a 4-M4 5-Mc  6-常规  7-保密 8-混合
	}

	/*重载析构函数*/
	~_ModelBus_sIFFJAM_Get_Para()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sIFFJAM_Get_Para(const _ModelBus_sIFFJAM_Get_Para &theStruct)
	{
		sRID          = nullptr;
		EquipmentName          = nullptr;
		EquipmentType          = nullptr;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sIFFJAM_Get_Para& operator=(const _ModelBus_sIFFJAM_Get_Para& theStruct)
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

		ID = theStruct.ID;
		PlatID = theStruct.PlatID;
		ATT = theStruct.ATT;

		fSiteLon = theStruct.fSiteLon;		//本站经度，单位：度（o）
		fSiteLat = theStruct.fSiteLat;		//本站纬度，单位：度（o）
		fHeight = theStruct.fHeight;      // 本站 高度  单位: 米
		fAntTurnStartAngle = theStruct.fAntTurnStartAngle;
		fAntTurnEndAngle = theStruct.fAntTurnEndAngle;
		iSignal_size = theStruct.iSignal_size;           // 信号强度  1 典型 2 强 默认典型
		sWave_Direction = theStruct.sWave_Direction;       // 波束指向 
		iSiteState = theStruct.iSiteState;              // 本站状态 开机  待机  工作 撤收  默认待机
		iAntWorkStyle = theStruct.iAntWorkStyle;           // 天线工作方式  固定方位   扇扫  默认固定方位 
		iSiteWorkStyle = theStruct.iSiteWorkStyle;          // 本站工作样式 ： 伪装 灵巧  默认 伪装
		iSiteWorkMode = theStruct.iSiteWorkMode;           // 本站工作模式    1-M1 2-M2 3-M3/a 4-M4 5-Mc  6-常规  7-保密 8-混合

		return *this;
	}
}sIFFJAM_Get_Para;


//783  add struct _ModelBus_sIFFJAM_RESULT
typedef struct _ModelBus_aIFFJAM_RESULT
{
	char*	sRID;								//身份字符串
	int		TargetID;						//ZC/GR设备ID
	bool    beffect;    // GR效果
	float   fRespProbability;   // 应答概率 * 100     如 51.1% 值为 51.1 

	/*重载构造函数*/
	_ModelBus_aIFFJAM_RESULT()
	{
		sRID          = nullptr;
		TargetID       = 0;
		beffect = false;
		fRespProbability = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aIFFJAM_RESULT()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aIFFJAM_RESULT(const _ModelBus_aIFFJAM_RESULT &jam)
	{
		sRID = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aIFFJAM_RESULT& operator=(const _ModelBus_aIFFJAM_RESULT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		TargetID         = theStruct.TargetID;

		beffect = theStruct.beffect;
		fRespProbability = theStruct.fRespProbability;
		return *this;
	}
}aIFFJAM_RESULT;

//783  add struct _ModelBus_aIFFJAM_RESULT
//! @Properties(description=输出, appType=modelOut)
typedef struct _ModelBus_sIFFJAM_RESULT
{
	char*	sRID;								//身份字符串
	int		JammerID;						//ZC/GR设备ID
	//bool    bJamSite;     // GR站类型   true-地面GR站   false-无人机GR站
	int		nResultNum;					//结果个数
	aIFFJAM_RESULT *pReconResult;	//ZC结论数据

	/*重载构造函数*/
	_ModelBus_sIFFJAM_RESULT()
	{
		sRID          = nullptr;
		JammerID       = 0;
		nResultNum      = 0;	
		pReconResult = nullptr;
	}

	/*重载析构函数*/
	~_ModelBus_sIFFJAM_RESULT()
	{
		SW_Free_Char(sRID);
		SW_Delete(pReconResult);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sIFFJAM_RESULT(const _ModelBus_sIFFJAM_RESULT &jam)
	{
		sRID = nullptr;
		pReconResult = nullptr;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sIFFJAM_RESULT& operator=(const _ModelBus_sIFFJAM_RESULT& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		JammerID         = theStruct.JammerID;

		nResultNum         = theStruct.nResultNum;
		//SW_Delete(pReconResult);
		SW_Malloc_Struct(aIFFJAM_RESULT,theStruct.pReconResult,pReconResult,theStruct.nResultNum,nResultNum);

		return *this;
	}
}sIFFJAM_RESULT;

typedef struct _ModelBus_aIFFJAM_OBJECT
{
	char*	sRID;			//身份字符串
	int		PlatID;			//仿真平台ID号 
	float	fLon;			//经度，单位：度
	float	fLat;			//纬度，单位：度
	float	fHeight;		//高度，单位：米（m）
	float	fSpeed;			//运动速度 单位：米/秒（m/s）
	float	fDir;			//运动方位角，单位：度
	float	fPitch;			//运动俯仰角，单位：度
	int     iWorkMode;      // 1-M1 2-M2 3-M3/a 4-M4 5-Mc  6-常规  7-保密 8-混合

	/*重载构造函数*/
	_ModelBus_aIFFJAM_OBJECT()
	{
		sRID          = nullptr;
		PlatID        = 0;
		fLon          = 0.0;
		fLat          = 0.0;
		fHeight       = 0.0;
		fSpeed        = 0.0;
		fDir          = 0.0;
		fPitch        = 0.0;
		iWorkMode     = 1;
	}

	/*重载析构函数*/
	~_ModelBus_aIFFJAM_OBJECT()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aIFFJAM_OBJECT(const _ModelBus_aIFFJAM_OBJECT &plat)
	{
		sRID = nullptr;
		*this = plat;
	}

	/*重载=*/
	_ModelBus_aIFFJAM_OBJECT& operator=(const _ModelBus_aIFFJAM_OBJECT& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		PlatID        = theStruct.PlatID;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		fSpeed        = theStruct.fSpeed;
		fDir          = theStruct.fDir;
		fPitch        = theStruct.fPitch;
		iWorkMode     = theStruct.iWorkMode;
		return *this;
	}
}aIFFJAM_OBJECT;

#pragma pack()

#endif

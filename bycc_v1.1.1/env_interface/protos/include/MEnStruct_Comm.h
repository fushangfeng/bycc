/**************************************************************************
**名    称:	通信及通信对抗领域模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.1		按照年(个数位)月日组合的方式	**
**版    本:	2024.12.13  											**
*************************************************************************/

#include "MEnStruct_Macros.h"
#include "MEnStruct_Common.h"

#ifndef MEN_STRUCT_Comm
#define MEN_STRUCT_Comm

#include <string.h>
#pragma pack(1)
//________________________通信辐射源__________________________________________//
//通信辐射源模型想定初始化参数
typedef struct _ModelBus_sCOM_SET_PARA
{
	char* sRID;				//身份字符串
	int   ComID;			//辐射源ID
	int   PlatID;			//搭载平台ID号
	char* EquipmentName;    //设备名称
	char* EquipmentType;    //设备型号
	DKDMS::Enum_PlatType  PlatType;//搭载平台类型
	DKDMS::Enum_ATT ATT;			//敌我属性
	float LON;				//经度 unit=度
	float LAT;				//纬度  unit=度
	float Height;			//高度 unit=米
	float StartRF;			//起始频率, unit=MHz 本次任务的起始频率，非装备最小工作频率；若小于等于0，则用模型内置默认值
	float EndRF;			//终止频率, unit=MHz 本次任务的起始频率，非装备最大工作频率；若小于等于0，则用模型内置默认值
	int FreqNo;                //频点个数FreqNo int >=0;若小于等于0，则用模型内置默认频率集
	float *FreqSet;  //频率集 FreqSet int[] 个数为频点个数  unit=MHz 频点个数：2n,最大1024
	int hopRate;     //跳频跳速 跳/s	[-1,10~2000] 	若小于等于0，则用模型内置默认跳速 
	float Bandwidth;		//! @Properties(description=通信信号带宽, unit=KHz) 若小于等于0，则用模型内置默认带宽
	DKDMS::Enum_CMD CMD;			//! @Properties(description=通信信号调制样式, defaultValue=1) 若为0，则模型计算时采用内部默认值
	DKDMS::Enum_SignalType SignalType;	//! @Properties(description=信号类型, defaultValue=5009) 若为0，则模型计算时采用内部默认值
	DKDMS::Enum_SignalworkMode workMode; // 通信信号工作模式 若为0，则模型计算时采用内部默认值
	bool  bCenterFlag;			//! @Properties(description=中心站标记, defaultValue=1) 收发标记 
	float ComAreaHeight;        //! @Properties(description=畅通区高度, defaultValue=5000) 标称高度
	bool  bUseTrans;        //! 仅短波设备有效，是否调用外部天波传播算法 可选
	int iHour;	    //作战时间小时时刻 启动推演时对应的作战时间-小时时刻；仅短波设备有效（用于影响传播衰减），随着推演过程模型内部自行更新时刻，其它波段可选
	// 计算畅通区时的起始方位角，度，0~360，正北为0，顺时针增加
	float fCalcStartAz;                 //! @Properties(description=起始方位角, unit=度, defaultValue=0) 0~360	正北为0，顺时针增加
	// 计算畅通区时的终止方位角，度，0~360，正北为0，顺时针增加
	float fCalcEndAz;                   //! @Properties(description=终止方位角, unit=度, defaultValue=360) 0~360	正北为0，顺时针增加
	int	  iRelationRadioNo; //! RelationRadioID关联电台ID个数
	int	  *pRelationRadioID; //! RelationRadioID关联电台ID

	/*重载构造函数*/
	_ModelBus_sCOM_SET_PARA()
	{
		sRID = NULL;
		ComID = 0;	
		PlatID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		PlatType = DKDMS::Enum_PlatType_6;
		ATT = DKDMS::Enum_ATT_2;
		LON = 0.;
		LAT = 0.;
		Height = 0.;	
		StartRF = 0.;
		EndRF = 0.;
		FreqNo =0;
		FreqSet = NULL;
		hopRate =0;
		Bandwidth = 0.;
		CMD = DKDMS::Enum_CMD_0;
		SignalType = DKDMS::Enum_SignalType_0;
		workMode = DKDMS::Enum_SignalworkMode_0;
		bCenterFlag = false;
		ComAreaHeight = 0.;
		bUseTrans = false;
		iHour = 0;
		fCalcStartAz = 0.;
		fCalcEndAz = 360.;
		iRelationRadioNo = 0;
		pRelationRadioID = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sCOM_SET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(FreqSet);
		SW_Delete(pRelationRadioID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOM_SET_PARA(const _ModelBus_sCOM_SET_PARA &radioSetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		FreqSet   = NULL;
		pRelationRadioID= NULL;
		*this = radioSetPara;
	}

	/*重载=*/
	_ModelBus_sCOM_SET_PARA& operator=(const _ModelBus_sCOM_SET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		ComID = theStruct.ComID;
		PlatID = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		PlatType = theStruct.PlatType;
		ATT = theStruct.ATT;
		LON = theStruct.LON;
		LAT = theStruct.LAT;
		Height = theStruct.Height;
		StartRF = theStruct.StartRF;
		EndRF = theStruct.EndRF;
		FreqNo = theStruct.FreqNo;;
		SW_Malloc_Float(theStruct.FreqSet,FreqSet,theStruct.FreqNo,FreqNo);
		hopRate = theStruct.hopRate;
		Bandwidth = theStruct.Bandwidth;
		CMD = theStruct.CMD;
		SignalType = theStruct.SignalType;
		workMode = theStruct.workMode;
		bCenterFlag = theStruct.bCenterFlag;
		ComAreaHeight = theStruct.ComAreaHeight;
		bUseTrans   = theStruct.bUseTrans;
		iHour   = theStruct.iHour;
		fCalcStartAz    = theStruct.fCalcStartAz; 
		fCalcEndAz      = theStruct.fCalcEndAz;
		iRelationRadioNo = theStruct.iRelationRadioNo;
		SW_Malloc_Int(theStruct.pRelationRadioID,pRelationRadioID,theStruct.iRelationRadioNo,iRelationRadioNo);
		return *this;
	}
}sCOM_SET_PARA;
// 通信辐射源参数
typedef struct _ModelBus_sCOM_PARA
{
	char* sRID;				//身份字符串
	int  ComID;				// 实体ID	
	int   PlatID;			// 搭载平台ID
	char* EquipmentName;	// 设备名称
	char* EquipmentType;	// 设备型号
	float fSimuTime;        //推演时间
	DKDMS::Enum_PlatType  PlatType;//搭载平台类型，用于选择传播模型  0401	
	DKDMS::Enum_ATT ATT;			// 敌我属性
	DKDMS::Enum_SurvivalState SurvivalState;			// 生存状态
	DKDMS::Enum_WorkState WorkState;			// 工作状态
	float LON;				// 经度
	float LAT;				// 纬度
	float Height;			// 高度	
	DKDMS::Enum_CMD CMD;				// 调制样式
	float Power;				// 功率,W
	DKDMS::Enum_InfoType   InfoType;	// 基带信息类型
	DKDMS::Enum_SignalType SignalType;	// 信号类别
	float StartRF;				// 起始频率,MHz(若用频方式为定频，则为中心频率-带宽/2)
	float EndRF;				// 终止频率,MHz(若用频方式为定频，则为中心频率+带宽/2)
	int FreqNo;                //频点个数FreqNo int >=0;
	MultiPntJamPara *FreqSet;  //频率集 FreqSet int[] 个数为频点个数  unit=MHz
	int MaxHopRate;                //跳频最大跳速 跳/s
	int MinHopRate;                //跳频最小跳速 跳/s
	float DutyRatio;             //占空比
	float fContinueTime;             //持续时间
	bool bCenterFlag;			// 中心站标记
	DKDMS::Enum_WaveTransType WaveTransType;	// 电波传播方式


	/*重载构造函数*/
	_ModelBus_sCOM_PARA()
	{
		sRID = NULL;
		ComID = 0;
		PlatID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		fSimuTime = 0.;
		PlatType = DKDMS::Enum_PlatType_6;
		ATT = DKDMS::Enum_ATT_2;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		WorkState = DKDMS::Enum_WorkState_0;
		LON = 0.;
		LAT = 0.;
		Height = 0.;
		CMD = DKDMS::Enum_CMD_0;
		Power = 0;
		StartRF = 0.;
		EndRF = 0.;
		SignalType = DKDMS::Enum_SignalType_0;
		InfoType   = DKDMS::Enum_InfoType_0;
		FreqNo =0;
		FreqSet = NULL;
		MaxHopRate = 0;
		MinHopRate = 0;
		DutyRatio = 0.;
		fContinueTime = 0.;
		bCenterFlag = false;
		WaveTransType = DKDMS::Enum_WaveTransType_0;

	}

	/*重载析构函数*/
	~_ModelBus_sCOM_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(FreqSet);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOM_PARA(const _ModelBus_sCOM_PARA &radioPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		FreqSet   = NULL;
		*this = radioPara;
	}

	/*重载=*/
	_ModelBus_sCOM_PARA & operator=(const _ModelBus_sCOM_PARA & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);

		ComID = theStruct.ComID;
		PlatID = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		fSimuTime = theStruct.fSimuTime;
		PlatType      = theStruct.PlatType;
		ATT = theStruct.ATT;
		SurvivalState = theStruct.SurvivalState;
		WorkState = theStruct.WorkState;
		LON = theStruct.LON;
		LAT = theStruct.LAT;
		Height = theStruct.Height;
		CMD = theStruct.CMD;
		Power = theStruct.Power;
		SignalType = theStruct.SignalType;
		InfoType   = theStruct.InfoType;
		StartRF = theStruct.StartRF;
		EndRF = theStruct.EndRF;
		FreqNo = theStruct.FreqNo;;
		SW_Malloc_Struct(MultiPntJamPara,theStruct.FreqSet,FreqSet,theStruct.FreqNo,FreqNo);
		MaxHopRate   = theStruct.MaxHopRate;
		MinHopRate = theStruct.MinHopRate;
		DutyRatio = theStruct.DutyRatio;
		fContinueTime = theStruct.fContinueTime;;
		bCenterFlag = theStruct.bCenterFlag;
		WaveTransType = theStruct.WaveTransType;
		
		return *this;
	}
}sCOM_PARA;
//通联电台参数
typedef struct _ModelBus_sRelaRadioPara
{

	int RelationRadioID;		//关联电台ID
	float RelationRadioLON;				// 经度
	float RelationRadioLAT;				// 纬度
	float RelationRadioHeight;			// 高度
	float isr;			// 干信比
	float errorRate;			// 误码率
	/*重载构造函数*/
	_ModelBus_sRelaRadioPara()
	{

		RelationRadioID = 0;
		RelationRadioLON=0.0;
		RelationRadioLAT=0.0;
		RelationRadioHeight=0.0;
		isr=0.0;
		errorRate=0.0;
	}

	/*重载析构函数*/
	~_ModelBus_sRelaRadioPara()
	{

	}

	/*重载拷贝构造函数*/
	_ModelBus_sRelaRadioPara(const _ModelBus_sRelaRadioPara &acommJamBeam)
	{
		*this = acommJamBeam;
	}

	/*重载=*/
	_ModelBus_sRelaRadioPara & operator=(const _ModelBus_sRelaRadioPara & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		RelationRadioID = theStruct.RelationRadioID;
		RelationRadioLON=theStruct.RelationRadioLON;
		RelationRadioLAT=theStruct.RelationRadioLAT;
		RelationRadioHeight=theStruct.RelationRadioHeight;
		isr=theStruct.isr;
		errorRate=theStruct.errorRate;
		return *this;
	}
}sRelaRadioPara;
//通联状态
typedef struct _ModelBus_sComState
{
	char* sRID;				//身份字符串
	int RadioID;			//辐射源ID
	int PlatID;		    	//搭载平台ID号
	char* EquipmentName;    //! @Properties(description=装备名称, alias=equipName) 场景中的名称
	char* EquipmentType;    //装备型号
	float fTime;				//时间 单位：秒(s)
	int RelationRadioNo;         //通联电台个数
	sRelaRadioPara*	pRelationRadioPara;  //通联电台参数

	/*重载构造函数*/
	_ModelBus_sComState()
	{
		sRID = NULL;
		RadioID = 0;
		PlatID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		fTime = 0.0;
		RelationRadioNo = 0;
		pRelationRadioPara = NULL;
		
	}

	/*重载析构函数*/
	~_ModelBus_sComState()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(pRelationRadioPara);

	}

	/*重载拷贝构造函数*/
	_ModelBus_sComState(const _ModelBus_sComState &acommJamBeam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		pRelationRadioPara = NULL;
		*this = acommJamBeam;
	}

	/*重载=*/
	_ModelBus_sComState & operator=(const _ModelBus_sComState & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}


		SW_Malloc_Char(theStruct.sRID,sRID);
		RadioID = theStruct.RadioID;
		PlatID = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		fTime = theStruct.fTime;
		RelationRadioNo  = theStruct.RelationRadioNo;
		SW_Malloc_Struct(sRelaRadioPara,theStruct.pRelationRadioPara,pRelationRadioPara,theStruct.RelationRadioNo,RelationRadioNo);
		return *this;
	}
}sComState;
//通信畅通区参数
typedef struct _ModelBus_CComArea
{	// 通信畅通区
	float	LON1;	// 经度1
	float	LAT1;	// 纬度1
	float	LON2;	// 经度2
	float	LAT2;	// 纬度2
	float	LON3;	// 经度3
	float	LAT3;	// 纬度3
	float	LON4;	// 经度4
	float	LAT4;	// 纬度4

	/*重载构造函数*/
	_ModelBus_CComArea()
	{
		LON1 = 0.;
		LAT1 = 0.;
		LON2 = 0.;
		LAT2 = 0.;
		LON3 = 0.;
		LAT3 = 0.;
		LON4 = 0.;
		LAT4 = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_CComArea()
	{

	}

	/*重载拷贝构造函数*/
	_ModelBus_CComArea(const _ModelBus_CComArea &comArea)
	{
		*this = comArea;
	}

	/*重载=*/
	_ModelBus_CComArea& operator=(const _ModelBus_CComArea& theStruct)
	{
		LON1 = theStruct.LON1;
		LAT1 = theStruct.LAT1;
		LON2 = theStruct.LON2;
		LAT2 = theStruct.LAT2;
		LON3 = theStruct.LON3;
		LAT3 = theStruct.LAT3;
		LON4 = theStruct.LON4;
		LAT4 = theStruct.LAT4;
		return *this;
	}
}CComArea;
//通信畅通区
typedef struct _ModelBus_CommUnblockedArea
{
	char* sRID;				//身份字符串
	int   ComID;			//辐射源ID
	int PlatID;		    	//搭载平台ID号
	char* EquipmentName;    //! @Properties(description=装备名称, alias=equipName) 场景中的名称
	char* EquipmentType;    //装备型号
	float SimuTime;			//仿真时间，动态推演时有效
	int   PtNum;
	CComArea *pComArea;		
	float Height;			// 通信畅通区高度

	/*重载构造函数*/
	_ModelBus_CommUnblockedArea()
	{
		sRID = NULL;
		ComID = 0;	
		PlatID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		SimuTime = 0;
		pComArea = NULL;
		PtNum = 0;
		Height = 0;
	}

	/*重载析构函数*/
	~_ModelBus_CommUnblockedArea()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(pComArea);
	}

	/*重载拷贝构造函数*/
	_ModelBus_CommUnblockedArea(const _ModelBus_CommUnblockedArea &commUnblockedArea)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		pComArea = NULL;
		*this = commUnblockedArea;
	}

	/*重载=*/
	_ModelBus_CommUnblockedArea & operator=(const _ModelBus_CommUnblockedArea & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);
		ComID = theStruct.ComID;
		PlatID = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		SimuTime = theStruct.SimuTime;
		PtNum = theStruct.PtNum;
		SW_Malloc_Struct(CComArea,theStruct.pComArea,pComArea,theStruct.PtNum,PtNum);
		Height = theStruct.Height;
		return *this;
	}
}CommUnblockedArea;
//_______________________________________________________________________________//
//________________________通信对抗ZC_____________________________________________//
//通信ZC装备初始化参数
typedef struct _ModelBus_sCOMRECON_SET_PARA
{
	char* sRID;				//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int   ReconID;			//! @Properties(description=装备ID号, alias=modelId, display=readonly)
	int   PlatID;			//搭载平台ID号
	char* EquipmentName;    //装备名称 场景中的名称
	char* EquipmentType;    //装备型号
	DKDMS::Enum_ATT ATT;			//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作属性, defaultValue=1)
	float		fLon;			//! @Properties(description=经度, alias=lon, unit=度)
	float		fLat;			//! @Properties(description=纬度, alias=lat, unit=度)
	float		fHeight;		//! @Properties(description=高度, alias=hei, unit=米)

	int iHour;	    //作战时间小时时刻 启动推演时对应的作战时间-小时时刻；仅短波设备有效（用于影响传播衰减），随着推演过程模型内部自行更新时刻，其它波段可选
	float	    fStartAZ;       //控守起始方位 度	[0,360]	地面装备有效
	float       fEndAZ;			//控守终止方位 度	[0,360]	地面装备有效
	float	    fAntAngAZ;       //天线法向指向方位角 度	[0,360]	地面装备有效
	float       fAntAngEL;			//天线法向指向俯仰角 度	[-90,90]	地面装备有效
	float       fStartEL;			//控守起始俯仰 [-90,90],100	地面装备有效 为100时用内部默认值
	float       fEndEL;			//控守终止俯仰 [-90,90],100	地面装备有效
	float       fStartRF;			//控守起始频率 兆赫兹 搜索模式时，起、止控守频率小于0，模型内部用默认最大范围；监视时，选取一部分监视频段
	float       fEndRF;			//控守终止频率 兆赫兹 搜索模式时，起、止控守频率小于0，模型内部用默认最大范围；监视时，选取一部分监视频段
	int         RngCalcID;			//计算ZC范围的目标ID 初始值=-1
	int			iKeyPtNum;		//! @Properties(description=关键点个数, display=readonly)
	sKeyPoint	*pKeyPt;		//! 关键点列表
	int	  iCoopStationNum; //协同站个数
	int	  *lCoopStationID; //协同站ID

	/*重载构造函数*/
	_ModelBus_sCOMRECON_SET_PARA()
	{
		sRID = NULL;
		ReconID = 0;	
		PlatID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT = DKDMS::Enum_ATT_2;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		iHour = 0;
		fStartAZ = 0.;
		fEndAZ = 360.;
		fAntAngAZ = 0.;
		fAntAngEL = 0.;
		fStartEL = 100.;
		fEndEL = 100.;
		fStartRF = 0.;
		fEndRF = 0.;
		RngCalcID = 0;
		iKeyPtNum	  = 0;
		pKeyPt		  = NULL;
		iCoopStationNum = 0;
		lCoopStationID = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sCOMRECON_SET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(pKeyPt);
		SW_Delete(lCoopStationID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOMRECON_SET_PARA(const _ModelBus_sCOMRECON_SET_PARA &radioSetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		pKeyPt   = NULL;
		lCoopStationID= NULL;
		*this = radioSetPara;
	}

	/*重载=*/
	_ModelBus_sCOMRECON_SET_PARA& operator=(const _ModelBus_sCOMRECON_SET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		ReconID = theStruct.ReconID;
		PlatID = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		ATT = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		iHour   = theStruct.iHour;
		fStartAZ   = theStruct.fStartAZ;
		fEndAZ   = theStruct.fEndAZ;
		fAntAngAZ   = theStruct.fAntAngAZ;
		fAntAngEL   = theStruct.fAntAngEL;
		fStartEL   = theStruct.fStartEL;
		fEndEL   = theStruct.fEndEL;
		fStartRF   = theStruct.fStartRF;
		fEndRF   = theStruct.fEndRF;
		RngCalcID   = theStruct.RngCalcID;
		iKeyPtNum=theStruct.iKeyPtNum;
		SW_Malloc_Struct(sKeyPoint,theStruct.pKeyPt,pKeyPt,theStruct.iKeyPtNum,iKeyPtNum);
		iCoopStationNum = theStruct.iCoopStationNum;
		SW_Malloc_Int(theStruct.lCoopStationID,lCoopStationID,theStruct.iCoopStationNum,iCoopStationNum);
		return *this;
	}
}sCOMRECON_SET_PARA;
// 通信对抗ZC设备信息输出参数
typedef struct _ModelBus_sCOMRECON_PARA
{
	char* sRID;				//身份字符串
	int ReconID;			//装备ID号 
	DKDMS::Enum_ATT	ATT;		//敌我属性
	char* EquipmentName;	//装备名称
	char* EquipmentType;	//装备类型
	float fLon;				//经度，单位：度
	float fLat;				//纬度，单位：度
	float fHeight;			//高度，单位：米（m）
	int	 PlatID;				//平台ID
	float fTime;			//时间 单位：s
	float	    StartAZ;       //起始方位 度	[0,360]	
	float       EndAZ;			//终止方位 度	[0,360]
	float       fStartEL;			//起始俯仰 [-90,90]
	float       fEndEL;			//终止俯仰 [-90,90]
	float       StartRF;			//起始频率 兆赫兹
	float       EndRF;			//终止频率 兆赫兹
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	DKDMS::Enum_WorkState	WorkState;	//工作属性
	int  WorkMode;  //工作模式 可重构装备适用大模式+小模式，4位16进制数，高两位为大模式，低两位为小模式：0xABcd

	/*重载构造函数*/
	_ModelBus_sCOMRECON_PARA()
	{
		sRID = NULL;
		ReconID = 0;
		ATT = DKDMS::Enum_ATT_1;
		EquipmentName = NULL;
		EquipmentType = NULL;
		fLon = 0.;
		fLat = 0.;
		fHeight = 0.;
		PlatID = 0;
		fTime = 0.;
		StartAZ = 0.;
		EndAZ = 0.;
		fStartEL = 0.;
		fEndEL = 0.;
		StartRF = 0.;
		EndRF = 0.;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		WorkState = DKDMS::Enum_WorkState_0;
		WorkMode = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sCOMRECON_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOMRECON_PARA(const _ModelBus_sCOMRECON_PARA &radioJamPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = radioJamPara;
	}

	/*重载=*/
	_ModelBus_sCOMRECON_PARA & operator=(const _ModelBus_sCOMRECON_PARA & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		ReconID = theStruct.ReconID;
		ATT = theStruct.ATT;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		fLon = theStruct.fLon;
		fLat = theStruct.fLat;
		fHeight = theStruct.fHeight;
		PlatID = theStruct.PlatID;
		fTime = theStruct.fTime;
		StartAZ = theStruct.StartAZ;
		EndAZ = theStruct.EndAZ;
		fStartEL = theStruct.fStartEL;
		fEndEL = theStruct.fEndEL;
		StartRF = theStruct.StartRF;
		EndRF = theStruct.EndRF;
		SurvivalState = theStruct.SurvivalState;
		WorkState = theStruct.WorkState;
		WorkMode = theStruct.WorkMode;
		return *this;
	}
}sCOMRECON_PARA;
//通信对抗ZC区域
typedef struct _ModelBus_COMMRECON_AREA
{
	char* sRID;				//身份字符串
	int   ID;			//装备本身ID
	int TrgID;		    	//目标ID
	float fTime;			//仿真时间，动态推演时有效
	int   PtNum;      //区域个数
	sRECON_POWERPOINT *pComReconArea; //通信对抗ZC区
	float TargetHeight;			// 目标高度

	/*重载构造函数*/
	_ModelBus_COMMRECON_AREA()
	{
		sRID = NULL;
		ID = 0;	
		TrgID = 0;
		fTime = 0.;
		PtNum = 0;
		pComReconArea = NULL;
		TargetHeight = 0;
	}

	/*重载析构函数*/
	~_ModelBus_COMMRECON_AREA()
	{
		SW_Free_Char(sRID);
		SW_Delete(pComReconArea);
	}

	/*重载拷贝构造函数*/
	_ModelBus_COMMRECON_AREA(const _ModelBus_COMMRECON_AREA &Area)
	{
		sRID = NULL;
		pComArea = NULL;
		*this = Area;
	}

	/*重载=*/
	_ModelBus_COMMRECON_AREA & operator=(const _ModelBus_COMMRECON_AREA & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);
		ID = theStruct.ID;
		TrgID = theStruct.TrgID;
		fTime = theStruct.fTime;
		PtNum = theStruct.PtNum;
		SW_Malloc_Struct(sRECON_POWERPOINT,theStruct.pComReconArea,pComReconArea,theStruct.PtNum,PtNum);
		TargetHeight = theStruct.TargetHeight;
		return *this;
	}
}COMMRECON_AREA;
//通信目标信号参数
typedef struct _ModelBus_CommTrgPara
{
	int   TrgID;
	float Bandwidth;			//信号带宽
	DKDMS::Enum_CMD CMD;	//调制样式
	DKDMS::Enum_SignalType  SignalType; //信号类别
	DKDMS::Enum_InfoType  InfoType;  //基带信息类型
	float StartRF;			//起始频率
	float EndRF;			//终止频率
	double Duration;        //信号持续时间
	float fLon;			//目标经度
	float fLat;			//目标纬度
	int iHopRate;			//跳频跳速
	int iNetID;			//网台编号
	int FreqNo;                //频点个数FreqNo int >=0;
	MultiPntJamPara *FreqSet;  //频率集 FreqSet int[] 个数为频点个数  unit=MHz
	float		AZ;								//信号方位，单位：度 
	float		EL;								//信号俯仰，单位：度
	float		DIS;							//信号距离，单位：Km
	DKDMS::Enum_SignalState SignalState;		// 信号活动情况
	float		fAZError;						//方位测量误差
	float		fELError;						//俯仰测量误差
	float		fLocDisError;					//定位距离误差
	float		fCaptureProb;					//截获概率，范围：0~1，

	_ModelBus_CommTrgPara()
	{
		TrgID = 0;
		Bandwidth = 0.;			//信号带
		CMD = DKDMS::Enum_CMD_0;	//
		SignalType = DKDMS::Enum_SignalType_0;
		InfoType = DKDMS::Enum_InfoType_0;
		StartRF = 0.;			//起始频率
		EndRF   = 0.;			//终止频率
		Duration      = 0.;
		fLon      = 0.;
		fLat      = 0.;
		iHopRate      = 0;
		iNetID      = 0;
		FreqNo =0;
		FreqSet = NULL;
		AZ      = 0.;						
		EL      = 0.;						
		DIS     = 0.;					
		SignalState = DKDMS::Enum_SignalState_0;
		fAZError      = 0.;
		fELError      = 0.;
		fLocDisError = 0.;			
		fCaptureProb   = 0.;			
	}
	/*重载析构函数*/
	~_ModelBus_CommTrgPara()
	{
		SW_Delete(FreqSet);
	}

	/*重载拷贝构造函数*/
	_ModelBus_CommTrgPara(const _ModelBus_CommTrgPara &Para)
	{
		FreqSet   = NULL;
		*this = Para;
	}

	/*重载=*/
	_ModelBus_CommTrgPara & operator=(const _ModelBus_CommTrgPara & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		TrgID = theStruct.TrgID;
		Bandwidth = theStruct.Bandwidth;
		CMD = theStruct.CMD;
		SignalType      = theStruct.SignalType;
		InfoType = theStruct.InfoType;
		StartRF = theStruct.StartRF;
		EndRF = theStruct.EndRF;
		Duration = theStruct.Duration;
		fLon = theStruct.fLon;
		fLat = theStruct.fLat;
		iHopRate = theStruct.iHopRate;
		iNetID = theStruct.iNetID;
		FreqNo = theStruct.FreqNo;;
		SW_Malloc_Struct(MultiPntJamPara,theStruct.FreqSet,FreqSet,theStruct.FreqNo,FreqNo);
		AZ   = theStruct.AZ;
		EL = theStruct.EL;
		DIS = theStruct.DIS;
		SignalState = theStruct.SignalState;;
		fAZError = theStruct.fAZError;
		fELError = theStruct.fELError;
		fLocDisError = theStruct.fLocDisError;
		fCaptureProb = theStruct.fCaptureProb;
		return *this;
	}
}CommTrgPara;
//通信对抗ZC结果
typedef struct _ModelBus_sCOMMDETECTPARA 
{
	char* sRID;				//身份字符串
	int   EquipID;			//ZC设备ID
	int   PlatID;			//搭载平台ID号
	char* EquipmentName;    //装备名称
	char* EquipmentType;    //装备型号
	float fTime;			//时间 单位：s
	int   nTrgNum;            //ZC到的信号数量
	CommTrgPara* TrgPara;   //具体信号参数

	/*重载构造函数*/
	_ModelBus_sCOMMDETECTPARA()
	{
		sRID = NULL;
		EquipID = 0;
		PlatID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		fTime = 0;
		nTrgNum = 0;
		TrgPara = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sCOMMDETECTPARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(TrgPara);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOMMDETECTPARA(const _ModelBus_sCOMMDETECTPARA &commJamPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		TrgPara = NULL;
		*this = commJamPara;
	}

	/*重载=*/
	_ModelBus_sCOMMDETECTPARA & operator=(const _ModelBus_sCOMMDETECTPARA & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}


		SW_Malloc_Char(theStruct.sRID,sRID);
		EquipID = theStruct.EquipID;
		PlatID = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		fTime = theStruct.fTime;				
		nTrgNum = theStruct.nTrgNum;
		SW_Malloc_Struct(CommTrgPara,theStruct.TrgPara,TrgPara,theStruct.nTrgNum,nTrgNum);

		return *this;
	}
}sCOMMDETECTPARA;
//_______________________________________________________________________________//
//________________________通信GR_______________________________________________//
//通信GR模型想定初始化参数
typedef struct _ModelBus_sCOMJAM_SET_PARA
{
	char* sRID;				//身份字符串
	int	 JammerID;			//GR机ID
	char* EquipmentName;    //装备名称 场景中的名称
	char* EquipmentType;    //装备型号
	int   PlatID;			//搭载平台ID号
	DKDMS::Enum_PlatType  PlatType;//! @Properties(description=搭载平台类型, defaultValue=6)
	DKDMS::Enum_ATT	   ATT;		//! @Properties(description=敌我属性, alias=iff, display=readonly)
	float fLon;				//! @Properties(description=经度, alias=lon, unit=度)
	float fLat;				//! @Properties(description=纬度, alias=lat, unit=度)
	float fHeight;			//! @Properties(description=高度, alias=hei, unit=米, defaultValue=400)
	DKDMS::Enum_WorkState	WorkState;	    //! @Properties(description=工作属性, defaultValue=1)
	float StartRF;			//! 起始频率	
	float EndRF;			//! 终止频率
	int FreqNo;                //频点个数FreqNo int >=0;
	float *FreqSet;  //频率集 FreqSet int[] 个数为频点个数  unit=MHz
	int iProtectRFNum; //保护频段个数
	ProtectRF *pProtectRFInfo;//保护频段信息
	float JamPointAZ;		//GR波束方位指向 度	[-180,180]	初始指向，根据实装特点，部分装备推演过程中可根据目标位置自动变化
	float JamPointEL;      //GR波束俯仰指向  unit=度 [-90,90]
	DKDMS::Enum_AntennaType AntennaType;//! 仅对短波设备有效，天线类型
	bool  bUseTrans;        //! 仅短波设备有效，是否调用外部天波传播算法
	int iHour;           //作战时间小时时刻 时	[0,23]	启动推演时对应的作战时间-小时时刻；仅短波设备有效（用于影响传播衰减），随着推演过程模型内部自行更新时刻，其它波段可选
	bool bForbidJam;     // 是否强制GR 为true时不进行ZC计算引导，直接辐射GR
	int		        iKeyPtNum;	    //关键点个数
	sKeyPoint*      pKeyPt;			//! 关键点列表
	int iJamComTrgNum;   //需对抗的通信目标个数
	int* pJamComTrgID;   //需对抗的通信目标列表

	/*重载构造函数*/
	_ModelBus_sCOMJAM_SET_PARA()
	{
		sRID = NULL;
		JammerID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		PlatID = 0;
		PlatType = DKDMS::Enum_PlatType_1;
		ATT = DKDMS::Enum_ATT_1;
		fLon = 0.;
		fLat = 0.;
		fHeight = 0.;
		WorkState = DKDMS::Enum_WorkState_0;
		StartRF = 0.;
		EndRF = 0.;
		FreqNo =0;
		FreqSet = NULL;
		iProtectRFNum =0;
		pProtectRFInfo = NULL;
		JamPointAZ = 0.;
		JamPointEL = 0.;
		AntennaType = DKDMS::Enum_AntennaType_0;
		bUseTrans = false;
		iHour	  = 0;
		bForbidJam = false;
		iKeyPtNum	  = 0;
		pKeyPt		  = NULL;
		iJamComTrgNum	  = 0;
		pJamComTrgID		  = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sCOMJAM_SET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(FreqSet);
		SW_Delete(pProtectRFInfo);
		SW_Delete(pKeyPt);
		SW_Delete(pJamComTrgID);
		
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOMJAM_SET_PARA(const _ModelBus_sCOMJAM_SET_PARA &radioJamSetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		FreqSet   = NULL;
		pProtectRFInfo   = NULL;
		pKeyPt		  = NULL;
		pJamComTrgID   = NULL;
		*this = radioJamSetPara;
	}

	/*重载=*/
	_ModelBus_sCOMJAM_SET_PARA & operator=(const _ModelBus_sCOMJAM_SET_PARA & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);
		JammerID = theStruct.JammerID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		PlatID = theStruct.PlatID;
		PlatType = theStruct.PlatType;
		ATT = theStruct.ATT;
		fLon = theStruct.fLon;
		fLat = theStruct.fLat;
		fHeight = theStruct.fHeight;
		WorkState = theStruct.WorkState;
		StartRF = theStruct.StartRF;
		EndRF = theStruct.EndRF;
		FreqNo = theStruct.FreqNo;
		SW_Malloc_Float(theStruct.FreqSet,FreqSet,theStruct.FreqNo,FreqNo);
		iProtectRFNum = theStruct.iProtectRFNum;
		SW_Malloc_Struct(ProtectRF,theStruct.pProtectRFInfo,pProtectRFInfo,theStruct.iProtectRFNum,iProtectRFNum)
		JamPointAZ = theStruct.JamPointAZ;
		JamPointEL = theStruct.JamPointEL;
		AntennaType = theStruct.AntennaType;
		bUseTrans   = theStruct.bUseTrans;
		iHour   = theStruct.iHour;
		bForbidJam   = theStruct.bForbidJam;
		iKeyPtNum = theStruct.iKeyPtNum;
		SW_Malloc_Struct(sKeyPoint,theStruct.pKeyPt,pKeyPt,theStruct.iKeyPtNum,iKeyPtNum);
		iJamComTrgNum   = theStruct.iJamComTrgNum;
		SW_Malloc_Int(theStruct.pJamComTrgID,pJamComTrgID,theStruct.iJamComTrgNum,iJamComTrgNum);
		return *this;
	}
}sCOMJAM_SET_PARA;
//通信GR设备输出参数
typedef struct _ModelBus_sCOMJAM_PARA
{
	char* sRID;				//身份字符串
	int JammerID;			//GR机ID
	int	 PlatID;				//平台ID         
	char* EquipmentName;	//装备名称
	char* EquipmentType;	//装备类型
	float fTime;			//时间 单位：s
	DKDMS::Enum_ATT	ATT;		//敌我属性
	DKDMS::Enum_WorkState	WorkState;	//工作属性
	DKDMS::Enum_SurvivalState	SurvivalState;	//生存状态
	float fLon;				//经度，单位：度
	float fLat;				//纬度，单位：度
	float fHeight;			//高度，单位：米（m）
	int	 JamPointAmount;				//GR波束个数
	sJAM_POINT *JamPointVar;  //GR波束值
	int FreqNo;                //频点个数
	float *FreqSet;  //频率集 FreqSet int[] 个数为频点个数  unit=MHz


	/*重载构造函数*/
	_ModelBus_sCOMJAM_PARA()
	{
		sRID = NULL;
		JammerID = 0;
		PlatID = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		fTime = 0.;
		ATT = DKDMS::Enum_ATT_1;
		WorkState = DKDMS::Enum_WorkState_0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		fLon = 0.;
		fLat = 0.;
		fHeight = 0.;
		JamPointAmount = 0;
		JamPointVar = NULL;
		FreqNo = 0;
		FreqSet = NULL;

	}

	/*重载析构函数*/
	~_ModelBus_sCOMJAM_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(JamPointVar);
		SW_Delete(FreqSet);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOMJAM_PARA(const _ModelBus_sCOMJAM_PARA &radioJamPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		JamPointVar = NULL;
		FreqSet = NULL;
		*this = radioJamPara;
	}

	/*重载=*/
	_ModelBus_sCOMJAM_PARA & operator=(const _ModelBus_sCOMJAM_PARA & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}


		SW_Malloc_Char(theStruct.sRID,sRID);
		JammerID = theStruct.JammerID;
		PlatID = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);

		fTime = theStruct.fTime;
		ATT = theStruct.ATT;
		WorkState = theStruct.WorkState;
		SurvivalState = theStruct.SurvivalState;
		fLon = theStruct.fLon;
		fLat = theStruct.fLat;
		fHeight = theStruct.fHeight;
		JamPointAmount = theStruct.JamPointAmount;
		SW_Malloc_Struct(sJAM_POINT,theStruct.JamPointVar,JamPointVar,theStruct.JamPointAmount,JamPointAmount);
		FreqNo = theStruct.FreqNo;
		SW_Malloc_Float(theStruct.FreqSet,FreqSet,theStruct.FreqNo,FreqNo);
		return *this;
	}
}sCOMJAM_PARA;
//通信GR参数内部结构
typedef struct _ModelBus_sCOMMJAMRARA_INNER
{
	int             ReceiveID;      //GR对象ID
	DKDMS::Enum_CJamType 	CJamType;	// GR方式
	DKDMS::Enum_CMD	    CMD;	    // GR调制样式
	float           Power;			//等效辐射功率 W
	float           StartRF;	    //起始频率,MHz
	float           EndRF;			//终止频率,MHz
	float           CjamFreInterval;			//梳状谱频率间隔 Hz	1~1000000000Hz	个数是通过起止频率和间隔进行计算
	float           CjamLinearTime;			//线性扫频驻留期 微秒 扫频GR时有效
	float           fContinueTime;			//GR持续时间 ms
	float           CJamBandWidth;			//GR带宽 KHz 某个频点的带宽
	float           JamPointAZ  ;			//GR波束方位指向 度	[0,360]
	float           JamPointEL  ;			//GR波束俯仰指向 度	[-90,90]
	float           fBeamWidth;			//GR天线波束宽度 度
	float           fBeamPitchWidth;			//GR天线波束俯仰宽度 度


	/*重载构造函数*/
	_ModelBus_sCOMMJAMRARA_INNER()
	{
		ReceiveID     = 0;
		CJamType = DKDMS::Enum_CJamType_1;
		CMD      = DKDMS::Enum_CMD_1;
		Power         = 0.;
		StartRF       = 0.;
		EndRF         = 0.;
		CjamFreInterval = 0.;
		CjamLinearTime = 0.;
		fContinueTime = 0.;
		CJamBandWidth = 0.;
		JamPointAZ = 0.;
		JamPointEL = 0.;
		fBeamWidth = 0.;
		fBeamPitchWidth = 0.;
		
	}

	/*重载析构函数*/
	~_ModelBus_sCOMMJAMRARA_INNER()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOMMJAMRARA_INNER(const _ModelBus_sCOMMJAMRARA_INNER &commJamPara)
	{
		*this = commJamPara;
	}

	/*重载=*/
	_ModelBus_sCOMMJAMRARA_INNER & operator=(const _ModelBus_sCOMMJAMRARA_INNER & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		ReceiveID     = theStruct.ReceiveID;
		CJamType      = theStruct.CJamType;
		CMD           = theStruct.CMD;
		Power         = theStruct.Power;
		StartRF       = theStruct.StartRF;
		EndRF         = theStruct.EndRF;
		CjamFreInterval = theStruct.CjamFreInterval;
		CjamLinearTime = theStruct.CjamLinearTime;
		fContinueTime = theStruct.fContinueTime;
		CJamBandWidth = theStruct.CJamBandWidth;
		JamPointAZ   = theStruct.JamPointAZ  ;
		JamPointEL   = theStruct.JamPointEL  ;
		fBeamWidth = theStruct.fBeamWidth;
		fBeamPitchWidth = theStruct.fBeamPitchWidth;
		return *this;
	}
}COMMJAMRARA_INNER;
//通信GR参数
typedef struct _ModelBus_sCOMMJAMPARA 
{
	char* sRID;				//身份字符串
	int JammerID;			//GR机ID
	DKDMS::Enum_ATT	ATT;		//敌我属性
	char* EquipmentName;	// 设备名称
	char* EquipmentType;	//装备类型
	DKDMS::Enum_PlatType    PlatType;//搭载平台类型 用于选择传播模型
	float fLon;				//经度，单位：度
	float fLat;				//纬度，单位：度
	float fHeight;			//高度，单位：米（m）
	float fTime;            //当前仿真时间，动态推演计算时有效
	DKDMS::Enum_AntennaType AntennaType;//天线类型，短波GR有效
	//注意！！！：天线方向图数据仅输出一次，电台需按型号在内部存储GR设备的天线方向图
	int     nAntDotNum;      //方位向天线方向图点数
	float*  AntData;         //方位向天线方向数据(增益，dB)，从主波束中心指向开始顺时针增加，[0,360)等间隔均匀分布,目前暂约定每隔1°输出一个
	int                nJamNum;   //当前在GR的目标数目
	COMMJAMRARA_INNER* JamPara;   //具体的GR参数

	/*重载构造函数*/
	_ModelBus_sCOMMJAMPARA()
	{
		sRID = NULL;
		JammerID = 0;
		ATT = DKDMS::Enum_ATT_2;
		EquipmentName = NULL;
		EquipmentType = NULL;
		PlatType    = DKDMS::Enum_PlatType_1;
		fLon = 0.;		
		fLat = 0.;		
		fHeight = 0.;
		fTime = 0.;
		AntennaType = DKDMS::Enum_AntennaType_0;
		nAntDotNum = 0;
		AntData   = NULL;
		nJamNum = 0;
		JamPara = NULL;
		
	}

	/*重载析构函数*/
	~_ModelBus_sCOMMJAMPARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(AntData);
		SW_Delete(JamPara);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sCOMMJAMPARA(const _ModelBus_sCOMMJAMPARA &commJamPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		AntData   = NULL;
		JamPara = NULL;
		*this = commJamPara;
	}

	/*重载=*/
	_ModelBus_sCOMMJAMPARA & operator=(const _ModelBus_sCOMMJAMPARA & theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		JammerID = theStruct.JammerID;
		ATT = theStruct.ATT;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		PlatType    = theStruct.PlatType;
		fLon = theStruct.fLon;		
		fLat = theStruct.fLat;		
		fHeight = theStruct.fHeight;
		fTime   = theStruct.fTime;
		AntennaType = theStruct.AntennaType;
		nAntDotNum = theStruct.nAntDotNum;
		SW_Malloc_Float(theStruct.AntData,AntData,theStruct.nAntDotNum,nAntDotNum);
		nJamNum = theStruct.nJamNum;
		SW_Malloc_Struct(COMMJAMRARA_INNER,theStruct.JamPara,JamPara,theStruct.nJamNum,nJamNum);
		return *this;
	}
}sCOMMJAMPARA;
//_______________________________________________________________________________//
#pragma pack()

#endif

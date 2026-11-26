/**************************************************************************
**名    称:	可重构装备数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 4.11.18		按照年(个数位)月日组合的方式	**
**版    本:	2024.11.18  											**
*************************************************************************/

#include "MEnStruct_Macros.h"
#include "MEnStruct_Common.h"

#ifndef MEN_STRUCT_KCG
#define MEN_STRUCT_KCG

#pragma pack(1)

//UHF频段可重构装备初始化参数
typedef struct _ModelBus_sKCG_UHF_Set_PARA
{
	char*		sRID;			//身份字符串
	int		    EquipID;		//GR机ID
	int		    PlatID;			//平台ID
	char*		EquipmentName;		//装备名称 场景中的名称
	char*		EquipmentType;		//设备型号
	DKDMS::Enum_ATT	ATT;			//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作属性, defaultValue=1)
	float		fLon;			//! @Properties(description=经度, alias=lon, unit=度)
	float		fLat;			//! @Properties(description=纬度, alias=lat, unit=度)
	float		fHeight;		//! @Properties(description=高度, alias=hei, unit=米)

	int		    nCoopNodeCount;	//! @Properties(description=下级/协同节点个数, display=readonly)
	int*		pCoopNodeID;	//! 下级/协同节点ID列表
	int		    iKeyPtNum;		//! @Properties(description=关键点个数, display=readonly)
	sKeyPoint	*pKeyPt;		//! 关键点列表

	DKDMS::Enum_KcgTaskType_UHF KcgTaskType;//工作模式
	float	    fStartAZ;           //控守起始方位, unit=度
	float       fEndAZ;			    //控守终止方位, unit=度
	float	    fStartEL;           //控守起始俯仰 度	[-90,90],100	地面装备有效 为100时用内部默认值
	float       fEndEL;			    //控守终止俯仰 度	[-90,90],100	地面装备有效 为100时用内部默认值
	float	    fAntAngAZ;			//天线法向指向方位角, unit=度
	float	    fAntAngEL;			//天线法向指向俯仰角, unit=度
	float	    fStartRF;			//控守起始频率 兆赫兹 搜索模式时，起、止控守频率小于0，模型内部用默认最大范围；监视时，选取一部分监视频段
	float	    fEndRF;			//控守终止频率 兆赫兹
	int		    iProtectRFNum;      //保护频段个数
	ProtectRF*  pProtectRFInfo;     //保护频段信息 
	//==========================雷达TC相关的-START===========================
	float	fSRCS;				//! @Properties(description=标称目标雷达截面积, unit=平方米, defaultValue=5)
	float	fSHeight;			//! @Properties(description=标称目标高度, unit=米, defaultValue=2000)
	// 指定标称RCS平台ID，如果为空或负数则使用标称fSRCS和fSHeight
	int	    StdRCSPlatID;		//! @Properties(description=标称RCS平台ID, defaultValue=-1)
	//==========================雷达TC相关的-END=============================
	//==========================雷达对抗相关的-START===========================
	int		RngCalcID;		//计算侦/干范围的雷达ID
	int		iJamRdTrgNum;		//需对抗的雷达个数
	int*	pJamRdTrgID;		//需对抗的雷达列表
	int		iJamComTrgNum;		//需对抗的通信目标个数
	int*	pJamComTrgID;		//需对抗的通信目标列表
	//==========================雷达对抗相关的-END=============================	

	/*重载构造函数*/
	_ModelBus_sKCG_UHF_Set_PARA()
	{
		sRID          = NULL;
		EquipID       = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		nCoopNodeCount      = 0;
		pCoopNodeID   = NULL;
		iKeyPtNum	  = 0;
		pKeyPt		  = NULL;
		KcgTaskType	  = DKDMS::Enum_KcgTaskType_UHF_0;
		fStartAZ = 0.;
		fEndAZ = 360.;
		fStartEL = 0.;
		fEndEL = 0.;
		fAntAngAZ = 0.;
		fAntAngEL = 0.;
		fStartRF = 0.;
		fEndRF = 0.;
		iProtectRFNum = 0;
		pProtectRFInfo = NULL;
		fSRCS = 5.;
		fSHeight = 2000.;
		StdRCSPlatID = -1;
		RngCalcID       = -1;
		iJamRdTrgNum        = 0;
		pJamRdTrgID       = NULL;
		iJamComTrgNum        = 0;
		pJamComTrgID       = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sKCG_UHF_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(pCoopNodeID);
		SW_Delete(pKeyPt);
		SW_Delete(pJamRdTrgID);
		SW_Delete(pJamComTrgID);
		SW_Delete(pProtectRFInfo);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sKCG_UHF_Set_PARA(const _ModelBus_sKCG_UHF_Set_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		pCoopNodeID=NULL;
		pKeyPt	= NULL;
		pJamRdTrgID	= NULL;
		pJamComTrgID	= NULL;
		pProtectRFInfo	= NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sKCG_UHF_Set_PARA& operator=(const _ModelBus_sKCG_UHF_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		EquipID       = theStruct.EquipID;
		PlatID        = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		nCoopNodeCount= theStruct.nCoopNodeCount;
		SW_Malloc_Int(theStruct.pCoopNodeID,pCoopNodeID,theStruct.nCoopNodeCount,nCoopNodeCount);
		iKeyPtNum=theStruct.iKeyPtNum;
		SW_Malloc_Struct(sKeyPoint,theStruct.pKeyPt,pKeyPt,theStruct.iKeyPtNum,iKeyPtNum);
		KcgTaskType      = theStruct.KcgTaskType;
		fStartAZ      = theStruct.fStartAZ;
		fEndAZ        = theStruct.fEndAZ;
		fStartEL      = theStruct.fStartEL;
		fEndEL        = theStruct.fEndEL;
		fAntAngAZ      = theStruct.fAntAngAZ;
		fAntAngEL        = theStruct.fAntAngEL;
		fStartRF      = theStruct.fStartRF;
		fEndRF        = theStruct.fEndRF;
		iProtectRFNum      = theStruct.iProtectRFNum;
		SW_Malloc_Struct(ProtectRF,theStruct.pProtectRFInfo,pProtectRFInfo,theStruct.iProtectRFNum,iProtectRFNum);
		fSRCS      = theStruct.fSRCS;
		fSHeight        = theStruct.fSHeight;		
		StdRCSPlatID      = theStruct.StdRCSPlatID;
		RngCalcID      = theStruct.RngCalcID;
		iJamRdTrgNum      = theStruct.iJamRdTrgNum;
		SW_Malloc_Int(theStruct.pJamRdTrgID,pJamRdTrgID,theStruct.iJamRdTrgNum,iJamRdTrgNum);
		iJamComTrgNum      = theStruct.iJamComTrgNum;
		SW_Malloc_Int(theStruct.pJamComTrgID,pJamComTrgID,theStruct.iJamComTrgNum,iJamComTrgNum);
		return *this;
	}
}sKCG_UHF_Set_PARA;

//L频段可重构装备初始化参数
typedef struct _ModelBus_sKCG_L_Set_PARA
{
	char*		sRID;			//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int			EquipID;		//! @Properties(description=装备id, alias=modelId, display=readonly)
	int			PlatID;			//! @Properties(description=平台id, alias=platformId, display=readonly)
	char*		EquipmentName;	//! @Properties(description=装备名称, alias=equipName)
	char*		EquipmentType;	//设备型号
	DKDMS::Enum_ATT	ATT;		//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作属性, defaultValue=1)
	float		fLon;			//! @Properties(description=经度, alias=lon, unit=度)
	float		fLat;			//! @Properties(description=纬度, alias=lat, unit=度)
	float		fHeight;		//! @Properties(description=高度, alias=hei, unit=米)

	int			nCoopNodeCount;	//! @Properties(description=下级/协同节点个数, display=readonly)
	int*		pCoopNodeID;	//! 下级/协同节点ID列表
	int			iKeyPtNum;		//! @Properties(description=关键点个数, display=readonly)
	sKeyPoint	*pKeyPt;		//! 关键点列表

	DKDMS::Enum_KcgTaskType_L KcgTaskType;
	float	    fStartAZ;       //! @Properties(description=控守起始方位, unit=度)
	float       fEndAZ;			//! @Properties(description=控守终止方位, unit=度)
	float	    fStartEL;           //控守起始俯仰 度	[-90,90],100	地面装备有效 为100时用内部默认值
	float       fEndEL;			    //控守终止俯仰 度	[-90,90],100	地面装备有效 为100时用内部默认值
	float	    fAntAngAZ;			//天线法向指向方位角, unit=度
	float	    fAntAngEL;			//天线法向指向俯仰角, unit=度
	float	    fStartRF;			//控守起始频率 兆赫兹 搜索模式时，起、止控守频率小于0，模型内部用默认最大范围；监视时，选取一部分监视频段
	float	    fEndRF;			//控守终止频率 兆赫兹
	int		    iProtectRFNum;      //保护频段个数
	ProtectRF*  pProtectRFInfo;     //保护频段信息 

	//==========================雷达TC相关的-START===========================
	float	fSRCS;				//! @Properties(description=标称目标雷达截面积, unit=平方米, defaultValue=5)
	float	fSHeight;			//! @Properties(description=标称目标高度, unit=米, defaultValue=2000)
	int		StdRCSPlatID;		//! @Properties(description=标称RCS平台ID, defaultValue=-1)
	//==========================雷达TC相关的-END=============================

	//==========================雷达对抗相关的-START===========================
	int		RngCalcID;		    //! @Properties(description=计算侦/干范围的雷达ID, defaultValue=-1)
	int		iJamRdTrgNum;		//需对抗的雷达个数
	int*	pJamRdTrgID;		//需对抗的雷达列表
	int		iJamComTrgNum;		//需对抗的通信目标个数
	int*	pJamComTrgID;		//需对抗的通信目标列表
	//==========================雷达对抗相关的-END=============================	

	/*重载构造函数*/
	_ModelBus_sKCG_L_Set_PARA()
	{
		sRID          = NULL;
		EquipID       = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		nCoopNodeCount      = 0;
		pCoopNodeID   = NULL;
		iKeyPtNum	  = 0;
		pKeyPt		  = NULL;
		KcgTaskType	  = DKDMS::Enum_KcgTaskType_L_1;
		fStartAZ = 0.;
		fEndAZ = 360.;
		fStartEL = 0.;
		fEndEL = 0.;
		fAntAngAZ = 0.;
		fAntAngEL = 0.;
		fStartRF = 0.;
		fEndRF = 0.;
		iProtectRFNum = 0;
		pProtectRFInfo = NULL;
		fSRCS = 5.;
		fSHeight = 2000.;
		StdRCSPlatID = -1;
		RngCalcID       = -1;
		iJamRdTrgNum        = 0;
		pJamRdTrgID       = NULL;
		iJamComTrgNum        = 0;
		pJamComTrgID       = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sKCG_L_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(pCoopNodeID);
		SW_Delete(pKeyPt);
		SW_Delete(pJamRdTrgID);
		SW_Delete(pJamComTrgID);
        SW_Delete(pProtectRFInfo);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sKCG_L_Set_PARA(const _ModelBus_sKCG_L_Set_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		pCoopNodeID=NULL;
		pKeyPt	= NULL;
		pJamRdTrgID	= NULL;
		pJamComTrgID	= NULL;
		pProtectRFInfo	= NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sKCG_L_Set_PARA& operator=(const _ModelBus_sKCG_L_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		EquipID       = theStruct.EquipID;
		PlatID        = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		nCoopNodeCount= theStruct.nCoopNodeCount;
		SW_Malloc_Int(theStruct.pCoopNodeID,pCoopNodeID,theStruct.nCoopNodeCount,nCoopNodeCount);
		iKeyPtNum=theStruct.iKeyPtNum;
		SW_Malloc_Struct(sKeyPoint,theStruct.pKeyPt,pKeyPt,theStruct.iKeyPtNum,iKeyPtNum);
		KcgTaskType      = theStruct.KcgTaskType;
		fStartAZ      = theStruct.fStartAZ;
		fEndAZ        = theStruct.fEndAZ;
		fStartEL      = theStruct.fStartEL;
		fEndEL        = theStruct.fEndEL;
		fAntAngAZ      = theStruct.fAntAngAZ;
		fAntAngEL        = theStruct.fAntAngEL;
		fStartRF      = theStruct.fStartRF;
		fEndRF        = theStruct.fEndRF;
		fSRCS      = theStruct.fSRCS;
		fSHeight        = theStruct.fSHeight;		
		StdRCSPlatID      = theStruct.StdRCSPlatID;
		RngCalcID      = theStruct.RngCalcID;
		iJamRdTrgNum      = theStruct.iJamRdTrgNum;
		SW_Malloc_Int(theStruct.pJamRdTrgID,pJamRdTrgID,theStruct.iJamRdTrgNum,iJamRdTrgNum);
		iJamComTrgNum      = theStruct.iJamComTrgNum;
		SW_Malloc_Int(theStruct.pJamComTrgID,pJamComTrgID,theStruct.iJamComTrgNum,iJamComTrgNum);
        iProtectRFNum      = theStruct.iProtectRFNum;
		SW_Malloc_Struct(ProtectRF,theStruct.pProtectRFInfo,pProtectRFInfo,theStruct.iProtectRFNum,iProtectRFNum);

		return *this;
	}
}sKCG_L_Set_PARA;

//XKu频段可重构装备初始化参数
typedef struct _ModelBus_sKCG_XKu_Set_PARA
{
	char*		sRID;			//! @Properties(description=仿真id, alias=simuId, display=readonly)
	int			EquipID;		//! @Properties(description=装备id, alias=modelId, display=readonly)
	int			PlatID;			//! @Properties(description=平台id, alias=platformId, display=readonly)
	char*		EquipmentName;	//! @Properties(description=装备名称, alias=equipName)
	char*		EquipmentType;	//设备型号
	DKDMS::Enum_ATT	ATT;		//! @Properties(description=敌我属性, alias=iff, display=readonly)
	DKDMS::Enum_WorkState	WorkState;	//! @Properties(description=工作属性, defaultValue=1)
	float		fLon;			//! @Properties(description=经度, alias=lon, unit=度)
	float		fLat;			//! @Properties(description=纬度, alias=lat, unit=度)
	float		fHeight;		//! @Properties(description=高度, alias=hei, unit=米)
	int			nCoopNodeCount;	//! @Properties(description=下级/协同节点个数, display=readonly)
	int*		pCoopNodeID;	//! 下级/协同节点ID列表
	int			iKeyPtNum;		//! @Properties(description=关键点个数, display=readonly)
	sKeyPoint	*pKeyPt;		//! 关键点列表

	DKDMS::Enum_KcgTaskType_XKu KcgTaskType_XKu;
	float	    fStartAZ;       //! @Properties(description=控守起始方位, unit=度)
	float       fEndAZ;			//! @Properties(description=控守终止方位, unit=度)
	float	    fStartEL;           //控守起始俯仰 度	[-90,90],100	地面装备有效 为100时用内部默认值
	float       fEndEL;			    //控守终止俯仰 度	[-90,90],100	地面装备有效 为100时用内部默认值
	float	    fAntAngAZ;			//天线法向指向方位角, unit=度
	float	    fAntAngEL;			//天线法向指向俯仰角, unit=度
	float	    fStartRF;			//控守起始频率 兆赫兹 搜索模式时，起、止控守频率小于0，模型内部用默认最大范围；监视时，选取一部分监视频段
	float	    fEndRF;			//控守终止频率 兆赫兹
	int		    iProtectRFNum;      //保护频段个数
	ProtectRF*  pProtectRFInfo;     //保护频段信息 
	
	//==========================雷达对抗相关的-START===========================
	int		RngCalcID;		    //! @Properties(description=计算侦/干范围的雷达ID, defaultValue=-1)
	int		iJamRdTrgNum;			//! @Properties(description=需对抗的雷达个数, display=readonly)
	int*	pJamRdTrgID;		    //! @Properties(description=需对抗的雷达列表, alias=gis-sRADAR_Set_PARA)
	//两行星历，用英文逗号区分第1、2行
	char*   cSatPara;           //! @Properties(description=卫星两行星历信息)
	//==========================雷达对抗相关的-END=============================	

	/*重载构造函数*/
	_ModelBus_sKCG_XKu_Set_PARA()
	{
		sRID          = NULL;
		EquipID       = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		nCoopNodeCount      = 0;
		pCoopNodeID   = NULL;
		iKeyPtNum	  = 0;
		pKeyPt		  = NULL;
		KcgTaskType_XKu	  = DKDMS::Enum_KcgTaskType_XKu_1;
		fStartAZ = 0.;
		fEndAZ = 360.;
		fStartEL = 0.;
		fEndEL = 0.;
		fAntAngAZ = 0.;
		fAntAngEL = 0.;
		fStartRF = 0.;
		fEndRF = 0.;
		iProtectRFNum = 0;
		pProtectRFInfo = NULL;
		RngCalcID       = -1;
		iJamRdTrgNum      = 0;
		pJamRdTrgID       = NULL;
		cSatPara        = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sKCG_XKu_Set_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
		SW_Delete(pCoopNodeID);
		SW_Delete(pKeyPt);
		SW_Delete(pJamRdTrgID);
        SW_Delete(pProtectRFInfo);
		SW_Free_Char(cSatPara);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sKCG_XKu_Set_PARA(const _ModelBus_sKCG_XKu_Set_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		pCoopNodeID   = NULL;
		pKeyPt	      = NULL;
		pJamRdTrgID	  = NULL;
		pProtectRFInfo	= NULL;
		cSatPara	  = NULL;
		*this = jam;
	}
	/*重载=*/
	_ModelBus_sKCG_XKu_Set_PARA& operator=(const _ModelBus_sKCG_XKu_Set_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);
		EquipID       = theStruct.EquipID;
		PlatID        = theStruct.PlatID;
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		nCoopNodeCount= theStruct.nCoopNodeCount;
		SW_Malloc_Int(theStruct.pCoopNodeID,pCoopNodeID,theStruct.nCoopNodeCount,nCoopNodeCount);
		iKeyPtNum=theStruct.iKeyPtNum;
		SW_Malloc_Struct(sKeyPoint,theStruct.pKeyPt,pKeyPt,theStruct.iKeyPtNum,iKeyPtNum);
		KcgTaskType_XKu      = theStruct.KcgTaskType_XKu;
		fStartAZ      = theStruct.fStartAZ;
		fEndAZ        = theStruct.fEndAZ;
		fStartEL      = theStruct.fStartEL;
		fEndEL        = theStruct.fEndEL;
		fAntAngAZ      = theStruct.fAntAngAZ;
		fAntAngEL        = theStruct.fAntAngEL;
		fStartRF      = theStruct.fStartRF;
		fEndRF        = theStruct.fEndRF;
		RngCalcID      = theStruct.RngCalcID;
		iJamRdTrgNum      = theStruct.iJamRdTrgNum;
		SW_Malloc_Int(theStruct.pJamRdTrgID,pJamRdTrgID,theStruct.iJamRdTrgNum,iJamRdTrgNum);
		iProtectRFNum      = theStruct.iProtectRFNum;
		SW_Malloc_Struct(ProtectRF,theStruct.pProtectRFInfo,pProtectRFInfo,theStruct.iProtectRFNum,iProtectRFNum);
        SW_Malloc_Char(theStruct.cSatPara,cSatPara);
		return *this;
	}
}sKCG_XKu_Set_PARA;


#pragma pack()

#endif

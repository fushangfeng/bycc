/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.1		按照年(个数位)月日组合的方式	**
**版    本:	2015.04.01  zoubz修改											**
*************************************************************************/

#ifndef MEN_STRUCT_SATJAM
#define MEN_STRUCT_SATJAM

#pragma pack(1)

//卫星平台输入参数
typedef struct _ModelBus_aSATPLAT_SET_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	DKDMS::Enum_ATT	ATT;			//敌我属性
	char*		EquipmentName;	//设备名称
	float		fI0;			//轨道倾角，单位：度
	float		fOMEGA0;		//升交点赤经，单位：度
	float		fOmega;			//近地点角距，单位：度
	float		fA;				//轨道长半轴，单位：米（m）
	float		fEcc;			//椭圆偏心率
	sTIME		sToe;			//星历参考时刻
	float		fM0;			//参考时刻的平近点角，单位：度
	sTIME		sStartTime;		//仿真开始时间
	float		fCalTime;		//计算时间，单位：秒（s）

	/*重载构造函数*/
	_ModelBus_aSATPLAT_SET_PARA()
	{
		sRID     = NULL;
		ID       = 0;
		ATT      = DKDMS::Enum_ATT_1;
		EquipmentName = NULL;
		fI0      = 0;
		fOMEGA0  = 0;
		fOmega   = 0;
		fA       = 0;
		fEcc     = 0;
		fM0      = 0;
		fCalTime = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aSATPLAT_SET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aSATPLAT_SET_PARA(const _ModelBus_aSATPLAT_SET_PARA &satplat)
	{
		sRID = NULL;
		EquipmentName = NULL;
		*this = satplat;
	}

	/*重载=*/
	_ModelBus_aSATPLAT_SET_PARA& operator=(const _ModelBus_aSATPLAT_SET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		ID      = theStruct.ID;
		ATT     = theStruct.ATT;
		fI0     = theStruct.fI0;
		fOMEGA0 = theStruct.fOMEGA0;
		fOmega  = theStruct.fOmega;
		fA      = theStruct.fA;
		fEcc    = theStruct.fEcc;
		sToe    = theStruct.sToe;
		fM0     = theStruct.fM0;
		sStartTime = theStruct.sStartTime;
		fCalTime = theStruct.fCalTime;

		return *this;
	}
}aSATPLAT_Set_PARA;

//卫星平台输出信息
typedef struct _ModelBus_aSATPLAT_PARA
{
	char*	sRID;		//身份字符串
	int		ID;			//实体ID
	float	fLon;		//经度，单位：度
	float	fLat;		//纬度，单位：度
	float	fHeight;	//高度，单位：米（m）
	float	RCS[3];		//雷达回波面积，单位：平方米（m^2）

	/*重载构造函数*/
	_ModelBus_aSATPLAT_PARA()
	{
		sRID = NULL;
		ID   = 0;
		fLon = 0.f;
		fLat = 0.f;
		fHeight = 0.f;
		for (int i=0; i<3; i++)
		{
			RCS[i] = 0;
		}
	}

	/*重载析构函数*/
	~_ModelBus_aSATPLAT_PARA()
	{
		SW_Free_Char(sRID);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aSATPLAT_PARA(const _ModelBus_aSATPLAT_PARA &satplat)
	{
		sRID = NULL;
		*this = satplat;
	}

	/*重载=*/
	_ModelBus_aSATPLAT_PARA& operator=(const _ModelBus_aSATPLAT_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID   = theStruct.ID;
		fLon = theStruct.fLon;
		fLat = theStruct.fLat;
		fHeight = theStruct.fHeight;
		for (int i=0; i<3; i++)
		{
			RCS[i] = theStruct.RCS[i];
		}

		return *this;
	}

}aSATPLAT_PARA;

//飞行位置
typedef struct _ModelBus_aSATPOSAREA
{
	float fLon;		//经度，单位：度
	float fLat;		//纬度，单位：度
	float fHeight;	//高度，单位：米（m）
	float fPsia;	//航向角，单位：度

	/*重载构造函数*/
	_ModelBus_aSATPOSAREA()
	{
		fLon = 0.f;
		fLat = 0.f;
		fHeight = 0.f;
		fPsia = 0.f;
	}

	/*重载析构函数*/
	~_ModelBus_aSATPOSAREA()
	{

	}

	/*重载拷贝构造函数*/
	_ModelBus_aSATPOSAREA(const _ModelBus_aSATPOSAREA &area)
	{
		*this = area;
	}

	/*重载=*/
	_ModelBus_aSATPOSAREA& operator=(const _ModelBus_aSATPOSAREA& theStruct)
	{
		fLon = theStruct.fLon;
		fLat = theStruct.fLat;
		fHeight = theStruct.fHeight;
		fPsia = theStruct.fPsia;
		return *this;
	}

}aSATPOSAREA;

//卫星平台位置信息
typedef struct _ModelBus_aSatPlatPositionArea
{
	char*	sRID;			//身份字符串
	int		ID;				//实体ID;
	int		PosNum;			//位置信息数量
	aSATPOSAREA *Position;	//位置信息

	/*重载构造函数*/
	_ModelBus_aSatPlatPositionArea()
	{
		sRID = NULL;
		ID   = 0;
		PosNum = 0;
		Position = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_aSatPlatPositionArea()
	{
		SW_Free_Char(sRID);

		SW_Delete(Position);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aSatPlatPositionArea(const _ModelBus_aSatPlatPositionArea &area)
	{
		sRID = NULL;
		Position = NULL;
		*this = area;
	}

	/*重载=*/
	_ModelBus_aSatPlatPositionArea& operator=(const _ModelBus_aSatPlatPositionArea& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Delete(Position);
		SW_Malloc_Struct(aSATPOSAREA,theStruct.Position,Position,theStruct.PosNum,PosNum);

		ID = theStruct.ID;
		PosNum = theStruct.PosNum;

		return *this;
	}

}aSatPlatPositionArea;

//卫星导航输入参数 
typedef struct _ModelBus_sSATNAVI_SET_PARA
{
	char*	sRID;				//身份字符串
	int     ID;					//接收机ID
	int		PlatID;				//平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	float       fStartTime;		//仿真开始时间
	DKDMS::Enum_ATT		ATT;		//敌我属性
	DKDMS::Enum_WorkState	WorkState;	//工作属性
	float	fLon;				//经度，单位：度
	float	fLat;				//纬度，单位：度
	float	fHeight;			//高度，单位：米（m）
	bool IsRefWaveModel;		// 是否调用电波传播模型
	DKDMS::Enum_CodeType CodeType;		// 扩频码码形
	DKDMS::Enum_ReceiverType ReceiverType;	// 接收机类型

	/*重载构造函数*/
	_ModelBus_sSATNAVI_SET_PARA()
	{
		sRID          = NULL;
		ID		      = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		IsRefWaveModel = false;
		CodeType	  = DKDMS::Enum_CodeType_0;
		ReceiverType	= DKDMS::Enum_ReceiverType_1;
		fStartTime = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sSATNAVI_SET_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sSATNAVI_SET_PARA(const _ModelBus_sSATNAVI_SET_PARA &sSatSetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = sSatSetPara;
	}

	/*重载=*/
	_ModelBus_sSATNAVI_SET_PARA& operator=(const _ModelBus_sSATNAVI_SET_PARA& theStruct)
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

		ID          = theStruct.ID;
		PlatID          = theStruct.PlatID;
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		IsRefWaveModel = theStruct.IsRefWaveModel;
		CodeType	  = theStruct.CodeType;
		ReceiverType	= theStruct.ReceiverType;
		fStartTime     = theStruct.fStartTime;

		return *this;
	}

}sSATNAVI_Set_PARA;

//卫星导航输入参数 
typedef struct _ModelBus_aSATNAVI_SET_PARA
{
	char*	sRID;				//身份字符串
	int     ID;
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	DKDMS::Enum_ATT		ATT;		//敌我属性
	DKDMS::Enum_WorkState	WorkState;	//工作属性
	float	fLon;				//经度，单位：度
	float	fLat;				//纬度，单位：度
	float	fHeight;			//高度，单位：米（m）
	DKDMS::Enum_CodeType CodeType;		// 扩频码码形
	DKDMS::Enum_ReceiverType ReceiverType;	// 接收机类型

	/*重载构造函数*/
	_ModelBus_aSATNAVI_SET_PARA()
	{
		sRID          = NULL;
		ID		      = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		CodeType	  = DKDMS::Enum_CodeType_0;
		ReceiverType	= DKDMS::Enum_ReceiverType_1;
	}

	/*重载析构函数*/
	~_ModelBus_aSATNAVI_SET_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aSATNAVI_SET_PARA(const _ModelBus_aSATNAVI_SET_PARA &aSatSetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = aSatSetPara;
	}

	/*重载=*/
	_ModelBus_aSATNAVI_SET_PARA& operator=(const _ModelBus_aSATNAVI_SET_PARA& theStruct)
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

		ID          = theStruct.ID;
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		CodeType	  = theStruct.CodeType;
		ReceiverType	= theStruct.ReceiverType;

		return *this;
	}

}aSATNAVI_Set_PARA;

//卫星导航输出基本参数报
typedef struct _ModelBus_sSATNAVI_Get_PARA
{
	char*	sRID;				//身份字符串
	int		ID;					//GR机ID
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
	float		StartRF;		//起始频率，单位：MHz
	float		EndRF;			//终止频率，单位：MHz

	/*重载构造函数*/
	_ModelBus_sSATNAVI_Get_PARA()
	{
		sRID          = NULL;
		ID      = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		fTime         = 0.;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		StartRF		= 0.;
		EndRF   = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sSATNAVI_Get_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sSATNAVI_Get_PARA(const _ModelBus_sSATNAVI_Get_PARA &sSatGetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = sSatGetPara;
	}

	/*重载=*/
	_ModelBus_sSATNAVI_Get_PARA& operator=(const _ModelBus_sSATNAVI_Get_PARA& theStruct)
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

		ID        = theStruct.ID;
		PlatID          = theStruct.PlatID;
		fTime         = theStruct.fTime;
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		SurvivalState = theStruct.SurvivalState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;

		StartRF       = theStruct.StartRF;
		EndRF         = theStruct.EndRF;

		return *this;
	}
}sSATNAVI_Get_PARA;

//卫星导航GR设备输入基本参数报
typedef struct _ModelBus_sSATNAVIJAM_Set_PARA
{
	char*	sRID;				//身份字符串
	int		JammerID;			//GR机ID
	int		PlatID;				//平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	DKDMS::Enum_ATT		ATT;		//敌我属性
	DKDMS::Enum_WorkState	WorkState;	//工作属性
	float	fLon;				//经度，单位：度
	float	fLat;				//纬度，单位：度
	float	fHeight;			//高度，单位：米（m）

	float	JamPointAZ;			// GR指向
	float	JamPointEL;			// GR仰角
	DKDMS::Enum_GPSJamDeviceType DeviceType;	// 设备类型
	DKDMS::Enum_AntennaMode AntennaMode;// 天线模式
	bool	IsRefWaveModel;		// 是否调用电波传播模型
	bool	ComJamArea;			// 是否计算GR区域
	int		ComStep;			// GR区域计算步长

	int		iKeyPtNum;			//关键时间点个数
	sKeyPoint *pKeyPt;			//关键时间点

	/*重载构造函数*/
	_ModelBus_sSATNAVIJAM_Set_PARA()
	{
		sRID          = NULL;
		JammerID      = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		JamPointAZ = 0.;
		JamPointEL = 0.;
		DeviceType = DKDMS::Enum_DeviceType_0;
		AntennaMode = DKDMS::Enum_AntennaMode_0;
		IsRefWaveModel = false;
		ComJamArea = false;
		ComStep = 0;
		iKeyPtNum	  = 0;
		pKeyPt		  = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sSATNAVIJAM_Set_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);
		SW_Delete(pKeyPt);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sSATNAVIJAM_Set_PARA(const _ModelBus_sSATNAVIJAM_Set_PARA &sSatJamSetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		pKeyPt		  = NULL;
		*this = sSatJamSetPara;
	}

	/*重载=*/
	_ModelBus_sSATNAVIJAM_Set_PARA& operator=(const _ModelBus_sSATNAVIJAM_Set_PARA& theStruct)
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
		JamPointAZ = theStruct.JamPointAZ;
		JamPointEL = theStruct.JamPointEL;
		DeviceType = theStruct.DeviceType;
		AntennaMode = theStruct.AntennaMode;
		IsRefWaveModel = theStruct.IsRefWaveModel;
		ComJamArea = theStruct.ComJamArea;
		ComStep = theStruct.ComStep;
		return *this;
	}
}sSATNAVIJAM_Set_PARA;

//卫星导航GR设备静态输入基本参数报
typedef struct _ModelBus_aSATNAVIJAM_Set_PARA
{
	char*	sRID;				//身份字符串
	int		JammerID;			//GR机ID
	int		PlatID;				//平台ID
	char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型
	DKDMS::Enum_ATT		ATT;		//敌我属性
	DKDMS::Enum_WorkState	WorkState;	//工作属性
	float	fLon;				//经度，单位：度
	float	fLat;				//纬度，单位：度
	float	fHeight;			//高度，单位：米（m）
	float	JamPointAZ;			// GR指向
	float	JamPointEL;			// GR仰角
	DKDMS::Enum_GPSJamDeviceType DeviceType;	// 设备类型
	DKDMS::Enum_AntennaMode AntennaMode;// 天线模式
	bool	IsRefWaveModel;		// 是否调用电波传播模型
	bool	ComJamArea;			// 是否计算GR区域
	int		ComStep;			// GR区域计算步长

	/*重载构造函数*/
	_ModelBus_aSATNAVIJAM_Set_PARA()
	{
		sRID          = NULL;
		JammerID      = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		JamPointAZ = 0.;
		JamPointEL = 0.;
		DeviceType = DKDMS::Enum_DeviceType_0;
		AntennaMode = DKDMS::Enum_AntennaMode_0;
		IsRefWaveModel = false;
		ComJamArea = false;
		ComStep = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aSATNAVIJAM_Set_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aSATNAVIJAM_Set_PARA(const _ModelBus_aSATNAVIJAM_Set_PARA &aSatJamSetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = aSatJamSetPara;
	}

	/*重载=*/
	_ModelBus_aSATNAVIJAM_Set_PARA& operator=(const _ModelBus_aSATNAVIJAM_Set_PARA& theStruct)
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

		JammerID        = theStruct.JammerID;
		PlatID          = theStruct.PlatID;
		ATT           = theStruct.ATT;
		WorkState     = theStruct.WorkState;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		JamPointAZ = theStruct.JamPointAZ;
		JamPointEL = theStruct.JamPointEL;
		DeviceType = theStruct.DeviceType;
		AntennaMode = theStruct.AntennaMode;
		IsRefWaveModel = theStruct.IsRefWaveModel;
		ComJamArea = theStruct.ComJamArea;
		ComStep = theStruct.ComStep;
		return *this;
	}
}aSATNAVIJAM_Set_PARA;

//卫星导航GR设备输出基本参数报
typedef struct _ModelBus_sSATNAVIJAM_Get_PARA
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

	float Power;				// 功率
	DKDMS::Enum_GPSJamDeviceType DeviceType; // 设备类型
	DKDMS::Enum_AntennaMode AntennaMode; // 天线模式

	/*重载构造函数*/
	_ModelBus_sSATNAVIJAM_Get_PARA()
	{
		sRID          = NULL;
		JammerID      = 0;
		PlatID        = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		fTime         = 0.;
		ATT           = DKDMS::Enum_ATT_1;
		WorkState     = DKDMS::Enum_WorkState_0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		JamPointAmount= 0;
		JamPointVar   = NULL;

		Power         = 0.;
		DeviceType           = DKDMS::Enum_DeviceType_0;
		AntennaMode     = DKDMS::Enum_AntennaMode_0;
	}

	/*重载析构函数*/
	~_ModelBus_sSATNAVIJAM_Get_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);

		SW_Delete(JamPointVar);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sSATNAVIJAM_Get_PARA(const _ModelBus_sSATNAVIJAM_Get_PARA &sSatJamGetPara)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		JamPointVar = NULL;
		*this = sSatJamGetPara;
	}

	/*重载=*/
	_ModelBus_sSATNAVIJAM_Get_PARA& operator=(const _ModelBus_sSATNAVIJAM_Get_PARA& theStruct)
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
		Power         = theStruct.Power;
		DeviceType           = theStruct.DeviceType;
		AntennaMode     = theStruct.AntennaMode;

		//SW_Delete(JamPointVar);

		SW_Malloc_Struct(sJAM_POINT,theStruct.JamPointVar,JamPointVar,theStruct.JamPointAmount,JamPointAmount);

		return *this;
	}
}sSATNAVIJAM_Get_PARA;

//GR交互信息
typedef struct _ModelBus_aSATNAVIJAM_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				// 实体ID
	char*		EquipmentType;	// GR站型号
	float		fLon;			//经度，单位：度（o）
	float		fLat;			//纬度，单位：度（o）
	float		fHeight;		//高度，单位：米（m）
	float		JamPower;		// GR功率
	
// 	float		JamPointAZ;		// GR天线指向
// 	float		JamPointEL;		// GR天线仰角
	sJAM_POINT JamPointVar;

	DKDMS::Enum_GPSJamDeviceType		DeviceType;		// GR设备类型
	DKDMS::Enum_AntennaMode	AntennaMode;	// 天线模式

	/*重载构造函数*/
	_ModelBus_aSATNAVIJAM_PARA()
	{
		sRID = NULL;
		EquipmentType = NULL;
		ID   = 0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		JamPower = 0.;
		DeviceType = DKDMS::Enum_DeviceType_0;
		AntennaMode = DKDMS::Enum_AntennaMode_0;
	}

	/*重载析构函数*/
	~_ModelBus_aSATNAVIJAM_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aSATNAVIJAM_PARA(const _ModelBus_aSATNAVIJAM_PARA &aSatJamPara)
	{
		sRID = NULL;
		EquipmentType = NULL;
		*this = aSatJamPara;
	}

	/*重载=*/
	_ModelBus_aSATNAVIJAM_PARA& operator = (const _ModelBus_aSATNAVIJAM_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(EquipmentType);
		SW_Malloc_Char(theStruct.EquipmentType,EquipmentType);

		ID      = theStruct.ID;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		JamPower = theStruct.JamPower;
		JamPointVar = theStruct.JamPointVar;
		DeviceType = theStruct.DeviceType;
		AntennaMode = theStruct.AntennaMode;
		return *this;
	}

}aSatNaviJAM_PARA;

typedef struct _ModelBus_aSATNAVIRECEIVER_PARA
{
	char*	sRID;			//身份字符串
	int		ID;				// 实体ID
	float	fLon;			//经度，单位：度（o）
	float	fLat;			//纬度，单位：度（o）
	float	fHeight;		//高度，单位：米（m）
	float	ShelterLoss;	// 遮挡损耗
	float	AntiJammingGain;	// 抗GR增益
	float	GPSNormalNavgError;	// 定位误差
	float	SideLoss;		// 旁瓣损耗
	float	Power;			// 卫星导航接收机功率

	/*重载构造函数*/
	_ModelBus_aSATNAVIRECEIVER_PARA()
	{
		sRID = NULL;
		ID   = 0;
		fLon          = 0.;
		fLat          = 0.;
		fHeight       = 0.;
		ShelterLoss = 0.;
		AntiJammingGain = 0.;
		GPSNormalNavgError = 0.;
		SideLoss = 0.;
		Power = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_aSATNAVIRECEIVER_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aSATNAVIRECEIVER_PARA(const _ModelBus_aSATNAVIRECEIVER_PARA &aSatPara)
	{
		sRID = NULL;
		*this = aSatPara;
	}

	/*重载=*/
	_ModelBus_aSATNAVIRECEIVER_PARA& operator = (const _ModelBus_aSATNAVIRECEIVER_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID      = theStruct.ID;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		ShelterLoss = theStruct.ShelterLoss;
		AntiJammingGain = theStruct.AntiJammingGain;
		GPSNormalNavgError = theStruct.GPSNormalNavgError;
		SideLoss = theStruct.SideLoss;
		Power = theStruct.Power;
		return *this;
	}

}aSatNaviReceiver_PARA;

// 输出导航状态
typedef struct _ModelBus_sNaviReceiverState
{
	char*	sRID;			//身份字符串
	float	fTime;			//时间 单位：秒（s）
	int		ReceiveID;		//雷达ID   
	int		SendID;			//目标ID  
	bool	IsLocated;		//
	float	GPSNavgError;	// 定位误差

	/*重载构造函数*/
	_ModelBus_sNaviReceiverState()
	{
		sRID          = NULL;
		fTime = 0.;
		ReceiveID = 0;
		SendID = 0;
		IsLocated = false;
		GPSNavgError = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_sNaviReceiverState()
	{
		SW_Free_Char(sRID);

	}

	/*重载拷贝构造函数*/
	_ModelBus_sNaviReceiverState(const _ModelBus_sNaviReceiverState &sNaviState)
	{
		sRID = NULL;
		*this = sNaviState;
	}

	/*重载=*/
	_ModelBus_sNaviReceiverState& operator=(const _ModelBus_sNaviReceiverState& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		fTime = theStruct.fTime;
		ReceiveID = theStruct.ReceiveID;
		SendID = theStruct.SendID;
		IsLocated = theStruct.IsLocated;
		GPSNavgError = theStruct.GPSNavgError;
		return *this;
	}
}sNaviReceiverState;

// 静态输出导航状态
typedef struct _ModelBus_aNaviReceiverState
{
	char*	sRID;			//身份字符串
	int		ReceiveID;		//雷达ID   
	int		SendID;			//目标ID  
	bool	IsLocated;		//
	float	GPSNavgError;	// 定位误差

	/*重载构造函数*/
	_ModelBus_aNaviReceiverState()
	{
		sRID          = NULL;
		ReceiveID = 0;
		SendID = 0;
		IsLocated = false;
		GPSNavgError = 0.;
	}

	/*重载析构函数*/
	~_ModelBus_aNaviReceiverState()
	{
		SW_Free_Char(sRID);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aNaviReceiverState(const _ModelBus_aNaviReceiverState &aNaviState)
	{
		sRID = NULL;
		*this = aNaviState;
	}

	/*重载=*/
	_ModelBus_aNaviReceiverState& operator=(const _ModelBus_aNaviReceiverState& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReceiveID = theStruct.ReceiveID;
		SendID = theStruct.SendID;
		IsLocated = theStruct.IsLocated;
		GPSNavgError = theStruct.GPSNavgError;
		return *this;
	}
}aNaviReceiverState;

// GR有效区域
typedef struct _ModelBus_sSatNaviJamEffectArea
{
	char*	sRID;			//身份字符串
	int		ReceiveID;		//雷达ID   
	int		SendID;			//目标ID  
	int		StationID;
	float	fTime;			//时间 单位：秒（s）
	int		RegionSort;
	float	Height; 
	int		RegionType; 
	int		PtNum;
	sPON_AGG *Position;

	/*重载构造函数*/
	_ModelBus_sSatNaviJamEffectArea()
	{
		sRID          = NULL;
		ReceiveID = 0;
		SendID = 0;
		StationID = 0;
		fTime = 0.;
		RegionSort = 0;
		Height = 0;
		RegionType = 0;
		PtNum = 0;
		Position  = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sSatNaviJamEffectArea()
	{
		SW_Free_Char(sRID);
		SW_Delete(Position);

	}

	/*重载拷贝构造函数*/
	_ModelBus_sSatNaviJamEffectArea(const _ModelBus_sSatNaviJamEffectArea &jamArea)
	{
		sRID = NULL;
		Position  = NULL; 
		*this = jamArea;
	}

	/*重载=*/
	_ModelBus_sSatNaviJamEffectArea& operator=(const _ModelBus_sSatNaviJamEffectArea& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		PtNum = theStruct.PtNum;
		//SW_Delete(Position);
		SW_Malloc_Struct(sPON_AGG,theStruct.Position,Position,theStruct.PtNum,PtNum);

		ReceiveID = theStruct.ReceiveID;
		SendID = theStruct.SendID;
		StationID = theStruct.StationID;
		fTime = theStruct.fTime;
		RegionSort = theStruct.RegionSort;
		Height = theStruct.Height;
		RegionType = theStruct.RegionType;

		return *this;
	}
}sSatNaviJamEffectArea;

typedef struct _ModelBus_aGPSGDOPArea
{
	char*	sRID;			//身份字符串
	int		ID;		//雷达ID  
	float	fTime;				//时间 单位：秒（s）
	DKDMS::Enum_AreaType AreaType; 
	int PosNum;
	sPON_AREA *Position;


	/*重载构造函数*/
	_ModelBus_aGPSGDOPArea()
	{
		sRID          = NULL;
		Position  = NULL;
		ID = 0;
		fTime = 0.;
		AreaType = DKDMS::Enum_AreaType_0;
		PosNum = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aGPSGDOPArea()
	{
		SW_Free_Char(sRID);
		SW_Delete(Position);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aGPSGDOPArea(const _ModelBus_aGPSGDOPArea &GPSArea)
	{
		sRID = NULL;
		Position  = NULL; 
		*this = GPSArea;
	}

	/*重载=*/
	_ModelBus_aGPSGDOPArea& operator=(const _ModelBus_aGPSGDOPArea& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		PosNum = theStruct.PosNum;
		//SW_Delete(Position);
		SW_Malloc_Struct(sPON_AREA,theStruct.Position,Position,theStruct.PosNum,PosNum);

		ID = theStruct.ID;
		fTime = theStruct.fTime;
		AreaType = theStruct.AreaType;

		return *this;
	}
}aGPSGDOPArea;

typedef struct _ModelBus_sJSRStruct
{
	float	fLon;			//经度，单位：度（o）
	float	fLat;			//纬度，单位：度（o）
	float	fHeight;		//高度，单位：米（m）
	float	JSR;			//干信比

	/*重载构造函数*/
	_ModelBus_sJSRStruct()
	{
		fLon      = 0;
		fLat      = 0;
		fHeight   = 0;
		JSR = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sJSRStruct()
	{
	}

	/*重载拷贝构造函数*/
	_ModelBus_sJSRStruct(const _ModelBus_sJSRStruct &JSRStruct)
	{
		*this = JSRStruct;
	}

	/*重载=*/
	_ModelBus_sJSRStruct& operator=(const _ModelBus_sJSRStruct& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		fLon      = theStruct.fLon;
		fLat      = theStruct.fLat;
		fHeight   = theStruct.fHeight;
		JSR = theStruct.JSR;

		return *this;
	}
}sJSRStruct;

typedef struct _ModelBus_aGPSGDOPResult
{
	char*	sRID;			//身份字符串
	int		ID;		//雷达ID  
	int		PlatID;				//平台ID
	int		PosNum;
	sJSRStruct *JSRData;

	/*重载构造函数*/
	_ModelBus_aGPSGDOPResult()
	{
		sRID          = NULL;
		JSRData  = NULL;
		ID = 0;
		PlatID = 0;
		PosNum = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aGPSGDOPResult()
	{
		SW_Free_Char(sRID);
		SW_Delete(JSRData);

	}

	/*重载拷贝构造函数*/
	_ModelBus_aGPSGDOPResult(const _ModelBus_aGPSGDOPResult &GPSResult)
	{
		sRID = NULL;
		JSRData  = NULL; 
		*this = GPSResult;
	}

	/*重载=*/
	_ModelBus_aGPSGDOPResult& operator=(const _ModelBus_aGPSGDOPResult& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		PosNum = theStruct.PosNum;
		//SW_Delete(JSRData);
		SW_Malloc_Struct(sJSRStruct,theStruct.JSRData,JSRData,theStruct.PosNum,PosNum);

		ID = theStruct.ID;
		PlatID = theStruct.PlatID;
		return *this;
	}
}aGPSGDOPResult;

//卫星平台输入参数
typedef struct _ModelBus_sSATPLAT_SET_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	DKDMS::Enum_ATT	ATT;			//敌我属性
	char*		EquipmentName;	//设备名称
	float		fI0;			//轨道倾角，单位：度
	float		fOMEGA0;		//升交点赤经，单位：度
	float		fOmega;			//近地点角距，单位：度
	float		fA;				//轨道长半轴，单位：米（m）
	float		fEcc;			//椭圆偏心率
	sTIME		sToe;			//星历参考时刻
	float		fM0;			//参考时刻的平近点角，单位：度
	sTIME		sStartTime;		//仿真开始时间

	/*重载构造函数*/
	_ModelBus_sSATPLAT_SET_PARA()
	{
		sRID    = NULL;
		ID      = 0;
		ATT     = DKDMS::Enum_ATT_1;
		EquipmentName = NULL;
		fI0     = 0;
		fOMEGA0 = 0;
		fOmega  = 0;
		fA      = 0;
		fEcc    = 0;
		fM0     = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sSATPLAT_SET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);

	}

	/*重载拷贝构造函数*/
	_ModelBus_sSATPLAT_SET_PARA(const _ModelBus_sSATPLAT_SET_PARA &satplat)
	{
		sRID = NULL;
		EquipmentName = NULL;
		*this = satplat;
	}

	/*重载=*/
	_ModelBus_sSATPLAT_SET_PARA& operator=(const _ModelBus_sSATPLAT_SET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID      = theStruct.ID;
		ATT     = theStruct.ATT;
		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		fI0     = theStruct.fI0;
		fOMEGA0 = theStruct.fOMEGA0;
		fOmega  = theStruct.fOmega;
		fA      = theStruct.fA;
		fEcc    = theStruct.fEcc;
		sToe    = theStruct.sToe;
		fM0     = theStruct.fM0;
		sStartTime = theStruct.sStartTime;

		return *this;
	}

}sSATPLAT_Set_PARA;

//卫星平台输出参数
typedef struct _ModelBus_sSATPLAT_GET_PARA
{
	char*		sRID;			//身份字符串
	int			ID;				//实体ID
	float		fTime;			//仿真时间
	char*		EquipmentName;	//设备名称
	char*		EquipmentType;	//设备型号
	float		fLon;			//经度，单位：度
	float		fLat;			//经度，单位：度
	float		fHeight;		//高度，单位：米（m）
	DKDMS::Enum_SurvivalState	SurvivalState; //生存状态
	DKDMS::Enum_WorkState		WorkState;		//工作状态
	DKDMS::Enum_ATT	ATT;			//敌我属性
	float		RCS[3];			//雷达回波面积，单位：平方米（m^2）
	float		Theta;			//俯仰角，单位：度
	float		Psia;			//航向角，单位：度
	float		Phie;			//滚转角，单位：度
	float		Xdote;			//x轴速度分量，单位：米/秒（m/s）
	float		Ydote;			//y轴速度分量，单位：米/秒（m/s）
	float		Zdote;			//z轴速度分量，单位：米/秒（m/s）
	float		Velocity;		//真空速，单位：米/秒（m/s）

	/*重载构造函数*/
	_ModelBus_sSATPLAT_GET_PARA()
	{
		sRID    = NULL;
		ID      = 0;
		fTime   = 0;
		EquipmentName = NULL;
		EquipmentType = NULL;
		fLon    = 0;
		fLat    = 0;
		fHeight = 0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		WorkState = DKDMS::Enum_WorkState_0;
		ATT     = DKDMS::Enum_ATT_1;
		for (int i=0; i<3; i++)
		{
			RCS[i] = 0;
		}
		Theta   = 0;
		Psia    = 0;
		Phie    = 0;
		Xdote   = 0;
		Ydote   = 0;
		Zdote   = 0;
		Velocity = 0;
	}

	/*重载析构函数*/
	~_ModelBus_sSATPLAT_GET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sSATPLAT_GET_PARA(const _ModelBus_sSATPLAT_GET_PARA &satplat)
	{
		sRID  = NULL;
		EquipmentType = NULL;
		EquipmentName = NULL;
		*this = satplat;
	}

	/*重载=*/
	_ModelBus_sSATPLAT_GET_PARA& operator=(const _ModelBus_sSATPLAT_GET_PARA& theStruct)
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

		ID      = theStruct.ID;
		fTime   = theStruct.fTime;
		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		SurvivalState = theStruct.SurvivalState;
		WorkState     = theStruct.WorkState;
		ATT           = theStruct.ATT;
		for (int i=0; i<3; i++)
		{
			RCS[i] = theStruct.RCS[i];
		}
		Theta   = theStruct.Theta;
		Psia    = theStruct.Psia;
		Phie    = theStruct.Phie;
		Xdote   = theStruct.Xdote;
		Ydote   = theStruct.Ydote;
		Zdote   = theStruct.Zdote;
		Velocity = theStruct.Velocity;

		return *this;
	}

}sSATPLAT_Get_PARA;

#pragma pack()

#endif

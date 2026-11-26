/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.3.31		按照年(个数位)月日组合的方式	**
**版    本:	2015.03.31  zoubz修改											**
*************************************************************************/

#include "MEnStruct_Macros.h"

#ifndef MEN_STRUCT_EO
#define MEN_STRUCT_EO

#include <string.h>
#pragma pack(1)

namespace DKDMS{//namespace DMS start zm20170912
enum Enum_WindSpeed {	// 风速等级
	Enum_WindSpeed_0 = 0,	// 无风
	Enum_WindSpeed_1 = 1,	// 软风
	Enum_WindSpeed_2 = 2,	// 轻风
	Enum_WindSpeed_3 = 3,	// 微风
	Enum_WindSpeed_4 = 4,	// 和风
	Enum_WindSpeed_5 = 5,	// 劲风
	Enum_WindSpeed_6 = 6,	// 强风以上风
};
#ifndef Enum_MK36Pos_DEF
#define Enum_MK36Pos_DEF
enum Enum_MK36Pos {
	Enum_MK36Pos_LF = 0, //左前
	Enum_MK36Pos_RF = 1, //右前
	Enum_MK36Pos_LB = 2, //左后
	Enum_MK36Pos_RB = 3,
};
#endif
#ifndef ENUM_EOENVIRONMENT_DEF
#define ENUM_EOENVIRONMENT_DEF
enum Enum_EOEnvironment {	// 光电环境信息
	Enum_EOEnvironment_1 = 1,	// 海洋
	Enum_EOEnvironment_2 = 2,	// 村庄
	Enum_EOEnvironment_3 = 3,	// 城市
};
#endif

#ifndef ENUM_EGUIDEMODE_DEF
#define ENUM_EGUIDEMODE_DEF
enum Enum_EGuideMode {	// 光电制导方式
	Enum_EGuideMode_0 = 0,	// 未知
	Enum_EGuideMode_1 = 1,	// 雷达制导
	Enum_EGuideMode_2 = 2,	// 红外制导
	Enum_EGuideMode_3 = 3,	// 毫米波制导
	Enum_EGuideMode_4 = 4,	// 激光制导
	Enum_EGuideMode_5 = 5,	// 电视制导
	Enum_EGuideMode_6 = 6,	// 复合制导作战状态
};
#endif

enum Enum_PLJamClass {	// 强激光GR等级
	Enum_PLJamClass_0 = 0,	// 无效
	Enum_PLJamClass_1 = 1,	// 致眩
	Enum_PLJamClass_2 = 2,	// 致盲
	Enum_PLJamClass_3 = 3,	// 毁伤
};
}

// 460系统各车（输入）
typedef struct _ModelBus_EOJams_SET_PARA
{
	char*	sRID;					  // 身份字符串
	int		ID;						  // 实体ID
	int		OwnerID;				  // 隶属关系
	int		PlatID;					  // 搭载平台ID
	DKDMS::Enum_ATT ATT;					  // 敌我属性
	float	fLon;			          // 经度,单位:度	
	float	fLat;			          // 纬度,单位:度	
	float	fHeight;			      // 高度,单位:米(m)	
	char*	EquipmentName;	          // 设备名称
	int		SaveTargetID;			  // 保护目标
	DKDMS::Enum_WorkMode WorkMode;	          // 作战模式
	DKDMS::Enum_EOEnvironment EOEnvironment; // 光电环境信息	
	DKDMS::Enum_WindSpeed WindSpeed;         // 风速

	/*重载构造函数*/
	_ModelBus_EOJams_SET_PARA()
	{
		sRID			= NULL;
		ID				= 0;
		OwnerID			= 0;
		PlatID			= 0;
		ATT				= DKDMS::Enum_ATT_1;
		fLon			=0;
		fLat			= 0.;
		fHeight			= 0;
		EquipmentName	=  NULL;
		SaveTargetID    = 0;
		WorkMode        = DKDMS::Enum_WorkMode_0;
		EOEnvironment   = DKDMS::Enum_EOEnvironment_1;
		WindSpeed       = DKDMS::Enum_WindSpeed_0;

	}

	/*重载析构函数*/
	~_ModelBus_EOJams_SET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);

	}

	/*重载拷贝构造函数*/
	_ModelBus_EOJams_SET_PARA(const _ModelBus_EOJams_SET_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_EOJams_SET_PARA& operator=(const _ModelBus_EOJams_SET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		ID       = theStruct.ID;
		OwnerID     = theStruct.OwnerID;
		PlatID         = theStruct.PlatID;
		ATT     = theStruct.ATT;
		fLon    = theStruct.fLon;
		fLat       = theStruct.fLat;
		fHeight    = theStruct.fHeight;
		WorkMode         = theStruct.WorkMode;
		SaveTargetID         = theStruct.SaveTargetID;
		EOEnvironment    = theStruct.EOEnvironment;
		WindSpeed   = theStruct.WindSpeed;

		return *this;
	}
}sEOJams_SET_PARA;

// 460系统各车（静态输入）
typedef struct _ModelBus_aEOJams_SET_PARA
{
	char*	sRID;			// 身份字符串
	int		ID;				// ID
	float   fLon;			// 经度,单位:度
	float   fLat;			// 纬度,单位:度
	float   fHeight;		// 高度,单位:米(m)
	DKDMS::Enum_EOEnvironment EOEnvironment; // 光电环境信息

	/*重载构造函数*/
	_ModelBus_aEOJams_SET_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		fLon					= 0.;
		fLat					= 0.;
		fHeight					= 0.;
		EOEnvironment			= DKDMS::Enum_EOEnvironment_1;
	}

	/*重载析构函数*/
	~_ModelBus_aEOJams_SET_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aEOJams_SET_PARA(const _ModelBus_aEOJams_SET_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aEOJams_SET_PARA& operator=(const _ModelBus_aEOJams_SET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID				= theStruct.ID;
		fLon			= theStruct.fLon;
		fLat			= theStruct.fLat;
		fHeight			= theStruct.fHeight;
		EOEnvironment	= theStruct.EOEnvironment;

		return *this;
	}

}aEOJams_SET_PARA;

// 460-1（光电指控车）（输出）
typedef struct _ModelBus_EOCommand_PARA
{
	char*	sRID;				//身份字符串
	int		ID;					// 实体ID
	int		PlatID;				// 搭载平台ID
	char*	EquipmentName;		// 设备名称
	char*	EquipmentType;		// 设备型号
	DKDMS::Enum_ATT ATT;			// 敌我属性
	float fLon;				// 经度
	float fLat;				// 纬度
	float fHeight;			// 高度
	float   fTime;			          // 时间,单位:秒(s)
	DKDMS::Enum_SurvivalState SurvivalState;	// 生存状态
	DKDMS::Enum_WorkState WorkState;			// 工作状态
	DKDMS::Enum_WorkMode WorkMode;	// 作战模式
	int	  nEquipCount;		// 下属装备数量
	int	    SaveTargetID;	          // 保护目标ID
	/*重载构造函数*/
	_ModelBus_EOCommand_PARA()
	{
		sRID          = NULL;
		ID       = 0;
		PlatID         = 0;
		ATT     = DKDMS::Enum_ATT_1;
		EquipmentName =  NULL;
		EquipmentType = NULL;
		fLon    =0;
		fLat       = 0.;
		fHeight    = 0;
		fTime = 0;
		SurvivalState = DKDMS::Enum_SurvivalState_0;
		WorkState = DKDMS::Enum_WorkState_0;
		WorkMode         = DKDMS::Enum_WorkMode_0;
		nEquipCount    = 0;
		SaveTargetID = 0;
	}

	/*重载析构函数*/
	~_ModelBus_EOCommand_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EOCommand_PARA(const _ModelBus_EOCommand_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_EOCommand_PARA& operator=(const _ModelBus_EOCommand_PARA& theStruct)
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


		ID       = theStruct.ID;
		PlatID         = theStruct.PlatID;
		ATT     = theStruct.ATT;
		fLon    = theStruct.fLon;
		fLat       = theStruct.fLat;
		fHeight    = theStruct.fHeight;
		fTime =  theStruct.fTime;
		SurvivalState =  theStruct.SurvivalState;
		WorkState =  theStruct.WorkState;
		WorkMode         = theStruct.WorkMode;
		nEquipCount         = theStruct.nEquipCount;
		SaveTargetID = theStruct.SaveTargetID;

		return *this;
	}
}sEOCommand_PARA;

// 460-2-3-5（红外ZC引导车、激光欺骗GR车、激光GR车）（输出）jcg
typedef struct _ModelBus_WarnJam_PARA
{
	char*	sRID;				        // 身份字符串
	int		ID;					        // 实体ID
	int		OwnerID;			        // 隶属关系
	int		PlatID;				        // 搭载平台ID
	char*	EquipmentName;		        // 设备名称
	char*	EquipmentType;		        // 设备型号
	DKDMS::Enum_ATT ATT;			            // 敌我属性
	float   fLon;				        // 经度,单位:度
	float   fLat;				        // 纬度,单位:度
	float   fHeight;			        // 高度,单位:米(m)
	float   fTime;			            // 时间,单位:秒(s)
	DKDMS::Enum_SurvivalState SurvivalState;	// 生存状态
	DKDMS::Enum_WorkState WorkState;			// 工作状态
	DKDMS::Enum_WorkMode  WorkMode;	        // 作战模式

	/*重载构造函数*/
	_ModelBus_WarnJam_PARA()
	{
		sRID		= NULL;
		ID			= 0;
		OwnerID     = 0;
		PlatID      = 0;
		ATT			= DKDMS::Enum_ATT_1;
		fLon		= 0.;
		fLat		= 0.;
		fHeight     = 0.;
		fTime		= 0.;
		EquipmentName	 =  NULL;
		EquipmentType	 =  NULL;
		SurvivalState	 = DKDMS::Enum_SurvivalState_0;
		WorkState		 = DKDMS::Enum_WorkState_0;
		WorkMode         = DKDMS::Enum_WorkMode_0;
	}

	/*重载析构函数*/
	~_ModelBus_WarnJam_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_WarnJam_PARA(const _ModelBus_WarnJam_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_WarnJam_PARA& operator=(const _ModelBus_WarnJam_PARA& theStruct)
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
		OwnerID     = theStruct.OwnerID;
		PlatID      = theStruct.PlatID;
		ATT			= theStruct.ATT;
		fLon		= theStruct.fLon;
		fLat        = theStruct.fLat;
		fHeight     = theStruct.fHeight;
		fTime	    = theStruct.fTime;
		SurvivalState =  theStruct.SurvivalState;
		WorkState	=  theStruct.WorkState;
		WorkMode    = theStruct.WorkMode;
		return *this;
	}

}sWarnJam_PARA;

// 460-4（光电综合GR车）（输出）
typedef struct _ModelBus_EOGeneralJam_PARA
{
	char*	sRID;				        //身份字符串
	int		ID;					        // 实体ID
	int		OwnerID;			        // 隶属关系
	int		PlatID;				        // 搭载平台ID
	char*	EquipmentName;		        // 设备名称
	char*	EquipmentType;		        // 设备型号
	DKDMS::Enum_ATT ATT;			            // 敌我属性
	float   fLon;				        // 经度,单位:度
	float   fLat;				        // 纬度,单位:度
	float   fHeight;			        // 高度,单位:米(m)
	float   fTime;			            // 时间,单位:秒(s)
	DKDMS::Enum_SurvivalState SurvivalState;	// 生存状态
	DKDMS::Enum_WorkState WorkState;			// 工作状态
	DKDMS::Enum_WorkMode  WorkMode;	        // 作战模式
	int		RocketGroup;	            // GR弹可用批数

	/*重载构造函数*/
	_ModelBus_EOGeneralJam_PARA()
	{
		sRID		= NULL;
		ID			= 0;
		OwnerID     = 0;
		PlatID      = 0;
		ATT			= DKDMS::Enum_ATT_1;
		fLon		= 0.;
		fLat		= 0.;
		fHeight     = 0.;
		fTime		= 0.;
		EquipmentName	 =  NULL;
		EquipmentType	 =  NULL;
		SurvivalState	 = DKDMS::Enum_SurvivalState_0;
		WorkState		 = DKDMS::Enum_WorkState_0;
		WorkMode         = DKDMS::Enum_WorkMode_0;
		RocketGroup = 0;
	}

	/*重载析构函数*/
	~_ModelBus_EOGeneralJam_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EOGeneralJam_PARA(const _ModelBus_EOGeneralJam_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_EOGeneralJam_PARA& operator=(const _ModelBus_EOGeneralJam_PARA& theStruct)
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
		OwnerID     = theStruct.OwnerID;
		PlatID      = theStruct.PlatID;
		ATT			= theStruct.ATT;
		fLon		= theStruct.fLon;
		fLat        = theStruct.fLat;
		fHeight     = theStruct.fHeight;
		fTime	    = theStruct.fTime;
		SurvivalState =  theStruct.SurvivalState;
		WorkState	=  theStruct.WorkState;
		WorkMode    = theStruct.WorkMode;
		RocketGroup = theStruct.RocketGroup;
		return *this;
	}

}sEOGeneralJam_PARA;

// 精确制导武器（输入）
// 增加光电制导方式	ZR
typedef struct _ModelBus_EOGuideMissile_SET_PARA
{
	char*	sRID;			          // 身份字符串
	int		ID;				          // ID
	int		PlatID;			          // 所属平台编号
	DKDMS::Enum_ATT ATT;			          // 敌我属性
	float   fLon;				      // 经度,单位:度
	float   fLat;				      // 纬度,单位:度
	float   fHeight;			      // 高度,单位:米(m)
	char*	EquipmentName;	          // 设备名称
	DKDMS::Enum_EOEnvironment EOEnvironment; // 光电环境信息
	int		TargetID;		          // 攻击目标ID
	float   fTLon;				      // 经度,单位:度
	float   fTLat;				      // 纬度,单位:度
	float   fTHeight;			      // 高度,单位:米(m)
	float	fFireTime;		          // 发射时间
	DKDMS::Enum_EGuideMode EGuideMode;		  // 光电制导方式

	/*重载构造函数*/
	_ModelBus_EOGuideMissile_SET_PARA()
	{
		sRID		= NULL;
		ID			= 0;
		PlatID      = 0;
		ATT			= DKDMS::Enum_ATT_1;
		fLon		= 0.;
		fLat		= 0.;
		fHeight     = 0.;
		EquipmentName	 = NULL;
		EOEnvironment    = DKDMS::Enum_EOEnvironment_1;
		TargetID	= 0;
		fTLon		= 0.;
		fTLat		= 0.;
		fTHeight    = 0.;
		fFireTime	= 0.;
		EGuideMode       = DKDMS::Enum_EGuideMode_0;
	}

	/*重载析构函数*/
	~_ModelBus_EOGuideMissile_SET_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EOGuideMissile_SET_PARA(const _ModelBus_EOGuideMissile_SET_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_EOGuideMissile_SET_PARA& operator=(const _ModelBus_EOGuideMissile_SET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(EquipmentName);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		ID			= theStruct.ID;
		PlatID      = theStruct.PlatID;
		ATT			= theStruct.ATT;
		fLon		= theStruct.fLon;
		fLat        = theStruct.fLat;
		fHeight     = theStruct.fHeight;
		EOEnvironment    = theStruct.EOEnvironment;
		TargetID	= theStruct.TargetID;
		fTLon		= theStruct.fTLon;
		fTLat       = theStruct.fTLat;
		fTHeight    = theStruct.fTHeight;
		fFireTime	= theStruct.fFireTime;
		EGuideMode  = theStruct.EGuideMode;
		return *this;
	}

}sEOGuideMissile_SET_PARA;

// 精确制导武器（输出）
typedef struct _ModelBus_EOGuideMissile_PARA
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
	DKDMS::Enum_SurvivalState SurvivalState; // 生存状态
	DKDMS::Enum_WorkState  WorkState;		  // 工作状态
	DKDMS::Enum_EGuideMode EGuideMode;		  // 光电制导方式	

	/*重载构造函数*/
	_ModelBus_EOGuideMissile_PARA()
	{
		sRID		= NULL;
		ID			= 0;
		PlatID      = 0;
		ATT			= DKDMS::Enum_ATT_1;
		fLon		= 0.;
		fLat		= 0.;
		fHeight     = 0.;
		fTime		= 0.;
		EquipmentName	 =  NULL;
		EquipmentType	 =  NULL;
		SurvivalState	 = DKDMS::Enum_SurvivalState_0;
		WorkState		 = DKDMS::Enum_WorkState_0;
		EGuideMode       = DKDMS::Enum_EGuideMode_0;
	}

	/*重载析构函数*/
	~_ModelBus_EOGuideMissile_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EOGuideMissile_PARA(const _ModelBus_EOGuideMissile_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_EOGuideMissile_PARA& operator=(const _ModelBus_EOGuideMissile_PARA& theStruct)
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
		SurvivalState =  theStruct.SurvivalState;
		WorkState	=  theStruct.WorkState;
		EGuideMode  = theStruct.EGuideMode;
		return *this;
	}

}sEOGuideMissile_PARA;

typedef struct _ModelBus_LaserJam_PARA// 强激光GR(462/465->导弹)jcg
{
	char*	sRID;				 // 身份字符串
	int		ReceiveID;           // 接收者ID
	int		SendID;              // 发送者ID
	float	fTime;               // 时间,单位:秒(s)      
	float	fWaveLength;         // 激光波长,单位:微米(um)
	float	fPulseEnergy;        // 单脉冲能量,单位:焦耳
	float	fAngle;              // 激光束散角,单位:豪弧度
	float	fDia;                // GR光斑直径,单位:毫米
	float	fLon;                // GR设备经度,单位:度
	float	fLat;                // GR设备纬度,单位:度
	float	fHeight;             // GR设备高度,单位:米

	/*重载构造函数*/
	_ModelBus_LaserJam_PARA()
	{
		sRID		= NULL;
		ReceiveID	= 0;
		SendID      = 0;
		fTime		= 0.;
		fWaveLength	= 0.;
		fPulseEnergy= 0.;
		fAngle      = 0.;
		fDia		= 0.;
		fLon		= 0.;
		fLat		= 0.;
		fHeight     = 0.;		
	}

	/*重载析构函数*/
	~_ModelBus_LaserJam_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_LaserJam_PARA(const _ModelBus_LaserJam_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_LaserJam_PARA& operator=(const _ModelBus_LaserJam_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReceiveID	= theStruct.ReceiveID;
		SendID      = theStruct.SendID;
		fTime		= theStruct.fTime;
		fWaveLength	= theStruct.fWaveLength;
		fPulseEnergy= theStruct.fPulseEnergy;
		fAngle      = theStruct.fAngle;
		fDia		= theStruct.fDia;
		fLon		= theStruct.fLon;
		fLat        = theStruct.fLat;
		fHeight     = theStruct.fHeight;

		return *this;
	}

}sLaserJam_PARA;

typedef struct _ModelBus_ActiveJam_PARA // 角度欺骗GR
{
	char*	sRID;				 // 身份字符串
	int		ReceiveID;           // 接收者ID
	int		SendID;              // 发送者ID
	float	fTime;               // 时间,单位:秒(s)      
	float   fShamTargetLon;      // 假目标经度
	float   fShamTargetLat;      // 假目标纬度
	float   fShamTargetHeight;   // 假目标高度
	int     paraCount;           // 激光欺骗GR码长
	int *   LaserWarnCode;       // 激光欺骗GR编码
	float   fLaserWarnEnergy;     // 激光欺骗GR能量
	float   fJamReflectLaserAZLower; // 激光欺骗GR方位下限
	float   fJamReflectLaserAZUpper; // 激光欺骗GR方位上限
	float   fJamReflectLaserELLower; // 激光欺骗GR俯仰下限
	float   fJamReflectLaserELUpper; // 激光欺骗GR俯仰上限
	bool    bActiveJam;	             // 是否可被GR

	/*重载构造函数*/
	_ModelBus_ActiveJam_PARA()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		fShamTargetLon			= 0.;
		fShamTargetLat			= 0.;
		fShamTargetHeight		= 0.;
		LaserWarnCode			= NULL;
		paraCount				= 0;
		fLaserWarnEnergy		= 0.;
		fJamReflectLaserAZLower	= 0.;
		fJamReflectLaserAZUpper  = 0.;
		fJamReflectLaserELLower	= 0.;
		fJamReflectLaserELUpper  = 0.;
		bActiveJam				= false;
	}

	/*重载析构函数*/
	~_ModelBus_ActiveJam_PARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(LaserWarnCode);
	}

	/*重载拷贝构造函数*/
	_ModelBus_ActiveJam_PARA(const _ModelBus_ActiveJam_PARA &jam)
	{
		sRID = NULL;
		LaserWarnCode	= NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_ActiveJam_PARA& operator=(const _ModelBus_ActiveJam_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		paraCount=theStruct.paraCount;
		//SW_Delete(LaserWarnCode);
		SW_Malloc_Int(theStruct.LaserWarnCode,LaserWarnCode,theStruct.paraCount,paraCount);

		ReceiveID		= theStruct.ReceiveID;
		SendID			= theStruct.SendID;
		fTime			= theStruct.fTime;
		fShamTargetLon	= theStruct.fShamTargetLon;
		fShamTargetLat	= theStruct.fShamTargetLat;
		fShamTargetHeight		= theStruct.fShamTargetHeight;
		paraCount		= theStruct.paraCount;
		fLaserWarnEnergy        = theStruct.fLaserWarnEnergy;
		fJamReflectLaserAZLower  = theStruct.fJamReflectLaserAZLower;
		fJamReflectLaserAZUpper  = theStruct.fJamReflectLaserAZUpper;
		fJamReflectLaserELLower  = theStruct.fJamReflectLaserELLower;
		fJamReflectLaserELUpper  = theStruct.fJamReflectLaserELUpper;
		bActiveJam				= theStruct.bActiveJam;

		return *this;
	}

}sActiveJam_PARA;

typedef struct _ModelBus_SmokeJam_PARA // 烟幕GR
{
	char*	sRID;				 // 身份字符串
	int		ReceiveID;           // 接收者ID
	int		SendID;              // 发送者ID
	float	fTime;               // 时间,单位:秒(s)      
	float   fSmogLon;            // 烟幕遮蔽经度
	float   fSmogLat;            // 烟幕遮蔽维度
	float   fSmogHeight;         // 烟幕遮蔽高度
	float   fSmogRadius;         // 烟幕遮蔽半径
	int     ShadeAZLower;        // 烟幕遮蔽方位下限
	int     ShadeAZUpper;        // 烟幕遮蔽方位上限
	int     ShadeELLower;        // 烟幕遮蔽俯仰下限
	int     ShadeELUpper;        // 烟幕遮蔽俯仰上限
	bool    bSmokeJam;           // 是否可被GR

	/*重载构造函数*/
	_ModelBus_SmokeJam_PARA()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		fSmogLon				= 0.;
		fSmogLat				= 0.;
		fSmogHeight				= 0.;
		fSmogRadius             = 0.;
		ShadeAZLower			= 0;
		ShadeAZUpper			= 0;
		ShadeELLower			= 0;
		ShadeELUpper            = 0;
		bSmokeJam				= false;
	}

	/*重载析构函数*/
	~_ModelBus_SmokeJam_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_SmokeJam_PARA(const _ModelBus_SmokeJam_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_SmokeJam_PARA& operator=(const _ModelBus_SmokeJam_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ReceiveID		= theStruct.ReceiveID;
		SendID			= theStruct.SendID;
		fTime           = theStruct.fTime;
		fSmogLon		= theStruct.fSmogLon;
		fSmogLat		= theStruct.fSmogLat;
		fSmogHeight		= theStruct.fSmogHeight;
		fSmogRadius     = theStruct.fSmogRadius;
		ShadeAZLower	= theStruct.ShadeAZLower;
		ShadeAZUpper	= theStruct.ShadeAZUpper;
		ShadeELLower	= theStruct.ShadeELLower;
		ShadeELUpper    = theStruct.ShadeELUpper;
		bSmokeJam		= theStruct.bSmokeJam;
		return *this;
	}

}sSmokeJam_PARA;

typedef struct _ModelBus_EOMissileLaunch_Para // 导弹发射
{
	char*	sRID;				// 身份字符串
	int		ReceiveID;          // 接收者ID
	int		SendID;             // 发送者ID
	float   fTime;			    // 时间,单位:秒(s)
	float   fLon;				// 经度,单位:度
	float   fLat;				// 纬度,单位:度
	float   fHeight;			// 高度,单位:米(m)
	float   fVelocity;          // 速度,单位:米/秒

	/*重载构造函数*/
	_ModelBus_EOMissileLaunch_Para()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		fLon					= 0.;
		fLat					= 0.;
		fHeight					= 0.;
		fVelocity				= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_EOMissileLaunch_Para()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EOMissileLaunch_Para(const _ModelBus_EOMissileLaunch_Para &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_EOMissileLaunch_Para& operator=(const _ModelBus_EOMissileLaunch_Para& theStruct)
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
		fLon			= theStruct.fLon;
		fLat			= theStruct.fLat;
		fHeight			= theStruct.fHeight;
		fVelocity		= theStruct.fVelocity;

		return *this;
	}

}sEOMissileLaunch_PARA;


typedef struct _ModelBus_EOMissileExplode_Para // 导弹爆炸
{
	char*	sRID;				//身份字符串
	int		ReceiveID;          // 接收者ID
	int		SendID;             // 发送者ID
	float   fTime;			    // 时间,单位:秒(s)
	float   fLon;				// 经度,单位:度
	float   fLat;				// 纬度,单位:度
	float   fHeight;			// 高度,单位:米(m)
	float   fDst;               // 脱靶量,单位:米(m)

	/*重载构造函数*/
	_ModelBus_EOMissileExplode_Para()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		fLon					= 0.;
		fLat					= 0.;
		fHeight					= 0.;
		fDst					= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_EOMissileExplode_Para()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EOMissileExplode_Para(const _ModelBus_EOMissileExplode_Para &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_EOMissileExplode_Para& operator=(const _ModelBus_EOMissileExplode_Para& theStruct)
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
		fLon			= theStruct.fLon;
		fLat			= theStruct.fLat;
		fHeight			= theStruct.fHeight;
		fDst			= theStruct.fDst;

		return *this;
	}

}sEOMissileExplode_PARA;

typedef struct _ModelBus_LaserTargetIndication_Para// 激光目标指示(导弹->462/463/464)jcg
{
	char*	sRID;				// 身份字符串
	int		ReceiveID;          // 接收者ID
	int		SendID;             // 发送者ID
	float	fTime;			    // 时间,单位:秒(s)
	int 	MissileID;          // 导弹ID
	float	fLon;               // 导弹经度,单位:度
	float	fLat;               // 导弹纬度,单位:度
	float	fHeight;            // 导弹高度,单位:米(m)
	float   fTargetLon;         // 目标经度,单位:度
	float   fTargetLat;         // 目标纬度,单位:度
	float   fTargetHeight;      // 目标高度,单位:米(m)
	float   fWaveLength;        // 指示器激光波长
	int     paraCount;          // 激光码长
	int*    PulseCode;          // 激光码型

	/*重载构造函数*/
	_ModelBus_LaserTargetIndication_Para()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		MissileID				= 0;
		fLon					= 0.;
		fLat					= 0.;
		fHeight					= 0.;
		fTargetLon				= 0.;
		fTargetLat				= 0.;
		fTargetHeight			= 0.;
		fWaveLength				= 0.;
		PulseCode				= NULL;
		paraCount				= 0;
	}

	/*重载析构函数*/
	~_ModelBus_LaserTargetIndication_Para()
	{
		SW_Free_Char(sRID);
		SW_Delete(PulseCode);
	}

	/*重载拷贝构造函数*/
	_ModelBus_LaserTargetIndication_Para(const _ModelBus_LaserTargetIndication_Para &jam)
	{
		sRID = NULL;
		PulseCode	= NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_LaserTargetIndication_Para& operator=(const _ModelBus_LaserTargetIndication_Para& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		paraCount=theStruct.paraCount;
		//SW_Delete(PulseCode);
		SW_Malloc_Int(theStruct.PulseCode,PulseCode,theStruct.paraCount,paraCount);

		ReceiveID		= theStruct.ReceiveID;
		SendID			= theStruct.SendID;
		fTime			= theStruct.fTime;
		MissileID       = theStruct.MissileID;
		fLon			= theStruct.fLon;
		fLat			= theStruct.fLat;
		fHeight			= theStruct.fHeight;
		fTargetLon		= theStruct.fTargetLon;
		fTargetLat		= theStruct.fTargetLat;
		fTargetHeight	= theStruct.fTargetHeight;
		fWaveLength		= theStruct.fWaveLength;

		return *this;
	}

}sLaserTargetIndication_PARA;

typedef struct _ModelBus_IRWarnCom_Para // 红外告警信息(462/465->461)jcg
{
	char*	sRID;				// 身份字符串
	int		ReceiveID;          // 接收者ID
	int		SendID;             // 发送者ID
	float	fTime;              // 时间,单位:秒(s)
	int		ObjectID;           // 目标编号
	float	fAZ;                // 目标方位,单位:度
	float	fEL;                // 目标仰角,单位:度

	/*重载构造函数*/
	_ModelBus_IRWarnCom_Para()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		ObjectID				= 0;
		fAZ						= 0.;
		fEL						= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_IRWarnCom_Para()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_IRWarnCom_Para(const _ModelBus_IRWarnCom_Para &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_IRWarnCom_Para& operator=(const _ModelBus_IRWarnCom_Para& theStruct)
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
		ObjectID		= theStruct.ObjectID;
		fAZ				= theStruct.fAZ;
		fEL				= theStruct.fEL;

		return *this;
	}

}sIRWarnCom_PARA;

typedef struct _ModelBus_LaserWarnCom_Para	// 激光告警信息(462/463/464->461)jcg
{
	char*	sRID;				// 身份字符串
	int		ReceiveID;          // 接收者ID
	int		SendID;             // 发送者ID
	float	fTime;              // 时间,单位:秒(s)
	int		ObjectID;           // 目标编号
	float   fLaserWarnAZ;       // 目标方位,单位:度
	float   fLaserWarnEL;       // 目标仰角,单位:度
	float   fLaserWarnWL;       // 激光告警波长
	float   fPulseWidth;        // 激光脉冲宽度
	int     paraCount;          // 激光编码个数
	int *   LaserWarnCode;      // 激光告警码型

	/*重载构造函数*/
	_ModelBus_LaserWarnCom_Para()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		ObjectID				= 0;
		fLaserWarnAZ			= 0.;
		fLaserWarnEL			= 0.;
		fLaserWarnWL			= 0.;
		fPulseWidth				= 0.;
		LaserWarnCode			= NULL;
		paraCount				= 0;
	}

	/*重载析构函数*/
	~_ModelBus_LaserWarnCom_Para()
	{
		SW_Free_Char(sRID);
		SW_Delete(LaserWarnCode);
	}

	/*重载拷贝构造函数*/
	_ModelBus_LaserWarnCom_Para(const _ModelBus_LaserWarnCom_Para &jam)
	{
		sRID = NULL;
		LaserWarnCode	= NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_LaserWarnCom_Para& operator=(const _ModelBus_LaserWarnCom_Para& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		paraCount=theStruct.paraCount;
		//SW_Delete(LaserWarnCode);
		SW_Malloc_Int(theStruct.LaserWarnCode,LaserWarnCode,theStruct.paraCount,paraCount);

		ReceiveID		= theStruct.ReceiveID;
		SendID			= theStruct.SendID;
		fTime			= theStruct.fTime;
		ObjectID		= theStruct.ObjectID;
		fLaserWarnAZ	= theStruct.fLaserWarnAZ;
		fLaserWarnEL	= theStruct.fLaserWarnEL;
		fLaserWarnWL	= theStruct.fLaserWarnWL;
		fPulseWidth     = theStruct.fPulseWidth;
		paraCount		= theStruct.paraCount;

		return *this;
	}

}sLaserWarnCom_PARA;	

typedef struct _ModelBus_JamInfo_Para// GR结果上报(462/463/464/465->461)ln
{
	char*	sRID;				// 身份字符串
	int		ReceiveID;          // 接收者ID
	int		SendID;             // 发送者ID
	float	fTime;              // 时间,单位:秒(s)
	int		ObjectID;           // GR目标ID
	bool    JamInfo;            // GR实施结果,(ture:GR结束,false:未实施GR)

	/*重载构造函数*/
	_ModelBus_JamInfo_Para()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		ObjectID				= 0;
		JamInfo					= false;
	}

	/*重载析构函数*/
	~_ModelBus_JamInfo_Para()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_JamInfo_Para(const _ModelBus_JamInfo_Para &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_JamInfo_Para& operator=(const _ModelBus_JamInfo_Para& theStruct)
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
		ObjectID		= theStruct.ObjectID;
		JamInfo			= theStruct.JamInfo;

		return *this;
	}

}sJamInfo_PARA;

typedef struct _ModelBus_StartJamOrder_Para// GR指令(烟幕\角度\激光GR)(461->462/463/464/465)ln
{
	char*	sRID;				 // 身份字符串
	int		ReceiveID;           // 接收者ID
	int		SendID;              // 发送者ID
	float	fTime;               // 时间,单位:秒(s)
	int		ObjectID;            // GR目标ID
	float	fAZ;                 // GR方位,单位:度
	float	fEL;                 // GR仰角,单位:度

	/*重载构造函数*/
	_ModelBus_StartJamOrder_Para()
	{
		sRID					= NULL;
		ReceiveID				= 0;
		SendID					= 0;
		fTime					= 0.;
		ObjectID				= 0;
		fAZ						= 0.;
		fEL						= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_StartJamOrder_Para()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_StartJamOrder_Para(const _ModelBus_StartJamOrder_Para &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_StartJamOrder_Para& operator=(const _ModelBus_StartJamOrder_Para& theStruct)
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
		ObjectID		= theStruct.ObjectID;
		fAZ				= theStruct.fAZ;
		fEL				= theStruct.fEL;

		return *this;
	}
}sStartJamOrder_PARA;

// 精确制导武器（静态输入）
// 增加光电制导方式	ZR
typedef struct _ModelBus_aEOGuideMissile_SET_PARA
{
	char*	sRID;			// 身份字符串
	int		ID;				// ID
	float   fLon;			// 经度,单位:度
	float   fLat;			// 纬度,单位:度
	float   fHeight;		// 高度,单位:米(m)
	float   fTargetLon; 	// 经度,单位:度
	float   fTargetLat;		// 纬度,单位:度
	float   fTargertHeight;	// 高度,单位:米(m)
	DKDMS::Enum_EGuideMode EGuideMode;		  // 光电制导方式

	/*重载构造函数*/
	_ModelBus_aEOGuideMissile_SET_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		fLon					= 0.;
		fLat					= 0.;
		fHeight					= 0.;
		fTargetLon              = 0.;
		fTargetLat              = 0.;
		fTargertHeight          = 0.;
		EGuideMode              = DKDMS::Enum_EGuideMode_0;
	}

	/*重载析构函数*/
	~_ModelBus_aEOGuideMissile_SET_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aEOGuideMissile_SET_PARA(const _ModelBus_aEOGuideMissile_SET_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aEOGuideMissile_SET_PARA& operator=(const _ModelBus_aEOGuideMissile_SET_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID				= theStruct.ID;
		fLon			= theStruct.fLon;
		fLat			= theStruct.fLat;
		fHeight			= theStruct.fHeight;
		fTargetLon		= theStruct.fTargetLon;
		fTargetLat		= theStruct.fTargetLat;
		fTargertHeight	= theStruct.fTargertHeight;
		EGuideMode      = theStruct.EGuideMode;
		return *this;
	}

}aEOGuideMissile_SET_PARA;

typedef struct _ModelBus_aInfraWarnMissile_PARA// 红外ZC告警能力导弹输出接口jcg
{
	char*	sRID;			   // 身份字符串
	int		ID;				   // 导弹ID
	float	fLon;			   // 经度,单位:度	
	float	fLat;			   // 纬度,单位:度	
	float	fHeight;		   // 高度,单位:米(m)
	DKDMS::Enum_EGuideMode GuideMode; // 制导类型

	/*重载构造函数*/
	_ModelBus_aInfraWarnMissile_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		fLon					= 0.;
		fLat					= 0.;
		fHeight					= 0.;
		GuideMode				= DKDMS::Enum_EGuideMode_0;
	}

	/*重载析构函数*/
	~_ModelBus_aInfraWarnMissile_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aInfraWarnMissile_PARA(const _ModelBus_aInfraWarnMissile_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aInfraWarnMissile_PARA& operator=(const _ModelBus_aInfraWarnMissile_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID				= theStruct.ID;
		fLon			= theStruct.fLon;
		fLat			= theStruct.fLat;
		fHeight			= theStruct.fHeight;
		GuideMode		= theStruct.GuideMode;

		return *this;
	}

}aInfraWarnMissile_PARA;

typedef struct _ModelBus_aLaserWarnMissile_PARA// 激光告警能力导弹输出接口jcg
{
	char*	sRID;			   // 身份字符串
	int		ID;				   // ID
	float	fILon;             // 目标指示器经度,单位:度
	float	fILat;             // 目标指示器纬度,单位:度
	float	fIHeight;          // 目标指示器高度,单位:米(m)
	float	fTargetLon;		   // 经度,单位:度	
	float	fTargetLat;		   // 纬度,单位:度	
	float	fTargetHeight;	   // 高度,单位:米(m)
	DKDMS::Enum_EGuideMode GuideMode; // 制导类型
	float	fWaveLength;       // 激光波长,单位:微米(um)
	int		paraCount;         // 激光编码个数
	int		*PulseCode;        // 激光码型
		
	/*重载构造函数*/
	_ModelBus_aLaserWarnMissile_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		fILon					= 0.;
		fILat					= 0.;
		fIHeight				= 0.;
		fTargetLon              = 0.;
		fTargetLat              = 0.;
		fTargetHeight           = 0.;
		GuideMode				= DKDMS::Enum_EGuideMode_0;
		fWaveLength				= 0.;
		PulseCode				= NULL;
		paraCount				= 0;
	}

	/*重载析构函数*/
	~_ModelBus_aLaserWarnMissile_PARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(PulseCode);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aLaserWarnMissile_PARA(const _ModelBus_aLaserWarnMissile_PARA &jam)
	{
		sRID = NULL;
		PulseCode	= NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aLaserWarnMissile_PARA& operator=(const _ModelBus_aLaserWarnMissile_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		paraCount=theStruct.paraCount;
		//SW_Delete(PulseCode);
		SW_Malloc_Int(theStruct.PulseCode,PulseCode,theStruct.paraCount,paraCount);

		ID				= theStruct.ID;
		fILon			= theStruct.fILon;
		fILat			= theStruct.fILat;
		fIHeight			= theStruct.fIHeight;
		GuideMode		= theStruct.GuideMode;
		fTargetLon			= theStruct.fTargetLon;
		fTargetLat			= theStruct.fTargetLat;
		fTargetHeight		= theStruct.fTargetHeight;
		fWaveLength		= theStruct.fWaveLength;

		return *this;
	}

}aLaserWarnMissile_PARA;

typedef struct _ModelBus_aInfraWarn_PARA// 红外告警能力计算jcg
{
	char*	sRID;			// 身份字符串
	int		ID;				// ID
	int		DangerClass;    // 威胁等级
	float	fInfraWarnDst;  // 红外告警距离,单位:米(m)
	float	fInfraWarnPro;	// 告警概率

	/*重载构造函数*/
	_ModelBus_aInfraWarn_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		DangerClass				= 0;
		fInfraWarnDst			= 0.;
		fInfraWarnPro			= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_aInfraWarn_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aInfraWarn_PARA(const _ModelBus_aInfraWarn_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aInfraWarn_PARA& operator=(const _ModelBus_aInfraWarn_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID				= theStruct.ID;
		DangerClass		= theStruct.DangerClass;
		fInfraWarnDst	= theStruct.fInfraWarnDst;
		fInfraWarnPro	= theStruct.fInfraWarnPro;

		return *this;
	}

}aInfraWarn_PARA;

typedef struct _ModelBus_aPowLaserJam_PARA// 强激光GR等级计算输出jcg
{
	char*	sRID;			      // 身份字符串
	int		ID;				      // ID
	float	fJamAZ;               // GR方位,单位:度
	float	fJamEL;               // GR仰角,单位:度
	float	fJamDst;              // GR有效距离,单位:米(m)
	float	fJamWaveLength;       // GR波长
	float	fPowDensity;          // 功率密度(到达GR目标)
	DKDMS::Enum_PLJamClass PLJamClass;	  // GR等级

	/*重载构造函数*/
	_ModelBus_aPowLaserJam_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		fJamAZ					= 0.;
		fJamEL					= 0.;
		fJamDst					= 0.;
		fJamWaveLength			= 0.;
		fPowDensity				= 0.;
		PLJamClass				= DKDMS::Enum_PLJamClass_0;
	}

	/*重载析构函数*/
	~_ModelBus_aPowLaserJam_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aPowLaserJam_PARA(const _ModelBus_aPowLaserJam_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aPowLaserJam_PARA& operator=(const _ModelBus_aPowLaserJam_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID				= theStruct.ID;
		fJamAZ			= theStruct.fJamAZ;
		fJamEL			= theStruct.fJamEL;
		fJamDst			= theStruct.fJamDst;
		fJamWaveLength	= theStruct.fJamWaveLength;
		fPowDensity		= theStruct.fPowDensity;
		PLJamClass		= theStruct.PLJamClass;

		return *this;
	}

}aPowLaserJam_PARA;

typedef struct _ModelBus_aLaserWarn_PARA// 激光告警能力计算输出接口jcg
{
	char*	sRID;			// 身份字符串
	int		ID;				// ID
	float	fWarnAZ;        // 告警方位,单位:度
	float	fWarnEL;        // 告警仰角,单位:度
	float	fWaveLength;    // 激光波长,单位:微米(um)
	int		paraCount;      // 激光码长
	int		*PulseCode;     // 激光码型
	float	fLaserWarnDst;  // 激光告警最大距离,单位:米(m)
	float	fIdentifyPro;   // TC概率

	/*重载构造函数*/
	_ModelBus_aLaserWarn_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		fWarnAZ					= 0.;
		fWarnEL					= 0.;
		fWaveLength				= 0.;
		PulseCode				= NULL;
		paraCount				= 0;
		fLaserWarnDst			= 0.;
		fIdentifyPro			= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_aLaserWarn_PARA()
	{
		SW_Free_Char(sRID);
		SW_Delete(PulseCode);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aLaserWarn_PARA(const _ModelBus_aLaserWarn_PARA &jam)
	{
		sRID = NULL;
		PulseCode	= NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aLaserWarn_PARA& operator=(const _ModelBus_aLaserWarn_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		paraCount=theStruct.paraCount;
		//SW_Delete(PulseCode);
		SW_Malloc_Int(theStruct.PulseCode,PulseCode,theStruct.paraCount,paraCount);

		ID				= theStruct.ID;
		fWarnAZ			= theStruct.fWarnAZ;
		fWarnEL			= theStruct.fWarnEL;
		fWaveLength		= theStruct.fWaveLength;
		fLaserWarnDst	= theStruct.fLaserWarnDst;
		fIdentifyPro	= theStruct.fIdentifyPro;

		return *this;
	}

}aLaserWarn_PARA;

typedef struct _ModelBus_aLaserAngleJam_PARA// 激光角度欺骗GR能力输出
{
	char*	sRID;			     // 身份字符串
	int		ID;				     // ID
	int		AZLower;             // GR方位下限
	int		AZUpper;             // GR方位上限
	int		ELLower;             // GR俯仰下限
	int		ELUpper;             // GR俯仰上限
	float	fJamDst;             // GR距离,单位:米(m)
	float	fDeceivePro;         // 欺骗概率
	float	fJamRange;	         // 欺骗GR有效距离,单位:米(m)

	/*重载构造函数*/
	_ModelBus_aLaserAngleJam_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		AZLower					= 0;
		AZUpper					= 0;
		ELLower					= 0;
		ELUpper					= 0;
		fJamDst					= 0.;
		fDeceivePro				= 0.;
		fJamRange				= 0.;
	}

	/*重载析构函数*/
	~_ModelBus_aLaserAngleJam_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aLaserAngleJam_PARA(const _ModelBus_aLaserAngleJam_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aLaserAngleJam_PARA& operator=(const _ModelBus_aLaserAngleJam_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID				= theStruct.ID;
		AZLower			= theStruct.AZLower;
		AZUpper			= theStruct.AZUpper;
		ELLower			= theStruct.ELLower;
		ELUpper			= theStruct.ELUpper;
		fJamDst			= theStruct.fJamDst;
		fDeceivePro		= theStruct.fDeceivePro;
		fJamRange		= theStruct.fJamRange;
		return *this;
	}


}aLaserAngleJam_PARA;

typedef struct _ModelBus_aSmogJam_PARA// 烟幕GR能力输出
{
	char*	sRID;			  // 身份字符串
	int		ID;				  // ID
	float	fSmogLon;         // 烟幕中心的经度,单位:度
	float	fSmogLat;         // 烟幕中心的维度,单位:度
	float	fSmogHeight;      // 烟幕中心的高度,单位:米(m)
	float	fSmogRadius;      // 烟幕半径
	float	fSmogArea;        // 成烟面积
	int		ShadeAZLower;     // 遮蔽方位下限
	int		ShadeAZUpper;     // 遮蔽方位上限
	int		ShadeELLower;     // 遮蔽俯仰下限
	int		ShadeELUpper;     // 遮蔽俯仰上限
	float	fSmogPersistTime; // 烟幕持续时间
	bool	bSmokeJam;	      // GR

	/*重载构造函数*/
	_ModelBus_aSmogJam_PARA()
	{
		sRID					= NULL;
		ID						= 0;
		fSmogLon				= 0.;
		fSmogLat				= 0.;
		fSmogHeight				= 0.;
		fSmogRadius				= 0.;
		fSmogArea				= 0.;
		ShadeAZLower			= 0;
		ShadeAZUpper			= 0;
		ShadeELLower			= 0;
		ShadeELUpper			= 0;
		fSmogPersistTime		= 0.;
		bSmokeJam				= false;
	}

	/*重载析构函数*/
	~_ModelBus_aSmogJam_PARA()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aSmogJam_PARA(const _ModelBus_aSmogJam_PARA &jam)
	{
		sRID = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_aSmogJam_PARA& operator=(const _ModelBus_aSmogJam_PARA& theStruct)
	{
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		ID					= theStruct.ID;
		fSmogLon			= theStruct.fSmogLon;
		fSmogLat			= theStruct.fSmogLat;
		fSmogHeight			= theStruct.fSmogHeight;
		fSmogRadius			= theStruct.fSmogRadius;
		fSmogArea			= theStruct.fSmogArea;
		ShadeAZLower		= theStruct.ShadeAZLower;
		ShadeAZUpper		= theStruct.ShadeAZUpper;
		ShadeELLower		= theStruct.ShadeELLower;
		ShadeELUpper		= theStruct.ShadeELUpper;
		fSmogPersistTime	= theStruct.fSmogPersistTime;
		bSmokeJam			= theStruct.bSmokeJam;

		return *this;
	}

}aSmogJam_PARA;

#pragma pack()

#endif
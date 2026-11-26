#ifndef _MENSTRUCT_MISSILE_H_
#define _MENSTRUCT_MISSILE_H_

#include "MEnStruct_Macros.h"

//#pragma pack(push)
#pragma pack(1)

/// 输入：初始输入参数（界面初始文件）line445
typedef struct _ModelBus_sMissile_Set_PARA
{
    char*	sRID;//身份字符串
	int	nMissileID;//实体ID
    int    PlatID;//导弹平台ID
	int nActPlatID;//实际搭载的运动平台ID（机载或舰载导弹，供行为模型用）
    int	nRadarID;//搭载的雷达ID
	int	nTgtID;//目标ID//暂作为实际搭载飞机ID
    char*	EquipmentName;		//装备名称
	char*	EquipmentType;		//装备类型0:固定 1:非固定
	DKDMS::Enum_ATT		ATT;		//敌我属性
	float	fLon;				//经度，单位：度
	float	fLat;				//纬度，单位：度
	float	fHeight;			//高度，单位：度
	float	fTgtLon;				//目标经度，单位：度
	float	fTgtLat;				//目标纬度，单位：度
	float	fTgtHeight;			//目标高度，单位：度
	float  fLanchTime;//发射时间点s
	float	fSpeed;//导弹速度m/s
	float  fOffsetDis;//平均诱骗距离m
	float  fJamValidProbability;//GR有效率%
	int nBackup;//int型备用字段
	float  fBackup;//float型备用字段

	/*重载构造函数*/
	_ModelBus_sMissile_Set_PARA()
	{
		/*memset(this,0,sizeof(*this));
		ATT           = DKDMS::Enum_ATT_1;
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;*/

		sRID = NULL;
		nMissileID = 0;//实体ID
		PlatID = 0;//导弹平台ID
		nActPlatID = 0;//实际搭载的运动平台ID（机
		nRadarID = 0;//搭载的雷达ID
		nTgtID = 0;//目标ID//暂作为实际搭载飞机ID
		EquipmentName = NULL;
		EquipmentType = NULL;
		ATT           = DKDMS::Enum_ATT_1;

		fLon = 0;				//经度，
		fLat = 0;				//纬度，
		fHeight = 0;			//高度，
		fTgtLon = 0;				//目
		fTgtLat = 0;				//目
		fTgtHeight = 0;			//目
		fLanchTime = 0;//发射时间点s
		fSpeed = 0;//导弹速度m/s
		fOffsetDis = 0;//平均诱骗距离m
		fJamValidProbability = 0;//
        nBackup = 0;//int型备用字段
		fBackup = 0;//float型备用字段
	}

	/*重载析构函数*/
	~_ModelBus_sMissile_Set_PARA()
	{
		SW_Free_Char(sRID);

		SW_Free_Char(EquipmentName);

		SW_Free_Char(EquipmentType);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sMissile_Set_PARA(const _ModelBus_sMissile_Set_PARA &jam)
	{
		sRID = NULL;
		EquipmentName = NULL;
		EquipmentType = NULL;
		*this = jam;
	}

	/*重载=*/
	_ModelBus_sMissile_Set_PARA& operator=(const _ModelBus_sMissile_Set_PARA& theStruct)
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

		nMissileID        = theStruct.nMissileID;
		PlatID          = theStruct.PlatID;
		nActPlatID		= theStruct.nActPlatID;
		nRadarID     = theStruct.nRadarID;
		nTgtID     = theStruct.nTgtID;
		ATT           = theStruct.ATT;

		fLon          = theStruct.fLon;
		fLat          = theStruct.fLat;
		fHeight       = theStruct.fHeight;
		fTgtLon          = theStruct.fTgtLon;
		fTgtLat          = theStruct.fTgtLat;
		fTgtHeight       = theStruct.fTgtHeight;
		fLanchTime       = theStruct.fLanchTime;
		fSpeed      = theStruct.fSpeed;
		fOffsetDis        = theStruct.fOffsetDis;
		fJamValidProbability        = theStruct.fJamValidProbability;
		nBackup = theStruct.nBackup;
		fBackup = theStruct.fBackup;

		return *this;
	}
} sMissile_Set_PARA;

///输入：打击目标信息
typedef struct _ModelBus_sMISSILE_Set_COMMAND
{
    /// 本导弹标识信息
    char*		sRID;           /// 身份字符串
    int        nMissileID;   /// 实体ID
    /// 目标信息
    unsigned short    wTarPlatID;
    DKDMS::MISSILE_STATE     iMissileState;
    double              dTarSpyLon;
    double              dTarSpyLat;
    double              dTarSpyHeight;
    ///
    _ModelBus_sMISSILE_Set_COMMAND()
    {
        sRID               = NULL;
        nMissileID       = 0;
        wTarPlatID       = 0;
        iMissileState   = DKDMS::MISSILE_WAIT;
        dTarSpyLon       = 0;
        dTarSpyLat       = 0;
        dTarSpyHeight   = 0;
    }
    ///
    ~_ModelBus_sMISSILE_Set_COMMAND()
    {
        SW_Free_Char(sRID);
    }
    ///
    _ModelBus_sMISSILE_Set_COMMAND(const _ModelBus_sMISSILE_Set_COMMAND& rv)
    {
        sRID  = NULL;
        *this = rv;
    }
    ///
    _ModelBus_sMISSILE_Set_COMMAND& operator=(const _ModelBus_sMISSILE_Set_COMMAND& theStruct)
    {
        if( this==&theStruct )
        {
            return *this;
        }
        /// -------
        SW_Malloc_Char(theStruct.sRID,sRID);
        ///
        nMissileID      = theStruct.nMissileID;
        wTarPlatID      = theStruct.wTarPlatID;
        iMissileState  = theStruct.iMissileState;
        dTarSpyLon      = theStruct.dTarSpyLon;
        dTarSpyLat      = theStruct.dTarSpyLat;
        dTarSpyHeight  = theStruct.dTarSpyHeight;
        ///
        return *this;
    }

} sMISSILE_Set_COMMAND;

/// 输出：导弹状态信息（主要是 目标平台、导弹下一时刻位置 等信息）
typedef struct _ModelBus_sMISSILE_STATUS
{
   char*		sRID;			//身份字符串
	int nMissileID;		//实体ID
	int PlatID;			//导弹平台ID
	int nActPlatID;//实际搭载的运动平台ID（机载或舰载导弹，供行为模型用）
	double CurrentTime;				//仿真时间戳单位：s
	char* MissileName;			//导弹名称单位：无范围：字符串最长为字节
	char* sMissileType;			//导弹类型单位：无范围：字符串最长为字节
	int nSeekMode;//制导方式
	DKDMS::Enum_ATT  PATT;			//平台敌我属性

	int nTgtID;//打击目标ID//暂时作为搭载飞机ID输入
	double dLonge;					//经度单位：度范围：-180-180 精度：.00001°，东经为正，西经为负。如东经°＇表示为.5°。
	double dLat;					//纬度单位：度范围：-90-90 精度：.00001°，表示南纬，表示北纬。
	float  fHeight;					//高度单位：m 范围：-10^9-10^9 精度：.01m，北纬为正，南纬为负。
	double dSpeed;					//速度大小单位: m/s
	double dCourse;					//航向单位：度范围：-360 精度：.1度，~360°,正北为0°
	double dPitch;					//运动俯仰角度 单位：度
	double dRoll;					//运动横滚角度 单位：度
    DKDMS::MISSILE_STATE	 iMissileState;			//导弹的状态，WAIT为未发射，FIRSTDETECT为中制导，SECONDDETECT为末制导，HITTED为命中目标，NOHITTED为未命中目标,INVALID失效

	float fKRadius;                                 //杀伤半径（m）
    bool bJamed;//是否受GR(受GR为true)
    double dRelativeDis;//弹目距离
    float	fTgtCourse;			//目标相对导弹的方位角，单位：度
	float	fTgtPitch;			//目标相对导弹的俯仰角，单位：度
	float fResTime;//剩余爆炸时间

	int nBackup;//int型备用字段
	float  fBackup;//float型备用字段

	_ModelBus_sMISSILE_STATUS()
	{
	    sRID = NULL;
	    nMissileID = 0;
	    PlatID = 0;
		nActPlatID = 0;
		CurrentTime = 0;
		nMissileID   = 0;
		MissileName = NULL;
		sMissileType = NULL;
		nSeekMode = 0;
		PATT     =  DKDMS::Enum_ATT_0;

		nTgtID = 0;
		dLonge   = 0;
		dLat     = 0;
		fHeight  = 0;
		dSpeed =0;
		dCourse  = 0;
		dPitch = 0;
		dRoll = 0;
		iMissileState = DKDMS::MISSILE_WAIT;
		fKRadius = 0;
		bJamed = false;
		dRelativeDis = 0;
		fTgtCourse =0;
        fTgtPitch = 0;
		fResTime = 0.0;

		nBackup = 0;
		fBackup = 0.0;
	}

	/*重载析构函数*/
	~_ModelBus_sMISSILE_STATUS()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(MissileName);
		SW_Free_Char(sMissileType);
	}
	/*重载拷贝构造函数*/
	_ModelBus_sMISSILE_STATUS(const _ModelBus_sMISSILE_STATUS &theStruct)
	{
		sRID = NULL;
		MissileName = NULL;
		sMissileType = NULL;
		*this = theStruct;
	}

	/*重载=*/
	_ModelBus_sMISSILE_STATUS& operator=(const _ModelBus_sMISSILE_STATUS& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.MissileName,MissileName);
		SW_Malloc_Char(theStruct.sMissileType,sMissileType);
		nMissileID			   = theStruct.nMissileID;
		PlatID           = theStruct.PlatID;
		nActPlatID = theStruct.nActPlatID;
		CurrentTime		   = theStruct.CurrentTime;
		nSeekMode = theStruct.nSeekMode;
		PATT      = theStruct.PATT;
		nTgtID = theStruct.nTgtID;
		dLonge		= theStruct.dLonge;
		dLat		= theStruct.dLat;
		fHeight  = theStruct.fHeight;
		dSpeed           = theStruct.dSpeed;
		dCourse		   = theStruct.dCourse;
		dPitch      = theStruct.dPitch;
		dRoll		= theStruct.dRoll;
		iMissileState  = theStruct.iMissileState;
		fKRadius		= theStruct.fKRadius;
		bJamed		= theStruct.bJamed;
		dRelativeDis		= theStruct.dRelativeDis;
		fTgtCourse = theStruct.fTgtCourse;
		fTgtPitch = theStruct.fTgtPitch;
		fResTime = theStruct.fResTime;

		nBackup = theStruct.nBackup;
		fBackup = theStruct.fBackup;
		return *this;
	}
  
} sMISSILE_STATUS;

#pragma pack()

#endif // _MENSTRUCT_MISSILE_H_


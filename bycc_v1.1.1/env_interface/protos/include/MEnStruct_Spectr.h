/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.1		按照年(个数位)月日组合的方式	**
**版    本:	2015.04.01  zoubz修改											**
*************************************************************************/

#include "MEnStruct_Macros.h"

#ifndef MEN_STRUCT_SPECTR
#define MEN_STRUCT_SPECTR


#include <string.h>
#pragma pack(1)

/*/ Add By Hanm 2011/04/11*/
/*************************************************************
*                   频谱管理软件新增加部分 （注：刘�依锩婷挥校�                  *
*************************************************************/
namespace DKDMS{//namespace DMS start zm20170912
enum Enum_CalcType	                // 静态计算类型
{	
	Enum_CalcType_EM = 0,			// 场强计算
	Enum_CalcType_EM_SEM = 1,		// 场强、功率计算
	Enum_CalcType_EM_SEM_SNR = 2,	// 场强、功率、信噪比计算
	Enum_CalcType_SEM = 3,			// 功率计算
	Enum_CalcType_SEM_SNR = 4,		// 功率、信噪比计算
	Enum_CalcType_SNR = 5,			// 信噪比计算
};
}

//时间和频率信息
typedef struct STIME_FREQ
{
	float fStartTime;			//开始时间
	float fEndTime;				//结束时间
	float fFreq;				//频率
	float fBand;				//频率带宽

	STIME_FREQ()
	{
		fStartTime = 0;
		fEndTime   = 0;
		fFreq	   = 0;
		fBand	   = 0;
	}

	~STIME_FREQ()
	{

	}

	/*重载拷贝构造函数*/
	STIME_FREQ(const STIME_FREQ &ProtectInfo )
	{
		*this = ProtectInfo;
	}

	/*重载=*/
	STIME_FREQ& operator = (const STIME_FREQ& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		memcpy( this, &theStruct, sizeof( STIME_FREQ ) );
		return *this;
	}
} sProtectFreq, sOpenWndFreq;

//频率信息
typedef struct SFREQ_INFO
{	
	float fFreq;				//频率
	float fBand;				//频率带宽

	SFREQ_INFO()
	{		
		fFreq	   = 0;
		fBand	   = 0;
	}

	~SFREQ_INFO()
	{
	}

	/*重载拷贝构造函数*/
	SFREQ_INFO(const SFREQ_INFO &ProtectInfo )
	{
		*this = ProtectInfo;
	}

	/*重载=*/
	SFREQ_INFO& operator = (const SFREQ_INFO& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		memcpy( this, &theStruct, sizeof( SFREQ_INFO ) );
		return *this;
	}
}sCurProtFreq, sFreqInfo;


//接收机信息
typedef struct RECEIVE_INFO						
{	
	float fRevGt;   			//接收机天线增益
	float fsenseitive;			//接收机灵敏度
	float AnteDir;				//接收机天线方向
	float AnteEl;				//接收机天线俯仰	
	float AnteHeight;			//接收机天线高度	
	DKDMS::Enum_POT RevPOT;		    //接收机极化类型
	float RevLoss;				//接收机损耗	
	float RBand;				//接收机带宽
	float RevSNR;				//接收机信噪比
	float fBandRespond;			//接收机带外响应
	float fStrayCtrl;			//接收机杂散抑制
	float centerfrequency;		//中心频率

	RECEIVE_INFO()
	{
		fRevGt		  = 0;
		fsenseitive	  = 0;
		AnteDir		  = 0;
		AnteEl		  = 0;
		AnteHeight    = 0;
		RevPOT		  = DKDMS::Enum_POT_0;
		RevLoss		  = 0;		
		RBand		  = 0;
		RevSNR		  = 0;
		fBandRespond  = 0;
		fStrayCtrl    = 0;
		centerfrequency = 0;	
	}

	/*重载析构函数*/
	~RECEIVE_INFO()
	{	
	}

	/*重载拷贝构造函数*/
	RECEIVE_INFO(const RECEIVE_INFO &RevInfo )
	{
		*this = RevInfo;
	}

	/*重载=*/
	RECEIVE_INFO& operator = (const RECEIVE_INFO& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		memcpy( this, &theStruct, sizeof( RECEIVE_INFO ) );
		return *this;
	}
}sReceiveInfo;

//GR机参数结构体定义（推演过程中输出信息）
typedef  struct  JAM_PARA    	
{
	char		 *sRID;			    //身份识别号
	int			 JammerID;			//GR机ID
	int			 PlatID;		    //GR机所在平台ID
	DKDMS::Enum_ATT	 ATT;				//敌我属性
	DKDMS::Enum_EquipSrc	SRCType;		//装备来源
	char		 *EquipmentName;	//装备名称
	float		 dTime;			 	//仿真时间（s）
	float		 LON;				//经度
	float		 LAT;				//纬度
	float		 Height;			//高度	
	DKDMS::Enum_WorkOnCtrl WorkOnCtrl;		//工作状态
	DKDMS::Enum_JamMode JamMode;	 		//GR样式
	float		 fPt;			    //GR机功率，单位：KW
	float		 fGt;			    //GR机天线主瓣增益，单位：dB
	float		 fAzBeamWidth;		//GR机主瓣水平波束宽度，单位：度
	float		 fElBeamWidth;  	//GR机主瓣俯仰波束宽度，单位：度
	float		 fAntPointAz;		//GR机天线波束方位指向，以正北方向为0度，0°～360°，单位：度）
	float		 fAntPointEl;       //GR机天线波束俯仰指向，以水平面为0度，向上为正，单位：度
	DKDMS::Enum_Priority Priority;		    //保护优先级						
	float		 fSendCenterRF;		//发射中心频率					
	float		 fSendBand;			//发射信号带宽	
	int			 lProtCount;		//当前保护频率组数
	sCurProtFreq *pCurProtect;		//当前保护频率
	int			 nRemark;			//备注


	JAM_PARA()
	{
		sRID		  = NULL;
		JammerID	  = 0;
		PlatID		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		EquipmentName = NULL;
		dTime		  = 0;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		WorkOnCtrl	  = DKDMS::Enum_WorkOnCtrl_0;
		JamMode		  = DKDMS::Enum_JamMode_0;
		fPt			  = 0;
		fGt			  = 0;
		fAzBeamWidth  = 0;
		fElBeamWidth  = 0;
		fAntPointAz   = 0;
		fAntPointEl   = 0;
		Priority      = DKDMS::Enum_Priority_0;
		fSendCenterRF = 0;
		fSendBand     = 0;
		lProtCount	  = 0;
		pCurProtect	  = NULL;
		nRemark		  = 0;
	}



	/*重载析构函数*/
	~JAM_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Delete(pCurProtect);
	}


	/*重载拷贝构造函数*/
	JAM_PARA(const JAM_PARA &jamvar)
	{
		*this = jamvar;
	}

	/*重载=*/
	JAM_PARA& operator = (const JAM_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Free_Char(EquipmentName);
		//SW_Delete(pCurProtect);

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		JammerID       = theStruct.JammerID;
		PlatID		   = theStruct.PlatID;
		ATT			   = theStruct.ATT;
		SRCType		   = theStruct.SRCType;

		dTime		   = theStruct.dTime;
		LON			   = theStruct.LON;
		LAT			   = theStruct.LAT;
		Height		   = theStruct.Height;
		WorkOnCtrl	   = theStruct.WorkOnCtrl;	
		JamMode		   = theStruct.JamMode;
		fPt			   = theStruct.fPt;
		fGt			   = theStruct.fGt;
		fAzBeamWidth   = theStruct.fAzBeamWidth;
		fElBeamWidth   = theStruct.fElBeamWidth;
		fAntPointAz    = theStruct.fAntPointAz;
		fAntPointEl    = theStruct.fAntPointEl;		
		Priority       = theStruct.Priority;
		fSendCenterRF  = theStruct.fSendCenterRF;
		fSendBand      = theStruct.fSendBand;
		nRemark        = theStruct.nRemark;
		SW_Malloc_Struct(sCurProtFreq,theStruct.pCurProtect,pCurProtect,theStruct.lProtCount,lProtCount);

		return *this;
	}

}sRadarJamOut, sCommJamOut;

//频谱受GR判断标准
typedef struct JUDGE_STANDARD		
{	
	float fTh1;   			    //正常工作的门限	SNR>fTh1
	float fTh2;					//降级工作门限		fTH1>SNR>fTh2;  故障：fTh2>SNR	

	JUDGE_STANDARD()
	{
		fTh1 = 0;
		fTh2 = 0;
	}

	/*重载析构函数*/
	~JUDGE_STANDARD()
	{	
	}


	/*重载拷贝构造函数*/
	JUDGE_STANDARD(const JUDGE_STANDARD &Judge )
	{
		*this = Judge;
	}

	/*重载=*/
	JUDGE_STANDARD& operator = (const JUDGE_STANDARD& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		fTh1 = theStruct.fTh1;
		fTh2 = theStruct.fTh2;
		return *this;
	}
}sJudgeStandard;

//雷达对象动态中输出
typedef struct  RADAR_PARA			
{
	char				*sRID;			    	//身份识别号
	int					RadarID;	        	//雷达ID号
	int					PlatID;	        		//搭载平台ID号	
	DKDMS::Enum_ATT			ATT;					//敌我属性
	DKDMS::Enum_EquipSrc		SRCType;				//装备来源
	char				*EquipmentName;			//装备名称
	float				dTime;	        		//时间(s)
	float				LON;					//经度
	float				LAT;					//纬度
	float				Height;					//高度	
	DKDMS::Enum_WorkOnCtrl		WorkOnCtrl;				//工作状态
	DKDMS::Enum_SendRevType	SendRevType;			//发射机和接收机工作类型  
	bool				bProtectWQ;				//是否是保护装备（新增）
	sReceiveInfo		RevInfo;				//接收机信息	
	int 				lValidEmitCount;		//当前有效辐射源个数	
	int					*pValidEmitID;    	    //当前有效辐射源ID	
	DKDMS::Enum_Priority		Priority;				//保护优先级				
	float				fSendCenterRF;			//发射中心频率					
	float				fSendBand;				//发射信号带宽				

	//雷达从性能描述文件中获取	
	float				fPt;		        	//雷达发射功率，单位：KW
	float				fGt;		        	//雷达天线主瓣增益，单位：dB
	float				fAzBeamWidth;     		//雷达天线主瓣水平波束宽度，单位：度
	float				fElBeamWidth;	     	//雷达天线主瓣俯仰波束宽度，单位：度
	float				AntAZ;            		//天线方位指向	单位：度
	float				AntEl;             		//天线俯仰指向	单位：度
	float				fAziMax;		     	//方位扫描最大值，单位：度
	float				fAziMin;		     	//方位扫描最小值，单位：度
	DKDMS::Enum_RFT			RFT;            		//射频类型
	float				PRI;               		//脉冲重复间隔
	DKDMS::Enum_PRIT			PRIT;			 		//脉冲重复间隔类型
	float				PW;                		//脉冲宽度
	DKDMS::Enum_POT			POT;			 		//极化类型	
	sJudgeStandard		JudgeStandard;			//判断标准	
	int					lProtCount;				//当前保护频率组数
	sCurProtFreq		*pCurProtect;			//当前保护频率
	int					nRemark;				//备注

	RADAR_PARA()
	{
		sRID		  = NULL;
		RadarID		  = 0;
		PlatID		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		EquipmentName = NULL;
		dTime		  = 0;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		WorkOnCtrl	  = DKDMS::Enum_WorkOnCtrl_0;
		SendRevType	  = DKDMS::Enum_SendRevType_0;
		bProtectWQ		= false;
		memset( &RevInfo, 0,sizeof( sReceiveInfo ) );
		lValidEmitCount = 0;
		pValidEmitID  = NULL;
		Priority      = DKDMS::Enum_Priority_0;
		fSendCenterRF = 0;
		fSendBand	  = 0;

		fPt			  = 0;
		fGt			  = 0;		
		fAzBeamWidth  = 0;
		fElBeamWidth  = 0;
		AntAZ		  = 0;
		AntEl	      = 0;
		fAziMax		  = 0;
		fAziMin		  = 0;
		RFT			  = DKDMS::Enum_RFT_0;
		PRI			  = 0;
		PRIT		  = DKDMS::Enum_PRIT_0;
		PW			  = 0;
		POT			  = DKDMS::Enum_POT_0;
		memset(&JudgeStandard, 0,sizeof( sJudgeStandard ));
		lProtCount	  = 0;
		pCurProtect	  = NULL;
		nRemark		  = 0;
	}

	/*重载析构函数*/
	~RADAR_PARA()
	{	
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Delete(pValidEmitID);
		SW_Delete(pCurProtect);
	}

	/*重载拷贝构造函数*/
	RADAR_PARA(const RADAR_PARA &radarPara)
	{
		sRID		  = NULL;
		EquipmentName = NULL;
		pValidEmitID  = NULL;
		pCurProtect   = NULL;
		*this = radarPara;
	}

	/*重载=*/
	RADAR_PARA& operator = (const RADAR_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Free_Char(EquipmentName);
		//SW_Delete(pValidEmitID);
		//SW_Delete(pCurProtect);

		RadarID		  = theStruct.RadarID;
		PlatID		  = theStruct.PlatID;
		ATT			  = theStruct.ATT;
		SRCType		  = theStruct.SRCType;

		dTime		  = theStruct.dTime;
		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;
		WorkOnCtrl	  = theStruct.WorkOnCtrl;
		SendRevType	  = theStruct.SendRevType;
		bProtectWQ	  = theStruct.bProtectWQ;
		RevInfo		  = theStruct.RevInfo;
		Priority      = theStruct.Priority;
		fSendCenterRF = theStruct.fSendCenterRF;
		fSendBand	  = theStruct.fSendBand;
		fPt			  = theStruct.fPt;
		fGt			  = theStruct.fGt;		
		fAzBeamWidth  = theStruct.fAzBeamWidth;
		fElBeamWidth  = theStruct.fElBeamWidth;
		AntAZ		  = theStruct.AntAZ;
		AntEl	      = theStruct.AntEl;
		fAziMax		  = theStruct.fAziMax;
		fAziMin		  = theStruct.fAziMin;
		RFT			  = theStruct.RFT;
		PRI			  = theStruct.PRI;
		PRIT		  = theStruct.PRIT;
		PW			  = theStruct.PW;
		POT			  = theStruct.POT;
		JudgeStandard = theStruct.JudgeStandard;
		nRemark        = theStruct.nRemark;

		SW_Malloc_Int(theStruct.pValidEmitID,pValidEmitID,theStruct.lValidEmitCount,lValidEmitCount);
		SW_Malloc_Struct(sCurProtFreq,theStruct.pCurProtect,pCurProtect,theStruct.lProtCount,lProtCount);

		return *this;
	}
}sRadarOut;


//通信电台推演过程中输出
typedef struct  COMM_PARA		
{
	char			 *sRID;					//身份识别号
	int				 RadioID;               //电台ID号
	int				 PlatID;				//平台ID号	
	DKDMS::Enum_ATT		 ATT;					//敌我属性
	DKDMS::Enum_EquipSrc	 SRCType;				//装备来源
	char			 *EquipmentName;		//装备名称
	float			 dTime;					//时间(s)
	float			 LON;					//经度
	float			 LAT;					//纬度
	float			 Height;				//高度	
	DKDMS::Enum_WorkOnCtrl  WorkOnCtrl;			//工作状态
	float			 AntAZ;					//天线方位指向
	float			 AntEl;					//天线俯仰指向	
	float			 fPt;			        //发射功率，单位：KW
	float			 fGt;			        //天线主瓣增益，单位：dB
	float			 fAzBeamWidth;	        //天线主瓣水平波束宽度，单位：度
	float			 fElBeamWidth;	        //天线主瓣俯仰波束宽度，单位：度
	DKDMS::Enum_CMD		 CMD;					//调制样式
	int				 lValidEmitCount;		//当前有效辐射源个数
	int				 *pValidEmitID;    		//当前有效辐射源ID			  
	DKDMS::Enum_SendRevType SendRevType;			//发射机和接收机工作类型
	bool			 bProtectWQ;			//是否是保护装备（新增）
	sReceiveInfo	 RevInfo;				//接收机信息 
	sJudgeStandard   JudgeStandard;			//判断标准
	DKDMS::Enum_Priority	 Priority;				//保护优先级					
	float			 fSendCenterRF;			//发射中心频率					
	float			 fSendBand;				//发射信号带宽	
	int				 lProtCount;			//当前保护频率组数
	sCurProtFreq	 *pCurProtect;			//当前保护频率
	int				 nRemark;				//备注

	COMM_PARA()
	{
		sRID		  = NULL;
		RadioID		  = 0;
		PlatID		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		EquipmentName = NULL;
		dTime		  = 0;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		WorkOnCtrl	  = DKDMS::Enum_WorkOnCtrl_0;		
		AntAZ		  = 0;
		AntEl	      = 0;		
		fPt			  = 0;
		fGt			  = 0;		
		fAzBeamWidth  = 0;
		fElBeamWidth  = 0;
		CMD			  = DKDMS::Enum_CMD_0;	
		pValidEmitID  = NULL;
		lValidEmitCount = 0;
		SendRevType	  = DKDMS::Enum_SendRevType_0;
		bProtectWQ    = false;
		memset( &RevInfo,0, sizeof( sReceiveInfo ) );
		memset( &JudgeStandard,0, sizeof( sJudgeStandard ) );
		Priority      = DKDMS::Enum_Priority_0;
		fSendCenterRF = 0;
		fSendBand	  = 0;
		lProtCount	  = 0;
		pCurProtect	  = NULL;
		nRemark		  = 0;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Delete(pValidEmitID);	
		SW_Delete(pCurProtect);
	}

	/*重载析构函数*/
	~COMM_PARA()
	{	
		Release();
	}
	
	/*重载拷贝构造函数*/
	COMM_PARA(const COMM_PARA &commPara)
	{
		*this = commPara;
	}

	/*重载=*/
	COMM_PARA& operator = (const COMM_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		RadioID		  = theStruct.RadioID;
		PlatID		  = theStruct.PlatID;
		ATT			  = theStruct.ATT;
		SRCType		  = theStruct.SRCType;

		dTime		  = theStruct.dTime;
		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;
		WorkOnCtrl	  = theStruct.WorkOnCtrl;		
		AntAZ		  = theStruct.AntAZ;
		AntEl	      = theStruct.AntEl;
		fPt			  = theStruct.fPt;
		fGt			  = theStruct.fGt;		
		fAzBeamWidth  = theStruct.fAzBeamWidth;
		fElBeamWidth  = theStruct.fElBeamWidth;
		CMD			  = theStruct.CMD;	

		SW_Malloc_Int(theStruct.pValidEmitID,pValidEmitID,theStruct.lValidEmitCount,lValidEmitCount);

		SendRevType	  = theStruct.SendRevType;
		bProtectWQ	  = theStruct.bProtectWQ;
		RevInfo		  = theStruct.RevInfo;
		JudgeStandard = theStruct.JudgeStandard;
		Priority      = theStruct.Priority;
		fSendCenterRF = theStruct.fSendCenterRF;
		fSendBand	  = theStruct.fSendBand;
		nRemark        = theStruct.nRemark;

		SW_Malloc_Struct(sCurProtFreq,theStruct.pCurProtect,pCurProtect,theStruct.lProtCount,lProtCount);

		return *this;
	}
}sCommOut;

//每个点静态频谱计算结果(动静态一样结构体)
typedef  struct  AFREQ_DATA
{
	float		LON;				//计算空间经度
	float		LAT;				//计算空间纬度
	float		Height;				//计算空间高度
	DKDMS::Enum_JamRlt JamRlt;				//GR结果
	float		fEM;				//场强
	float		fSNR;				//信噪比
	float		fPower;				//功率

	AFREQ_DATA()
	{
		LON		= 0;
		LAT		= 0;
		Height	= 0;
		JamRlt	= DKDMS::Enum_JamRlt_0;	//故障
		fEM		= 0;
		fSNR	= 0;
		fPower	= 0;
	}

	/*重载析构函数*/
	~AFREQ_DATA()
	{
	}

	/*重载拷贝构造函数*/
	AFREQ_DATA(const AFREQ_DATA &freqData )
	{
		*this = freqData;
	}

	/*重载=*/
	AFREQ_DATA& operator = (const AFREQ_DATA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		LON		= theStruct.LON;
		LAT		= theStruct.LAT;
		Height	= theStruct.Height;
		JamRlt	= theStruct.JamRlt;	
		fEM		= theStruct.fEM;
		fSNR	= theStruct.fSNR;
		fPower	= theStruct.fPower;
		return *this;
	}

}aFreqOut, sFreqOut;

//动态过程中每个点频谱计算结果
typedef  struct  FREQ_RLTDATA
{
	char		*sRID;		  //身份识别号
	int			nRevID;		  //电台接收机ID	 
	float		dTime;		  //仿真时间（s）
	DKDMS::EEquipKind	RevEQKind;	  //装备类型	
	int			lEmitCount;	  //有效辐射源ID个数 
	int			*pEmitID;	  //有效辐射源ID数组 	
	int		    lJamSrcCount; //GR源个数
	int		    *pJamSrcID;	  //GR源ID序列
	sFreqOut	FreqOut;      //场强	

	FREQ_RLTDATA()
	{
		sRID		  = NULL;
		nRevID		  = 0;	
		dTime		  = 0;
		RevEQKind	  = DKDMS::et_Radar;
		pEmitID		  = NULL;
		lEmitCount	  = 0;
		lJamSrcCount  = 0;
		pJamSrcID     = NULL;
		memset( &FreqOut,0, sizeof( sFreqOut ) );
	}

	/*重载析构函数*/
	~FREQ_RLTDATA()
	{
		SW_Free_Char(sRID);
		SW_Delete(pEmitID);
		SW_Delete(pJamSrcID);
	}

	/*重载拷贝构造函数*/
	FREQ_RLTDATA(const FREQ_RLTDATA &freqRlt)
	{
		*this = freqRlt;
	}

	/*重载=*/
	FREQ_RLTDATA& operator = (const FREQ_RLTDATA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Delete(pEmitID);
		//SW_Delete(pJamSrcID);

		SW_Malloc_Char(theStruct.sRID,sRID);

		nRevID		  = theStruct.nRevID;	
		dTime		  = theStruct.dTime;
		RevEQKind	  = theStruct.RevEQKind;
		FreqOut		  = theStruct.FreqOut;	

		SW_Malloc_Int(theStruct.pEmitID,pEmitID,theStruct.lEmitCount,lEmitCount);
		SW_Malloc_Int(theStruct.pJamSrcID,pJamSrcID,theStruct.lJamSrcCount,lJamSrcCount);

		return *this;
	}

}sPtFreqRltOut;


//动态过程中，单GR源产生的频谱GR效果
typedef  struct  FREQ_RLTDATA_JAMSRC		 
{
	char		*sRID;			  //身份识别号
	int			nRevID;			  //电台接收机ID	 
	float		dTime;			  //仿真时间（s）
	DKDMS::EEquipKind  RevEQKind;		  //装备类型
	int			lEmitCount;		  //有效辐射源ID个数
	int			*pEmitID;		  //有效辐射源ID数组	
	int			nJamSrcID;		  //GR源ID;
	sFreqOut	FreqOut;		  //场强	

	FREQ_RLTDATA_JAMSRC()
	{
		sRID		  = NULL;
		nRevID		  = 0;	
		dTime		  = 0;
		RevEQKind	  = DKDMS::et_Radar;
		pEmitID		  = NULL;
		lEmitCount	  = 0;
		nJamSrcID	  = 0;
		memset( &FreqOut, 0,sizeof( sFreqOut ) );
	}

	/*重载析构函数*/
	~FREQ_RLTDATA_JAMSRC()
	{
		SW_Free_Char(sRID);
		SW_Delete(pEmitID);
	}

	/*重载拷贝构造函数*/
	FREQ_RLTDATA_JAMSRC(const FREQ_RLTDATA_JAMSRC &freqRlt)
	{
		*this = freqRlt;
	}

	/*重载=*/
	FREQ_RLTDATA_JAMSRC& operator = (const FREQ_RLTDATA_JAMSRC& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Delete(pEmitID);

		SW_Malloc_Char(theStruct.sRID,sRID);

		nRevID		  = theStruct.nRevID;	
		dTime		  = theStruct.dTime;
		RevEQKind	  = theStruct.RevEQKind;
		nJamSrcID	  = theStruct.nJamSrcID;
		FreqOut		  = theStruct.FreqOut;	

		SW_Malloc_Int(theStruct.pEmitID,pEmitID,theStruct.lEmitCount,lEmitCount);

		return *this;
	}

}sPtFreqRltJamSrcOut;

//静态计算：综合频谱GR效果
typedef  struct  AFREQ_RLTDATA
{
	char			*sRID;				//身份识别号
	int				nRevID;				//接收机ID	
	DKDMS::EEquipKind		RevEQKind;			//装备类型		
	DKDMS::Enum_CalcType	CalcType;			//计算类型
	int				nEmitID;			//辐射源ID；=0：则表示多辐射源合成；>0: 单辐射源ID;	
	int				lCount;				//点数	
	aFreqOut		*pFreqOut;			//各点场强、信号功率、信噪比

	AFREQ_RLTDATA()
	{
		sRID		  = NULL;
		nRevID		  = 0;	
		RevEQKind	  = DKDMS::et_Radar;
		CalcType      = DKDMS::Enum_CalcType_EM;
		nEmitID		  = 0;
		pFreqOut	  = NULL;
		lCount		  = 0;
	}

	/*重载析构函数*/
	~AFREQ_RLTDATA()
	{
		SW_Free_Char(sRID);
		SW_Delete(pFreqOut);
	}

	/*重载拷贝构造函数*/
	AFREQ_RLTDATA(const AFREQ_RLTDATA &freqRlt)
	{
		*this = freqRlt;
	}

	/*重载=*/
	AFREQ_RLTDATA& operator = (const AFREQ_RLTDATA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Delete(pFreqOut);

		SW_Malloc_Char(theStruct.sRID,sRID);

		nRevID		  = theStruct.nRevID;			
		RevEQKind	  = theStruct.RevEQKind;
		CalcType	  = theStruct.CalcType;
		nEmitID		  = theStruct.nEmitID;		

		SW_Malloc_Struct(aFreqOut,theStruct.pFreqOut,pFreqOut,theStruct.lCount,lCount);

		return *this;
	}

}aPtFreqRltOut;

//静态面计算：综合频谱GR效果
typedef  struct  AAREAFREQ_RLTDATA
{
	char			*sRID;				//身份识别号
	char			*sPath;				//文件路径
	int				nRevID;				//接收机ID	
	DKDMS::EEquipKind		RevEQKind;			//装备类型		
	DKDMS::Enum_CalcType	CalcType;			//计算类型
	int				nEmitID;			//辐射源ID；=0：则表示多辐射源合成；>0: 单辐射源ID;	

	AAREAFREQ_RLTDATA()
	{
		sRID		  = NULL;
		sPath		  = NULL;
		nRevID		  = 0;	
		RevEQKind	  = DKDMS::et_Radar;
		CalcType      = DKDMS::Enum_CalcType_EM;
		nEmitID		  = 0;	
	}

	/*重载析构函数*/
	~AAREAFREQ_RLTDATA()
	{	
		SW_Free_Char(sRID);
		SW_Free_Char(sPath);
	}

	/*重载拷贝构造函数*/
	AAREAFREQ_RLTDATA(const AAREAFREQ_RLTDATA &freqRlt)
	{
		*this = freqRlt;
	}

	/*重载=*/
	AAREAFREQ_RLTDATA& operator = (const AAREAFREQ_RLTDATA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Free_Char(sPath);

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sPath,sPath);

		nRevID		  = theStruct.nRevID;			
		RevEQKind	  = theStruct.RevEQKind;
		CalcType	  = theStruct.CalcType;
		nEmitID		  = theStruct.nEmitID;		

		return *this;
	}

}aAreaFreqRltOut;

typedef struct REV_FREQ		//接收机用频	
{
	float dStartTime;		//开始时间
	float dEndTime;			//结束时间
	float  fRevCenterRF;	//接收中心频率
	float  fRevBand;		//接收信号带宽
	float  fRevStartRF;		//接收起始频率
	float  fRevEndRF;		//接收终止频率

	REV_FREQ()
	{
		dStartTime		= 0;
		dEndTime		= 0;	
		fRevCenterRF	= 0;
		fRevBand		= 0;
		fRevStartRF		= 0;
		fRevEndRF		= 0;
	}

	/*重载析构函数*/
	~REV_FREQ()
	{	
	}

	/*重载拷贝构造函数*/
	REV_FREQ(const REV_FREQ &radarPara)
	{
		*this = radarPara;
	}

	/*重载=*/
	REV_FREQ& operator = (const REV_FREQ& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		dStartTime		= theStruct.dStartTime;
		dEndTime		= theStruct.dEndTime;	
		fRevCenterRF	= theStruct.fRevCenterRF;
		fRevBand		= theStruct.fRevBand;
		fRevStartRF		= theStruct.fRevStartRF;
		fRevEndRF		= theStruct.fRevEndRF;

		return *this;
	}

}sRevFreq;

typedef struct SEND_FREQ	//发射机信息	
{
	float dStartTime;		//开始时间
	float dEndTime;			//结束时间
	float  fStartAZ;		//起始方位角
	float  fEndAZ;			//终止方位角
	float  fStartPitch;		//起始俯仰
	float  fEndPitch;		//终止俯仰
	DKDMS::Enum_Priority Priority; //保护优先级
	float  fSendCenterRF;	//发射中心频率
	float  fSendBand;		//发射信号带宽
	float  fSendPW;			//发射功率
	float  fSendStartRF;	//发射起始频率
	float  fSendEndRF;		//发射终止频率

	SEND_FREQ()
	{	
		dStartTime	= 0;
		dEndTime	= 0;	
		fStartAZ	= 0;
		fEndAZ		= 0;
		fStartPitch	= 0;
		fEndPitch	= 0;
		Priority    = DKDMS::Enum_Priority_0;
		fSendCenterRF = 0;
		fSendBand   = 0;
		fSendPW		= 0;
		fSendStartRF = 0;
		fSendEndRF  = 0;
	}	

	/*重载析构函数*/
	~SEND_FREQ()
	{	
	}


	/*重载拷贝构造函数*/
	SEND_FREQ(const SEND_FREQ &radarPara)
	{
		*this = radarPara;
	}

	/*重载=*/
	SEND_FREQ& operator = (const SEND_FREQ& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		dStartTime		= theStruct.dStartTime;
		dEndTime		= theStruct.dEndTime;	
		fStartAZ		= theStruct.fStartAZ;
		fEndAZ			= theStruct.fEndAZ;
		fStartPitch		= theStruct.fStartPitch;
		fEndPitch		= theStruct.fEndPitch;
		Priority		= theStruct.Priority;
		fSendCenterRF	= theStruct.fSendCenterRF;
		fSendBand		= theStruct.fSendBand;
		fSendPW			= theStruct.fSendPW;
		fSendStartRF	= theStruct.fSendStartRF;
		fSendEndRF		= theStruct.fSendEndRF;
		return *this;
	}
}sSendFreq;

//用频需求	
typedef struct FREQ_DEMAND	 	
{
	char		*ArmyName;			 //部队名称
	char		*EquipType;			 //装备型号
	int			lSendFreqCount;		 //发射用频组数
	sSendFreq	*pSendFreq;			 //发射用频
	int			lRevFreqCount;		 //接收用频组数
	sRevFreq	*pRevFreq;			 //接收用频

	FREQ_DEMAND()
	{
		ArmyName		= NULL;
		EquipType		= NULL;	
		lSendFreqCount	= 0;
		pSendFreq		= NULL;
		lRevFreqCount	= 0;
		pRevFreq		= NULL;		
	}
	void Release()
	{
		SW_Free_Char(ArmyName);
		SW_Free_Char(EquipType);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
	}

	/*重载析构函数*/
	~FREQ_DEMAND()
	{	
		Release();
	}


	/*重载拷贝构造函数*/
	FREQ_DEMAND(const FREQ_DEMAND &FreqDemand)
	{
		*this = FreqDemand;
	}

	/*重载=*/
	FREQ_DEMAND& operator = (const FREQ_DEMAND& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.ArmyName,ArmyName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);

		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.lSendFreqCount,lSendFreqCount);
		SW_Malloc_Struct(sRevFreq,theStruct.pRevFreq,pRevFreq,theStruct.lRevFreqCount,lRevFreqCount);

		return *this;
	}
}sFreqDemand;

//雷达的静态计算初始化参数
typedef struct  ARADAR_PARA_Scene		
{
	char			 *sRID;					//身份识别号
	int				 RadarID;	       		//雷达ID号
	int				 PlatID;	        	//搭载平台ID号	
	DKDMS::Enum_ATT		 ATT;					//敌我属性
	DKDMS::Enum_EquipSrc	 SRCType;				//装备来源
	char			 *EquipmentName;		//装备名称
	char			 *ModelName;			//模型名称（MID）
	float			 fTime;					//时间（修改）
	float			 LON;					//经度
	float			 LAT;					//纬度
	float			 Height;				//高度	
	DKDMS::Enum_SendRevType SendRevType;			//发射机和接收机工作类型 
	bool			 bProtectWQ;			//是否是保护装备
	//用频需求	    
	char			*ArmyName;				//部队名称
	char			*EquipType;				//装备型号
	int				nSendFreq;				//发射频率个数
	sSendFreq		*pSendFreq;				//发射频率信息
	int				nRevFreqCount;			//接收用频组数
	sRevFreq		*pRevFreq;				//接收用频
	int				nValidEmitCount;		//有效辐射源个数
	int				*pValidEmitID;			//有效辐射源ID
	int				lProtCount;				//保护频率组数
	sProtectFreq	*pProtect;				//保护频率
	int				nOpenWndCount;			//开窗频率组数
	sOpenWndFreq	*pOpenWndFreq;			//开窗频率

	ARADAR_PARA_Scene()
	{
		sRID			= NULL;
		RadarID			= 0;	
		PlatID			= 0;
		ATT				= DKDMS::Enum_ATT_1;
		SRCType			= DKDMS::Enum_EquipSrc_0;
		EquipmentName	= NULL;
		ModelName		= NULL;
		fTime			= 0;
		LON				= 0;
		LAT				= 0;
		Height			= 0;
		SendRevType		= DKDMS::Enum_SendRevType_0;
		bProtectWQ		= false;
		ArmyName		= NULL;
		EquipType		= NULL;		
		nSendFreq		= 0;
		pSendFreq		= NULL;
		nRevFreqCount	= 0;
		pRevFreq		= NULL;
		nValidEmitCount = 0;
		pValidEmitID	= NULL;
		lProtCount		= 0;
		pProtect		= NULL;
		nOpenWndCount	= 0;
		pOpenWndFreq	= NULL;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(ModelName);
		SW_Free_Char(ArmyName);
		SW_Free_Char(EquipType);

		SW_Delete(pValidEmitID);
		SW_Delete(pProtect);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
		SW_Delete(pOpenWndFreq);
	}
	
	/*重载析构函数*/
	~ARADAR_PARA_Scene()
	{
		Release();
	}


	/*重载拷贝构造函数*/
	ARADAR_PARA_Scene(const ARADAR_PARA_Scene &radarPara)
	{
		*this = radarPara;
	}

	/*重载=*/
	ARADAR_PARA_Scene& operator = (const ARADAR_PARA_Scene& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.ModelName,ModelName);
		SW_Malloc_Char(theStruct.ArmyName,ArmyName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);

		SW_Malloc_Int(theStruct.pValidEmitID,pValidEmitID,theStruct.nValidEmitCount,nValidEmitCount);
		SW_Malloc_Struct(sProtectFreq,theStruct.pProtect,pProtect,theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.nSendFreq,nSendFreq);
		SW_Malloc_Struct(sRevFreq,theStruct.pRevFreq,pRevFreq,theStruct.nRevFreqCount,nRevFreqCount);
		SW_Malloc_Struct(sOpenWndFreq,theStruct.pOpenWndFreq,pOpenWndFreq,theStruct.nOpenWndCount,nOpenWndCount);

		RadarID		  = theStruct.RadarID;	
		PlatID		  = theStruct.PlatID;
		ATT			  = theStruct.ATT;
		SRCType		  = theStruct.SRCType;
		fTime		  = theStruct.fTime;
		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;
		SendRevType	  = theStruct.SendRevType;	
		bProtectWQ	  = theStruct.bProtectWQ;		

		return *this;
	}
}aRadarIn;

//电台的静态计算初始化参数
typedef struct  ACOMM_PARA_Scene		
{
	char			*sRID;				  //身份识别号
	int				RadioID;              //电台ID号
	int				PlatID;		          //搭载平台ID号
	DKDMS::Enum_ATT		ATT;				  //敌我属性
	DKDMS::Enum_EquipSrc	SRCType;			  //装备来源
	char			*EquipmentName;		  //装备名称
	char			*ModelName;			  //模型名称（MID）
	float			fTime;				  //时间（修改）
	float			LON;				  //经度
	float			LAT;				  //纬度
	float			Height;				  //高度	
	DKDMS::Enum_SendRevType SendRevType;		  //发射机和接收机工作类型
	bool			 bProtectWQ;		  //是否是保护装备
	char			*ArmyName;			  //部队名称
	char			*EquipType;			  //装备型号
	int				nSendFreq;			  //发射频率个数
	sSendFreq		*pSendFreq;			  //发射频率信息
	int				nRevFreqCount;		  //接收用频组数
	sRevFreq		*pRevFreq;			  //接收用频
	int				nValidEmitCount;	  //有效辐射源个数
	int				*pValidEmitID;		  //有效辐射源ID
	int				lProtCount;			  //保护频率组数
	sProtectFreq	*pProtect;			  //保护频率
	int				nOpenWndCount;		  //开窗频率组数
	sOpenWndFreq	*pOpenWndFreq;		  //开窗频率

	ACOMM_PARA_Scene()
	{
		sRID		    = NULL;
		RadioID		    = 0;	
		PlatID		    = 0;
		ATT			    = DKDMS::Enum_ATT_1;
		SRCType			= DKDMS::Enum_EquipSrc_0;
		EquipmentName   = NULL;
		ModelName       = NULL;
		fTime		    = 0;
		LON			    = 0;
		LAT			    = 0;
		Height		    = 0;
		SendRevType	    = DKDMS::Enum_SendRevType_0;
		bProtectWQ	    = false;
		ArmyName		= NULL;
		EquipType		= NULL;	
		nSendFreq		= 0;
		pSendFreq		= NULL;
		nRevFreqCount	= 0;
		pRevFreq		= NULL;
		nValidEmitCount = 0;
		pValidEmitID	= 0;
		lProtCount		= 0;
		pProtect		= NULL;
		nOpenWndCount	= 0;
		pOpenWndFreq	= NULL;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(ModelName);
		SW_Free_Char(ArmyName);
		SW_Free_Char(EquipType);

		SW_Delete(pValidEmitID);
		SW_Delete(pProtect);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
		SW_Delete(pOpenWndFreq);
	}

	/*重载析构函数*/
	~ACOMM_PARA_Scene()
	{
		Release();
	}

	/*重载拷贝构造函数*/
	ACOMM_PARA_Scene(const ACOMM_PARA_Scene &CommPara)
	{
		*this = CommPara;
	}

	/*重载=*/
	ACOMM_PARA_Scene& operator = (const ACOMM_PARA_Scene& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.ModelName,ModelName);
		SW_Malloc_Char(theStruct.ArmyName,ArmyName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);

		SW_Malloc_Int(theStruct.pValidEmitID,pValidEmitID,theStruct.nValidEmitCount,nValidEmitCount);
		SW_Malloc_Struct(sProtectFreq,theStruct.pProtect,pProtect,theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.nSendFreq,nSendFreq);
		SW_Malloc_Struct(sRevFreq,theStruct.pRevFreq,pRevFreq,theStruct.nRevFreqCount,nRevFreqCount);
		SW_Malloc_Struct(sOpenWndFreq,theStruct.pOpenWndFreq,pOpenWndFreq,theStruct.nOpenWndCount,nOpenWndCount);

		RadioID		  = theStruct.RadioID;	
		PlatID		  = theStruct.PlatID;
		ATT			  = theStruct.ATT;
		SRCType		  = theStruct.SRCType;
		fTime		  = theStruct.fTime;

		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;
		SendRevType	  = theStruct.SendRevType;
		bProtectWQ	  = theStruct.bProtectWQ;		
		return *this;
	}
}aCommIn;

//GR机静态计算初始化参数结构体（雷达GR、电台GR）
typedef  struct  AJAM_PARA  
{
	char*		sRID;			    //身份识别号
	int			JammerID;			//GR机ID
	int			PlatID;		   		//GR机所在平台ID
	DKDMS::Enum_ATT	ATT;				//敌我属性
	DKDMS::Enum_EquipSrc	SRCType;		//装备来源
	char	    *EquipmentName;		//装备名称
	char		*ModelName;			//模型名称	
	float		fTime;				//时间（修改）
	float		LON;				//经度
	float		LAT;				//纬度
	float		Height;				//高度
	char		*ArmyName;			//部队名称
	char		*EquipType;			//装备型号
	DKDMS::Enum_SendRevType SendRevType;	//发射机和接收机工作类型
	int			nSendFreq;			//发射频率个数
	sSendFreq	*pSendFreq;			//发射频率信息	
	int			 lProtCount;		//保护频率组数
	sProtectFreq *pProtect;			//保护频率
	int			 nOpenWndCount;		//开窗频率组数
	sOpenWndFreq *pOpenWndFreq;		//开窗频率

	AJAM_PARA()
	{
		sRID		    = NULL;
		JammerID	    = 0;
		PlatID		    = 0;
		ATT			    = DKDMS::Enum_ATT_1;
		SRCType			= DKDMS::Enum_EquipSrc_0;
		EquipmentName   = NULL;
		ModelName       = NULL;
        fTime			= 0;
		LON			    = 0;
		LAT			    = 0;
		Height		    = 0;	
		ArmyName		= NULL;
		EquipType		= NULL;	
		nSendFreq		= 0;
		pSendFreq		= NULL;		
		SendRevType     = DKDMS::Enum_SendRevType_0;	
		lProtCount	    = 0;
		pProtect		= NULL;
		nOpenWndCount   = 0;
		pOpenWndFreq    = NULL;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(ModelName);
		SW_Free_Char(ArmyName);
		SW_Free_Char(EquipType);

		SW_Delete(pProtect);
		SW_Delete(pSendFreq);
		SW_Delete(pOpenWndFreq);
	}

	/*重载析构函数*/
	~AJAM_PARA()
	{		
		Release();
	}

	/*重载拷贝构造函数*/
	AJAM_PARA(const AJAM_PARA &JamPara)
	{
		*this = JamPara;
	}

	/*重载=*/
	AJAM_PARA& operator = (const AJAM_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.ModelName,ModelName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);
		SW_Malloc_Char(theStruct.ArmyName,ArmyName);

		JammerID	  = theStruct.JammerID;
		PlatID		  = theStruct.PlatID;
		ATT			  = theStruct.ATT;	
		SRCType		  = theStruct.SRCType;
		fTime		  = theStruct.fTime;

		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;
		SendRevType   = theStruct.SendRevType;

		SW_Malloc_Struct(sProtectFreq,theStruct.pProtect,pProtect, theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq, theStruct.nSendFreq,nSendFreq);
		SW_Malloc_Struct(sOpenWndFreq,theStruct.pOpenWndFreq,pOpenWndFreq, theStruct.nOpenWndCount,nOpenWndCount);

		return *this;
	}

}aRadarJamIn, aCommJamIn;

//离散点输入信息
typedef  struct  Point_CALPARAM
{
	float	RfSample;			//采样频率
	int		SampleNum;			//采样点数
	float	LON;				//经度
	float	LAT;				//纬度
	float	Height;				//高度	
	float	fRF;		     	//计算目标频段，单位：Hz

	Point_CALPARAM()
	{
		RfSample	  = 0;
		SampleNum	  = 0;	
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;	
		fRF		      = 0;	
	}

	/*重载析构函数*/
	~Point_CALPARAM()
	{
		RfSample	  = 0;
		SampleNum	  = 0;	
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;	
		fRF		      = 0;	
	}

	/*重载拷贝构造函数*/
	Point_CALPARAM(const Point_CALPARAM &PtCalcPara)
	{
		*this = PtCalcPara;
	}

	/*重载=*/
	Point_CALPARAM& operator = (const Point_CALPARAM& theStruct)
	{
		if(this == &theStruct)
		{
			return *this;
		}
		RfSample	  = theStruct.RfSample;
		SampleNum	  = theStruct.SampleNum;	
		LON			  = theStruct.LON;
		LAT  		  = theStruct.LAT;
		Height		  = theStruct.Height;
		fRF		      = theStruct.fRF;
		return *this;
	}
} sPointCalParam;

//静态计算给计算模型设置的离散点参数
typedef  struct  APoint_CAL			
{
	char			*sRID;				//本席位身份识别号
	int				nID;				//计算模型ID
	int				nRevID;				//接收机ID
	DKDMS::Enum_CalcType	CalcType;			//计算类型
	int				lCount;
	sPointCalParam  *pPtCalPara;
	int				lVaildEmitCount;
	int				*pVaildEmitID; 		//有效信号ID若lEmitCount=0，则全部辐射源都计算；若lEmitCount>0,第一个ID为有用信号，其余信号为噪声信号。

	APoint_CAL()
	{
		sRID		  = NULL;
		nID			  = 0;	
		nRevID		  = 0;
		CalcType	  = DKDMS::Enum_CalcType_EM;		
		pPtCalPara    = NULL;
		lCount		  = 0;
		pVaildEmitID  = NULL;		
		lVaildEmitCount = 0;
	}

	/*重载析构函数*/
	~APoint_CAL()
	{
		SW_Free_Char(sRID);
		SW_Delete(pPtCalPara);
		SW_Delete(pVaildEmitID);
	}
	
	/*重载拷贝构造函数*/
	APoint_CAL(const APoint_CAL &PointCal)
	{
		*this = PointCal;
	}

	/*重载=*/
	APoint_CAL& operator = (const APoint_CAL& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		//SW_Delete(pPtCalPara);
		//SW_Delete(pVaildEmitID);

		SW_Malloc_Char(theStruct.sRID,sRID);

		nID		  = theStruct.nID;	
		nRevID    = theStruct.nRevID;
		CalcType  = theStruct.CalcType;

		SW_Malloc_Struct(sPointCalParam,theStruct.pPtCalPara,pPtCalPara,theStruct.lCount,lCount);
		SW_Malloc_Int(theStruct.pVaildEmitID,pVaildEmitID,theStruct.lVaildEmitCount,lVaildEmitCount);

		return *this;
	}
} aPointCal;

//静态计算给计算模型设置的面区域参数
typedef  struct  Area_CALPARAM				
{
	float		RfSample;			//采样频率
	int			SampleNum;			//采样点数
	float		fRF;		        //计算目标频率值，单位：MHz
	float		fLonMin;			//计算空间经度（float）
	float		fLonMax;
	float		fLatMin;			//计算空间纬度
	float		fLatMax;
	float		fHeightMin;	  		//计算空间高度
	float		fHeightMax;
	float		fdelLon;			//计算空间经度分辨率（度）
	float		fdelLat;			//计算空间纬度分辨率
	float		fdelHeight;     	//计算空间高度分辨率
	bool		bUsedelHeight;		//是否使用“高度分辨率”；若不使用，则直接用高度序列
	int			nHeightCount;		//高度个数
	int			*pHegiht;			//高度序列

	Area_CALPARAM()
	{
		RfSample	  = 0;
		SampleNum	  = 0;	
		fRF			  = 0;		
		fLonMin	      = 0;
		fLonMax		  = 0;
		fLatMin		  = 0;		
		fLatMax		  = 0;
		fHeightMin	  = 2000;
		fHeightMax	  = 10000;
		fdelLon		  = 0;
		fdelLat		  = 0;
		fdelHeight	  = 2000;
		bUsedelHeight = false;
		nHeightCount  = 0;
		pHegiht		  = NULL;
	}

	/*重载析构函数*/
	~Area_CALPARAM()
	{	
		SW_Delete(pHegiht);
	}

	/*重载拷贝构造函数*/
	Area_CALPARAM(const Area_CALPARAM &AreaCalPara)
	{
		*this = AreaCalPara;
	}

	/*重载=*/
	Area_CALPARAM& operator = (const Area_CALPARAM& theStruct)
	{	
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Delete(pHegiht);

		RfSample	  = theStruct.RfSample;
		SampleNum	  = theStruct.SampleNum;	
		fRF			  = theStruct.fRF;		
		fLonMin	      = theStruct.fLonMin;
		fLonMax		  = theStruct.fLonMax;
		fLatMin		  = theStruct.fLatMin;		
		fLatMax		  = theStruct.fLatMax;
		fHeightMin	  = theStruct.fHeightMin;
		fHeightMax	  = theStruct.fHeightMax;
		fdelLon		  = theStruct.fdelLon;
		fdelLat		  = theStruct.fdelLat;
		fdelHeight	  = theStruct.fdelHeight;	
		bUsedelHeight = theStruct.bUsedelHeight;

		SW_Malloc_Int(theStruct.pHegiht,pHegiht,theStruct.nHeightCount,nHeightCount);

		return *this;
	}
}sAreaCalParam;

typedef struct RECV_GROUP
{
	int			  nRevCount;		//接收机数量
	int			  *pRevID;			//接收机ID序列
	int			  lVaildEmitCount;
	int			  *pVaildEmitID; 	//若nRevCount=1,pVaildEmitID才有意义
	RECV_GROUP()
	{
		nRevCount = 0;
		pRevID = NULL;
		lVaildEmitCount = 0;
		pVaildEmitID = NULL;
	}
	~RECV_GROUP()
	{	
		SW_Delete(pRevID);
		SW_Delete(pVaildEmitID);
	}

	/*重载拷贝构造函数*/
	RECV_GROUP(const RECV_GROUP &RevGroup)
	{
		*this = RevGroup;
	}

	/*重载=*/
	RECV_GROUP& operator = (const RECV_GROUP& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Delete(pRevID);
		//SW_Delete(pVaildEmitID);

		SW_Malloc_Int(theStruct.pRevID,pRevID,theStruct.nRevCount,nRevCount);
		SW_Malloc_Int(theStruct.pVaildEmitID,pVaildEmitID,theStruct.lVaildEmitCount,lVaildEmitCount);

		return *this;
	}
}stRecvGroup;


//静态计算给计算模型设置的带面区域信息的结构体
typedef  struct  AArea_CAL		
{
	char		  *sRID;			//本席位身份识别号
	int			  nID;				//计算模型ID	
	DKDMS::Enum_CalcType CalcType;			//计算类型
	sAreaCalParam PtCalPara; 
	stRecvGroup   RecvGroup;		//接收机和有效辐射源信息
	int			  nJamCount;		//GR源数量
	int			  *pJamID;			//GR源数组

	AArea_CAL()
	{
		sRID		  = NULL;
		nID			  = 0;		
		CalcType	  = DKDMS::Enum_CalcType_EM;
		memset( &PtCalPara, 0,sizeof( sAreaCalParam ) );
		memset( &RecvGroup, 0,sizeof( stRecvGroup ) );			

		nJamCount	  = 0;
		pJamID		  = NULL;
	}

	/*重载析构函数*/
	~AArea_CAL()
	{	
		SW_Free_Char(sRID);
		SW_Delete(pJamID);
	}


	/*重载拷贝构造函数*/
	AArea_CAL(const AArea_CAL &AreaCal)
	{
		*this = AreaCal;
	}

	/*重载=*/
	AArea_CAL& operator = (const AArea_CAL& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		//SW_Delete(pJamID);

		SW_Malloc_Char(theStruct.sRID,sRID);

		nID		  = theStruct.nID;		

		CalcType  = theStruct.CalcType;
		PtCalPara = theStruct.PtCalPara;
		RecvGroup = theStruct.RecvGroup;

		SW_Malloc_Int(theStruct.pJamID,pJamID,theStruct.nJamCount,nJamCount);

		return *this;
	}
}aAreaCal;

struct sValidEmitInfo												
{
	float dStartTime;				//起始时间（s）
	float dEndTime;					//终止时间（s）
	int	   nEmitID;					//该时间段中有用辐射源ID

	sValidEmitInfo()
	{
		dStartTime	  = 0;
		dEndTime	  = 0;	
		nEmitID		  = 0;
	}

	/*重载析构函数*/
	~sValidEmitInfo()
	{	

	}

	/*重载拷贝构造函数*/
	sValidEmitInfo(const sValidEmitInfo &Info)
	{
		*this = Info;
	}

	/*重载=*/
	sValidEmitInfo& operator = (const sValidEmitInfo& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		dStartTime = theStruct.dStartTime;
		dEndTime   = theStruct.dEndTime;
		nEmitID    = theStruct.nEmitID;
		return *this;
	}
};

struct sOpenCloseCtrl			//装备开关机控制
{
	float dStartTime;			//起始时间（s）
	float dEndTime;			//终止时间（s）	
	DKDMS::Enum_WorkOnCtrl WorkOnCtrl;	//开机or关机

	sOpenCloseCtrl()
	{
		dStartTime	  = 0;
		dEndTime	  = 0;	
		WorkOnCtrl	  = DKDMS::Enum_WorkOnCtrl_1;
	}

	/*重载析构函数*/
	~sOpenCloseCtrl()
	{	
	}

	/*重载拷贝构造函数*/
	sOpenCloseCtrl(const sOpenCloseCtrl &Info)
	{
		*this = Info;
	}

	/*重载=*/
	sOpenCloseCtrl& operator = (const sOpenCloseCtrl& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		dStartTime = theStruct.dStartTime;
		dEndTime   = theStruct.dEndTime;
		WorkOnCtrl = theStruct.WorkOnCtrl;
		return *this;
	}
};

//GR机参数结构体定义（想定输入）
typedef struct JAM_PARA_Scene	
{
	char			*sRID;			    //身份识别号
	int				JammerID;			//GR机ID
	DKDMS::Enum_ATT		ATT;				//敌我属性
	DKDMS::Enum_EquipSrc	SRCType;			//装备来源
	char			*EquipmentName;		//装备名称
	int				PlatID;		     	//GR机所在平台ID
	float			LON;				//经度
	float			LAT;				//纬度
	float			Height;				//高度
	int				lCtrlCount;
	sOpenCloseCtrl  *pCtrl;	 			//开关机时段
	int				nObjCount;			//GR目标个数
	int				*pObjID;			//GR目标列表
	char			*ArmyName;			//部队名称			
	char			*EquipType;			//装备型号
	int				lSendFreqCount;		//发射用频组数
	sSendFreq		*pSendFreq;			//发射用频
	int 			lRevFreqCount;		//接收用频组数
	sRevFreq		*pRevFreq;			//接收用频
	int				lProtCount;			//保护频率组数（新增）
	sProtectFreq	*pProtect;			//保护频率（新增）
	int				nOpenWndCount;		//开窗频率组数
	sOpenWndFreq	*pOpenWndFreq;		//开窗频率

	JAM_PARA_Scene()
	{
		sRID		  = NULL;
		JammerID	  = 0;
		ATT			  = DKDMS::Enum_ATT_1;	
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		EquipmentName = NULL;		
		PlatID		  = 0;
		LON			  = 0;
		LAT		      = 0;
		Height		  = 0;
		lCtrlCount	  = 0;
		pCtrl		  = NULL;
		nObjCount	  = 0;
		pObjID		  = NULL;
		ArmyName	  = NULL;
		EquipType	  = NULL;	
		lSendFreqCount= 0;
		pSendFreq	  = NULL;
		lRevFreqCount = 0;
		pRevFreq	  = NULL;
		lProtCount	  = 0;
		pProtect	  = NULL;
		nOpenWndCount = 0;
		pOpenWndFreq  = NULL;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(ArmyName);
		SW_Free_Char(EquipType);

		SW_Delete(pCtrl);
		SW_Delete(pObjID);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
		SW_Delete(pProtect);
		SW_Delete(pOpenWndFreq);
	}
	
	/*重载析构函数*/
	~JAM_PARA_Scene()
	{			
		Release();
	}

	/*重载拷贝构造函数*/
	JAM_PARA_Scene(const JAM_PARA_Scene &Info)
	{
		*this = Info;
	}

	/*重载=*/
	JAM_PARA_Scene& operator = (const JAM_PARA_Scene& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.ArmyName,ArmyName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);

		JammerID = theStruct.JammerID;
		ATT      = theStruct.ATT;
		SRCType	 = theStruct.SRCType;

		PlatID   = theStruct.PlatID;
		LON 	 = theStruct.LON;
		LAT		 = theStruct.LAT;
		Height	 = theStruct.Height;

		SW_Malloc_Struct(sOpenCloseCtrl,theStruct.pCtrl,pCtrl,theStruct.lCtrlCount,lCtrlCount);
		SW_Malloc_Int(theStruct.pObjID,pObjID,theStruct.nObjCount,nObjCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.lSendFreqCount,lSendFreqCount);
		SW_Malloc_Struct(sRevFreq,theStruct.pRevFreq,pRevFreq,theStruct.lRevFreqCount,lRevFreqCount);
		SW_Malloc_Struct(sProtectFreq,theStruct.pProtect,pProtect,theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sOpenWndFreq,theStruct.pOpenWndFreq,pOpenWndFreq,theStruct.nOpenWndCount,nOpenWndCount);

		return *this;
	}
}sRadarJamIn;

//GR机参数结构体定义
typedef  struct  COMM_JAM_PARA_Scene 
{
	char			*sRID;			     	//身份识别号
	int				JammerID;			 	//GR机ID
	DKDMS::Enum_ATT		ATT;				    //敌我属性
	DKDMS::Enum_EquipSrc	SRCType;				//装备来源
	char			*EquipmentName;		    //装备名称
	int				PlatID;		     	    //GR机所在平台ID
	float			LON;					//经度
	float			LAT;					//纬度
	float			Height;					//高度	
	DKDMS::Enum_SendRevType SendRevType;			//发射机和接收机工作类型
	int				lCtrlCount;
	sOpenCloseCtrl  *pCtrl;	 				//开关机时段
	int				nObjCount;			    //GR目标个数
	int				*pObjID;				//GR目标列表
	char			*ArmyName;				//部队名称			
	char			*EquipType;				//装备型号
	int				lSendFreqCount;			//发射用频组数
	sSendFreq		*pSendFreq;				//发射用频
	int				lRevFreqCount;			//接收用频组数
	sRevFreq		*pRevFreq;				//接收用频	
	int				lProtCount;				//保护频率组数（新增）
	sProtectFreq	*pProtect;				//保护频率（新增）
	int				nOpenWndCount;			//开窗频率组数
	sOpenWndFreq	*pOpenWndFreq;			//开窗频率


	COMM_JAM_PARA_Scene()
	{
		sRID		  = NULL;
		JammerID	  = 0;
		ATT			  = DKDMS::Enum_ATT_1;	
		EquipmentName = NULL;		
		PlatID		  = 0;
		LON			  = 0;
		LAT		      = 0;
		Height		  = 0;
		SendRevType   = DKDMS::Enum_SendRevType_0;
		lCtrlCount	  = 0;
		pCtrl		  = NULL;
		nObjCount	  = 0;
		pObjID		  = NULL;
		ArmyName	  = NULL;
		EquipType	  = NULL;	
		lSendFreqCount= 0;
		pSendFreq	  = NULL;
		lRevFreqCount = 0;
		pRevFreq	  = NULL;
		lProtCount	  = 0;
		pProtect	  = NULL;
		nOpenWndCount = 0;
		pOpenWndFreq  = NULL;
		SRCType       = DKDMS::Enum_EquipSrc_0;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(ArmyName);
		SW_Free_Char(EquipType);

		SW_Delete(pObjID);
		SW_Delete(pCtrl);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
		SW_Delete(pProtect);
		SW_Delete(pOpenWndFreq);
	}

	/*重载析构函数*/
	~COMM_JAM_PARA_Scene()
	{
		Release();
	}
	
	/*重载拷贝构造函数*/
	COMM_JAM_PARA_Scene(const COMM_JAM_PARA_Scene &Info)
	{
		*this = Info;
	}

	/*重载=*/
	COMM_JAM_PARA_Scene& operator = (const COMM_JAM_PARA_Scene& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.ArmyName,ArmyName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);

		JammerID = theStruct.JammerID;
		ATT      = theStruct.ATT;

		PlatID   = theStruct.PlatID;
		LON		 = theStruct.LON;
		LAT		 = theStruct.LAT;
		Height	 = theStruct.Height;
		SendRevType = theStruct.SendRevType;

		SW_Malloc_Struct(sOpenCloseCtrl,theStruct.pCtrl,pCtrl,theStruct.lCtrlCount,lCtrlCount);
		SW_Malloc_Int(theStruct.pObjID,pObjID,theStruct.nObjCount,nObjCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.lSendFreqCount,lSendFreqCount);
		SW_Malloc_Struct(sRevFreq,theStruct.pRevFreq,pRevFreq,theStruct.lRevFreqCount,lRevFreqCount);
		SW_Malloc_Struct(sProtectFreq,theStruct.pProtect,pProtect,theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sOpenWndFreq,theStruct.pOpenWndFreq,pOpenWndFreq,theStruct.nOpenWndCount,nOpenWndCount);

		return *this;
	}
}sCommJamIn;

//GR机参数结构体定义
typedef  struct  AJAM_DATA		
{
	char			*sRID;			    //身份识别号
	int				JammerID;			//GR机ID
	int				PlatID;		     	//GR机所在平台ID
	DKDMS::Enum_ATT		ATT;				//敌我属性
	DKDMS::Enum_EquipSrc	SRCType;			//装备来源
	float			LON;				//经度
	float			LAT;				//纬度
	float			Height;				//高度	
	DKDMS::Enum_WorkOnCtrl WorkOnCtrl;			//工作状态
	DKDMS::Enum_JamMode	JamMode;	 		//GR样式
	float			fPt;			    //GR机功率，单位：KW
	float			fGt;			    //GR机天线主瓣增益，单位：dB
	float			fAzBeamWidth;		//GR机主瓣水平波束宽度，单位：度
	float			fElBeamWidth;  		//GR机主瓣俯仰波束宽度，单位：度
	float			fAntPointAzMin;		//GR机天线波束方位起始指向，以正北方向为0度，0°～360°，单位：度）
	float			fAntPointAzMax;		//GR机天线波束方位终止指向，以正北方向为0度，0°～360°，单位：度）
	float			fAntPointElMin;     //GR机天线波束俯仰起始指向，以水平面为0度，向上为正，单位：度
	float			fAntPointElMax;     //GR机天线波束俯仰终止指向，以水平面为0度，向上为正，单位：度
	DKDMS::Enum_Priority	Priority;			//保护优先级						
	int				nSendFreq;			//发射频率个数
	sSendFreq		*pSendFreq;			//发射频率信息	
	int				lProtCount;			//当前保护频率组数
	sCurProtFreq	*pCurProtect;		//当前保护频率

	AJAM_DATA()
	{
		sRID		  = NULL;
		JammerID	  = 0;
		PlatID		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;	
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		WorkOnCtrl	  = DKDMS::Enum_WorkOnCtrl_0;
		JamMode		  = DKDMS::Enum_JamMode_0;
		fPt			  = 0;
		fGt			  = 0;
		fAzBeamWidth  = 0;
		fElBeamWidth  = 0;
		fAntPointAzMin = 0;
		fAntPointAzMax = 0;
		fAntPointElMin = 0;
		fAntPointElMax = 0;
		Priority       = DKDMS::Enum_Priority_0;
		nSendFreq	   = 0;
		pSendFreq	   = NULL;		
		lProtCount	  = 0;
		pCurProtect	  = NULL;
	}

	/*重载析构函数*/
	~AJAM_DATA()
	{
		SW_Free_Char(sRID);
		SW_Delete(pCurProtect);
		SW_Delete(pSendFreq);
	}

	/*重载拷贝构造函数*/
	AJAM_DATA(const AJAM_DATA &jamvar)
	{
		*this = jamvar;
	}

	/*重载=*/
	AJAM_DATA& operator = (const AJAM_DATA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Delete(pCurProtect);
		//SW_Delete(pSendFreq);

		SW_Malloc_Char(theStruct.sRID,sRID);

		JammerID       = theStruct.JammerID;
		PlatID		   = theStruct.PlatID;
		ATT			   = theStruct.ATT;
		SRCType		   = theStruct.SRCType;
		LON			   = theStruct.LON;
		LAT			   = theStruct.LAT;
		Height		   = theStruct.Height;
		WorkOnCtrl	   = theStruct.WorkOnCtrl;	
		JamMode		   = theStruct.JamMode;
		fPt			   = theStruct.fPt;
		fGt			   = theStruct.fGt;
		fAzBeamWidth   = theStruct.fAzBeamWidth;
		fElBeamWidth   = theStruct.fElBeamWidth;
		fAntPointAzMin = theStruct.fAntPointAzMin;
		fAntPointAzMax = theStruct.fAntPointAzMax;
		fAntPointElMin = theStruct.fAntPointElMin;		
		fAntPointElMax = theStruct.fAntPointElMax;	
		Priority       = theStruct.Priority;		

		SW_Malloc_Struct(sCurProtFreq,theStruct.pCurProtect,pCurProtect,theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.nSendFreq,nSendFreq);

		return *this;
	}
}aRadarJamOut, aCommJamOut;

//雷达动态推演想定信息
typedef struct  RADAR_PARA_Scene	
{
	char		*sRID;			    	//身份识别号
	int			RadarID;	        	//雷达ID号
	int			PlatID;	        		//搭载平台ID号	
	DKDMS::Enum_ATT	ATT;					//敌我属性
	DKDMS::Enum_EquipSrc	SRCType;			//装备来源
	char		*EquipmentName;			//装备名称
	float		LON;					//经度
	float		LAT;					//纬度
	float		Height;					//高度	
	DKDMS::Enum_SendRevType SendRevType;		//发射机和接收机工作类型 
	bool		bProtectWQ;				//是否是保护装备（新增）
	int			lCtrlCount;
	sOpenCloseCtrl *pCtrl;	 			//开关机时段
	int			nEmitCount;			    //有效辐射源个数		
	sValidEmitInfo *pEmitInfo;			//有效辐射源信息
	char		*ArmyName;				//部队名称		
	char		*EquipType;				//装备型号
	int			lSendFreqCount;			//发射用频组数
	sSendFreq	*pSendFreq;				//发射用频
	int			lRevFreqCount;			//接收用频组数
	sRevFreq	*pRevFreq;				//接收用频		
	int			lProtCount;				//保护频率组数
	sProtectFreq *pProtect;				//保护频率
	int			nOpenWndCount;			//开窗频率组数
	sOpenWndFreq *pOpenWndFreq;			//开窗频率

	RADAR_PARA_Scene()
	{
		sRID		  = NULL;
		RadarID		  = 0;
		PlatID		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		EquipmentName = NULL;		
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		SendRevType   = DKDMS::Enum_SendRevType_0;
		bProtectWQ	  = false;
		lCtrlCount	  = 0;
		pCtrl		  = NULL;
		nEmitCount	  = 0;
		pEmitInfo	  = NULL;
		ArmyName	  = NULL;
		EquipType	  = NULL;	
		lSendFreqCount= 0;
		pSendFreq	  = NULL;
		lRevFreqCount = 0;
		pRevFreq	  = NULL;
		lProtCount	  = 0;
		pProtect	  = NULL;
		nOpenWndCount = 0;
		pOpenWndFreq  = NULL;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipType);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(ArmyName);

		SW_Delete(pEmitInfo);
		SW_Delete(pCtrl);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
		SW_Delete(pProtect);
		SW_Delete(pOpenWndFreq);
	}

	/*重载析构函数*/
	~RADAR_PARA_Scene()
	{	
		Release();
	}
	
	/*重载拷贝构造函数*/
	RADAR_PARA_Scene(const RADAR_PARA_Scene &Info)
	{
		*this = Info;
	}

	/*重载=*/
	RADAR_PARA_Scene& operator = (const RADAR_PARA_Scene& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);
		SW_Malloc_Char(theStruct.ArmyName,ArmyName);

		RadarID = theStruct.RadarID;
		ATT     = theStruct.ATT;
		SRCType	= theStruct.SRCType;

		PlatID   = theStruct.PlatID;
		LON		 = theStruct.LON;
		LAT		 = theStruct.LAT;
		Height	 = theStruct.Height;
		SendRevType = theStruct.SendRevType;
		bProtectWQ  = theStruct.bProtectWQ;

		SW_Malloc_Struct(sOpenCloseCtrl,theStruct.pCtrl,pCtrl,theStruct.lCtrlCount,lCtrlCount);
		SW_Malloc_Struct(sValidEmitInfo,theStruct.pEmitInfo,pEmitInfo,theStruct.nEmitCount,nEmitCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.lSendFreqCount,lSendFreqCount);
		SW_Malloc_Struct(sRevFreq,theStruct.pRevFreq,pRevFreq,theStruct.lRevFreqCount,lRevFreqCount);
		SW_Malloc_Struct(sProtectFreq,theStruct.pProtect,pProtect,theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sOpenWndFreq,theStruct.pOpenWndFreq,pOpenWndFreq,theStruct.nOpenWndCount,nOpenWndCount);

		return *this;
	}
}sRadarIn;

typedef struct  ARADAR_PARA
{
	char			*sRID;				//身份识别号
	int				RadarID;	       	//雷达ID号
	int				PlatID;	        	//搭载平台ID号	
	DKDMS::Enum_ATT		ATT;				//敌我属性
	DKDMS::Enum_EquipSrc	SRCType;			//装备来源
	float			LON;				//经度
	float			LAT;				//纬度
	float			Height;				//高度	
	float			fPt;		        //雷达发射功率，单位：KW
	float			fLt;		        //发射损失，单位：dB
	float			fGt;		        //雷达天线主瓣增益，单位：dB
	float			fAzBeamWidth;     	//雷达天线主瓣水平波束宽度，单位：度
	float			fElBeamWidth;		//雷达天线主瓣俯仰波束宽度，单位：度
	float			AntAZ;            	//天线方位指向
	float			AntEl;            	//天线俯仰指向
	float			fAziMax;		    //方位扫描最大值，单位：度
	float			fAziMin;		    //方位扫描最小值，单位：度
	DKDMS::Enum_RFT		RFT;				//射频类型
	float			PRI;             	//脉波重复间隔
	DKDMS::Enum_PRIT		PRIT;         		//脉冲重复间隔类型
	float			PW;               	//脉冲宽度
	float			RBand;            	//雷达接收机带宽
	DKDMS::Enum_POT		POT;				//极化类型
	DKDMS::Enum_SendRevType SendRevType;		//发射机和接收机工作类型
	bool			bProtectWQ;			//是否是保护装备（新增）
	sReceiveInfo	RevInfo;			//接收机信息			   
	sJudgeStandard	JudgeStandard;		//判断标准
	DKDMS::Enum_Priority	Priority;			//保护优先级					
	int				nSendFreq;			//发射频率个数
	sSendFreq		*pSendFreq;			//发射频率信息
	int				nRevFreqCount;		//接收用频组数
	sRevFreq		*pRevFreq;			//接收用频
	int				nValidEmitCount;	//有效辐射源个数
	int				*pValidEmitID;		//有效辐射源ID
	int				lProtCount;			//当前保护频率组数
	sCurProtFreq	*pCurProtect;		//当前保护频率

	ARADAR_PARA()
	{
		sRID		  = NULL;
		RadarID		  = 0;
		PlatID		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		fPt			  = 0;
		fLt			  = 0;
		fGt			  = 0;		
		fAzBeamWidth  = 0;
		fElBeamWidth  = 0;
		AntAZ		  = 0;
		AntEl	      = 0;
		fAziMax		  = 0;
		fAziMin		  = 0;
		RFT			  = DKDMS::Enum_RFT_0;
		PRI			  = 0;
		PRIT		  = DKDMS::Enum_PRIT_0;
		PW			  = 0;
		RBand		  = 0;
		POT			  = DKDMS::Enum_POT_0;	
		SendRevType	  = DKDMS::Enum_SendRevType_0;
		bProtectWQ	  = false;
		memset( &RevInfo,0, sizeof( sReceiveInfo ) );
		memset( &JudgeStandard,0, sizeof( sJudgeStandard ) );
		Priority      = DKDMS::Enum_Priority_0;
		nSendFreq		= 0;
		pSendFreq		= NULL;
		nRevFreqCount	= 0;
		pRevFreq		= NULL;
		nValidEmitCount = 0;
		pValidEmitID  = NULL;
		lProtCount	  = 0;
		pCurProtect	  = NULL;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Delete(pValidEmitID);
		SW_Delete(pCurProtect);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
	}

	/*重载析构函数*/
	~ARADAR_PARA()
	{	
		Release();		
	}


	/*重载拷贝构造函数*/
	ARADAR_PARA(const ARADAR_PARA &radarPara)
	{
		*this = radarPara;
	}

	/*重载=*/
	ARADAR_PARA& operator = (const ARADAR_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);

		RadarID		  = theStruct.RadarID;
		PlatID		  = theStruct.PlatID;
		ATT			  = theStruct.ATT;
		SRCType		  = theStruct.SRCType;
		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;
		fPt			  = theStruct.fPt;
		fLt			  = theStruct.fLt;
		fGt			  = theStruct.fGt;		
		fAzBeamWidth  = theStruct.fAzBeamWidth;
		fElBeamWidth  = theStruct.fElBeamWidth;
		AntAZ		  = theStruct.AntAZ;
		AntEl	      = theStruct.AntEl;
		fAziMax		  = theStruct.fAziMax;
		fAziMin		  = theStruct.fAziMin;
		RFT			  = theStruct.RFT;
		PRI			  = theStruct.PRI;
		PRIT		  = theStruct.PRIT;
		PW			  = theStruct.PW;
		RBand		  = theStruct.RBand;
		POT			  = theStruct.POT;
		SendRevType	  = theStruct.SendRevType;
		bProtectWQ	  = theStruct.bProtectWQ;
		memcpy( &RevInfo, &theStruct.RevInfo, sizeof( sReceiveInfo ) );
		memcpy( &JudgeStandard, &theStruct.JudgeStandard, sizeof( sJudgeStandard ) );		
		Priority      = theStruct.Priority;

		SW_Malloc_Int(theStruct.pValidEmitID,pValidEmitID,theStruct.nValidEmitCount,nValidEmitCount);
		SW_Malloc_Struct(sCurProtFreq,theStruct.pCurProtect,pCurProtect,theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.nSendFreq,nSendFreq);
		SW_Malloc_Struct(sRevFreq,theStruct.pRevFreq,pRevFreq,theStruct.nRevFreqCount,nRevFreqCount);

		return *this;
	}
}aRadarOut;

//电台场景输入信息
typedef struct  COMM_PARA_Scene				
{
	char			*sRID;				//身份识别号
	int				RadioID;            //电台ID号
	int				PlatID;		        //搭载平台ID号
	DKDMS::Enum_ATT		ATT;				//敌我属性
	DKDMS::Enum_EquipSrc	SRCType;			//装备来源
	char			*EquipmentName;		//装备名称
	float			dTime;		        //时间(s)
	float			LON;				//经度
	float			LAT;				//纬度
	float			Height;				//高度	
	DKDMS::Enum_SendRevType SendRevType;		//发射机和接收机工作类型
	bool			bProtectWQ;			//是否是保护装备（新增）
	int				lCtrlCount;
	sOpenCloseCtrl  *pCtrl;				//开关机时段
	int				nEmitCount;			//有效辐射源个数
	sValidEmitInfo	*pEmitInfo;			//有效辐射源信息
	char			*ArmyName;			//部队名称	
	char			*EquipType;			//装备型号
	int				lSendFreqCount;		//发射用频组数
	sSendFreq		*pSendFreq;			//发射用频
	int				lRevFreqCount;		//接收用频组数
	sRevFreq		*pRevFreq;			//接收用频	
	int				lProtCount;			//保护频率组数
	sProtectFreq	*pProtect;			//保护频率
	int				nOpenWndCount;		//开窗频率组数
	sOpenWndFreq	*pOpenWndFreq;		//开窗频率


	COMM_PARA_Scene()
	{
		sRID		  = NULL;
		RadioID		  = 0;
		PlatID		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;	
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		EquipmentName = NULL;	
		dTime		  = 0;
		LON			  = 0;
		LAT		      = 0;
		Height		  = 0;
		SendRevType   = DKDMS::Enum_SendRevType_0;
		lCtrlCount	  = 0;
		pCtrl		  = NULL;
		nEmitCount	  = 0;
		pEmitInfo	  = NULL;
		ArmyName	  = NULL;
		EquipType	  = NULL;	
		lSendFreqCount= 0;
		pSendFreq	  = NULL;
		lRevFreqCount = 0;
		pRevFreq	  = NULL;
		lProtCount	  = 0;
		pProtect	  = NULL;
		nOpenWndCount = 0;
		pOpenWndFreq  = NULL;
		bProtectWQ    = false;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipType);
		SW_Free_Char(ArmyName);

		SW_Delete(pEmitInfo);
		SW_Delete(pCtrl);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
		SW_Delete(pProtect);
		SW_Delete(pOpenWndFreq);
	}

	/*重载析构函数*/
	~COMM_PARA_Scene()
	{	
		Release();
	}


	/*重载拷贝构造函数*/
	COMM_PARA_Scene(const COMM_PARA_Scene &Info)
	{
		*this = Info;
	}

	/*重载=*/
	COMM_PARA_Scene& operator = (const COMM_PARA_Scene& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,			sRID);
		SW_Malloc_Char(theStruct.EquipmentName,	EquipmentName);
		SW_Malloc_Char(theStruct.ArmyName,		ArmyName);
		SW_Malloc_Char(theStruct.EquipType,		EquipType);

		RadioID		= theStruct.RadioID;
		ATT			= theStruct.ATT;
		SRCType		= theStruct.SRCType;
		dTime		= theStruct.dTime;
		PlatID		= theStruct.PlatID;
		LON			= theStruct.LON;
		LAT			= theStruct.LAT;
		Height		= theStruct.Height;
		SendRevType = theStruct.SendRevType;
		bProtectWQ  = theStruct.bProtectWQ;

		SW_Malloc_Struct(sOpenCloseCtrl,theStruct.pCtrl,		pCtrl,			theStruct.lCtrlCount,		lCtrlCount		);
		SW_Malloc_Struct(sValidEmitInfo,theStruct.pEmitInfo,	pEmitInfo,		theStruct.nEmitCount,		nEmitCount		);
		SW_Malloc_Struct(sSendFreq,		theStruct.pSendFreq,	pSendFreq,		theStruct.lSendFreqCount,	lSendFreqCount	);
		SW_Malloc_Struct(sRevFreq,		theStruct.pRevFreq,		pRevFreq,		theStruct.lRevFreqCount,	lRevFreqCount	);
		SW_Malloc_Struct(sProtectFreq,	theStruct.pProtect,		pProtect,		theStruct.lProtCount,		lProtCount		);
		SW_Malloc_Struct(sOpenWndFreq,	theStruct.pOpenWndFreq,	pOpenWndFreq,	theStruct.nOpenWndCount,	nOpenWndCount	);

		return *this;
	}
}sCommIn;

typedef struct ACOMM_PARA
{
	char			*sRID;			    //身份识别号
	int				RadioID;            //电台ID号
	int				PlatID;		        //平台ID号	
	DKDMS::Enum_ATT		ATT;				//敌我属性
	DKDMS::Enum_EquipSrc	SRCType;			//装备来源
	float			LON;				//经度
	float			LAT;				//纬度
	float			Height;				//高度	
	float			AntAZ;              //天线方位指向
	float			AntEl;              //天线俯仰指向
	float			fPt;			    //发射功率，单位：KW
	float			fLt;			    //发射损失，单位：dB
	float			fGt;			    //天线主瓣增益，单位：dB
	float			fAzBeamWidth;	    //天线主瓣水平波束宽度，单位：度
	float			fElBeamWidth;	    //天线主瓣俯仰波束宽度，单位：度
	DKDMS::Enum_CMD		CMD;		        //调制样式
	DKDMS::Enum_SendRevType SendRevType;		//发射机和接收机类型  
	bool			bProtectWQ;			//是否是保护装备
	sReceiveInfo	ReceiveInfo;		//接收机信息 
	sJudgeStandard	JudgeStandard;		//判断标准	
	DKDMS::Enum_Priority	Priority;			//保护优先级					
	int				nSendFreq;			//发射频率个数
	sSendFreq		*pSendFreq;			//发射频率信息
	int				nRevFreqCount;		//接收用频组数
	sRevFreq		*pRevFreq;			//接收用频
	int				nValidEmitCount;	//有效辐射源个数
	int				*pValidEmitID;		//有效辐射源ID
	int				lProtCount;			//当前保护频率组数
	sCurProtFreq	*pCurProtect;		//当前保护频率

	ACOMM_PARA()
	{
		sRID		  = NULL;
		RadioID		  = 0;
		PlatID		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;	
		SRCType		  = DKDMS::Enum_EquipSrc_0;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		AntAZ		  = 0;
		AntEl	      = 0;
		fPt			  = 0;
		fLt			  = 0;
		fGt			  = 0;		
		fAzBeamWidth  = 0;
		fElBeamWidth  = 0;
		CMD			  = DKDMS::Enum_CMD_0;	
		SendRevType	  = DKDMS::Enum_SendRevType_0;
		bProtectWQ	  = false;
		memset( &ReceiveInfo,0, sizeof( sReceiveInfo ) );
		memset( &JudgeStandard,0, sizeof( sJudgeStandard ) );
		Priority      = DKDMS::Enum_Priority_0;		
		nValidEmitCount	= 0;
		pValidEmitID  = NULL;
		lProtCount	  = 0;
		pCurProtect	  = NULL;
		nRevFreqCount = 0;
		pRevFreq      = NULL;	
		nSendFreq     = 0;
		pSendFreq     = NULL;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Delete(pValidEmitID);
		SW_Delete(pCurProtect);
		SW_Delete(pSendFreq);
		SW_Delete(pRevFreq);
	}

	/*重载析构函数*/
	~ACOMM_PARA()
	{
		Release();
	}

	/*重载拷贝构造函数*/
	ACOMM_PARA(const ACOMM_PARA &radarPara)
	{
		*this = radarPara;
	}

	/*重载=*/
	ACOMM_PARA& operator = (const ACOMM_PARA& theStruct)
	{
		if(this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);

		RadioID		  = theStruct.RadioID;
		PlatID		  = theStruct.PlatID;
		ATT			  = theStruct.ATT;	
		SRCType		  = theStruct.SRCType;
		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;		
		fPt			  = theStruct.fPt;
		fLt			  = theStruct.fLt;
		fGt			  = theStruct.fGt;		
		fAzBeamWidth  = theStruct.fAzBeamWidth;
		fElBeamWidth  = theStruct.fElBeamWidth;
		AntAZ		  = theStruct.AntAZ;
		AntEl	      = theStruct.AntEl;
		CMD			  = theStruct.CMD;			
		SendRevType	  = theStruct.SendRevType;
		bProtectWQ	  = theStruct.bProtectWQ;
		memcpy( &ReceiveInfo, &theStruct.ReceiveInfo, sizeof( sReceiveInfo ) );
		memcpy( &JudgeStandard, &theStruct.JudgeStandard, sizeof( sJudgeStandard ) );		
		Priority      = theStruct.Priority;		

		SW_Malloc_Int(theStruct.pValidEmitID,pValidEmitID,theStruct.nValidEmitCount,nValidEmitCount);
		SW_Malloc_Struct(sCurProtFreq,theStruct.pCurProtect,pCurProtect,theStruct.lProtCount,lProtCount);
		SW_Malloc_Struct(sSendFreq,theStruct.pSendFreq,pSendFreq,theStruct.nSendFreq,nSendFreq);
		SW_Malloc_Struct(sRevFreq,theStruct.pRevFreq,pRevFreq,theStruct.nRevFreqCount,nRevFreqCount);

		return *this;
	}
}aCommOut;

// Hanm 2011.6.27 增加
typedef struct AJAMSRC_RLT
{
	int			nJamSrcID;			//GR源ID
	DKDMS::Enum_JamRlt JamRlt;				//GR结果
	float		fEM;				//场强
	float		fSNR;				//信噪比
	float		fPower;				//功率
	AJAMSRC_RLT()
	{
		nJamSrcID	= 0;
		JamRlt		= DKDMS::Enum_JamRlt_0;
		fEM			= 0.0;
		fSNR		= 0.0;
		fPower		= 0.0;
	}

	~AJAMSRC_RLT()
	{

	}

	/*重载拷贝构造函数*/
	AJAMSRC_RLT(const AJAMSRC_RLT &radarPara)
	{
		*this = radarPara;
	}

	/*重载=*/
	AJAMSRC_RLT& operator = (const AJAMSRC_RLT& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		nJamSrcID = theStruct.nJamSrcID;
		JamRlt    = theStruct.JamRlt;
		fEM		  = theStruct.fEM;
		fSNR	  = theStruct.fSNR;
		fPower	  = theStruct.fPower;	
		return *this;
	}
}aJamSrcRlt;


// Hanm 2011.6.27 增加
typedef struct AASS_CLASH_CALC
{
	char			*sRID;			    //身份识别号
	int				nID;				//接收机ID
	aFreqOut		RltOut;		        //综合静态计算结果
	int				nCount;				//GR源个数
	aJamSrcRlt   	*pJamSrcRlt;		//GR源GR信息

	AASS_CLASH_CALC()
	{
		sRID = NULL;
		nID  = 0;
		memset( &RltOut, 0, sizeof( aFreqOut ) );
		nCount = 0;
		pJamSrcRlt = NULL;
	}


	/*重载析构函数*/
	~AASS_CLASH_CALC()
	{	
		SW_Free_Char(sRID);
		SW_Delete(pJamSrcRlt);
	}


	/*重载拷贝构造函数*/
	AASS_CLASH_CALC(const AASS_CLASH_CALC &radarPara)
	{
		*this = radarPara;
	}

	/*重载=*/
	AASS_CLASH_CALC& operator = (const AASS_CLASH_CALC& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Delete(pJamSrcRlt);

		SW_Malloc_Char(theStruct.sRID,sRID);

		nID		= theStruct.nID;
		RltOut  = theStruct.RltOut;

		SW_Malloc_Struct(aJamSrcRlt,theStruct.pJamSrcRlt,pJamSrcRlt,theStruct.nCount,nCount);

		return *this;
	}
}aAssClashCalcOut;

//自定义导弹动态推演想定信息(后台没有实际模型，态势特殊处理)
typedef struct  WEAPON_PARA_Scene	
{
	char		*sRID;			    	//身份识别号
	int			nID;	        		//ID号
	int			PlatID;	        		//搭载平台ID号	
	int			nAttackID;				//攻击目标ID
	DKDMS::Enum_ATT	ATT;					//敌我属性
	char		*EquipmentName;			//装备名称
	char		*EquipType;				//装备型号
	float		LON;					//经度
	float		LAT;					//纬度
	float		Height;					//高度		
	float		fInitVel;				//初始速度
	float	    fDownVel;				//俯冲段平均速度，单位:m/s
	float		fTurnVel;				//水平/转向段平均速度，单位:m/s
	float		fMaxTime;				//动力射程最大作用时间，单位:s
	float		fOptAlt;				//最佳平飞高度，单位:m,典型取值1500米
	float		fOptAngle;				//最佳俯冲角,单位:度,典型取值45.0度


	WEAPON_PARA_Scene()
	{
		sRID		  = NULL;
		nID			  = 0;
		PlatID		  = 0;
		nAttackID	  = 0;	
		ATT			  = DKDMS::Enum_ATT_1;			
		EquipmentName = NULL;
		EquipType	  = NULL;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		fInitVel	  = 0;
		fDownVel	  = 0;
		fTurnVel	  = 0;
		fMaxTime	  = 0;
		fOptAlt		  = 0;
		fOptAngle	  = 0;		
	}

	/*重载析构函数*/
	~WEAPON_PARA_Scene()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipType);
	}

	/*重载拷贝构造函数*/
	WEAPON_PARA_Scene(const WEAPON_PARA_Scene &Info)
	{
		*this = Info;
	}

	/*重载=*/
	WEAPON_PARA_Scene& operator = (const WEAPON_PARA_Scene& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		//SW_Free_Char(EquipmentName);
		//SW_Free_Char(EquipType);
		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);
		nID			  = theStruct.nID;
		PlatID		  = theStruct.PlatID;
		nAttackID	  = theStruct.nAttackID;	
		ATT			  = theStruct.ATT;			
		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;
		fInitVel	  = theStruct.fInitVel;
		fDownVel	  = theStruct.fDownVel;
		fTurnVel	  = theStruct.fTurnVel;
		fMaxTime	  = theStruct.fMaxTime;
		fOptAlt		  = theStruct.fOptAlt;
		fOptAngle	  = theStruct.fOptAngle;		
		return *this;
	}
}sWeaponIn;


//导弹动态推演输出
typedef struct  WEAPON_PARA	
{
	char		*sRID;			    	//身份识别号
	int			nID;	        		//ID号
	int			PlatID;	        		//搭载平台ID号	
	int			nAttackID;				//攻击目标ID
	float		dTime;					//当前时间
	DKDMS::Enum_ATT	ATT;					//敌我属性
	char		*EquipmentName;			//装备名称
	char		*EquipType;				//装备型号	
	DKDMS::Enum_WorkState WorkState;			//工作状态
	bool        bEnd;					//是否着落
	float		LON;					//经度
	float		LAT;					//纬度
	float		Height;					//高度	
	float		fAZ;					//航向角（初始化航向角和搭载飞机航向角相同）
	float		fEl;					//俯仰

	WEAPON_PARA()
	{
		sRID		  = NULL;
		nID			  = 0;
		PlatID		  = 0;
		nAttackID	  = 0;	
		dTime		  = 0;
		ATT			  = DKDMS::Enum_ATT_1;			
		EquipmentName = NULL;
		EquipType	  = NULL;		
		WorkState	  = DKDMS::Enum_WorkState_1;
		bEnd		  = false;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		fAZ			  = 0;
		fEl			  = 0;	
	}

	/*重载析构函数*/
	~WEAPON_PARA()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipType);
	}

	/*重载拷贝构造函数*/
	WEAPON_PARA(const WEAPON_PARA &Info)
	{
		*this = Info;
	}

	/*重载=*/
	WEAPON_PARA& operator = (const WEAPON_PARA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		//SW_Free_Char(EquipmentName);
		//SW_Free_Char(EquipType);
		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);
		SW_Malloc_Char(theStruct.EquipType,EquipType);

		nID			  = theStruct.nID;
		PlatID		  = theStruct.PlatID;
		nAttackID	  = theStruct.nAttackID;
		dTime		  = theStruct.dTime;
		WorkState     = theStruct.WorkState;
		ATT			  = theStruct.ATT;		
		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		bEnd		  = theStruct.bEnd;
		Height		  = theStruct.Height;
		fAZ			  = theStruct.fAZ;
		fEl			  = theStruct.fEl;
		return *this;
	}
}sWeaponOut;


//自定义导弹静态想定信息(和静态输出结构体一致)
typedef struct  AWEAPON_PARA_Scene	
{
	char		*sRID;			    	//身份识别号
	int			nID;	        		//ID号
	int			PlatID;	        		//搭载平台ID号		
	DKDMS::Enum_ATT	ATT;					//敌我属性
	char		*EquipmentName;			//装备名称
	char		*EquipType;				//装备型号
	char		*MID;					//模型ID
	float		LON;					//经度
	float		LAT;					//纬度
	float		Height;					//高度		
	float		fAZ;					//航向
	float		fEl;					//俯仰	

	AWEAPON_PARA_Scene()
	{
		sRID		  = NULL;
		nID			  = 0;
		PlatID		  = 0;	
		ATT			  = DKDMS::Enum_ATT_1;			
		EquipmentName = NULL;
		EquipType	  = NULL;
		MID			  = NULL;
		LON			  = 0;
		LAT			  = 0;
		Height		  = 0;
		fAZ			  = 0;
		fEl			  = 0;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(EquipmentName);
		SW_Free_Char(EquipType);
		SW_Free_Char(MID);
	}

	/*重载析构函数*/
	~AWEAPON_PARA_Scene()
	{
		Release();
	}

	/*重载拷贝构造函数*/
	AWEAPON_PARA_Scene(const AWEAPON_PARA_Scene &Info)
	{
		*this = Info;
	}

	/*重载=*/
	AWEAPON_PARA_Scene& operator = (const AWEAPON_PARA_Scene& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.EquipmentName,EquipmentName);

		SW_Malloc_Char(theStruct.EquipType,EquipType);
		SW_Malloc_Char(theStruct.MID,MID);

		nID			  = theStruct.nID;
		PlatID		  = theStruct.PlatID;		
		ATT			  = theStruct.ATT;			
		LON			  = theStruct.LON;
		LAT			  = theStruct.LAT;
		Height		  = theStruct.Height;
		fAZ			  = theStruct.fAZ;
		fEl			  = theStruct.fEl;
		return *this;
	}
}aWeaponIn, aWeaponOut;

//aRadarGroupCal: 静态雷达组网TC能力(计算模型计算)
//aCommGroupCal:  静态通信覆盖范围能力(计算模型计算)
typedef struct AEMIT_GROUP
{
	char	*sRID;				//本席位身份识别号
	float	fHeight;
	int		nJamIDCount;
	int		* pJamID;
	int		nIDCount;
	int		* pID;

	AEMIT_GROUP()
	{
		memset( this, 0, sizeof( AEMIT_GROUP ) );
	}

	/*重载析构函数*/
	~AEMIT_GROUP()
	{
		SW_Free_Char(sRID);
		SW_Delete(pJamID);
		SW_Delete(pID);
	}

	/*重载拷贝构造函数*/
	AEMIT_GROUP(const AEMIT_GROUP &Info)
	{
		*this = Info;
	}

	/*重载=*/
	AEMIT_GROUP& operator = (const AEMIT_GROUP& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		//SW_Delete(pJamID);
		//SW_Delete(pID);
		SW_Malloc_Char(theStruct.sRID,sRID);	
		fHeight = theStruct.fHeight;
		SW_Malloc_Int( theStruct.pJamID, pJamID,  theStruct.nJamIDCount, nJamIDCount  );
		SW_Malloc_Int( theStruct.pID, pID, theStruct.nIDCount,  nIDCount );

		return *this;
	}
}aRadarGroupCal, aCommGroupCal;

typedef struct ONE_DET_RANGE
{
	int	  nID;
	int	  nPtCount;
	float *pfLon;
	float *pfLat;
	float *pfHeight;

	ONE_DET_RANGE()
	{	
		memset( this, 0, sizeof( ONE_DET_RANGE ) );
	}
	/*重载析构函数*/
	~ONE_DET_RANGE()
	{
		SW_Delete(pfLon);
		SW_Delete(pfLat);
		SW_Delete(pfHeight);
	}

	/*重载拷贝构造函数*/
	ONE_DET_RANGE(const ONE_DET_RANGE &Info)
	{
		*this = Info;
	}

	/*重载=*/
	ONE_DET_RANGE& operator = (const ONE_DET_RANGE& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Delete(pfLon);
		//SW_Delete(pfLat);
		//SW_Delete(pfHeight);

		nID = theStruct.nID;
		nPtCount = theStruct.nPtCount;
		SW_Malloc_Struct( float, theStruct.pfLon, pfLon, theStruct.nPtCount, nPtCount );	
		SW_Malloc_Struct( float, theStruct.pfLat, pfLat, theStruct.nPtCount, nPtCount );	
		SW_Malloc_Struct( float, theStruct.pfHeight, pfHeight, theStruct.nPtCount, nPtCount );	

		return *this;
	}
}sOneDetRange;

typedef struct AEMIT_OUT
{
	char			*sRID;				//身份识别号
	float			fHeight;
	int				nRadarCount;
	sOneDetRange	*pOneRadarDet;

	AEMIT_OUT()
	{	
		memset( this, 0, sizeof( AEMIT_OUT ) );
	}
	/*重载析构函数*/
	~AEMIT_OUT()
	{
		SW_Free_Char(sRID);	
		SW_Delete(pOneRadarDet);
	}

	/*重载拷贝构造函数*/
	AEMIT_OUT(const AEMIT_OUT &Info)
	{
		*this = Info;
	}

	/*重载=*/
	AEMIT_OUT& operator = (const AEMIT_OUT& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);	
		//SW_Delete(pOneRadarDet);

		SW_Malloc_Char(theStruct.sRID,sRID);	
		fHeight = theStruct.fHeight;
		SW_Malloc_Struct( sOneDetRange, theStruct.pOneRadarDet, pOneRadarDet, theStruct.nRadarCount, nRadarCount );		

		return *this;
	}
}aRadarGroupOut, aCommGroupOut;


//装备是否受到GR(计算模型计算)-- 静态
typedef struct AEQ_JAM_CAL
{
	char	*sRID;			//身份识别号
	int		nEquipCount;	//指定装备个数
	int		*pEquipID;		//指定装备ID
	int		nJamCount;
	int		*pJamID;		//GR源ID

	AEQ_JAM_CAL()
	{
		memset( this, 0, sizeof( AEQ_JAM_CAL ) );
	}
	~AEQ_JAM_CAL()
	{
		SW_Free_Char(sRID);	
		SW_Delete(pEquipID);
		SW_Delete(pJamID);
	}

	/*重载拷贝构造函数*/
	AEQ_JAM_CAL(const AEQ_JAM_CAL &Info)
	{
		*this = Info;
	}

	/*重载=*/
	AEQ_JAM_CAL& operator = (const AEQ_JAM_CAL& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);	
		//SW_Delete(pEquipID);
		//SW_Delete(pJamID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Int( theStruct.pEquipID, pEquipID, theStruct.nEquipCount, nEquipCount );	
		SW_Malloc_Int( theStruct.pJamID, pJamID, theStruct.nJamCount, nJamCount );	

		return *this;
	}

}aEQJamCal;

typedef struct ONE_EQ_JAM_OUT
{
	int			nJamedID;		//被GR装备
	DKDMS::Enum_JamRlt eJamRlt;		//GR程度
	int			nJamEQCount;
	aJamSrcRlt	*pJamEQRlt;		//GR装备

	ONE_EQ_JAM_OUT()
	{
		memset( this, 0, sizeof( ONE_EQ_JAM_OUT ) );
	}
	~ONE_EQ_JAM_OUT()
	{
		SW_Delete(pJamEQRlt);
	}

	/*重载拷贝构造函数*/
	ONE_EQ_JAM_OUT(const ONE_EQ_JAM_OUT &Info)
	{
		*this = Info;
	}

	/*重载=*/
	ONE_EQ_JAM_OUT& operator = (const ONE_EQ_JAM_OUT& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Delete(pJamEQRlt);

		nJamedID = theStruct.nJamedID;	
		eJamRlt = theStruct.eJamRlt;	
		SW_Malloc_Struct( aJamSrcRlt, theStruct.pJamEQRlt, pJamEQRlt, theStruct.nJamEQCount , nJamEQCount);	

		return *this;
	}

}aOneEQJamOut;

typedef struct EQ_JAM_OUT
{
	char		*sRID;			//身份识别号
	int			nOneJamNum;		//GR结果个数
	aOneEQJamOut *pOneEQJamOut;

	EQ_JAM_OUT()
	{
		memset( this, 0, sizeof( EQ_JAM_OUT ) );
	}
	~EQ_JAM_OUT()
	{
		SW_Free_Char(sRID);	
		SW_Delete(pOneEQJamOut);
	}
	
	/*重载拷贝构造函数*/
	EQ_JAM_OUT(const EQ_JAM_OUT &Info)
	{
		*this = Info;
	}

	/*重载=*/
	EQ_JAM_OUT& operator = (const EQ_JAM_OUT& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
	/*	SW_Free_Char(sRID);	
		SW_Delete(pOneEQJamOut);*/

		SW_Malloc_Char(theStruct.sRID,sRID);		
		SW_Malloc_Struct( aOneEQJamOut, theStruct.pOneEQJamOut, pOneEQJamOut, theStruct.nOneJamNum , nOneJamNum);	

		return *this;
	}

}aEQJamOut;

//指定装备间是否GR(计算模型计算)
typedef struct SPECIAL_EQ_JAM_CAL
{
	char	*sRID;				//身份识别号
	int		nEQCount;
	int		*pEQID;	

	SPECIAL_EQ_JAM_CAL()
	{
		memset( this, 0, sizeof( SPECIAL_EQ_JAM_CAL ) );
	}
	~SPECIAL_EQ_JAM_CAL()
	{
		SW_Free_Char(sRID);		
		SW_Delete(pEQID);
	}
	
	/*重载拷贝构造函数*/
	SPECIAL_EQ_JAM_CAL(const SPECIAL_EQ_JAM_CAL &Info)
	{
		*this = Info;
	}

	/*重载=*/
	SPECIAL_EQ_JAM_CAL& operator = (const SPECIAL_EQ_JAM_CAL& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
	/*	SW_Free_Char(sRID);		
		SW_Delete(pEQID);*/

		SW_Malloc_Char(theStruct.sRID,sRID);		
		SW_Malloc_Int( theStruct.pEQID, pEQID, theStruct.nEQCount , nEQCount);	

		return *this;
	}

}aSpecialEQJamCal;

#pragma pack()

#endif
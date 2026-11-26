#pragma once

#include "CalModelBase.h"
#include "MEnStruct.h"

class  CKCG_XKu: public CalModelBase
{
public:
	////===================================动态推演接口==================================////
	//1通用
	virtual void SetRunMode(int RunMode) = 0;     //设置控制方式（0-人工控制;1-智能体控制;2-平行战场自主控制;3-作战管理系统控制）
	virtual void SetMountEquip(int RunMode) = 0;  //设置挂载方式（0-挂载信号级样机；1-不挂样机）
	
	virtual void SetMod_KCG_XKu(sKCG_XKu_Set_PARA *RadarPos) = 0;		    //场景初始参数输入
	virtual void Set_OutPlat(sPLAT_PARA *OutPlat) = 0;                      //搭载平台和目标平台输入
	virtual int Send_ImportEventReport(eIMPORT_EVENT_REPORT *&pImport) = 0; //重要事件输出
	virtual int Send_MnqOutData(sMNQ_OUTDATA *&pMnqData) = 0;               //模拟器模式实装报文输出（至管理系统）
	
	//3雷达对抗
	virtual void Set_Radar(sRADAR_PARA *pRadar) = 0;                        //雷达参数输入
	//3-1 雷侦	
	virtual void Set_RadarReconEquip(sRECON_Get_PARA *pReconIn) = 0;        //协同站信息输入
	virtual void Set_RadarParaInfo(sRECON_RADARPARA *pReconedRadarParaIn) = 0;//协同站ZC结果输入
	virtual bool GetMod_RadarReconEquip(sRECON_Get_PARA *&pJamOut) = 0;     //雷达ZC装备状态输出
	virtual bool Send_Sit_ReconnaissanceArea(sRECON_AREA *&pArea) = 0;      //雷达ZC范围输出（对特定目标）
    virtual bool Send_Sit_RadarParaInfo(sRECON_RADARPARA *&pReconedRadarPara) = 0;//雷达ZC结果输出
	//virtual bool Send_Sit_DataFusionInfo(sRECON_DATAFUSIONPARA *&pDataFusionInfo) = 0;//数据融合定位结果输出（待定？？？）
	//3-2 雷干
	virtual bool GetMod_RadarJamEquip(sJAM_Get_PARA *&pJamOut) = 0;         //雷达GR装备状态输出，含GR波束信息
	virtual int Send_RadarJamParam(sJAM_PARA *&pRadarJamParam) = 0;         //雷达GR参数输出
	virtual bool Send_Sit_JamPowerRange(sJAM_JAMRANGE *&pRange) = 0;        //雷达GR威力范围输出（对特定目标）
	
    ////===================================静态计算接口==================================////
	//2雷达对抗
	virtual void AbilitySetMod_RadarJamEquip(aJAM_Set_PARA *pAJam) = 0;     //设置雷达对抗初始化参数
	//virtual void AbilitySetMod_RadarReconEquip(aRECON_Set_PARA *pARecon) = 0;
	virtual void AbilityIn_RadarPara(aRADAR_PARA *pARadarPara) = 0;         //雷达工作参数输入
    virtual int AbilityOut_JamPara(aJAM_PARA *&pAJamPara) = 0;              //雷达GR信号输出
    virtual int AbilityCal_JamPointVar(aJamPointVar *&pJamPointVar) = 0;    //雷达GR波束计算输出
	virtual int AbilityCal_JamPowerRange(sJAM_JAMRANGE *&pRange) = 0;       //雷达GR威力范围计算输出
	virtual int AbilityCal_RadarJamResult( aJAM_RESULT* &pResult ) = 0;     //对多个雷达的GR结果计算输出（可GR性，非GR有效性）
   	virtual int AbilityCal_RadarReconRange(aReconRange *&pReconRange) = 0;  //对某型雷达的二维ZC范围计算输出
	virtual int AbilityCal_RadarReconRange3D(aReconRange* &pReconRange) = 0;//对某型雷达的三维ZC范围计算输出
	virtual int AbilityCal_RadarReconResult( aRECON_RESULT* &pResult ) = 0; //对多个雷达的ZC结果计算输出
};

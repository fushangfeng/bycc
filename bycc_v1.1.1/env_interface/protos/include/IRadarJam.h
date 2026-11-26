#pragma once

#include "CalModelBase.h"
#include "MEnStruct_RadarJam.h"

class CIRadarJam : public CalModelBase  
{
public:
	/*以下为动态推演功能函数*/
	virtual void SetMod_RadarJamEquip(sJAM_Set_PARA *pJam) = 0;       //初始化参数输入
	virtual bool GetMod_RadarJamEquip(sJAM_Get_PARA *&pJamOut) = 0;   //状态参数输出
	virtual void Set_Radar(sRADAR_PARA *pRadar) = 0;                  //雷达辐射参数输入
	virtual void Set_PlanePlat(sPLAT_PARA *pPlat) = 0;                //搭载平台信息输入
	//virtual void Set_JAMPARA(sJAM_PARA *pRadarJamParam) = 0;
    virtual bool Send_Sit_ReconnaissanceArea(sRECON_AREA *&pArea) = 0;//ZC能力范围输出（对特定目标）
    virtual bool Send_Sit_RadarParaInfo(sRECON_RADARPARA *&pReconedRadarPara) = 0;//ZC结果参数输出
    virtual int Send_RadarJamParam(sJAM_PARA *&pRadarJamParam) = 0;   //GR参数输出（可连续输出多组）
	virtual bool Send_Sit_JamPowerRange(sJAM_JAMRANGE *&pRange) = 0;  //GR威力范围输出（对特定目标）
	//virtual int Send_RadarRange(sRADAR_RANGE *&RadarRange) = 0;
	 virtual int Send_ImportEventReport(eIMPORT_EVENT_REPORT *&pImport) = 0;//重要事件输出
	
	/*以下为静态计算功能函数*/
	virtual void AbilitySetMod_RadarJamEquip(aJAM_Set_PARA *pAJam) = 0;      //静态GR初始参数设置
	virtual void AbilityIn_RadarPara(aRADAR_PARA *pARadarPara) = 0;          //静态雷达辐射参数输入
    virtual int AbilityOut_JamPara(aJAM_PARA *&pAJamPara) = 0;               //静态GR参数计算
    virtual int AbilityCal_JamPointVar(aJamPointVar *&pJamPointVar) = 0;     //静态GR波束计算
	virtual int AbilityCal_RadarReconRange(aReconRange *&pReconRange) = 0;   //静态ZC能力范围计算（二维点）
	virtual int AbilityCal_RadarReconResult( aRECON_RESULT* &pResult ) = 0;  //静态ZC结果计算
	virtual int AbilityCal_JamPowerRange(sJAM_JAMRANGE *&pRange) = 0;        //静态GR威力范围计算
	virtual int AbilityCal_RadarJamResult( aJAM_RESULT* &pResult ) = 0;      //静态GR对抗关系计算(能否构成GR关系，非能否有效GR)
	//virtual void AbilitySet_ReconCfgPara(aRadarReconCfgPara *pCfgPara) = 0;
	//virtual void AbilitySet_JamCfgPara(aRadarJamCfgPara *pCfgPara) = 0;
	virtual int AbilityCal_RadarReconRange3D(aReconRange* &pReconRange) = 0; //静态ZC能力范围计算（三维）
};

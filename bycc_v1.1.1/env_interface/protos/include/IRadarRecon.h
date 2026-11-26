#pragma once

#include "CalModelBase.h"

class CIRadarRecon : public CalModelBase
{
public:
	virtual void SetMod_RadarJamEquip(sJAM_Set_PARA *pJam) = 0;
	virtual bool GetMod_RadarJamEquip(sJAM_Get_PARA *&pJamOut) = 0;
	virtual void SetMod_RadarReconEquip(sRECON_Set_PARA *pRecon) = 0;//初始化雷侦
	virtual bool GetMod_RadarReconEquip(sRECON_Get_PARA *&pJamOut) = 0;//
	virtual void Set_Radar(sRADAR_PARA *pRadar) = 0;
	virtual void Set_PlanePlat(sPLAT_PARA *pPlat) = 0;//雷侦平台信息
	virtual void Set_JAMPARA(sJAM_PARA *pRadarJamParam) = 0;
	virtual void Set_RadarReconEquip(sRECON_Get_PARA *pReconIn) = 0;//设置其他雷侦信息
	virtual void Set_RadarParaInfo(sRECON_RADARPARA *pReconedRadarParaIn) = 0;//雷侦TC信息
    /*事件类*/
    virtual bool Send_Sit_ReconnaissanceArea(sRECON_AREA *&pArea) = 0;//ZC范围
    virtual bool Send_Sit_RadarParaInfo(sRECON_RADARPARA *&pReconedRadarPara) = 0;//ZC结果信息
	virtual bool Send_Sit_DataFusionInfo(sRECON_DATAFUSIONPARA *&pDataFusionInfo) = 0;
    virtual int Send_RadarJamParam(sJAM_PARA *&pRadarJamParam) = 0;
    virtual int Send_ImportEventReport(eIMPORT_EVENT_REPORT *&pImport) = 0;
	virtual bool Send_Sit_JamPowerRange(sJAM_JAMRANGE *&pRange) = 0;			// 2013.1.22 add
	virtual int Send_RadarRange(sRADAR_RANGE *&RadarRange) = 0;
	//virtual void Set_ReconControlOrder(sRadarReconControlOrder *pOrder) = 0;
	//virtual void Set_ReconDataFusionOrder(sAction_Get_PARA *pOrder) = 0;
	//virtual void Set_JammerControlOrder(sRadarJammerControlOrder *pOrder) = 0;


	/*静态类*/
	virtual void AbilitySetMod_RadarJamEquip(aJAM_Set_PARA *pAJam) = 0;
	virtual void AbilitySetMod_RadarReconEquip(aRECON_Set_PARA *pARecon) = 0;
	virtual void AbilityIn_RadarPara(aRADAR_PARA *pARadarPara) = 0;
    virtual int AbilityOut_JamPara(aJAM_PARA *&pAJamPara) = 0;
    virtual int AbilityCal_JamPointVar(aJamPointVar *&pJamPointVar) = 0;
	virtual int AbilityCal_RadarReconRange(aReconRange *&pReconRange) = 0;
	virtual int AbilityCal_RadarReconResult( aRECON_RESULT* &pResult ) = 0;
	virtual int AbilityCal_JamPowerRange(sJAM_JAMRANGE *&pRange) = 0;
	virtual int AbilityCal_RadarJamResult( aJAM_RESULT* &pResult ) = 0;
	virtual void AbilitySet_ReconCfgPara(aRadarReconCfgPara *pCfgPara) = 0;
	virtual void AbilitySet_JamCfgPara(aRadarJamCfgPara *pCfgPara) = 0;
	virtual int AbilityCal_RadarReconRange3D(aReconRange* &pReconRange) = 0;
};

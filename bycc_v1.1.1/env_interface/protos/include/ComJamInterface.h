/*
* @file     ComJamInterface.h
* @brief    通信GR模型接口类
*/
#pragma once
#include "CalModelBase.h"
#include "MEnStruct.h"
class ComJamInterface : public CalModelBase
{
public:
	// 初始化信息设置
	virtual void SetMod_RadioJam(sCOMJAM_SET_PARA *pRadioJam) = 0;	
	// 搭载平台参数输入
	virtual void Set_Plat(sPLAT_PARA *pPlat) = 0; 
	// 通信辐射源装备信息输入
	virtual void Set_Radio(sCOM_PARA *pRadioPara) = 0;		
	// 通信GR设备信息输出
	virtual bool GetMod_RadioJam(sCOMJAM_PARA *&pRadioJam) = 0;	
	// 发送通信GR参数输出
	virtual bool Send_Sit_CommJamPara(sCOMMJAMPARA *&pCommJamPara) = 0; 
	// 发送ZC结果输出
	virtual bool Send_Sit_CommRecPara(sCOMMDETECTPARA *&pCommRecPara) = 0 ;	
	// 重要事件输出
	virtual int Send_ImportEventReport(eIMPORT_EVENT_REPORT *&pImport) = 0;

	//静态计算后续再设计
	//virtual void AbilitySetMod_Jam(RADIOJAM_SET_PARA *pJam)=0;//静态初始化
	//virtual void AbilityIn_Radio(RADIO_PARA *pRadio)=0;//静态对端电台输入
	//virtual int AbilityOut_JamParam(COMMJAMPARA *&pJam)=0;//静态GR参数输出
	//virtual int AbilityCal_COMMReconRange(COMMRECON_AREA *&pRange)=0;//对某型电台/链路的ZC范围
	//virtual int AbilityCal_COMMReconResult(aCOMMRECON_RESULT *&pResult)=0;//通信ZC结果//增加“显示ZC结果”
	//virtual int AbilityCal_CommJamPowerRange(sJAM_JAMRANGE *&pRange)=0;//对某型电台/链路的GR能力范围
	//virtual int AbilityCal_COMMJamResult(aCOMMJAM_RESULT *&pResult ) =0;//对众多电台/链路的GR结果
};

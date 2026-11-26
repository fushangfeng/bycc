#pragma once
#include "CalModelBase.h"
#include "MEnStruct.h"

class ComRadioInterface :public CalModelBase
{
public:
	// 场景初始化信息设置
	virtual void SetMod_Radio(sCOM_SET_PARA *pRadio) = 0;	
	// 搭载平台参数输入
	virtual void Set_Plat(sPLAT_PARA *pPlat) = 0; 
	// 通信GR参数输入
	virtual void Set_CommJamPara(sCOMMJAMPARA *pCommJamPara) = 0;		
	// 通信辐射源装备状态信息输出
	virtual bool GetMod_Radio(sCOM_PARA *&pRadioPara) = 0;	
	// 通信畅通区输出
	virtual bool Send_Sit_sCommUnblockedArea(CommUnblockedArea *&pCommUnblockedArea)=0; 
	//通联计算结果输出 与具体的多个接收台站之间的通联状态计算
	virtual bool Send_Sit_sCommState(sComState *&pComState)=0;
	// 重要事件输出
	virtual int Send_ImportEventReport(eIMPORT_EVENT_REPORT *&pImport) = 0;

	//静态计算后续再设计
	//virtual void AbilitySetMod_Radio(RADIO_SET_PARA *pRadio)=0;//静态初始化
	//virtual int AbilityOut_Radio(RADIO_PARA *&pRadio)=0;//静态电台参数输出	
	//virtual void AbilityIn_JamParam(COMMJAMPARA *pJam)=0;//静态GR参数输入
	//virtual int AbilityCal_CommUnblockedArea(CommUnblockedArea *&pCommUnblockedArea)=0;// 通信畅通区
	//virtual int AbilityCal_ComState(aComState *&pComState)=0;//通联状态

};

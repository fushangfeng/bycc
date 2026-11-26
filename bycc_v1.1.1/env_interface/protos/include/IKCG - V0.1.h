#pragma once

#include "CalModelBase.h"
#include "MEnStruct.h"

class  CKCG: public CalModelBase（//！！！增加设置使用模式的基类函数；对GPS终端的GR如何体现？）
{
public:
	////===================================动态推演接口==================================////
	//1通用
	virtual bool SetMod_KCG(sKCG_Set_PARA *RadarPos) = 0;				    //初始参数输入，待定，各样机根据KCG.txt中sKCG_Set_PARA的基线版按需修改
	virtual bool Set_OutPlat(sPLAT_PARA *OutPlat) = 0;                      //搭载平台和目标平台输入
	virtual int Send_ImportEventReport(eIMPORT_EVENT_REPORT *&pImport) = 0; //重要事件输出
	virtual int Send_MnqOutData(sMNQ_OUTDATA *&pMnqData) = 0;               //模拟器模式输出（至管理系统）
	
	//2雷达
	virtual bool Set_JAMPARA(sJAM_PARA *Jamparas) = 0;						//GR参数输入
	virtual bool GetMod_Radar(sRADAR_PARA *&RadarPara) = 0;					//雷达装备参数及状态输出
	virtual bool Send_Sit_RadarRange(sRADAR_RANGE *&RadarRange) = 0;        //雷达TC范围输出
	virtual bool Send_Sit_RadarDetectInfo(sRadar_DetectInfo *&RadarDetactInfo) = 0;//雷达TC结果输出（考虑如何补充航迹的输出）
	
	//3雷达对抗
	virtual void Set_Radar(sRADAR_PARA *pRadar) = 0;                        //雷达参数输入
	//3-1 雷侦	（考虑协同ZC）！！！！场景中增加范围计算id
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
			
	//5通信对抗
	virtual void Set_Radio(RADIO_PARA *pRadioPara) = 0;	                    //通信电台参数输入
	//5-1 通侦（考虑协同ZC）！！！！场景中增加范围计算id、以及协同站信息输入
	virtual void Set_CommReconEquip(sRECON_Get_PARA *pReconIn) = 0;         //协同站信息输入（待修改）
	virtual void Set_CommParaInfo(sCOMMDETECTPARA *pCommRecPara) = 0;       //协同站ZC结果输入（待修改）
    virtual bool Send_Sit_CommReconArea(sRECON_AREA *&pArea) = 0;           //！！！缺ZC范围（待修改，找到DKL的ZC范围输出结构体）
	virtual bool Send_Sit_CommRecPara(sCOMMDETECTPARA *&pCommRecPara) = 0 ;	//发送ZC结果（待修改，确定是否有测向信息）
	//5-2 通干（考虑协同GR）！！！！场景中增加范围计算id、以及协同站信息输入
	virtual bool GetMod_RadioJam(sRADIOJAM_PARA *&pRadioJam) = 0;           // 通信GR设备信息输出(待修改，GR波束结构要改)
	virtual bool Send_Sit_CommJamPara(COMMJAMPARA *&pCommJamPara) = 0;      // 通信GR参数输出
	

    ////===================================静态计算接口==================================////
	//1雷达
	virtual void AbilitySetMod_Radar(aRADAR_Set_PARA *pRadarPos) = 0;	    //设置雷达初始参数
	virtual int  AbilityOut_RadarPara(aRADAR_PARA *&pRadarPara) = 0;	    //雷达交互参数输出
	virtual void AbilityIn_JamPara(aJAM_PARA *pJamPara) = 0;	            // 雷达GR信号输入
	virtual void AbilityIn_PlatPara(aPLAT_PARA * pTrgPlat) = 0;	            // 雷达TC目标平台信息输入
	virtual int  AbilityCal_DetectRange(aRadarRange *&pRadarRange) = 0;	    // 雷达二维TC范围计算输出
	virtual int  AbilityCal_DetectResult(aRADAR_RESULT *&pRadarResult) = 0;	// 雷达TC结果计算输出（考虑视距遮挡）
	//virtual int  AbilityCal_DetectResultMulti(aRADAR_RESULTEX *&pRadarResult) = 0;	// 雷达多目标TC结果计算输出
	virtual int  AbilityCal_DetectDist(aRADAR_DIST *&pRadarDist) = 0;	    // 无GR条件下的雷达TC距离计算输出
	virtual int  AbilityCal_RadarJamed(aRadarJamed*& pRadarJamed) = 0;	    // 雷达受扰关系计算输出
	virtual int  AbilityCal_DetectRange3D(RadarRange3D *&pRadarRange) = 0;	// 雷达三维TC范围计算输出
	//2雷达对抗
	virtual void AbilitySetMod_RadarJamEquip(aJAM_Set_PARA *pAJam) = 0;     //设置雷达对抗初始化参数
	//virtual void AbilitySetMod_RadarReconEquip(aRECON_Set_PARA *pARecon) = 0;
	virtual void AbilityIn_RadarPara(aRADAR_PARA *pARadarPara) = 0;         //雷达工作参数输入
    virtual int AbilityOut_JamPara(aJAM_PARA *&pAJamPara) = 0;              //雷达GR信号输出
    virtual int AbilityCal_JamPointVar(aJamPointVar *&pJamPointVar) = 0;    //雷达GR波束计算输出
	virtual int AbilityCal_JamPowerRange(sJAM_JAMRANGE *&pRange) = 0;       //雷达GR威力范围计算输出
	virtual int AbilityCal_RadarJamResult( aJAM_RESULT* &pResult ) = 0;     //对多个雷达的GR结果计算输出（可GR性，非GR有效性）
    virtual int AbilityCal_RadarReconRange(aReconRange *&pReconRange) = 0;  //对某型雷达的二维ZC范围计算输出（考虑视距遮挡）
	virtual int AbilityCal_RadarReconRange3D(aReconRange* &pReconRange) = 0;//对某型雷达的三维ZC范围计算输出
	virtual int AbilityCal_RadarReconResult( aRECON_RESULT* &pResult ) = 0; //对多个雷达的ZC结果计算输出
		
	//4通信对抗
	virtual void AbilitySetMod_Jam(RADIOJAM_SET_PARA *pJam)=0;             //静态初始化
	virtual void AbilityIn_Radio(RADIO_PARA *pRadio)=0;                    //静态目标电台工作参数输入
	virtual int AbilityOut_JamParam(COMMJAMPARA *&pJam)=0;                 //静态通信GR参数输出
	virtual int AbilityCal_COMMReconRange(COMMRECON_AREA *&pRange)=0;      //对某型电台/链路的ZC范围计算输出
	virtual int AbilityCal_COMMReconResult(aCOMMRECON_RESULT *&pResult)=0; //对多个电台/链路的通信ZC结果计算输出
	virtual int AbilityCal_CommJamPowerRange(sJAM_JAMRANGE *&pRange)=0;    //对某型电台/链路的GR能力范围计算输出
	virtual int AbilityCal_COMMJamResult(aCOMMJAM_RESULT *&pResult ) =0;   //对多个电台/链路的GR结果计算输出（可GR性，非GR有效性）
};

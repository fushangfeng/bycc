#pragma once

#include "CalModelBase.h"
#include "MEnStruct.h"

class  CGuidRadar: public CalModelBase
{
public:
    /*以下为动态推演功能函数*/
    virtual void SetRunMode(int RunMode) = 0;     //设置控制方式（0-人工控制;1-智能体控制;2-平行战场自主控制;3-作战管理系统控制(！！仅限红方)）
	virtual void SetMountEquip(int RunMode) = 0;  //设置挂载方式（0-挂载信号级样机；1-不挂样机）
	
	virtual void SetMod_Radar(sRADAR_Set_PARA *RadarPos) = 0;				//雷达场景初始化参数输入
	virtual void Set_OutPlat(sPLAT_PARA *OutPlat) = 0;                      //雷达搭载平台和目标平台输入
	virtual void Set_JAMPARA(sJAM_PARA *Jamparas) = 0;						//雷达GR参数输入
	virtual void Set_GuidTrgInfo(sRadar_DetectInfo *GuidTrgInfo) = 0;		//关联的预警雷达的引导信息输入
	virtual bool GetMod_Radar(sRADAR_PARA *&RadarPara) = 0;					//雷达参数及状态输出
	virtual bool Send_Sit_RadarRange(sRADAR_RANGE *&RadarRange) = 0;        //雷达TC范围输出（二维）
	virtual bool Send_Sit_RadarDetectInfo(sRadar_DetectInfo *&RadarDetactInfo) = 0;//点迹输出
	virtual bool Send_Sit_RadarDetectTrack(sRadar_DetectInfoTrack *&RadarDetactTrack) = 0;//航迹输出
	virtual int  Send_ImportEventReport(eIMPORT_EVENT_REPORT *&pImport) = 0;	//重要事件输出
	
	/*以下为静态计算功能函数*/
	virtual void AbilitySetMod_Radar(aRADAR_Set_PARA *pRadarPos) = 0;	//输入雷达初始化参数
	virtual int  AbilityOut_RadarPara(aRADAR_PARA *&pRadarPara) = 0;	//雷达参数输出
	virtual void AbilityIn_JamPara(aJAM_PARA *pJamPara) = 0;	        // 雷达GR参数输入
	virtual void AbilityIn_PlatPara(aPLAT_PARA * pTrgPlat) = 0;	        // 雷达TC平台信息输入
	virtual int  AbilityCal_DetectRange(aRadarRange *&pRadarRange) = 0;	// 雷达TC范围计算（二维）
	//virtual int  AbilityCal_DetectResult(aRADAR_RESULT *&pRadarResult) = 0;	// 雷达TC结果计算
	virtual int  AbilityCal_DetectResultMulti(aRADAR_RESULTEX *&pRadarResult) = 0;	// 雷达多目标TC结果计算
	virtual int  AbilityCal_DetectDist(aRADAR_DIST *&pRadarDist) = 0;	       //无GR条件下的雷达TC距离计算
	//virtual void AbilitySet_CfgPara(aRadarCfgPara *pCfgPara) = 0;            //调整雷达计算参数
	//virtual int  AbilityCal_RadarJamed(aRadarJamed*& pRadarJamed) = 0;	   // 雷达受扰关系计算
	virtual int  AbilityCal_DetectRange3D(RadarRange3D *&pRadarRange) = 0;	   // 雷达TC范围计算（三维）
	virtual void AbilitySet_PdRegion(aPD_REGION *pPdRegion) = 0;		       // 计算区域检测概率输入
	virtual int AbilityCal_DetectRegionPd(aRADAR_REGION_PD *&pRdRegionPd) = 0; // 雷达区域检测概率计算
};

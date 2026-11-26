#pragma once
#include "MEnStruct_RadarJam.h"

class CCheck_RadarJam
{
public:
	CCheck_RadarJam(void);
	~CCheck_RadarJam(void);

	//推演输入
	bool Check_sPLAT_PARA(sPLAT_PARA* pPlatPara);
	bool Check_sJAM_PARA(sJAM_PARA* pJamPara);
	bool Check_sRADAR_Set_PARA(sRADAR_Set_PARA* pRadarPara);
	bool Check_sUAV_ATTRACK_PARA(sUAV_ATTRACK_PARA* pUAVPara);
	bool Check_sJAM_Set_PARA(sJAM_Set_PARA* pJamPara);
	bool Check_sRADAR_PARA(sRADAR_PARA* pRadarPara);
	bool Check_sUAV_Set_PARA(sUAV_Set_PARA* pUAVPara);
	bool Check_sRECON_Set_PARA(sRECON_Set_PARA* pReconPara);
	bool Chech_sPLAT_Set_PARA(sPLAT_Set_PARA* pPlatPara);

	//静态计算输入
	bool Check_aPLAT_PARA(aPLAT_PARA* pPlatPara);
	bool Check_aJAM_PARA(aJAM_PARA* pJamPara);
	bool Check_aRADAR_Set_PARA(aRADAR_Set_PARA* pRadarPara);
	bool Check_aPD_REGION(aPD_REGION* pPdPara);
    bool Check_aJAM_Set_PARA(aJAM_Set_PARA* pJamPara);
	bool Check_aRADAR_PARA(aRADAR_PARA* pRadarPara);
    bool Check_aUAV_Set_Skyway(aUAV_Set_Skyway* pUAVPara);
	bool Check_aUAV_Set_PARA(aUAV_Set_PARA* pUAVPara);
	bool Check_aRECON_Set_PARA(aRECON_Set_PARA* pReconPara);
	bool Chech_aPLAT_Set_PARA(aPLAT_Set_PARA* pPlatPara);

private:
	bool Check_Pos(float fLon, float fLat,float fHeight);
	bool Check_Az(float fAz);
	bool Check_El(float fEl);
};

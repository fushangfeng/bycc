#include "StdAfx.h"
#include "Check_RadarJam.h"
#include <math.h>
#define  EPSILON 1e-6

CCheck_RadarJam::CCheck_RadarJam(void)
{
}

CCheck_RadarJam::~CCheck_RadarJam(void)
{
}

//检查平台参数合法性
bool CCheck_RadarJam::Check_sPLAT_PARA( sPLAT_PARA* pPlatPara )
{
	if (NULL == pPlatPara)
	{
		return false;
	}

   if (/*pPlatPara->PlatID < 0 || */(!(Check_Pos(pPlatPara->fLon,pPlatPara->fLat,pPlatPara->fHeight))) || pPlatPara->fSpeed < 0 || pPlatPara->nRCSNum < 1 || NULL == pPlatPara->RCSArray)
   {
	   return false;
   } 
   else
   {
	   return true;
   }
}

bool CCheck_RadarJam::Check_aPLAT_PARA( aPLAT_PARA* pPlatPara )
{
	if (NULL == pPlatPara)
	{
		return false;
	}

	if (/*pPlatPara->ID < 0 || */(!(Check_Pos(pPlatPara->LON,pPlatPara->LAT,pPlatPara->Height))) || pPlatPara->fSpeed < 0 
		|| pPlatPara->nRCSNum < 1 || NULL == pPlatPara->RCSArray || pPlatPara->Radius < 0)
	{
		return false;
	} 
	else
	{
		return true;
	}
}

//检查雷达GR参数合法性
bool CCheck_RadarJam::Check_sJAM_PARA( sJAM_PARA* pJamPara )
{
	if (NULL == pJamPara)
	{
		return false;
	}

	if (/*pJamPara->JammerID < 0 || */pJamPara->RadarID < 0 || (!(Check_Pos(pJamPara->fLon,pJamPara->fLat,pJamPara->fHeight))) || pJamPara->PlatID < 0 
		|| pJamPara->fRF < 0 || pJamPara->fPt < 0 || pJamPara->fGt < 0 || pJamPara->fLoss < 0 || pJamPara->iFalseTrgNum < 0 
		|| !Check_Az(pJamPara->JamPointAZ) || !Check_El(pJamPara->JamPointEL) || pJamPara->fJamSigBW < 0 || !Check_Az(pJamPara->fBeamWidth))
	{
		return false;
	} 
	else
	{
		return true;
	}
}

bool CCheck_RadarJam::Check_aJAM_PARA( aJAM_PARA* pJamPara )
{
	if (NULL == pJamPara)
	{
		return false;
	}

	if (/*pJamPara->ID < 0 || pJamPara->RadarID < 0 || */(!(Check_Pos(pJamPara->LON,pJamPara->LAT,pJamPara->Height))) || pJamPara->ERP < 0 
		|| pJamPara->QRF < 1 || pJamPara->RJamBandWidth < 0 || pJamPara->QDecoyTarget < 0 || pJamPara->DecoyTargetInterval < 0)
	{
		return false;
	}

	for (int i = 0; i < pJamPara->QRF ;i++)
	{
		if (pJamPara->RF[i] < 0)
		{
			return false;
		} 
	}

	return true;
}

//检查雷达参数合法性
bool CCheck_RadarJam::Check_sRADAR_Set_PARA( sRADAR_Set_PARA* pRadarPara )
{
	if (NULL == pRadarPara)
	{
		return false;
	}

	if (/*pRadarPara->RadarID < 0 || pRadarPara->PlatID < 0 ||*/ (!(Check_Pos(pRadarPara->fLon,pRadarPara->fLat,pRadarPara->fHeight))) 
		|| pRadarPara->fSRCS < 0 || pRadarPara->fSHeight <0 )
	{
		return false;
	} 
	else
	{
		return true;
	}
}

bool CCheck_RadarJam::Check_aRADAR_Set_PARA( aRADAR_Set_PARA* pRadarPara )
{
	if (NULL == pRadarPara)
	{
		return false;
	}

	int nBaitNum = pRadarPara->RadarBaitNum;
	if (/*pRadarPara->ID < 0 || */(!(Check_Pos(pRadarPara->LON,pRadarPara->LAT,pRadarPara->Height))) 
		|| nBaitNum < 0 || pRadarPara->fPd <0 )
	{
		return false;
	} 
    
	if (nBaitNum > 0 && NULL == pRadarPara->RadarBaitID)
	{
		return false;
	}
    
	for (int i = 0; i < pRadarPara->RadarBaitNum ;i++)
	{
		if (pRadarPara->RadarBaitID[i] < 0)
		{
			return false;
		} 
	}

	return true;
}

bool CCheck_RadarJam::Check_Pos( float fLon, float fLat ,float fHeight)
{
	if ((fabs(fLon) - 180.0 > -EPSILON) || (fabs(fLat) - 90.0 > -EPSILON) || fHeight < 0)
	{
		return false;
	} 
	else
	{
		return true;
	}

}

bool CCheck_RadarJam::Check_aPD_REGION( aPD_REGION* pPdPara )
{
	if (NULL == pPdPara)
	{
        return false;
	}

	int nPtNum = pPdPara->PtNum ;
    if (nPtNum < 0 || (nPtNum > 0 && NULL == pPdPara->RegionPoint))
    {
		return false;
    }

	for (int i = 0;i < nPtNum; i++)
	{
		aPD_REGION_POINT RegionPoint = pPdPara->RegionPoint[i];
		if (RegionPoint.ID < 0 || RegionPoint.RCS < 0 || (!Check_Pos(RegionPoint.Position.LON,RegionPoint.Position.LAT,RegionPoint.Position.Height)))
		{
			return false;
		}
	}

	return true;
}

bool CCheck_RadarJam::Check_sUAV_ATTRACK_PARA( sUAV_ATTRACK_PARA* pUAVPara )
{
	if (NULL == pUAVPara)
	{
		return false;
	}

    if (/*pUAVPara->TargetID < 0 || pUAVPara->UAVID < 0 || */pUAVPara->KillProb < 0 || pUAVPara->KillProb > 1)
    {
		return false;
    } 
    else
    {
		return true;
    }
}

bool CCheck_RadarJam::Check_sJAM_Set_PARA( sJAM_Set_PARA* pJamPara )
{
	if (NULL == pJamPara)
	{
		return false;
	}
    
	if (/*pJamPara->JammerID < 0 || pJamPara->PlatID < 0 || */(!(Check_Pos(pJamPara->fLon,pJamPara->fLat,pJamPara->fHeight))) || (!Check_Az(pJamPara->fStartAZ)) 
		|| (!Check_Az(pJamPara->fEndAZ)) || pJamPara->iTrgNum < 0 || pJamPara->iCenterPoint < 0 || pJamPara->iKeyPtNum < 0)
	{
		return false;
	}

	int nNum = pJamPara->iTrgNum;
	if (nNum > 0 && NULL == pJamPara->lTrgVal)
	{
		return false;
	}
	for (int i = 0; i < nNum ;i++)
	{
		if (pJamPara->lTrgVal[i] < 0)
		{
			return false;
		} 
	}

	nNum = pJamPara->iCenterPoint;
	if (nNum > 0 && NULL == pJamPara->pCenterPoint)
	{
		return false;
	}
	for (int i = 0; i < nNum ;i++)
	{
		sPON_AREA CenterPoint = pJamPara->pCenterPoint[i];
		if (!(Check_Pos(CenterPoint.LON,CenterPoint.LAT,CenterPoint.Height)))
		{
			return false;
		} 
	}

	if (pJamPara->iKeyPtNum > 0 && NULL == pJamPara->pKeyPt)
	{
		return false;
	}

	return true;
}

bool CCheck_RadarJam::Check_sRADAR_PARA( sRADAR_PARA* pRadarPara )
{
	if (NULL == pRadarPara)
	{
		return false;
	}

	if (/*pRadarPara->RadarID < 0 || pRadarPara->PlatID < 0 || */(!(Check_Pos(pRadarPara->fLon,pRadarPara->fLat,pRadarPara->fHeight)))
		|| pRadarPara->fRF < 0 || pRadarPara->fRFMax < 0 || pRadarPara->fRFMin < 0 || pRadarPara->fPt < 0 ||/* pRadarPara->fLt < 0 || */pRadarPara->ScanCycle < 0 ||
		pRadarPara->PRI < 0 || pRadarPara->PW < 0 || pRadarPara->RBand < 0 || pRadarPara->AutoTrackDistance < 0 ||
		(!Check_Az(pRadarPara->fAzBeamWidth)) || (!Check_Az(pRadarPara->AntAZ))  || (!Check_Az(pRadarPara->fAziMax))  || (!Check_Az(pRadarPara->fAziMin))  ||
		(pRadarPara->fElBeamWidth < 0 || pRadarPara->fElBeamWidth > 180)|| (!Check_El(pRadarPara->fElMax))  || (!Check_El(pRadarPara->fElMin)))
	{
		return false;
	} 
	else
	{
		return true;
	}
}

bool CCheck_RadarJam::Check_aJAM_Set_PARA( aJAM_Set_PARA* pJamPara )
{
	if (NULL == pJamPara)
	{
		return false;
	}

	if (/*pJamPara->ID < 0 || */(!(Check_Pos(pJamPara->LON,pJamPara->LAT,pJamPara->Height))) || (!Check_Az(pJamPara->StartAZ)) 
		|| (!Check_Az(pJamPara->EndAZ)) || (!Check_Az(pJamPara->Psia)) || pJamPara->TargetNum < 0 || pJamPara->iCenterPoint < 0 || pJamPara->RCS < 0)
	{
		return false;
	}

	int nNum = pJamPara->TargetNum;
	if (nNum > 0 && NULL == pJamPara->TargetID)
	{
		return false;
	}
	for (int i = 0; i < nNum ;i++)
	{
		if (pJamPara->TargetID[i] < 0)
		{
			return false;
		} 
	}

	nNum = pJamPara->iCenterPoint;
	if (nNum > 0 && NULL == pJamPara->pCenterPoint)
	{
		return false;
	}
	for (int i = 0; i < nNum ;i++)
	{
		sPON_AREA CenterPoint = pJamPara->pCenterPoint[i];
		if (!(Check_Pos(CenterPoint.LON,CenterPoint.LAT,CenterPoint.Height)))
		{
			return false;
		} 
	}

	return true;
}

bool CCheck_RadarJam::Check_aRADAR_PARA( aRADAR_PARA* pRadarPara )
{
	if (NULL == pRadarPara)
	{
		return false;
	}

	if (/*pRadarPara->ID < 0 || */pRadarPara->QRF < 1 || pRadarPara->QRF > 64 || (!(Check_Pos(pRadarPara->LON,pRadarPara->LAT,pRadarPara->Height))) ||
		(!Check_Az(pRadarPara->HBeamWidth)) || (pRadarPara->VBeamWidth < 0 || pRadarPara->VBeamWidth > 180) || (!Check_Az(pRadarPara->StartAZ))
		|| (!Check_Az(pRadarPara->EndAZ)) || pRadarPara->PW < 0	|| pRadarPara->Power < 0 || pRadarPara->Gt < 0 || pRadarPara->ScanCycle < 0)
	{
		return false;
	} 
	
	int nNum = pRadarPara->QRF;
	for (int i = 0; i < nNum ;i++)
	{
		if (pRadarPara->RF[i] < 0)
		{
			return false;
		} 
	}

	return true;
}

bool CCheck_RadarJam::Check_Az( float fAz )
{
   if (fAz + EPSILON > 0.0 && fAz < 360.0 + EPSILON)
   {
	   return true;
   } 
   else
   {
	   return false;
   }
}

bool CCheck_RadarJam::Check_El( float fEl )
{
	if (fEl + EPSILON > -90.0 && fEl < 90.0 + EPSILON)
	{
		return true;
	} 
	else
	{
		return false;
	}

}

bool CCheck_RadarJam::Check_sUAV_Set_PARA( sUAV_Set_PARA* pUAVPara )
{
	if (NULL == pUAVPara)
	{
		return false;
	}

	if (/*pUAVPara->ID < 0 || pUAVPara->PlatID < 0 || */(!(Check_Pos(pUAVPara->LON,pUAVPara->LAT,pUAVPara->Height))) ||
		pUAVPara->TargetNum < 0 || pUAVPara->PosNum < 0)
	{
		return false;
	} 

	int nNum = pUAVPara->TargetNum;
	if (nNum > 0 && NULL == pUAVPara->TargetID)
	{
		return false;
	}
	for (int i = 0; i < nNum ;i++)
	{
		if (pUAVPara->TargetID[i] < 0)
		{
			return false;
		} 
	}

	nNum = pUAVPara->PosNum;
	if (nNum > 0 && NULL == pUAVPara->CombatTracklist)
	{
		return false;
	}
	for (int i = 0; i < nNum ;i++)
	{
		sTRACK_POINT point = pUAVPara->CombatTracklist[i];
		if (point.PlatformSpeed < 0 || !(Check_Pos(point.LON,point.LAT,point.Height))|| !Check_Az(point.Psia) || !Check_El(point.Slope)
			|| (point.DamageProbability < 0 || point.DamageProbability > 1)) 
		{
			return false;
		} 
	}

	return true;
}

bool CCheck_RadarJam::Check_aUAV_Set_Skyway( aUAV_Set_Skyway* pUAVPara )
{
	if (NULL == pUAVPara)
	{
		return false;
	}
	if (!Check_Pos(pUAVPara->RadarLON,pUAVPara->RadarLAT,pUAVPara->RadarHeight))
	{
		return false;
	} 
	else
	{
		return true;
	}
}

bool CCheck_RadarJam::Check_aUAV_Set_PARA( aUAV_Set_PARA* pUAVPara )
{
	if (NULL == pUAVPara)
	{
		return false;
	}
	if (/*pUAVPara->ID < 0 || */(!Check_Pos(pUAVPara->LON,pUAVPara->LAT,pUAVPara->Height)) ||
		pUAVPara->TargetNum < 0 || pUAVPara->PosNum < 0 || pUAVPara->BombPointNum < 0)
	{
		return false;
	} 

	int nNum = pUAVPara->TargetNum;
	if (nNum > 0 && NULL == pUAVPara->TargetID)
	{
		return false;
	}
	for (int i = 0; i < nNum ;i++)
	{
		if (pUAVPara->TargetID[i] < 0)
		{
			return false;
		} 
	}

	nNum = pUAVPara->PosNum;
	if (nNum > 0 && NULL == pUAVPara->CombatTracklist)
	{
		return false;
	}
	for (int i = 0; i < nNum ;i++)
	{
		sTRACK_POINT point = pUAVPara->CombatTracklist[i];
		if (point.PlatformSpeed < 0 || !(Check_Pos(point.LON,point.LAT,point.Height))|| !Check_Az(point.Psia) || !Check_El(point.Slope)
			|| (point.DamageProbability < 0 || point.DamageProbability > 1)) 
		{
			return false;
		} 
	}

	return true;
}

bool CCheck_RadarJam::Chech_sPLAT_Set_PARA( sPLAT_Set_PARA* pPlatPara )
{
	//if (pPlatPara->PlatID < 0)
	//{
	//	return false;
	//}

	int nTrackNum = pPlatPara->TrackNum;
	if (nTrackNum > 0 && NULL == pPlatPara->TrackData)
	{
		return false;
	}
	for (int i = 0;i < nTrackNum;i++)
	{
		sPLAT_TRACK_DATA TrackTemp = pPlatPara->TrackData[i];
		if (!Check_Pos(TrackTemp.fLon,TrackTemp.fLat,TrackTemp.fHeight))
		{
			return false;
		}
		if (TrackTemp.fSpeed < 0/* || TrackTemp.fReachTime < 0*/)//对时间小于0的判断先去掉，有的场景时间就是负数 add zm 20180807
		{
			return false;
		}
	}

	int nRCS = pPlatPara->nRCSNum;
	if (nRCS > 0 && NULL == pPlatPara->RCSArray)
	{
		return false;
	}
	for (int i = 0;i < nRCS;i++)
	{
		if (pPlatPara->RCSArray[i].fRCS < 1e-6)
		{
			return false;
		}
	}

	return true;
}

bool CCheck_RadarJam::Check_sRECON_Set_PARA( sRECON_Set_PARA* pReconPara )
{
	if (NULL == pReconPara)
	{
		return false;
	}

	if (/*pReconPara->ReconID < 0 || pReconPara->PlatID < 0 || */(!(Check_Pos(pReconPara->fLon,pReconPara->fLat,pReconPara->fHeight))) 
		|| (!Check_Az(pReconPara->fStartAZ)) || (!Check_Az(pReconPara->fEndAZ)) || pReconPara->iKeyPtNum < 0)
	{
		return false;
	}

	//int nNum = pReconPara->SlaveNum;
	//if (nNum > 0 && NULL == pReconPara->PonAreaData)
	//{
	//	return false;
	//}

	if (pReconPara->iKeyPtNum > 0 && NULL == pReconPara->pKeyPt)
	{
		return false;
	}

	return true;
}

bool CCheck_RadarJam::Check_aRECON_Set_PARA( aRECON_Set_PARA* pReconPara )
{
	if (NULL == pReconPara)
	{
		return false;
	}

	if (/*pReconPara->ID < 0 || */(!(Check_Pos(pReconPara->LON,pReconPara->LAT,pReconPara->Height))) 
		|| (!Check_Az(pReconPara->StartAZ)) || (!Check_Az(pReconPara->EndAZ)) || !Check_Az(pReconPara->Psia)
		|| pReconPara->fProb < 0 || pReconPara->fProb > 1 || pReconPara->WorkMode > 10)
	{
		return false;
	}

	return true;
}

bool CCheck_RadarJam::Chech_aPLAT_Set_PARA( aPLAT_Set_PARA* pPlatPara )
{
	//if (pPlatPara->ID < 0)
	//{
	//	return false;
	//}

	if (!Check_Pos(pPlatPara->LON,pPlatPara->LAT,pPlatPara->Height))
	{
		return false;
	}

	if (pPlatPara->TargetRadius < 0)
	{
		return false;
	}

	int nRCS = pPlatPara->nRCSNum;
	if (nRCS > 0 && NULL == pPlatPara->RCSArray)
	{
		return false;
	}
	for (int i = 0;i < nRCS;i++)
	{
		if (pPlatPara->RCSArray[i].fRCS < 1e-6)
		{
			return false;
		}
	}

	return true;
}

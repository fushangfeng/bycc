#ifndef AtmosModel_H
#define AtmosModel_H
///////////////////////////////////////////////////////////
//  AtomosTransModelClass.h
//  Implementation of the Class AtomosTransModelClass
//  Created on:      18-五月-2018 9:24:23
//  Original author: 王纳
///////////////////////////////////////////////////////////
#include<iostream>
#include "StdAfx.h"
#include "targetver.h"
#include "ITerrainAccessor.h"
#include "GTypes.h"
using namespace std;



#ifndef WIN32
#define DLL_ATMOSAPI 
#else

#ifndef ATMOSMODEL_EXPORTS		//应用程序引入说明
#define DLL_ATMOSAPI __declspec(dllimport)
#pragma comment(lib,"AtmosModel.lib")
#else				            //库函数输出说明
#define DLL_ATMOSAPI __declspec(dllexport)

#endif

#endif


/**
 * @author 王纳
 * @version 1.0
 * @created 18-五月-2018 9:24:23
 */
#include <math.h>
//#include "Packdef.h"

#ifndef _GEO_COORDINATE
#define _GEO_COORDINATE
typedef struct GEO_COORDINATE//地理坐标
{
	double longitude;	//经度
	double latitude;	//纬度	
	double altitude;	//高度
}GEO_COORDINATE;
#endif

 class DLL_ATMOSAPI AtomosTransModelClass
{

public:
	 /**
	  * 计算大气传输损耗率
	  *
	  * @param dFre      输入 频率 单位 GHz
	  * @param pdAtte	 输出 大气损耗率 dB/km
	  * @return int
	  * @author 常贺
	  */
	int AtmosphereLoss(double dFre, double* pdAtte);
	 /**
	  * 计算雪传输损耗率
	  *
	  * @param dRate     输入 降雪率单位（mm/h）
	  * @param dFre		 输入 频率 单位 GHz
	  * @param pdAtte	 输出 雪损耗率 dB/km
	  * @return int
	  * @author 常贺
	  */
	int SnowLoss(double dRate, double dFre, double* pdAtte);
	 /**
	  * 计算雾传输损耗率
	  *
	  * @param dFre    输入 频率 单位 GHz
	  * @param dUM	   输入 粒子密度 单位（g/m^3 ）
	  * @param dCon	   输入 粒子浓度 单位（个/m^3 ）
	  * @param dTP	   输入 粒子介电常数实部
	  * @param dVP	   输入 粒子介电常数虚部
	  * @param pdAtte  输出 雾损耗率 dB/km
	  * @return int
	  * @author 常
	  */
	int FogLoss(double dFre, double dUM, double dCon, double dTP, double dVP, double* pdAtte);
	 /**
	  * 计算雨传输损耗率
	  *
	  * @param dFre        输入 电磁波频率 单位 （GHz）
	  * @param dRS		   输入 雨强 单位 （mm/h）
	  * @param dEle		   输入 路径仰角 度
	  * @param dDip		   输入 极化倾角 度
	  * @param pdAtte	   输出 雨损耗率 dB/km
	  * @return int
	  * @author 常贺
	  */
	int RainLoss(double dFre,double dRS, double dEle, double dDip, double* pdAtte );
	 /**
	  * 计算云传输损耗率
	  *
	  * @param dFre        输入 频率 单位 GHz 
	  * @param dUM		   输入 粒子密度 单位（g/m^3 ）
	  * @param dCon		   输入 粒子浓度 单位（个/m^3 ）
	  * @param dTP		   输入 粒子介电常数实部
	  * @param dVP		   输入 粒子介电常数虚部
	  * @param pdAtte	   输出 云损耗率 dB/km
	  * @return int
	  * @author 常贺
	  */
	int CloudLoss(double dFre, double dUM, double dCon, double dTP, double dVP, double* pdAtte);
	int Splineestimate(double dX[],double dY[],int nNumber,double dInX,double *dOutY);
	int DefiladePass( GEO_COORDINATE LunPoint, GEO_COORDINATE RecePoint[],int Num, GEO_COORDINATE* GeoCoor, bool* bPass);
};
#endif 

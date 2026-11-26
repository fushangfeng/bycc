#ifndef _I_TERRAIN_H_
#define _I_TERRAIN_H_
#include "GTypes.h"

#ifdef WIN32
#ifdef TERRAINCALC_LIB
#define ITERRAIN_ACCESSOR Q_DECL_EXPORT
#else
#define ITERRAIN_ACCESSOR _declspec(dllimport)
#endif
#else
#define ITERRAIN_ACCESSOR
#endif

#define GTILEDIR_NORTHWEST 0
#define GTILEDIR_NORTHEAST 1
#define GTILEDIR_SOUTHWEST 2
#define GTILEDIR_SOUTHEAST 3
#define GTILEDIR_NONE      4

#pragma comment(lib,"TerrainCalc.lib")

ITERRAIN_ACCESSOR void Init();

ITERRAIN_ACCESSOR int GetReadLayer();//

// 即时获取高程数据，其特点是快速加载内存中存在的最精细高程数据，而不考虑加载硬盘数据文件
ITERRAIN_ACCESSOR double GetElevationAt(double longitude, double latitude);

// 根据采样精度，获取指定经纬度坐标的高层
ITERRAIN_ACCESSOR double GetElevationAt(double longitude, double latitude, double targetSamplesPerDegree);
// 根据方位、仰角计算通视点
ITERRAIN_ACCESSOR void GetVisibleDot(double Lng, double Lat, double Altitude, double Azimuth, double Elevation, double Distance, double nSamples, 
	GPoint3 * pVisiblePnt, double * DistanceOut);
// 根据两点，计算高度剖面图

// 根据剖面，计算实际可视剖面
// 计算Lng1,Lat1到Lng2,Lat2的可视点 
ITERRAIN_ACCESSOR bool GetVisibleDot(double Lng1, double Lat1, double Altitude, double Lng2, double Lat2, double Altitude2,
	GPoint3 * pVisibleDot, double nSamples, int nSamplePoints = 30);
// 获取直线的高程数据, data返回高层数据, pLngOut, pLatOut返回对应高层数据的经纬度
ITERRAIN_ACCESSOR void GetElevationArray(double Lng1, double Lat1, double Lng2, double Lat2, int nSamples, int nPointsOut, float * data, double *pLngOut, double * pLatOut);

// 计算通视范围
ITERRAIN_ACCESSOR void GetVisibleRegion(double dLng, double dLat, double dAlt, double dElevation, double dStartAngle, double dEndAngle,double dmultiple/*角度间隔*/, double dRadius, int nSamples, GVector3 ** pResults);


// 获取即时高程数据，同时返回当前层号，其特点是快速加载内存中存在的最精细高程数据，而不考虑加载硬盘数据文件
ITERRAIN_ACCESSOR double GetElevationAt(double longitude, double latitude, int * pLayer);

// 根据方位、仰角计算通视点，同时可指定采样精度与采样方式
ITERRAIN_ACCESSOR void GetVisibleDot(double Lng, double Lat, double Altitude, double Azimuth, double Elevation, double Distance, double nSamples, 
	GPoint3 * pVisiblePnt, double * DistanceOut, bool bInstant, int nPrecision);

#endif

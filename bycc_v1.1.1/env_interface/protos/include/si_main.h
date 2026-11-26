#ifndef __SI_MAIN_H__
#define __SI_MAIN_H__

//作战系统ID对应的综合射频系统ID转换
#define ID_BATTLE_TO_RF(X)	((0xff00)|(X))


//量化单位
#define UNIT_TIME			(0.0001)				//时间【秒】

#define UNIT_COURSE_HIGH	(180.0/pow(2.0,30.0))	//航向（高精度）【度】
#define UNIT_ROLL_HIGH		(90.0/pow(2.0,30.0))	//横摇（高精度）【度】
#define UNIT_PITCH_HIGH		(90.0/pow(2.0,30.0))	//纵摇（高精度）【度】

#define UNIT_COURSE			(90.0/pow(2.0,14.0))	//航向【度】
#define UNIT_ROLL			(90.0/pow(2.0,14.0))	//横摇【度】
#define UNIT_PITCH			(90.0/pow(2.0,14.0))	//纵摇【度】

#define UNIT_SHIP_V			(0.01)					//平台速度【米/秒】

#define UNIT_LON			(90.0/pow(2.0,30.0))	//经【度】
#define UNIT_LAT			(90.0/pow(2.0,30.0))	//纬【度】
#define UNIT_ALT			(1)						//高【米】

#define UNIT_ERROR			(0.01)					//误差

#define UNIT_R				(1)						//距离【米】
#define UNIT_A				(90.0/pow(2.0,14.0))	//方位【度】
#define UNIT_E				(90.0/pow(2.0,14.0))	//仰角【度】
#define UNIT_AV             (180.0/pow(2.0,16.0))   //角度速度[度]

#define UNIT_XYZ			(0.1)					//东/北/天【米】

#define UNIT_V				(0.1)				    //目标速度【米/秒】

#define UNIT_RESOURCE		(0.0001)				//资源【0.01%】

#define UNIT_PERCENT		(0.01)			    //百分比 (20181105   0.0001->0.01)

#define UNIT_FD_CORR		(0.001)				    //修正系数

#define UNIT_WIDTH_R		(0.1)					//距离宽度
#define UNIT_WIDTH_AE		(90.0/pow(2.0,14.0))	//方位/仰角宽度

#define UNIT_RCS			(0.01)

#include "si_out.h"

#ifdef _WIN32
#define DLL_EXPORT_C
_declspec(dllexport)
#else
#define DLL_EXPORT_C
__attribute__((visibility("default")))
#endif

//初始化函数
DLL_EXPORT_C void init_simulation_e2d();
//退出函数
DLL_EXPORT_C void exit_simulation_e2d();

//输出
DLL_EXPORT_C void out_e2d_track_jam(unsigned int timeTickCnt, int &nTrkNum, ST_tgt_track trackBuf[], int &nPlotNum, ST_tgt_plot jamPlotBuf[], int &nPltNum, ST_tgt_plot plotBuf[], bool is_print);

//20240724 只更新设备    我方雷达
DLL_EXPORT_C void update_e2d_info_radar(unsigned int timeTickCnt, ST_radar_plat radar_plat);
//20240724 只更新目标/GR机    目标雷达
DLL_EXPORT_C void update_e2d_info_tgt(unsigned int timeTickCnt, ST_radar_tgt radar_tgt);
//20240724 更新设备对目标的操作
DLL_EXPORT_C void update_e2d_info_cmd(unsigned int timeTickCnt, unsigned int radar_id, unsigned int tgt_id, BYTE work_type, ST_tws_cmd tws_cmd);

DLL_EXPORT_C ST_orbitpred orbit_pre(unsigned int plat_radar_id, unsigned int plat_tgt_id);


#endif // DLL_TEST_H

#ifndef __SI_OUT_H__
#define __SI_OUT_H__


#define MY_WINDOWS_VER
#define  MY_LITTLE_ENDIAN
#define SUPJAM_NUM_MAX 20//20 20240818

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;


//平台信息
typedef struct ST_radar_plat_tag
{
	double		t;							//时戳 单位：ms
	unsigned int	platform_id;				//平台ID
	char radar_type[16];		//雷达型号:雷达型号的描述标签，如346A等
	double		platform_x;					//平台位置X 量化单位：米
	double		platform_y;					//平台位置Y 量化单位：米
	double		platform_z;					//平台位置Z 量化单位：米

	BYTE		work_type;				//雷达TC方式指令 0：搜索;	1：粗跟踪; 2：精跟踪
	BYTE        anti_jam_enble;             //反GR启用 0：未启用：1：启用
	BYTE        anti_jam_level;             //抗GR等级 1，2，3  等级越高，抗GR能力越强
	bool        JudgeBeamDirection;         //是否判断波束指向
	BYTE		work_mode;				//雷达工作模式 	1：对空; 2：对天（反导）
	double      azi_point;                  //阵面方位指向
	double      ele_point;                  //阵面俯仰指向
	BYTE        bValid;                     //1-更新

}ST_radar_plat;

//压制GR信息
typedef struct ST_SuppressJam_info_tag
{
	double      Gj;                         //GR发射天线增益
	double      TraAntbeamWith;             //发射天线方位波束宽度 °
	double      TraAntbeamWithYaw;          //发射天线俯仰波束宽度 °
	double      TraAntPitch;                //发射天线俯仰角 °
	double      TraAntAzimuthAngle;         //发射天线方位角 °

}ST_SuppressJam_info;

//目标信息
typedef struct ST_radar_tgt_tag
{
	double		t;							//时戳 单位：ms
	unsigned int tgt_id;						//目标ID

	double		tgt_x;						//目标位置X 量化单位：米
	double		tgt_y;						//目标位置Y 量化单位：米
	double		tgt_z;						//目标位置Z 量化单位：米
	double		tgt_Vx;						//目标速度X 量化单位：米
	double		tgt_Vy;						//目标速度Y 量化单位：米
	double		tgt_Vz;						//目标速度Z 量化单位：米
	BYTE		work_type;				        //目标TC方式指令 0：搜索;	1：粗跟踪; 2：精跟踪


	double		rcs;						//目标RCS
	BYTE		tgt_type;					//目标类型 0:常规目标；1:高超音速导弹或弹道导弹
	BYTE		jam_type;					//GR类型 0:非GR； 1:压制GR； 2:窄带瞄频GR； 3 : 密集假目标GR；
	BYTE        jam_level;                  //GR等级

	int         fre_miao;                   //瞄频频率   窄带瞄频GR启用
	UINT        mijia_num;                  //密假个数   密集假目标GR启用
	double      Rmijia_begin;               //密假目标起始距离  m
	double      R_jiange;                   //密假点juljiange   m
	double      V_mijia;                    //密假点速度参数
	double      Pj;                         //GR发射功率
	double      Gj;                         //GR发射天线增益
	double      Jam_lon;                    //GR装置经度 °
	double      Jam_lat;                    //GR装置纬度 °
	double      Jam_height;                 //GR装置高度 m
	int         Jam_info_num;               //GR波束信息个数
	ST_SuppressJam_info SuppressJam_info[SUPJAM_NUM_MAX];   //GR机可能具有多个GR波束信息

	BYTE        bValid;                     //1-更新

}ST_radar_tgt;



//包头定义（16字节）
typedef struct ST_pkg_head_tag
{
	WORD id;					//信息标识
	WORD len;					//信息长度
	WORD info_sn;				//信息编号
	WORD packet_sn;				//打包编号
	UINT time;					//时戳(4字节)
	WORD bak1[2];				//备用(4字节)
}ST_pkg_head;


//航迹
typedef struct ST_tgt_track_tag
{
	ST_pkg_head head;
	bool				valid;                      //航迹合法标示
	unsigned int	    platform_id;			//雷达所在的平台实体ID
	unsigned int		radar_model_id;				//雷达ID号
	unsigned int		tgt_platform_id;			//目标平台ID号

#ifdef  MY_LITTLE_ENDIAN
	UINT        bak1 : 4;     //备用
	UINT        tgt_type : 4;     //目标类型。2：空中目标；6：视距内海上目标；15：不明目标。其他备用。 

	UINT        bak3 : 1;     //备用
	UINT        info_src_x : 1;     //X参与融合。0-不参与；1-参与
	UINT        info_src_s : 1;     //S参与融合。0-不参与；1-参与
	UINT        bak2 : 5;     //备用

	UINT        bak4 : 6;     //备用
	UINT        trk_state : 2;     //航迹状态。1：更新；3：丢失

	UINT        bak6 : 1;     //备用
	UINT        tas_mode : 4;     //跟踪方式。0：TWS；5：跟踪
	UINT        bak5 : 3;     //备用
#endif
#ifdef  MY_BIG_ENDIAN
	UINT        tgt_type : 4;     //目标类型。2：空中目标；6：视距内海上目标；15：不明目标。其他备用。 
	UINT        bak1 : 4;     //备用

	UINT        bak2 : 5;     //备用
	UINT        info_src_s : 1;     //S参与融合。0-不参与；1-参与
	UINT        info_src_x : 1;     //X参与融合。0-不参与；1-参与
	UINT        bak3 : 1;     //备用

	UINT        trk_state : 2;     //航迹状态。1：更新；3：丢失
	UINT        bak4 : 6;     //备用

	UINT        bak5 : 3;     //备用
	UINT        tas_mode : 4;     //跟踪方式。0：TWS；5：跟踪
	UINT        bak6 : 1;     //备用
#endif                                      

	UINT        r;                          //目标距离
	WORD        a;                          //目标方位
	short       e;                          //目标仰角

	int         tgt_lon;				    //平台经度
	int         tgt_lat;					//平台纬度
	int         tgt_high;					//平台高度

	//20240808 开始 地心地固系中的位置速度
	double x_ecef;
	double y_ecef;
	double z_ecef;
	double vx_ecef;
	double vy_ecef;
	double vz_ecef;
	//20240808 结束

	WORD        abs_v;                     //绝对航速                                            
	WORD        batch_num;                  //目标批号
	WORD		trk_qnty;					//航迹质量。0-7:0-7级
	WORD		tgt_type2;					//0：战斗机；1：直升机；2：大型飞机；3：反舰导弹；4：弹道导弹；5：诱饵弹；6：舰船；7：小艇；8：无人机
	WORD		abs_dir;                   //绝对航向

										   //WORD		bak7[4];					//备用
										   //20240110  增加误差输出
	short        dr;						//距离误差 单位：1m
	short        da;						//方位误差 量化单位：(90.0/pow(2.0,14.0))
	short        de;						//俯仰误差 量化单位：(90.0/pow(2.0,14.0))
	WORD         bak7;					    //备用

	double		 eirp;						//等效辐射功率（离开天线口面） 量化单位：dBm
	double		 bw_a;						//波束方位 量化单位：度
	double		 bw_e;						//波束俯仰 量化单位：度
	double		 hor_wide;					//水平波束宽度 量化单位：度
	double		 ver_wide;					//垂直波束宽度 量化单位：度
	unsigned char car_fre_type;				//载频类型 0：固定；1：捷变；2：分集
	double		 car_fre;					//中心载频 量化单位：MHz
	double		 agile_fre;					//捷变量 量化单位：MHz
	unsigned char prf_type;					//重频类型 0：固定；1：抖动；2：参差
	double		 prt;						//重复周期 量化单位：Us
	double		 jitter;					//抖动量 量化单位：%
	double		 pulse_wide;				//脉冲宽度 量化单位：Us
	unsigned char pol_type;					//天线极化方式 0：HH; 1：HV; 2：VH 3：VV; 4：斜极化; 5：左旋圆极化;	6：右旋圆极化

}ST_tgt_track;

//点迹
typedef struct ST_tgt_plot_tag
{
	ST_pkg_head head;
	bool				valid;                      //航迹合法标示
	unsigned int		platform_id;				//雷达所在的平台实体ID
	unsigned int		radar_model_id;				//雷达ID号
	unsigned int		tgt_platform_id;			//目标平台ID号
	WORD		plot_type;					//点迹类型。2-空中目标；6-海上目标；15-不明目标；其它备用                            

	UINT		r;                          //目标距离
	WORD        a;                          //目标方位
	short       e;                          //目标仰角

	int         tgt_lon;					//目标经度
	int         tgt_lat;					//目标纬度
	int         tgt_high;					//目标高度

	WORD        amp;		                //幅度
	WORD        snr;						//信噪比

	WORD		bak[4];						//备用

}ST_tgt_plot;

//搜索命令结构体定义（报文）
typedef struct ST_tws_cmd_tag
{
	ST_pkg_head head;

	unsigned int platform_id;			//雷达所在的平台实体ID

										//#ifdef MY_WINDOWS_VER
										//	BYTE task_type			:6;	//搜索任务类型。1：常规TC；2：低空TC；3：对海TC；4：近程警戒；5：中程警戒；6：远程警戒。
										//	BYTE enable				:2;	//搜索任务使能。1:建立任务，2：删除任务
										//#else
										//	BYTE enable				:2;	//搜索任务使能。1:建立任务，2：删除任务
										//	BYTE task_type			:6;	//搜索任务类型，对应任务0-5。1：常规TC；2：低空TC；3：对海TC；4：近程警戒；5：中程警戒；6：远程警戒。
										//#endif

	WORD task_type;	//搜索任务类型。1：常规TC；2：低空TC；3：对海TC；4：近程警戒；5：中程警戒；6：远程警戒。
	WORD enable;	//搜索任务使能。1:建立任务，2：删除任务

	WORD task_index;			//任务序号

	WORD azi_start;				//搜索任务方位起始
	WORD azi_end;				//搜索任务方位结束

	short ele_start;			//搜索任务仰角起始
	short ele_end;				//搜索任务仰角结束

	WORD date_rate_ctrl;		//数据率控制。0:12S；1:6s

	WORD bak;					//备用

}ST_tws_cmd;


//弹道预报信息
typedef struct ST_orbitpred_tag
{
	unsigned int		plat_radar_id;				//雷达平台ID
	unsigned int		plat_tgt_id;				//目标平台ID
													//目标状态
	double              cur_time;                   //初始时刻
	double              state_ecef_cur[6];          //WGS84RV：目标初始位置速度  m, m/s
	double              ITime;                      //落点时刻
	double		        state_ecef_luo[6];			//地固系中的落点位置速度  m, m/s
	double              LTime;                      //发点时刻
	double		        state_ecef_fa[6];		    //地固系中的发点位置速度  m, m/s
	double              tral;						//tral:发、落点间射程 (m)
	double              dOrbitH;					//dOrbitH:最大高度（m）

													//参数
	double              himp;					//himp:0（落点基准高度）
	double              hlaun;					//hlaun:0（发点基准高度）

}ST_orbitpred;



#endif
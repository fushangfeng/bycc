//TwoPathRadiowaveInterface.h: interface for the CTwoPathRadiowaveInterface class.

#ifndef TwoPathRadiowaveINTERFACE_INCLUDE
#define TwoPathRadiowaveINTERFACE_INCLUDE

struct SUMTransPosition//发射台位置信息
{
	double          LON;		//经度 度
	double          LAT;			//纬度 度
	float          Height;       //高度m
};

struct SUMReceiveInfo//接收台的位置信息
{
	double         LON;		       //经度 度
	double         LAT;		        //纬度 度
	float           Height;           //高度m
	float           Rf;              //频率	Mhz
};

struct SUM2PathResult      //传播损耗结果
{
	int          isLOS;               //是否通视
	float        LOSPathLoss;         //直接损耗值结果 dB
    float        AddPathLoss;         //附加损耗值结果 dB
    float        FlashAngle;          //反射夹角 度
    float        SendAngle;           //直射夹角 度
    float        ReflectFactor;       //反射系数幅度
    float        DeltaR;              //双路程差 m
};

class  CTwoPathRadiowaveInterface  
{
	
public:
	CTwoPathRadiowaveInterface();
	virtual ~CTwoPathRadiowaveInterface();
	virtual int UM2PathWaveCompute(SUMTransPosition tp,SUMReceiveInfo* rp,int Number,int PolarType,SUM2PathResult *res,int &resultNumber)= 0 ;
	virtual double UM2PathWaveCompute_F(double G_d,double G_r,float nReflectFactor, float nDeltaR,float nWavelengh) = 0;
	
};

class CTwoPathRadiowaveModelFactory
{
public:
	CTwoPathRadiowaveModelFactory(){};
	~CTwoPathRadiowaveModelFactory(){};
	
public:
	static	CTwoPathRadiowaveInterface * CreateTwoPathRadiowaveDevice();
	static	void DeleteTwoPathRadiowaveDevice(CTwoPathRadiowaveInterface*  pRadar);
};

#endif  //TwoPathRadiowaveINTERFACE_INCLUDE





#if !defined MODELBASE
#define MODELBASE
/*
	-----------------------模型基本信息-------------------
	实体模型分类ID：
	实体模型分类中文名称：公用基础模型
	实体模型分类英文名称：CalModeBase
	父实体模型分类ID：
	------------------------------------------------------
*/

#ifdef _WIN32
    #define CalModelBaseExport __declspec(dllexport)
#else
    #define CalModelBaseExport
#endif


class CalModelBaseExport CalModelBase {
public:
	virtual bool DestroySelf() = 0;
	virtual bool IsUpdate () = 0;		// 模型对象参数更新的信号灯函数
	virtual bool IsSendEvent() = 0;		// 事件信息输出的信号灯函数
	virtual bool IsSendSit() = 0;	    // 显示类信息输出的信号灯函数
	virtual bool IsDeleted() = 0;	    // 通知删除模型对象实例信号灯函数
	virtual void StepCalculate(double curTime, double stepTime, double nextTime) = 0;	// 仿真计算函数入口
	virtual void ActionFun(/*LPCTSTR*/char* ActionName, /*LPCTSTR*/char* ActionParamDescribe) = 0;		// 行为入口函数
	virtual bool CallFunction( /*LPCTSTR*/char* fuctionName,  void *pInParam, void *&pOutParam,void *&pRet )=0;  //函数调用接口
	virtual bool FreeStruct( /*LPCTSTR*/char* lpStructName, void *pStruct ) = 0;    //输出参数内存释放函数
	virtual bool GetSelfDescribe(void *& pSelfInfo) = 0;// 获取自描述信息
};


class CalModelBaseExport CalModelBaseFactory {	// 模型工厂类导出
public:
	virtual bool  CreateCalModelInstance(CalModelBase** ppModel) = 0;	
};

extern "C" bool CalModelBaseExport DllCreateFactory(void** pfact);
extern "C" void CalModelBaseExport DllDelFactory();

#endif

/*
 * @file         DealControlStruct.h
 * @brief        模型报文定义头文件
 * @author       邱常华
 * @create date  2012-2-5 
 * @history      
 **/
#ifndef _DEAL_CONTROL_STRUCT_H_
#define _DEAL_CONTROL_STRUCT_H_

#define		SW_Malloc(T,n)         (new T[(n)])	 
#define		SW_Free(p)			   SW_Delete(p)
#pragma pack(1)

//模型控制类报文定义开始
//用户注册报 用户应答报 用户撤销报
typedef struct _ModelBus_UserOper
{
	char* sRID;	//身份字符串
	/*重载构造函数*/
	_ModelBus_UserOper()
	{
		init();
	}
	void init()
	{
		sRID = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_UserOper()
	{
		release();
	}
	void release()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_UserOper(const _ModelBus_UserOper& useAsk)
	{
		init();
		*this = useAsk;
	}

	/*重载=*/
	_ModelBus_UserOper& operator=(const _ModelBus_UserOper& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);

		SW_Malloc_Char(theStruct.sRID,sRID);

		return *this;
	}

}cUserAsk,cUserRespond,cUserDelete;


//推演状态报

typedef struct _ModelBus_TYState
{
	char* sRID;	//身份字符串
	bool  bType; //推演方式
	float fTime; //推演总时间
	char* sFileName; //场景名称

	/*重载构造函数*/
	_ModelBus_TYState()
	{
		sRID = NULL;
		bType = false;
		fTime = 0;
		sFileName = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_TYState()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sFileName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_TYState(const _ModelBus_TYState& useAsk)
	{
		sRID  = NULL;
		sFileName = NULL;
		*this = useAsk;
	}

	/*重载=*/
	_ModelBus_TYState& operator=(const _ModelBus_TYState& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		//SW_Free_Char(sFileName);

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sFileName,sFileName);

		bType = theStruct.bType;
		fTime = theStruct.fTime;

		return *this;
	}

}cTYState;


//推演状态应答报
typedef struct _ModelBus_TYStateRespond
{
	char* sRID;	//身份字符串
	int iState; //推演状态(0:初始化 1：完成准备 2：完成推演 3：推演失败)

	/*重载构造函数*/
	_ModelBus_TYStateRespond()
	{
		sRID = NULL;
		iState = 0;
	}

	/*重载析构函数*/
	~_ModelBus_TYStateRespond()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_TYStateRespond(const _ModelBus_TYStateRespond& useAsk)
	{
		sRID  = NULL;
		*this = useAsk;
	}

	/*重载=*/
	_ModelBus_TYStateRespond& operator=(const _ModelBus_TYStateRespond& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		iState = theStruct.iState;

		return *this;
	}

}cTYStateRespond;



//模型问询报
typedef struct _ModelBus_ModelAsk
{
	char* sRID;	//身份字符串
	char* sModelName;	//模型名称
	/*重载构造函数*/
	_ModelBus_ModelAsk()
	{
		init();
	}
	void init()
	{
		sRID = NULL;
		sModelName = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_ModelAsk()
	{
		release();
	} 
	void release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sModelName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_ModelAsk(const _ModelBus_ModelAsk& modelAsk)
	{
		init();
		*this = modelAsk;
	}

	/*重载=*/
	_ModelBus_ModelAsk& operator=(const _ModelBus_ModelAsk& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		release();
		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sModelName,sModelName);

		return *this;
	}

}cModelAsk;



//模型应答报
typedef struct _ModelBus_ModelRespond
{
	char* sRID;	//身份字符串（源地址）
	char* sTID;	//身份字符串（目的地址）
	char* sModelName;	//模型名称
	/*重载构造函数*/
	_ModelBus_ModelRespond()
	{
		init();
	}
	void init()
	{
		sRID		= NULL;
		sTID		= NULL;
		sModelName	= NULL;
	}

	/*重载析构函数*/
	~_ModelBus_ModelRespond()
	{
		release();
	}
	void release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTID);
		SW_Free_Char(sModelName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_ModelRespond(const _ModelBus_ModelRespond& modelRespond)
	{
		init();
		*this = modelRespond;
	}

	/*重载=*/
	_ModelBus_ModelRespond& operator=(const _ModelBus_ModelRespond& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		release();

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sTID,sTID);
		SW_Malloc_Char(theStruct.sModelName,sModelName);

		return *this;
	}

}cModelRespond;



//模型实例问询报
typedef struct _ModelBus_EntityAsk
{
	char* sRID;	//身份字符串
	char* sModelName;	//模型名称
	char* sInstanceID;	//实例标识号
	/*重载构造函数*/
	_ModelBus_EntityAsk()
	{
		init();
	}
	void init()
	{
		sRID		= NULL;
		sModelName	= NULL;
		sInstanceID = NULL;	
	}

	/*重载析构函数*/
	~_ModelBus_EntityAsk()
	{
		release();
	}
	void release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sModelName);
		SW_Free_Char(sInstanceID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EntityAsk(const _ModelBus_EntityAsk& entityAsk)
	{
		init();
		*this = entityAsk;
	}

	/*重载=*/
	_ModelBus_EntityAsk& operator=(const _ModelBus_EntityAsk& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		release();

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sModelName,sModelName);
		SW_Malloc_Char(theStruct.sInstanceID,sInstanceID);

		return *this;
	}

}cEntityAsk;



//模型实例应答报 模型实例删除报
typedef struct _ModelBus_Entity
{
	char* sRID;	//身份字符串（源地址）
	char* sTID;	//身份字符串（目的地址）
	char* sModelName;	//模型名称
	char* sInstanceID;	//实例标识号

	/*重载构造函数*/
	_ModelBus_Entity()
	{
		init();
	}
	void init()
	{
		sRID = NULL;
		sTID = NULL;
		sModelName = NULL;
		sInstanceID = NULL;	
	}

	/*重载析构函数*/
	~_ModelBus_Entity()
	{
		release();
	}
	void release()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTID);
		SW_Free_Char(sModelName);
		SW_Free_Char(sInstanceID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_Entity(const _ModelBus_Entity& entityRespond)
	{
		init();
		*this = entityRespond;
	}

	/*重载=*/
	_ModelBus_Entity& operator=(const _ModelBus_Entity& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		release();

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sTID,sTID);
		SW_Malloc_Char(theStruct.sModelName,sModelName);
		SW_Malloc_Char(theStruct.sInstanceID,sInstanceID);

		return *this;
	}

}cEntityRespond,cEntityDelete;


//模型计算节拍报
typedef struct _ModelBus_ModelHeart
{
	char* sRID;	//身份字符串
	float CurTime;	//当前时间 单位：s
	float StepTime;	//步长 单位：s
	float NextTime;	//下一时间 单位：s
	/*重载构造函数*/
	_ModelBus_ModelHeart()
	{
		init();
	}
	void init()
	{
		sRID = NULL;
		CurTime = 0;
		StepTime = 0;
		NextTime = 0;
	}
	
	void release()
	{		
		SW_Free_Char(sRID);
	}
	/*重载析构函数*/
	~_ModelBus_ModelHeart()
	{
		release();
	}

	/*重载拷贝构造函数*/
	_ModelBus_ModelHeart(const _ModelBus_ModelHeart& heart)
	{
		init();
		*this = heart;
	}

	/*重载=*/
	_ModelBus_ModelHeart& operator=(const _ModelBus_ModelHeart& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		release();

		SW_Malloc_Char(theStruct.sRID,sRID);

		CurTime  = theStruct.CurTime;
		StepTime = theStruct.StepTime;
		NextTime = theStruct.NextTime;

		return *this;
	}

}cModelHeart;


//模型行为控制报文
typedef struct _ModelBus_ActionFun 
{
	char* sRID;                   //身份字符串
	char* sActionName;            //行为名称
	char* sActionParamDescribe;   //行为描述

	/*重载构造函数*/
	_ModelBus_ActionFun()
	{
		sRID = NULL;
		sActionName= NULL;
		sActionParamDescribe= NULL;
	}

	/*重载析构函数*/
	~_ModelBus_ActionFun()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sActionName);
		SW_Free_Char(sActionParamDescribe);
	}

	/*重载拷贝构造函数*/
	_ModelBus_ActionFun(const _ModelBus_ActionFun& ActionFun)
	{
		sRID = NULL;
		sActionName= NULL;
		sActionParamDescribe= NULL;
		*this = ActionFun;
	}

	/*重载=*/
	_ModelBus_ActionFun& operator=(const _ModelBus_ActionFun& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(sActionName);
		SW_Malloc_Char(theStruct.sActionName,sActionName);
		//SW_Free_Char(sActionParamDescribe);
		SW_Malloc_Char(theStruct.sActionParamDescribe,sActionParamDescribe);

		return *this;
	}
}cActionFun,cReloadModel;
//模型控制类报文定义结束


//辅助计算交换类报文定义开始
//辅助计算申请报
typedef struct _ModelBus_aAssCalcApply
{
	char* sRID;	//身份字符串
	char* CalcParam;	//计算参数(以0为结束)

	/*重载构造函数*/
	_ModelBus_aAssCalcApply()
	{
		sRID = NULL;
		CalcParam = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_aAssCalcApply()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(CalcParam);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aAssCalcApply(const _ModelBus_aAssCalcApply& assApply)
	{
		sRID = NULL;
		CalcParam = NULL;
		*this = assApply;
	}

	/*重载=*/
	_ModelBus_aAssCalcApply& operator=(const _ModelBus_aAssCalcApply& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Free_Char(CalcParam);

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.CalcParam,CalcParam);

		return *this;
	}

}cAssCalcApply;


//辅助计算应答报
typedef struct _ModelBus_aAssCalcRespond 
{
	char* sRID;	//身份字符串(用户标识)
	char* sTID;	//身份字符串(服务标识)
	bool IsFlow;    //流程查询标识
	bool IsUser;    //用户查询标识

	/*重载构造函数*/
	_ModelBus_aAssCalcRespond()
	{
		sRID = NULL;
		sTID = NULL;
		IsFlow = false;
		IsUser = false;
	}

	/*重载析构函数*/
	~_ModelBus_aAssCalcRespond()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aAssCalcRespond(const _ModelBus_aAssCalcRespond& assRepond)
	{
		sRID = NULL;
		sTID = NULL;
		*this = assRepond;
	}

	/*重载=*/
	_ModelBus_aAssCalcRespond& operator=(const _ModelBus_aAssCalcRespond& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Free_Char(sTID);

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sTID,sTID);

		IsFlow = theStruct.IsFlow;
		IsUser = theStruct.IsUser;

		return *this;
	}

}cAssCalcRespond;


//辅助计算控制报
typedef struct _ModelBus_aAssCalcControl
{
	char* sRID;    //身份字符串
	char* CalcFlow;    //计算流程

	/*重载构造函数*/
	_ModelBus_aAssCalcControl()
	{
		sRID = NULL;
		CalcFlow = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_aAssCalcControl()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(CalcFlow);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aAssCalcControl(const _ModelBus_aAssCalcControl& assApply)
	{
		sRID = NULL;
		CalcFlow = NULL;
		*this = assApply;
	}

	/*重载=*/
	_ModelBus_aAssCalcControl& operator=(const _ModelBus_aAssCalcControl& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Free_Char(CalcFlow);

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.CalcFlow,CalcFlow);

		return *this;
	}
}cAssCalcControl;



//辅助计算结论报
typedef struct _ModelBus_aAssCalcResult
{
	char* sRID;	//身份字符串(用户标识)
	char* sTID;	//身份字符串(服务标识)
	int iCalcResult;	//计算结论

	/*重载构造函数*/
	_ModelBus_aAssCalcResult()
	{
		sRID = NULL;
		sTID = NULL;
		iCalcResult = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aAssCalcResult()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aAssCalcResult(const _ModelBus_aAssCalcResult& assResult)
	{
		sRID = NULL;
		sTID = NULL;
		*this = assResult;
	}

	/*重载=*/
	_ModelBus_aAssCalcResult& operator=(const _ModelBus_aAssCalcResult& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		//SW_Free_Char(sTID);

		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sTID,sTID);

		iCalcResult = theStruct.iCalcResult;

		return *this;
	}

}cAssCalcResult;

//辅助计算交换类报文定义结束

//状态恢复报
typedef struct _ModelBus_BackStatus
{
	char* sRID;	  //身份字符串(用户标识)
	float fTime;  //时间点

	/*重载构造函数*/
	_ModelBus_BackStatus()
	{
		sRID  = NULL;
		fTime = 0;
	}

	/*重载析构函数*/
	~_ModelBus_BackStatus()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_BackStatus(const _ModelBus_BackStatus& oTmp)
	{
		sRID = NULL;
		*this = oTmp;
	}

	/*重载=*/
	_ModelBus_BackStatus& operator=(const _ModelBus_BackStatus& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		fTime = theStruct.fTime;
		return *this;
	}

}cBackStatus;

//辅助计算状态报：适用于无流程的辅助计算
typedef struct _ModelBus_aAssCalcStatus
{
	char*    sRID;	 //身份字符串(用户标识)
	char*    sTID;	 //身份字符串(服务标识)
	float    fStatus;//完成百分比

	/*重载构造函数*/
	_ModelBus_aAssCalcStatus()
	{
		sRID = NULL;
		sTID = NULL;
		fStatus = 0;
	}

	/*重载析构函数*/
	~_ModelBus_aAssCalcStatus()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_aAssCalcStatus(const _ModelBus_aAssCalcStatus& assStatus)
	{
		sRID = NULL;
		sTID = NULL;
		*this = assStatus;
	}

	/*重载=*/
	_ModelBus_aAssCalcStatus& operator=(const _ModelBus_aAssCalcStatus& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		//SW_Free_Char(sTID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		SW_Malloc_Char(theStruct.sTID,sTID);
		fStatus = theStruct.fStatus;
		return *this;
	}

}cAssCalcStatus;

//并行计算;节点状态
typedef struct
{
	int   nNodeID;          //节点ID
	int   nStartTime;       //启动时间
	float fCpu;             //Cpu利用率
	float fMem;             //可用内存,因为模型调度采用内存池，这里的可用内存是指内存池的可用内存 
}cParallelNodeStatus;

//并行计算;任务单
typedef struct _cParallelNodeTask
{
	int   nSrcNodeID;       //任务发送节点ID
	int   nDstNodeID;       //任务目标节点ID
	int   nTaskNo;          //任务单编号
	char  cTaskType;        //任务类别，1：有流程静态计算，2：无流程静态计算，3：动态计算
	char* sRID;	            //身份字符串(用户标识)
	char* sTask;	        //任务内容，有流程静态计算：流程名称, 无流程静态计算：无效，动态计算：实例ID用逗号隔开

	/*重载构造函数*/
	_cParallelNodeTask()
	{
		init();
	}

	void init()
	{
        nSrcNodeID = 0;
		nDstNodeID = 0;
		nTaskNo    = 0;
		cTaskType  = '3';
		sRID       = NULL;
        sTask      = NULL;
	}

	/*重载析构函数*/
	~_cParallelNodeTask()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTask);
	}

	/*重载拷贝构造函数*/
	_cParallelNodeTask(const _cParallelNodeTask& nodetask)
	{
		init();
		*this = nodetask;
	}

	/*重载=*/
	_cParallelNodeTask& operator=(const _cParallelNodeTask& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(sTask);
		SW_Malloc_Char(theStruct.sTask,sTask);
		nSrcNodeID = theStruct.nSrcNodeID;
		nDstNodeID = theStruct.nDstNodeID;
		nTaskNo    = theStruct.nTaskNo;
		cTaskType  = theStruct.cTaskType;

		return *this;
	}
}cParallelNodeTask;

//并行计算;任务回应单,节点发出该信息表示已经完成指定计算
typedef struct
{
	int   nSrcNodeID;       //任务发送节点ID
	int   nDstNodeID;       //任务目标节点ID
	int   nTaskNo;          //任务单编号
}cParallelNodeTaskRespond;


////////////////////////////////内部AllModeldata//////////////////////////////////////////
typedef struct _sModelData_inner 
{
	char			sInstanceID[32];	//实例号
	char			sBitID[32];			//位名称
	//void*			pData;              //位数据
	unsigned int	nDataCount;			//位数据字节数
	unsigned char*	pData;				//位数据---根据sBitID获得具体结构指针	

	void Init()
	{
		memset(sInstanceID, 0x00, 32);
		memset(sBitID, 0x00, 32);
		nDataCount = 0;
		pData = NULL;
	}

	void Release()
	{
		memset(sInstanceID, 0x00, 32);
		memset(sBitID, 0x00, 32);		
		SW_Free_Char(pData);
		nDataCount = 0;

	}
	_sModelData_inner()
	{
		Init();
	}

	_sModelData_inner(const _sModelData_inner &md)
	{
		Init();
		*this = md;
	}

	_sModelData_inner& operator=(const _sModelData_inner &md)
	{
		if (this == &md)
		{
			return *this;
		}

		Release();

		memcpy(sInstanceID, md.sInstanceID, 32);
		memcpy(sBitID, md.sBitID, 32);
        nDataCount = md.nDataCount;
		if (NULL != md.pData && md.nDataCount > 0)
		{			
			pData      = new unsigned char[md.nDataCount];
			memset(pData, 0x00, sizeof(unsigned char) * md.nDataCount);
			memcpy(pData, md.pData, sizeof(unsigned char) * md.nDataCount);
		}

		return *this;
	}

	~_sModelData_inner()
	{
		Release();
	}
}sModelData_inner;

typedef struct _sModelInfo_inner 
{
	char            sModelName[32];     //模型名称
	unsigned int    uInstanceNum;       //实例数目
	sModelData_inner*     pModelData;         //模型初始化数据

	void Init()
	{
		memset(sModelName, 0x00, 32);
		uInstanceNum = 0;
		pModelData = NULL;
	}

	void Release()
	{
		memset(sModelName, 0x00, 32);
		uInstanceNum = 0;
		SW_Free(pModelData);

	}
	_sModelInfo_inner()
	{
		Init();
	}

	~_sModelInfo_inner()
	{
		Release();
	}
	_sModelInfo_inner(const _sModelInfo_inner &mi)
	{
		Init();
		*this = mi;
	}

	_sModelInfo_inner& operator=(const _sModelInfo_inner &mi)
	{
		if (this == &mi)
		{
			return *this;
		}

		Release();

		memcpy(sModelName, mi.sModelName, 32);
		uInstanceNum = mi.uInstanceNum;
		if (uInstanceNum > 0 && mi.pModelData)
		{
			pModelData = new sModelData_inner[mi.uInstanceNum];
			for (unsigned int i = 0; i < mi.uInstanceNum; i++)
			{
				pModelData[i] = mi.pModelData[i];
			}
		}
		
		return *this;
	}
}sModelInfo_inner;

//用户设置输入信息
typedef struct _TREAT_Inner 
{
	int nDesEquipCount;                  //计算装备数量
	int* pDesEquipID;                    //计算装备ID
	int nSrcEquipCount;                  //GR装备数量
	int* pSrcEquipID;                    //GR装备ID


	void Init()
	{
		nDesEquipCount = 0;
		pDesEquipID = NULL;
		nSrcEquipCount = 0;
		pSrcEquipID = NULL;
	}

	void Release()
	{
		nDesEquipCount = 0;
		SW_Free(pDesEquipID);
		nSrcEquipCount = 0;
		SW_Free(pSrcEquipID);
	}

	_TREAT_Inner()
	{
		Init();
	}

	_TREAT_Inner(const _TREAT_Inner& t)
	{
		Release();

		*this = t;

	}



	_TREAT_Inner& operator=(const _TREAT_Inner& t)
	{
		if (this == &t)
		{
			return *this;
		}

		Release();

		nDesEquipCount = t.nDesEquipCount;
		if (t.nDesEquipCount > 0)
		{
			pDesEquipID = new int[t.nDesEquipCount];

			memcpy(pDesEquipID, t.pDesEquipID, sizeof(int)*t.nDesEquipCount);
		}

		nSrcEquipCount = t.nSrcEquipCount;
		if (t.nSrcEquipCount > 0)
		{
			pSrcEquipID = new int[t.nSrcEquipCount];

			memcpy(pSrcEquipID, t.pSrcEquipID, sizeof(int)*t.nSrcEquipCount);
		}

		return *this;
	}


	~_TREAT_Inner()
	{
		Release();
	}
}sTreatInfo_Inner;

//用户设置输入结构
typedef struct _STATIC_CALC_Inner
{
	int  nTreatInfoCount;                //用户设置组数
	sTreatInfo_Inner* pTreatInfo;				 //用户设置预处理数据

	char  sBitID[32];                   //计算初始化位   ////与装备初始化数据发送流程相同，在装备初始化数据发送完毕之后
	unsigned int nDataCount;			//计算初始化位数据字节数
	unsigned char* pData;				//计算初始化位数据----转入内部时，将原来的void*指向的结构体数据打包成unsigned char*，并获得打包后字节数nDataCount
	//void* pData;                        //计算初始化位数据
	//静态计算接口或文件名
	char           sAssCalcFileName[32];//静态计算文件名称，新流程为静态计算接口名称


	void Init()
	{
		nTreatInfoCount = 0;
		pTreatInfo = NULL;
		memset(sBitID, 0x00, 32);
		nDataCount = 0;
		pData = NULL;
		memset(sAssCalcFileName, 0x00, 32);
	}

	void Release()
	{
		nTreatInfoCount = 0;
		SW_Free(pTreatInfo);
		memset(sBitID, 0x00, 32);
		nDataCount = 0;
		SW_Free_Char(pData);
		memset(sAssCalcFileName, 0x00, 32);
	}

	_STATIC_CALC_Inner()
	{
		Init();
	}

	~_STATIC_CALC_Inner()
	{
		Release();
	}

	_STATIC_CALC_Inner(const _STATIC_CALC_Inner& sc)
	{
		Release();

		*this = sc;
	}

	_STATIC_CALC_Inner& operator = (const _STATIC_CALC_Inner& sc)
	{
		if (this == &sc)
		{
			return *this;
		}

		Release();

		nTreatInfoCount = sc.nTreatInfoCount;
		if (sc.nTreatInfoCount > 0 && sc.pTreatInfo)
		{
			pTreatInfo = new sTreatInfo_Inner[sc.nTreatInfoCount];

			for (int i = 0; i < sc.nTreatInfoCount; i++)
			{
				pTreatInfo[i] = sc.pTreatInfo[i];
			}
		}

		memcpy(sBitID, sc.sBitID, 32);

		nDataCount = sc.nDataCount;

		SW_Malloc_Struct(unsigned char, sc.pData, pData, sc.nDataCount, nDataCount);

		memcpy(sAssCalcFileName, sc.sAssCalcFileName, 32);

		return *this;

	}
}sStaCalcInfo_Inner;

typedef struct _DYNAMIC_CALC_Inner
{
	//动态计算
	char			szDynID[128];		//回放使用的动态推演场景名
	unsigned int   uStepTime;           //步长-毫秒		  0:表示无效
	unsigned int   uStartTime;			//开始时间-毫秒   
	unsigned int   uEndTime;            //结束时间-毫秒

	void Init()
	{
		uStepTime = 0;
		uStartTime = 0;
		uEndTime = 0;
	}

	void Release()
	{
		uStepTime = 0;
		uStartTime = 0;
		uEndTime = 0;
	}

	_DYNAMIC_CALC_Inner()
	{
		Init();
	}

	~_DYNAMIC_CALC_Inner()
	{
		Release();
	}

	_DYNAMIC_CALC_Inner(const _DYNAMIC_CALC_Inner& dc)
	{
		Init();

		*this = dc;
	}

	_DYNAMIC_CALC_Inner& operator = (const _DYNAMIC_CALC_Inner& dc)
	{
		if (this == &dc)
		{
			return *this;
		}

		Release();

		memcpy(szDynID, dc.szDynID, 128);
		uStepTime = dc.uStepTime;
		uStartTime = dc.uStartTime;
		uEndTime = dc.uEndTime;

		return *this;
	}

}sDynCalcInfo_Inner;

typedef struct _sAllModelData_inner
{
	//模型信息
	char*				sRID;				
	SHE					she;
	unsigned int		uModelInfoNum;       //模型数目
	sModelInfo_inner*	pModelInfo;          //模型信息

	bool				bCalcFlag;			// true 静态计算,false 动态计算
	sStaCalcInfo_Inner	staCalcInfo;			//  静态计算
	sDynCalcInfo_Inner	dynCalcInfo;			//  动态计算


	void Init()
	{
		sRID = NULL;
		she.Init();
		uModelInfoNum = 0;
		pModelInfo = NULL;
		bCalcFlag = true;
		staCalcInfo.Init();
		dynCalcInfo.Init();
	}

	void Release()
	{
		SW_Free_Char(sRID);
		she.Release();
		uModelInfoNum = 0;
		SW_Free(pModelInfo);
		bCalcFlag = true;
		staCalcInfo.Release();
		dynCalcInfo.Release();
	}
	_sAllModelData_inner()
	{
		Init();
	}

	~_sAllModelData_inner()
	{
		Release();
	}

	_sAllModelData_inner(const _sAllModelData_inner& all)
	{
		Init();

		*this = all;
	}

	_sAllModelData_inner& operator = (const _sAllModelData_inner& all)
	{
		if (this == &all)
		{
			return *this;
		}

		Release();

		SW_Malloc_Char(all.sRID,sRID);
		she = all.she;

		uModelInfoNum = all.uModelInfoNum;

		if (all.uModelInfoNum > 0 && all.pModelInfo)
		{
			pModelInfo = new _sModelInfo_inner[all.uModelInfoNum];

			for (int i = 0; i < all.uModelInfoNum; i++)
			{
				pModelInfo[i] = all.pModelInfo[i];
			}
		}

		bCalcFlag = all.bCalcFlag;

		staCalcInfo = all.staCalcInfo;

		dynCalcInfo = all.dynCalcInfo;

		return *this;
	}

}sAllModelData_inner;


// pathname = dirname + basename
#define SVC_PATH_MAX 1024   /* max length for a pathname, include tail '\0' */
// filename = basename
#define SVC_NAME_MAX 255    /* max length for a filename, include tail '\0' */

typedef struct _sBitData_inner_DK 
{
	char			sBitID[32];			//位名称
	//void*			pData;              //位数据
	unsigned int	nDataCount;			//位数据字节数
	unsigned char*	pData;				//位数据---根据sBitID获得具体结构指针	

	void Init()
	{
		memset(sBitID, 0x00, 32);
		nDataCount = 0;
		pData = NULL;
	}

	void Release()
	{
		memset(sBitID, 0x00, 32);
		nDataCount = 0;
		SW_Free_Char(pData);
	}
	_sBitData_inner_DK()
	{
		Init();
	}

	_sBitData_inner_DK(const _sBitData_inner_DK &md)
	{
		Init();
		*this = md;
	}

	_sBitData_inner_DK& operator=(const _sBitData_inner_DK &md)
	{
		if (this == &md)
		{
			return *this;
		}

		Release();

		memcpy(sBitID, md.sBitID, 32);

		if (NULL != md.pData && md.nDataCount > 0)
		{
			nDataCount = md.nDataCount;
			pData      = new unsigned char[md.nDataCount];
			memset(pData, 0x00, sizeof(unsigned char) * md.nDataCount);
			memcpy(pData, md.pData, sizeof(unsigned char) * md.nDataCount);
		}
		else
		{
			nDataCount = 0;
			pData      = NULL;
		}

		return *this;
	}

	~_sBitData_inner_DK()
	{
		Release();
	}
}sBitData_inner_DK;

typedef struct _sModelData_inner_DK 
{
	char			sInstanceID[32];	//实例号
	unsigned int    uBitDataNum;        //初始化位数据数目
	sBitData_inner_DK* pBitData;         //初始化位数据

	void Init()
	{
		memset(sInstanceID, 0x00, 32);
		uBitDataNum = 0;
		pBitData = NULL;
	}

	void Release()
	{
		memset(sInstanceID, 0x00, 32);
		uBitDataNum = 0;
		SW_Free(pBitData);
	}
	_sModelData_inner_DK()
	{
		Init();
	}

	_sModelData_inner_DK(const _sModelData_inner_DK &md)
	{
		Init();
		*this = md;
	}

	_sModelData_inner_DK& operator=(const _sModelData_inner_DK &md)
	{
		if (this == &md)
		{
			return *this;
		}

		Release();

		memcpy(sInstanceID, md.sInstanceID, 32);
        uBitDataNum = md.uBitDataNum;
		if (NULL != md.pBitData && md.uBitDataNum > 0)
		{			
			pBitData = new sBitData_inner_DK[md.uBitDataNum];
			for (unsigned int i = 0; i < md.uBitDataNum; i++)
			{
				pBitData[i] = md.pBitData[i];
			}
		} 
		
		return *this;
	}

	~_sModelData_inner_DK()
	{
		Release();
	}
}sModelData_inner_DK;

typedef struct _sModelInfo_inner_DK 
{
	char                     szModelName[32];     //模型名称
	unsigned int			 uInstanceNum;       //实例数目
	sModelData_inner_DK*     pModelData;         //模型初始化数据

	void Init()
	{
		memset(szModelName, 0x00, 32);
		uInstanceNum = 0;
		pModelData = NULL;
	}

	void Release()
	{
		memset(szModelName, 0x00, 32);
		SW_Free(pModelData);
		uInstanceNum = 0;
	}
	_sModelInfo_inner_DK()
	{
		Init();
	}

	_sModelInfo_inner_DK(const _sModelInfo_inner_DK &mi)
	{
		Init();
		*this = mi;
	}

	_sModelInfo_inner_DK& operator=(const _sModelInfo_inner_DK &mi)
	{
		if (this == &mi)
		{
			return *this;
		}

		Release();
		memcpy(szModelName, mi.szModelName, 32);
		uInstanceNum = mi.uInstanceNum;

		if (mi.uInstanceNum > 0 && mi.pModelData != NULL)
		{
			pModelData = new sModelData_inner_DK[mi.uInstanceNum];
			for (unsigned int i = 0; i < mi.uInstanceNum; i++)
			{
				pModelData[i] = mi.pModelData[i];
			}
		}

		return *this;
	}

	~_sModelInfo_inner_DK()
	{
		Release();
	}
}sModelInfo_inner_DK;

typedef struct _sAllModelDataDK
{
	//模型信息
	char*                sRID;                  //身份标识符
	SHE			         she;                   //发送地址
	unsigned int	     uiModelInfoNum;        //模型数目
	sModelInfo_inner_DK* pModelInfo;            //模型信息

	int				nCalcType;			//计算类型，0:动态计算；1：离线计算；2静态计算
	//离线计算
	int             nStartTime;			//开始时间-秒   
	unsigned int    uiStepTime;         //步长-秒		  0:表示无效
	int             nEndTime;           //结束时间-秒  

	//静态计算
	char            szCalcFileName[SVC_NAME_MAX];//静态计算对应流程文件名称，离线计算对应场景名称

	void Init()
	{
		sRID = NULL;
		she.Init();
		uiModelInfoNum = 0;
		pModelInfo = NULL;
		nCalcType  = 2;
		nStartTime = 0;
		uiStepTime = 0;
		nEndTime   = 0;
		memset(szCalcFileName, 0x00, SVC_NAME_MAX);
	}

	void Release()
	{
		SW_Free_Char(sRID);
		she.Release();
		uiModelInfoNum = 0;
		SW_Free(pModelInfo);
		nCalcType  = 2;
		nStartTime = 0;
		uiStepTime = 0;
		nEndTime   = 0;
		memset(szCalcFileName, 0x00, SVC_NAME_MAX);
	}

	_sAllModelDataDK()
	{
		Init();
	}

	~_sAllModelDataDK()
	{
        Release();
	}

	_sAllModelDataDK(const _sAllModelDataDK& all)
	{
		Init();

		*this = all;
	}

	_sAllModelDataDK& operator = (const _sAllModelDataDK& all)
	{
		if (this == &all)
		{
			return *this;
		}

		Release();

		SW_Malloc_Char(all.sRID,sRID);
		she = all.she;

		uiModelInfoNum = all.uiModelInfoNum;

		if (all.uiModelInfoNum > 0 && all.pModelInfo)
		{
			pModelInfo = new _sModelInfo_inner_DK[all.uiModelInfoNum];

			for (int i = 0; i < all.uiModelInfoNum; i++)
			{
				pModelInfo[i] = all.pModelInfo[i];
			}
		}

		nCalcType  = all.nCalcType;
		nStartTime = all.nStartTime;
		uiStepTime = all.uiStepTime;
		nEndTime   = all.nEndTime;
		memcpy(szCalcFileName, all.szCalcFileName, SVC_NAME_MAX);

		return *this;
	}

}stAllModelDataDK;


#define DYNCTRL_RESUME	0;
#define DYNCTRL_PAUSE	1;
#define DYNCTRL_STOP	2;
#define DYNCTRL_SPEED	3;
#define DYNCTRL_SETCUR	4;

typedef struct _DynCalcControl 
{
	char *sRID;			//身份信息
	int  ControlCode;	//控制码：0--恢复/不阻塞, 1--暂停，2--停止，3--速度控制，4--改变当前推演时间
	unsigned int m_uiStep;//步长值 毫秒
	unsigned int m_uiCurrent;//当前时间

	void Init()
	{
		sRID = NULL;
		ControlCode = 0;
		m_uiStep = 0;
		m_uiCurrent = 0;
	}

	void Release()
	{
		SW_Free_Char(sRID);
		ControlCode = 0;
		m_uiStep = 0;
		m_uiCurrent = 0;
	}
	_DynCalcControl()
	{
		Init();
	}

	~_DynCalcControl()
	{
		Release();
	}

	_DynCalcControl(const _DynCalcControl& dcc)
	{
		Init();
		*this = dcc;
	}

	_DynCalcControl& operator=(const _DynCalcControl& dcc)
	{
		if (this == &dcc)
		{
			return *this;
		}

		Release();
		SW_Malloc_Char(dcc.sRID,  sRID);
		ControlCode = dcc.ControlCode;
		m_uiStep = dcc.m_uiStep;
		m_uiCurrent = dcc.m_uiCurrent;

		return *this;
	}
}cDynCalcControl;

//任务状态码定义

#define SVC_TASK_NORM_STAFINISH	6001	//静态计算结束
#define SVC_TASK_NORM_DYNFINISH	6002	//动态推演就绪
#define SVC_TASK_NORM_OFFPROCESS 6003	//离线推演进度
#define SVC_TASK_NORM_OFFFINISH 6004	//离线计算结束
#define SVC_TASK_NORM_DYNSTEPINISH 6005	//本次推演节拍计算完成

#define SVC_TASK_ERR_DESHEAD	7001	//解包报文头错误
#define SVC_TASK_ERR_DESGRAM	7002	//解包报文体错误
#define SVC_TASK_ERR_NOEQUIP	7003	//没有计算装备
#define SVC_TASK_ERR_NOMODEL	7004	//模型不存在
#define SVC_TASK_ERR_CREATINST	7005	//创建模型实例失败
#define SVC_TASK_ERR_SETSTAINIT	7006	//设置静态装备初始化数据失败
#define SVC_TASK_ERR_SETDYNINIT	7007	//设置动态装备初始化数据失败
#define SVC_TASK_ERR_NOSTARLT	7008	//没有获取静态计算结果
#define SVC_TASK_ERR_NODYNRLT	7009	//没有获取动态计算结果
#define SVC_TASK_ERR_NOFlowFile	7010	//没有静态流程文件
#define SVC_TASK_ERR_NOTYDBTABLE 7011	//推演数据库表不存在
#define SVC_TASK_ERR_SETTYTIME  7012	//推演起止时间设置错误
#define SVC_TASK_ERR_CREATFILE  7013	//离线推演创建文件失败
#define SVC_TASK_ERR_WRITEDB	7014	//离线推演写数据库失败


//任务状态信息
typedef struct _StructStatus
{
	char* sRID;
	int	nStatusCode;			//状态码
	char szStatusMsg[128];	    //状态描述信息

	void Init()
	{
		sRID = NULL;
		nStatusCode = 0;//默认正常
		memset(szStatusMsg, 0x00, 128);
	}

	void Release()
	{
		SW_Free_Char(sRID);
	}

	_StructStatus()
	{
		Init();
	}

	~_StructStatus()
	{
		Release();
	}

	_StructStatus(const _StructStatus& status)
	{
		Init();
		*this = status;
	}

	_StructStatus& operator=(const _StructStatus& status)
	{
		if (this == &status)
		{
			return *this;
		}

		memset(szStatusMsg, 0x00, 128);

		SW_Malloc_Char(status.sRID,  sRID);
		nStatusCode = status.nStatusCode;
		memcpy(szStatusMsg, status.szStatusMsg, 128);

		return *this;
	}

} structTaskStatus;


#pragma pack()

#endif

/**************************************************************************
**名    称:	内部模型数据结构												**
**用    途:	用于内部定义的所有数据结构定义					**
**版 本 号:  ST 5.4.1		按照年(个数位)月日组合的方式	**
**版    本:	2015.04.01  zoubz修改											**
*************************************************************************/

#include "MEnStruct_Macros.h"

#ifndef MEN_STRUCT_DMS
#define MEN_STRUCT_DMS

#pragma pack(1)

/*************************************************************
*                         模型控制类                             *
*************************************************************/
//用户注册报
typedef struct _ModelBus_UserAsk
{
	char* sRID;	//身份字符串

	/*重载构造函数*/
	_ModelBus_UserAsk()
	{
		sRID = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_UserAsk()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_UserAsk(const _ModelBus_UserAsk& useAsk)
	{
		sRID  = NULL;
		*this = useAsk;
	}

	/*重载=*/
	_ModelBus_UserAsk& operator=(const _ModelBus_UserAsk& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		return *this;
	}

}cUserAsk;

//用户应答报
typedef struct _ModelBus_UserRespond
{
	char* sRID;   //身份字符串

	/*重载构造函数*/
	_ModelBus_UserRespond()
	{
		sRID = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_UserRespond()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_UserRespond(const _ModelBus_UserRespond& useRespond)
	{
		sRID  = NULL;
		*this = useRespond;
	}

	/*重载=*/
	_ModelBus_UserRespond& operator=(const _ModelBus_UserRespond& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		return *this;
	}
}cUserRespond;

//用户撤销报
typedef struct _ModelBus_UserDelete
{
	char* sRID;	//身份字符串

	/*重载构造函数*/
	_ModelBus_UserDelete()
	{
		sRID = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_UserDelete()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_UserDelete(const _ModelBus_UserDelete& useDelete)
	{
		sRID  = NULL;
		*this = useDelete;
	}

	/*重载=*/
	_ModelBus_UserDelete& operator=(const _ModelBus_UserDelete& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		return *this;
	}

}cUserDelete;


//推演状态报
typedef struct _ModelBus_TYState
{
	char* sRID;			//身份字符串
	bool  bType;		//推演方式
	float fTime;		//推演总时间
	char* sFileName;	//场景名称

	/*/ *重载构造函数* /*/
	_ModelBus_TYState()
	{
		sRID = NULL;
		bType = false;
		fTime = 0;
		sFileName = NULL;
	}

	/*/ *重载析构函数* /*/
	~_ModelBus_TYState()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sFileName);

	}


	/*/ *重载拷贝构造函数* / * /*/

	_ModelBus_TYState(const _ModelBus_TYState& useAsk)
	{
		sRID  = NULL;
		sFileName = NULL;
		*this = useAsk;
	}

	/*/ *重载=* /*/
	_ModelBus_TYState& operator=(const _ModelBus_TYState& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(sFileName);
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
	char* sRID;			//身份字符串
	char* sModelName;	//模型名称

	/*重载构造函数*/
	_ModelBus_ModelAsk()
	{
		sRID = NULL;
		sModelName = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_ModelAsk()
	{

		SW_Free_Char(sRID);
		SW_Free_Char(sModelName);

	}

	/*重载拷贝构造函数*/
	_ModelBus_ModelAsk(const _ModelBus_ModelAsk& modelAsk)
	{
		sRID  = NULL;
		sModelName = NULL;
		*this = modelAsk;
	}

	/*重载=*/
	_ModelBus_ModelAsk& operator=(const _ModelBus_ModelAsk& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(sModelName);
		SW_Malloc_Char(theStruct.sModelName,sModelName);

		return *this;
	}

}cModelAsk;

//模型应答报
typedef struct _ModelBus_ModelRespond
{
	char* sRID;			//身份字符串（源地址）
	char* sTID;			//身份字符串（目的地址）
	char* sModelName;	//模型名称

	/*重载构造函数*/
	_ModelBus_ModelRespond()
	{
		sRID = NULL;
		sTID = NULL;
		sModelName = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_ModelRespond()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTID);
		SW_Free_Char(sModelName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_ModelRespond(const _ModelBus_ModelRespond& modelRespond)
	{
		sRID = NULL;
		sTID = NULL;
		sModelName = NULL;
		*this = modelRespond;
	}

	/*重载=*/
	_ModelBus_ModelRespond& operator=(const _ModelBus_ModelRespond& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(sTID);
		SW_Malloc_Char(theStruct.sTID,sTID);
		//SW_Free_Char(sModelName);
		SW_Malloc_Char(theStruct.sModelName,sModelName);

		return *this;
	}

}cModelRespond;

//模型实例问询报
typedef struct _ModelBus_EntityAsk
{
	char* sRID;			//身份字符串
	char* sModelName;	//模型名称
	char* sInstanceID;	//实例标识号

	/*重载构造函数*/
	_ModelBus_EntityAsk()
	{
		sRID = NULL;
		sModelName = NULL;
		sInstanceID = NULL;	
	}

	/*重载析构函数*/
	~_ModelBus_EntityAsk()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sInstanceID);
		SW_Free_Char(sModelName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EntityAsk(const _ModelBus_EntityAsk& entityAsk)
	{
		sRID = NULL;
		sModelName = NULL;
		sInstanceID = NULL;
		*this = entityAsk;
	}

	/*重载=*/
	_ModelBus_EntityAsk& operator=(const _ModelBus_EntityAsk& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(sInstanceID);
		SW_Malloc_Char(theStruct.sInstanceID,sInstanceID);
		//SW_Free_Char(sModelName);
		SW_Malloc_Char(theStruct.sModelName,sModelName);
		return *this;
	}

}cEntityAsk;

//模型实例应答报
typedef struct _ModelBus_EntityRespond
{
	char* sRID;			//身份字符串（源地址）
	char* sTID;			//身份字符串（目的地址）
	char* sModelName;	//模型名称
	char* sInstanceID;	//实例标识号

	/*重载构造函数*/
	_ModelBus_EntityRespond()
	{
		sRID = NULL;
		sTID = NULL;
		sModelName = NULL;
		sInstanceID = NULL;	
	}

	/*重载析构函数*/
	~_ModelBus_EntityRespond()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTID);
		SW_Free_Char(sInstanceID);
		SW_Free_Char(sModelName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EntityRespond(const _ModelBus_EntityRespond& entityRespond)
	{
		sRID = NULL;
		sTID = NULL;
		sModelName = NULL;
		sInstanceID = NULL;
		*this = entityRespond;
	}

	/*重载=*/
	_ModelBus_EntityRespond& operator=(const _ModelBus_EntityRespond& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(sTID);
		SW_Malloc_Char(theStruct.sTID,sTID);
		//SW_Free_Char(sInstanceID);
		SW_Malloc_Char(theStruct.sInstanceID,sInstanceID);
		//SW_Free_Char(sModelName);
		SW_Malloc_Char(theStruct.sModelName,sModelName);
		return *this;
	}

}cEntityRespond;

//模型实例删除报
typedef struct _ModelBus_EntityDelete
{
	char* sRID;			//身份字符串（源地址）
	char* sTID;			//身份字符串（目的地址）
	char* sModelName;	//模型名称
	char* sInstanceID;	//实例标识号

	/*重载构造函数*/
	_ModelBus_EntityDelete()
	{
		sRID = NULL;
		sTID = NULL;
		sModelName = NULL;
		sInstanceID = NULL;	
	}

	/*重载析构函数*/
	~_ModelBus_EntityDelete()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sTID);
		SW_Free_Char(sInstanceID);
		SW_Free_Char(sModelName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EntityDelete(const _ModelBus_EntityDelete& entityDelete)
	{
		sRID = NULL;
		sTID = NULL;
		sModelName = NULL;
		sInstanceID = NULL;
		*this = entityDelete;
	}

	/*重载=*/
	_ModelBus_EntityDelete& operator=(const _ModelBus_EntityDelete& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(sTID);
		SW_Malloc_Char(theStruct.sTID,sTID);
		//SW_Free_Char(sInstanceID);
		SW_Malloc_Char(theStruct.sInstanceID,sInstanceID);
		//SW_Free_Char(sModelName);
		SW_Malloc_Char(theStruct.sModelName,sModelName);
		return *this;
	}

}cEntityDelete;

//模型计算节拍报
typedef struct _ModelBus_ModelHeart
{
	char* sRID;		//身份字符串
	float CurTime;	//当前时间 单位：秒（s）
	float StepTime;	//步长 单位：秒（s）
	float NextTime;	//下一时间 单位：秒（s）

	/*重载构造函数*/
	_ModelBus_ModelHeart()
	{
		sRID = NULL;
		CurTime = 0;
		StepTime = 0;
		NextTime = 0;
	}

	/*重载析构函数*/
	~_ModelBus_ModelHeart()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_ModelHeart(const _ModelBus_ModelHeart& heart)
	{
		sRID = NULL;
		*this = heart;
	}

	/*重载=*/
	_ModelBus_ModelHeart& operator=(const _ModelBus_ModelHeart& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		CurTime  = theStruct.CurTime;
		StepTime = theStruct.StepTime;
		NextTime = theStruct.NextTime;

		return *this;
	}

}cModelHeart;


//评估状态报
typedef struct _ModelBus_EvalStatus
{
	char*	sRID;		//身份字符串
	int		nID;		//装备ID
	int		nEvalType;	//评估模式(0：战役级1：战术级)

	/*重载构造函数*/
	_ModelBus_EvalStatus()
	{
		sRID = NULL;
		nID = 0;
		nEvalType = 0;

	}

	/*重载析构函数*/
	~_ModelBus_EvalStatus()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_EvalStatus(const _ModelBus_EvalStatus& v)
	{
		sRID = NULL;
		*this = v;
	}

	/*重载=*/
	_ModelBus_EvalStatus& operator=(const _ModelBus_EvalStatus& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		nID  = theStruct.nID;
		nEvalType = theStruct.nEvalType;
		return *this;
	}
}cEvalStatus;


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














/*************************************************************
*                       总线控制类                           *
*************************************************************/
//总线单元身份报
typedef struct _ModelBus_SIdentityReport
{
	char* sRID;			//身份字符串
	char* sSoftName;	//软件名称

	/*重载构造函数*/
	_ModelBus_SIdentityReport()
	{
		sRID = NULL;
		sSoftName = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_SIdentityReport()
	{
		SW_Free_Char(sRID);
		SW_Free_Char(sSoftName);
	}

	/*重载拷贝构造函数*/
	_ModelBus_SIdentityReport(const _ModelBus_SIdentityReport& ideReport)
	{
		sRID = NULL;
		sSoftName = NULL;
		*this = ideReport;
	}

	/*重载=*/
	_ModelBus_SIdentityReport& operator=(const _ModelBus_SIdentityReport& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		//SW_Free_Char(sSoftName);
		SW_Malloc_Char(theStruct.sSoftName,sSoftName);

		return *this;
	}

}cSIdentityReport;

//总线单元状态报
typedef struct _ModelBus_SStateReport
{
	char* sRID;	//身份字符串

	/*重载构造函数*/
	_ModelBus_SStateReport()
	{
		sRID = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_SStateReport()
	{
		SW_Free_Char(sRID);
	}

	/*重载拷贝构造函数*/
	_ModelBus_SStateReport(const _ModelBus_SStateReport& stateReport)
	{
		sRID = NULL;
		*this = stateReport;
	}

	/*重载=*/
	_ModelBus_SStateReport& operator=(const _ModelBus_SStateReport& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);

		return *this;
	}

}cSStateReport;


/*************************************************************
*                    辅助计算交换类                          *
*************************************************************/
//辅助计算申请报
typedef struct _ModelBus_aAssCalcApply
{
	char* sRID;			//身份字符串
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
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(CalcParam);
		SW_Malloc_Char(theStruct.CalcParam,CalcParam);

		return *this;
	}

}cAssCalcApply;

//辅助计算应答报
typedef struct _ModelBus_aAssCalcRespond 
{
	char*	sRID;		//身份字符串(用户标识)
	char*	sTID;		//身份字符串(服务标识)
	bool	IsFlow;		//流程查询标识
	bool	IsUser;		//用户查询标识

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
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(sTID);
		SW_Malloc_Char(theStruct.sTID,sTID);
		IsFlow = theStruct.IsFlow;
		IsUser = theStruct.IsUser;

		return *this;
	}

}cAssCalcRespond;

//辅助计算控制报
typedef struct _ModelBus_aAssCalcControl
{
	char*	sRID;		//身份字符串
	char*	CalcFlow;	//计算流程

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
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(CalcFlow);
		SW_Malloc_Char(theStruct.CalcFlow,CalcFlow);
		return *this;
	}

}cAssCalcControl;

//辅助计算结论报
typedef struct _ModelBus_aAssCalcResult
{
	char*	sRID;			//身份字符串(用户标识)
	char*	sTID;			//身份字符串(服务标识)
	int		iCalcResult;	//计算结论

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
		if( this==&theStruct )
		{
			return *this;
		}

		//SW_Free_Char(sRID);
		SW_Malloc_Char(theStruct.sRID,sRID);
		//SW_Free_Char(sTID);
		SW_Malloc_Char(theStruct.sTID,sTID);
		iCalcResult = theStruct.iCalcResult;

		return *this;
	}

}cAssCalcResult;

//动态计算控制报文

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

		SW_Malloc_Char(dcc.sRID,  sRID);
		ControlCode = dcc.ControlCode;
		m_uiStep = dcc.m_uiStep;
		m_uiCurrent = dcc.m_uiCurrent;

		return *this;
	}
}cDynCalcControl;

#pragma pack()

#endif
#ifndef _MEMORYMGR_H
#define _MEMORYMGR_H
//#include <new>
#include <stdlib.h>
#include <stdio.h>
//#ifndef _WIN32
//typedef unsigned __int64 size_t ;
//#endif

// 设置最小分配空间
void  HrSetMemoryMinSize(size_t nSize);
// 设置最大分配空间
void  HrSetMemoryMaxSize(size_t nSize);
// 初始化分配内存
bool   HRMemoryInit(size_t size);
// 退出分配内存
bool   HRMemoryExit();
// 获取内存块的大小
size_t HRMemorySize(void* p);
// 分配大小为size的数据块
void* HrMemoryMalloc(size_t size);
void* HrMemoryMallocByLog(size_t size,const char* strFile, int nLine);

// 释放由hr_malloc返回的内存块
void  HrMemoryFree(void* p);

// 返回可用内存空间
size_t GetFreeMemory();

// 设置是否记录未删除的分配
void SetIsLogNoFree(bool bIsLog);

// 分配大小为size的数据块
inline void* operator new (size_t size)
{
	return	HrMemoryMalloc(size);
}
inline void* operator new (size_t size, const char* strFile, int nLine)
{
	return	HrMemoryMallocByLog(size,strFile,nLine);
}

// 分配大小为size的数据块
inline void* operator new [] (size_t size)
{
	return	HrMemoryMalloc(size);
}
inline void* operator new [] (size_t size, const char* strFile, int nLine)
{
	return	HrMemoryMallocByLog(size,strFile,nLine);
}

// 释放内存块
inline void operator delete(void* p)
{
	HrMemoryFree(p);
}
inline void operator delete(void* p, const char* strFile, int nLine)
{
	HrMemoryFree(p);
}
// 释放内存块
inline void operator delete[](void* p)
{
	HrMemoryFree(p);
}
inline void operator delete[](void* p, const char* strFile, int nLine)
{
	HrMemoryFree(p);
}


#ifdef malloc(nSize)
#undef malloc(nSize)
#endif
#define malloc(nSize)	HrMemoryMallocByLog(nSize,__FILE__, __LINE__)

#ifdef free(p)
#undef free(p)
#endif
#define free(p)         HrMemoryFree(p)

#ifdef new
#undef new
#endif
#define new		        new(__FILE__, __LINE__)

////////////////////////////////Modified by wht 2012-11-1//////////////////////////////////////////
/*************************************************************************
* 函数名: GetNoFreeAll
* 功  能:返回未释放分配
* 参  数:
* 返回值:未释放分配的信息 
*************************************************************************/
char* GetNoFreeAll();
//////////////////////////////////////////////////////////////////////////
#endif

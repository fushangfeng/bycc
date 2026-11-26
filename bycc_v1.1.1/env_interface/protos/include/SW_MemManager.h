#ifndef  _SW_MEMMANAGER_H_

#define  _SW_MEMMANAGER_H_



#include <new>

#include <stdio.h>

#include <stdlib.h>



/**

* 初始化内存数据大小的区间以及内存分配锁

*

* @param[in] max 分配内存的最大值

* @param[in] min 分配内存的最小值

* @param[in] pMutex 内存分配锁

* @return 无

*/

extern void SW_MemManagerinit(unsigned long max,unsigned long min, void* pMutex);





/**

 * 分配内存数据 

 *

 * @param[out] pData  分配内存后的地址

 * @param[in] nLength 需要分配出的内存数据大小

 * @return void* 返回为已经分配出的内存数据，如果分配失败则返回 NULL

 */

//template <typename T>

//extern void SW_malloc(T*& pData, int nLength);



extern void SW_malloc(void*& pData, int nLength);

/**

* 分配内存数据 

*

* @param[in] nLength 需要分配出的内存数据大小

* @return void* 返回为已经分配出的内存数据，如果分配失败则返回 NULL

*/

extern void* SW_malloc(int nLength);



/**

 * 释放已经分配出的数据

 *

 * @param[in] void * pData 需要释放的数据

 * @return 无

 */



extern void SW_free(void *& pData);



// 分配大小为size的数据块

inline	void *operator new(size_t size)

{

	return SW_malloc(size);

}

// 释放大小为size的数据块

inline	void operator delete(void* p)

{

	SW_free(p);

}

// 分配大小为size的数据块

inline	void *operator new[](size_t size)

{

	return SW_malloc(size);

}

// 释放大小为size的数据块

inline	void operator delete[](void* p)

{

	SW_free(p);

}





#endif //_SW_MEMMANAGER_H_






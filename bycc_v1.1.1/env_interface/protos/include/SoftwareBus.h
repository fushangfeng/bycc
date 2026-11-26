#ifndef __SOFTWAREBUS_H__
#define __SOFTWAREBUS_H__

#include <stddef.h>
#include <stdio.h>
#include <time.h>


#if !defined(_WIN32) && !defined(__cdecl)
#define __cdecl
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef UNICODE
typedef wchar_t char_t;
#else
typedef char char_t;
#endif

typedef char           sftb_bool_t;
typedef signed char    sftb_int1_t;
typedef unsigned char  sftb_nat1_t;
typedef signed short   sftb_int2_t;
typedef unsigned short sftb_nat2_t;
typedef float          sftb_real4_t;
typedef double         sftb_real8_t;
typedef time_t         sftb_time_t;



#if !defined(SIZEOF_LONG) && (defined(_L64) || defined(_LP64) || defined(__osf__))
#define SIZEOF_LONG 8
#endif

#if (defined(_WIN32) || defined(__BORLANDC__)) && !defined(__MINGW32__)
typedef signed __int32     sftb_int4_t;
typedef unsigned __int32   sftb_nat4_t;
typedef __int64            sftb_int8_t;
typedef unsigned __int64   sftb_nat8_t;
#else
typedef signed int         sftb_int4_t;
typedef unsigned int       sftb_nat4_t;
#if SIZEOF_LONG == 8
typedef signed long        sftb_int8_t;
typedef unsigned long      sftb_nat8_t;
#else
typedef signed long long   sftb_int8_t;
typedef unsigned long long sftb_nat8_t;
#endif
#endif

//对象的拷贝，传输，生成，条件
enum SoftwareBusResultCode 
{
    rt_ok = 0,
    rt_address = -1,
    rt_connection_refused = -2,
    rt_bus_not_found = -3,
    rt_bit_not_found = -4,
    rt_subcriber_repeat = -5,
    rt_no_subcriber = -6,
    rt_subcriber_null = -7,
    rt_bus_repeat = -8,
    rt_bus_name_null = -9,
    rt_bit_repeat = -10,
    rt_memory_error = -11,
    rt_network_error = -12,
    rt_data_error = -13,
    rt_length_error = -14,
    rt_field_repeat_error = -15,
    rt_field_length_error = -16,
    rt_var_array_field_error = -17,
    rt_bit_percent_error = -18,
    rt_network_too_busy = -19,
    rt_busname_error = -20,
    rt_busbit_error = -21,
    rt_subcriber_id_error = -22,
    rt_no_init = -99,
    rt_xml_parse_error = -100
};
//所支持的字段类型
enum FieldVarType 
{
    fd_bool = 0,
    fd_int1,
    fd_int2,
    fd_int4,
    fd_int8,
    fd_nat1,
    fd_nat2,
    fd_nat4,
    fd_nat8,
    fd_real4,
    fd_real8,
    fd_asciiz,
    fd_pasciiz,
    fd_array_of_bool,
    fd_array_of_int1,
    fd_array_of_int2,
    fd_array_of_int4,
    fd_array_of_int8,
    fd_array_of_uint1,
    fd_array_of_uint2,
    fd_array_of_uint4,
    fd_array_of_uint8,
    fd_array_of_real4,
    fd_array_of_real8, 
    fd_array_of_string ,
    fd_datetime ,
	fd_struct,
	fd_array_of_struct
};
static char *g_strFieldVarType [] = 
{
    "fd_bool",
    "fd_int1",
    "fd_int2",
    "fd_int4",
    "fd_int8",
    "fd_nat1",
    "fd_nat2",
    "fd_nat4",
    "fd_nat8",
    "fd_real4",
    "fd_real8",
    "fd_asciiz",
    "fd_pasciiz",
    "fd_array_of_bool",
    "fd_array_of_int1",
    "fd_array_of_int2",
    "fd_array_of_int4",
    "fd_array_of_int8",
    "fd_array_of_uint1",
    "fd_array_of_uint2",
    "fd_array_of_uint4",
    "fd_array_of_uint8",
    "fd_array_of_real4",
    "fd_array_of_real8", 
    "fd_array_of_string" ,
    "fd_datetime" ,
	"fd_struct",
	"fd_array_of_struct"
};
//总线位对象字段描述
typedef struct BitFieldDescriptor
{ 
    enum FieldVarType type;     //字段类型
	sftb_int4_t       length;   //长度：固定长度字符串、固定长度数组有效率
    char_t            name[50]; //字段名称
    char_t            size[50]; //描述变长字段长度的字段名称
	char_t			  bitid[50];//如果为扩展结构，表示使用结构的总线位描述
}BitFieldDescriptor;

/*********************************************************************
 * ClientNetBroken
 *     总线客户端断开处理方法原型
 * Parameters:
 *     NetAddr  - 断开客户的网络地址
 * Returns:
 *     无
 */
typedef void (*ClientNetBroken)(char_t* NetAddr);

/*********************************************************************
 * ServerNetBroken
 *     总线服务器端断开处理方法原型
 * Parameters:
 *     BusName - 总线名称
 * Returns:
 *     无
 */
typedef void (*ServerNetBroken)(char_t* BusName);

/*********************************************************************
 * CeateSoftwareBus
 *    创建软件总线
 * 参数:
 *     BusName - 总线名称
 *     url     - 服务器地址
 *     local   - 是否为局部总线
 * 返回:
 *     =  0 - 正确
 *     <  0 - 错误
 */
int CreateSoftwareBus(const char_t* BusName,const char_t* url,bool local ,ClientNetBroken oFunc);

/*********************************************************************
 * ConnectRemoteSoftwareBus
 *    连接远程软件总线
 * 参数:
 *     server_url - 服务器地址,比如localhost:5101,195.239.208.240:6100,...
 *     BusName    - 总线名称
 * 返回:
 *     =  0 - 正确
 *     <  0 - 错误
 */
int ConnectRemoteSoftwareBus(const char_t*   server_url,const char_t* BusName,ServerNetBroken oFunc);


/*********************************************************************
 * CloseSoftwareBus
 *     关闭总线
 * 参数:
 *     BusName - 总线名称
 * Returns:
 *     = 0 -正确
 *     < 0 -错误
 */
int CloseSoftwareBus(char_t* BusName);

/*********************************************************************
 * CreateBusBit
 *    创建总线位表
 * Parameters:
 *     BusName       - 总线名称
 *     BitID         - 总线位ID
 *     intLength     - 记录固定长度
 *     nFields       - 字段数量
 *     fields        - 字段定义
 *     MaxRec        - 保留的最大记录数
 *     dblPercent    - 当超过最大记录数十删除记录百分比
 * Returns:
 *     = 0 -正确
 *     < 0 -错误
 */
int CreateBusBit(char_t* BusName, char_t* BitID, int intLength,int nFields, BitFieldDescriptor* fields,int MaxRec = 100,double dblPercent = 0.2);

/*********************************************************************
 * CreateBusBitByXML
 *    通过XML创建总线位
 * Parameters:
 *     BusName       - 总线名称
 *     xml            - XML描述文件或者xml本身
 * Returns:
 *     = 0 -正确
 *     < 0 -错误
 */
int CreateBusBitByXML(char_t* BusName, char_t* xml);
/*********************************************************************
 * DropBusBit
 *    删除总线位
 * Parameters:
 *     BusName       - 总线名称
 *     BitID         - 总线位ID
 * Returns:
 *     = 0 -正确
 *     < 0 -错误
 */
int DropBusBit(char_t* BusName, char_t* BitID);

/*********************************************************************
 * GetBitDescribe
 *     取位定义
 * Parameters:
 *     BusName       - 总线名称
 *     BitID         - 总线位ID
 *     fields        - 字段描述
 * Returns:
 *     > 0 -字段数
 *     = 0 - 错误
 */
int GetBitDescribe(char_t* BusName, char_t* BitID, BitFieldDescriptor** fields);

//总线位描述
typedef struct SoftwareBusBitDescriptor 
{
    char_t   BitID[50];
} SoftwareBusBitDescriptor;

/*********************************************************************
 * GetAllBits
 *     返回指定总线的所有位定义
 * Parameters:
 *     BusName   - 总线名称
 *     Bits      - 返回位定义
 * Returns:
 *     >= 0 - 总线位数量
 *     < 0  - 错误
 */
int GetAllBits(char_t* BusName, SoftwareBusBitDescriptor** Bits);

/*********************************************************************
 * BusBitProc
 *     总线位数据处理方法原型
 * Parameters:
 *     BusName        - 总线名称
 *     BitID          - 总线位ID
 *     SubcriberID    - 订阅者D
 *     intRecCount    - 等待处理记录数
 * Returns:
 *     无
 */
typedef void (*BusBitProc)(char_t* BusName,char_t* BitID,char_t* SubcriberID, int intRecCount);

/*********************************************************************
 * AddBusBitSubcriber
 *     增加数据消费者
 * Parameters:
 *     BusName    - 总线名称
 *     BitID      - 总线位ID
 *     Subcriber  - 消费者名称
 *     Method     - 消费者数据处理回调方法
 * Returns:
 *     = 0  - 成功
 *     < 0  - 错误
 */
int AddBusBitSubcriber(char_t* BusName,char_t* BitID, char_t* Subcriber, BusBitProc Method);

/*********************************************************************
 * RemoveBusBitSubcriber
 *     删除数据消费者
 * Parameters:
 *     BusName    - 总线名称
 *     BitID      - 总线位ID
 *     Subcriber  - 消费者名称
 * Returns:
 *     = 0  - 成功
 *     < 0  - 错误
 */
int RemoveBusBitSubcriber(char_t* BusName,char_t* BitID, char_t* Subcriber);

/*********************************************************************
 * PostBitData
 *     不等待返回发送位数据
 * Parameters:
 *     BusName       - 总线名称
 *     BitID         - 总线位ID
 *     BitData       - 总线位数据
 *     DataLength    - 记录数
 * Returns:
 *     = 0  - 成功
 *     < 0  - 错误
 */
int PostBitData(char_t* BusName,char_t* BitID, void* BitData, int DataLength);

/*********************************************************************
 * FreeMemory
 *     释放软件总线分配的内存
 * Parameters:
 *     data      - 内存对象
 * Returns:无
 */
void FreeMemory(void* data);

/*********************************************************************
 * StartSoftwareBus
 *     启动软件总线
 * Parameters:
 * Returns:无
 */
bool StartSoftwareBus();

/*********************************************************************
 * StopSoftwareBus
 *     停止软件总线
 * Parameters:
 * Returns:无
 */
void StopSoftwareBus();

/*********************************************************************
 * CopyBitData
 *     拷贝总线位数据
 * Parameters:
 *     BusName       - 总线名称
 *     BitID         - 总线位ID
 *     Subcriber  - 订阅ID
 *     BitData    - 总线位数据
 * Returns:记录数量
 */
int CopyBitData(char_t* BusName,char_t* BitID, char_t* Subcriber,void*& BitData);
/*********************************************************************
 * FreeBitData
 *     释放总线位数据所占用内存
 * Parameters:
 *     BusName       - 总线名称
 *     BitID         - 总线位ID
 *     BitData    - 总线位数据
 *     intRec     - 记录数量
 * Returns:无
 */
void FreeBitData(char_t* BusName,char_t* BitID, void* BitData,int intRec);
/*********************************************************************
* CopyExistingBitData
*     拷贝已有总线位数据
* Parameters:
*     BusName    - 总线名称
*     BitID      - 总线位ID
*     InData     - 已有总线位数据
*     intRec     - 记录数量
*     OutData    - 新总线位数据
* Returns:无
*/
void CopyExistingBitData(char_t* BusName,char_t* BitID, void* InData,int intLength,void*& OutData);

/*********************************************************************
* CreateBit4Xml
*     根据xml文件创建总线和总线位
* Parameters:
*     fileName    - xml描述文件
xml文件格式
<BusInst>
	<Inst InstName="www" busName="name1" bLocal="1" Host="192.192.192.20" Port="555">
		<BusInfo busName="name1">
			<BusBit BitName="www">
				<BitInfo 字段类型="0" 长度="0" 字段名称="Text: 1 " 变长字段长度的字段名称="" 扩展结构="" />
			</BusBit>
		</BusInfo>
	</Inst>
</BusInst>
* Returns:
*     = 0  - 成功
*     < 0  - 错误
*/
int CreateBit4Xml(char_t* fileName);
#ifdef __cplusplus
}
#endif

typedef sftb_bool_t		sf_bool;
typedef sftb_int1_t		sf_int1;
typedef sftb_nat1_t		sf_nat1;
typedef sftb_int2_t		sf_int2;
typedef sftb_nat2_t     sf_nat2;
typedef sftb_real4_t	sf_real4;
typedef sftb_real8_t	sf_real8;
typedef sftb_time_t		sf_time;
typedef sftb_int4_t		sf_int4;
typedef sftb_nat4_t		sf_nat4;
typedef sftb_int8_t		sf_int8;
typedef sftb_nat8_t     sf_nat8;
#define sf_CreateSoftwareBus			CreateSoftwareBus			
#define	sf_ConnectRemoteSoftwareBus		ConnectRemoteSoftwareBus	
#define	sf_CloseSoftwareBus				CloseSoftwareBus			
#define	sf_CreateBusBit					CreateBusBit				
#define	sf_CreateBusBitByXML			CreateBusBitByXML			
#define	sf_DropBusBit					DropBusBit					
#define	sf_GetBitDescribe				GetBitDescribe				
#define	sf_GetAllBits					GetAllBits					
#define	sf_BusBitProc					BusBitProc					
#define	sf_AddBusBitSubcriber			AddBusBitSubcriber			
#define	sf_RemoveBusBitSubcriber		RemoveBusBitSubcriber		
#define	sf_PostBitData					PostBitData					
#define	sf_FreeMemory					FreeMemory					
#define	sf_StartSoftwareBus				StartSoftwareBus			
#define	sf_StopSoftwareBus				StopSoftwareBus				
#define	sf_CopyBitData					CopyBitData					
#define	sf_FreeBitData					FreeBitData		
#define sf_CopyExistingBitData			CopyExistingBitData
#define sf_CreateBit4Xml				CreateBit4Xml


#endif

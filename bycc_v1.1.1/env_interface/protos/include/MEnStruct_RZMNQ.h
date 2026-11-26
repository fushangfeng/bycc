/**************************************************************************
**名    称:	可重构zb模型（模拟器模式）数据结构												**
**用    途:	用于定义对外报送数据结构					**
**版 本 号:  V0.1	**
**版    本:	2024.12.17  zm											**
*************************************************************************/


#ifndef MEN_STRUCT_MNQ
#define MEN_STRUCT_MNQ

#pragma pack(1)

typedef struct _ModelBus_sMNQ_OUTDATA
{
	char*	sRID;           //身份字符串	 
	int     EquipID;		//装备ID
	int     EquipType;		//装备类型，1-UHF；2—L；3-XKu
	int     DataType;       //数据类型,有效报文字典表，待后续统一编号
	int     nDataLen;	    //数据长度
	char*   pData;          //有效数据报文

	/*重载构造函数*/
	_ModelBus_sMNQ_OUTDATA()
	{
		sRID          = NULL;
		EquipID       = 0;
		EquipType     = 0;
		DataType      = 0;
		nDataLen      = 0;
		pData         = NULL;
	}

	/*重载析构函数*/
	~_ModelBus_sMNQ_OUTDATA()
	{
	    SW_Free_Char(sRID);
		SW_Free_Char(pData);
	}

	/*重载拷贝构造函数*/
	_ModelBus_sMNQ_OUTDATA(const _ModelBus_sMNQ_OUTDATA &equip)
	{
		*this = equip;
	}

	/*重载=*/
	_ModelBus_sMNQ_OUTDATA& operator=(const _ModelBus_sMNQ_OUTDATA& theStruct)
	{
		if (this == &theStruct)
		{
			return *this;
		}
		SW_Malloc_Char(theStruct.sRID,sRID);

		EquipID       = theStruct.EquipID;
		EquipType     = theStruct.EquipType;
		DataType      = theStruct.DataType;
		nDataLen      = theStruct.nDataLen;
		SW_Malloc_Char(theStruct.pData,pData);

		return *this;
	}
}sMNQ_OUTDATA;

#pragma pack()

#endif

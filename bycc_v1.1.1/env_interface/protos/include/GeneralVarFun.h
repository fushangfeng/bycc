// GeneralVarFun.h: interface for the CGeneralFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GENERALVARFUN_H__865120EF_876C_432A_A6E4_1B34D9C81282__INCLUDED_)
#define AFX_GENERALVARFUN_H__865120EF_876C_432A_A6E4_1B34D9C81282__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/**************************************************************
文 件 名:	GeneralVarFun.h
用    途:	常用函数和常量，大家可以共同维护,使用方式如：_GenFuc::_File_GetExeFilePath();
单    位:	中电29所软件部
创 建 人:	yangzs
修 改 人:	
版    本:	2009.03.11
***************************************************************/
#pragma comment(lib, "Netapi32.lib")
#include <math.h>
#include <afxtempl.h>
//***********获取物理地址用*****************
#include <windows.h>
#include <wincon.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <nb30.h>
#include <afxsock.h>


namespace _GenCns
{
////////////////////////////////////////////////常量////////////////////////////////////////////////////
	const CString DateFormat_Str = "%Y-%m-%d %H:%M:%S";
	const CString DateFormat_Db = "YYYY-MM-DD HH24:MI:SS";
	const float EarthRad = 6371;//地球半径(千米)
	const double PI = 3.1415926932384626;
};

namespace _GenFuc  
{
	typedef struct _ASTAT_
	{
		ADAPTER_STATUS adapt;
		NAME_BUFFER NameBuff[ 30 ];
	}ASTAT,*PASTAT;
//************************文件相关****************************
	//逐个创建目录，如果目录存在，则不创建---目录层数不限
	inline 	BOOL _File_CreatDir( CString strDir );
	//获取磁盘可用空间，单位M
	inline 	BOOL _File_GetDiskAviableSpace( CString csDisk , DWORD &dwSpace );
	//获取可执行目录
	inline CString _File_GetExeFilePath();
	//判断文件是否存在
	inline 	BOOL _File_IsFileExist( CString fileName );
	//生成可用的文件名
	inline 	BOOL _File_GetUsableFileName( CString srcFileName, CString &usableFileName );
	//得到给定目录下最晚创建的文件
	inline 	BOOL _File_GetLastFileByPath( CString filePath, CString &fileName, CString filter="*.*" );
	//得到给定目录下所有的文件
	inline 	void _File_GetAllFilesByPath( CString filePath, CStringArray &arFileName, CString filter="*.*"  );

//************************ini相关****************************
	//从配置文件读取一行
	inline 	CString _ini_ReadStringFromIni(LPCSTR lpszFile, LPCSTR lpszSection, LPCSTR lpszKey);
	//获取所有的section名称
	inline 	void _ini_GetAllSectionsFromIni( LPCSTR lpszFile, CStringArray &arSection, CString filter="" );
	//获取所有的key名称
	inline 	void _ini_GetAllKeysFromIni( LPCSTR lpszFile, const CString &section, CStringArray &arKeys, CString filter="" );


//************************CListCtrl****************************
	//获区表格中选中的第一行
	inline 	int _List_GetFirstSelItem( CListCtrl *pList );
	//获取表格中鼠标点击的行		
	inline 	int  _List_GetHitItem( CListCtrl *pList, UINT * pFlags /* = NULL */);
	//获区表格中选中的所有行
	inline void  _List_GetAllSelItem( CListCtrl *pList, CArray<int, int> &arSelItem );
	//获取树上鼠标点击的节点		
	inline HTREEITEM  _Tree_GetHitItem( CTreeCtrl *pTree, UINT * pFlags= NULL /* = NULL */);

//************************常用****************************
	//判断时间是否有效
	inline 	BOOL _Com_IsColeDTValid( COleDateTime dt );
	//判断IP是否有效
	inline 	BOOL _Com_IsIpValid( CString ip );
	//判断是否是数字
	inline 	BOOL _Com_IsNumber( CString str );
//**************************生成唯一ID函数*********************************8
	//获取36位全局唯一ID
	inline CString _GUI_GetGUID36() ;
	//获取24位全局唯一ID
	inline CString _GUI_GetGUID24() ;
//**************************地址有关*********************************8
	//获取本机物理地址
	inline CString _ADR_GetMacAddress();
	//获取本机ip
	inline CString _ADR_GetLocalIpAddress();


};


/**************************************************************
用    途:	逐个创建目录，如果目录存在，则不创建
参    数:	
	strDir[in]:	需要创建的目录
返 回 值:	TRUE-创建成功，FALSE-创建失败
***************************************************************/
BOOL _GenFuc::_File_CreatDir( CString strDir )
{
	// 检查目录是否存在，如不存在则创建目录	
	WIN32_FIND_DATA	FindFileInfo;	// 查找文件信息
	HANDLE			hFindDirFile;	// 文件查找句柄
	CString tempDir,restDir, filename;
	int index;
	restDir = strDir;
	tempDir = restDir.Left( restDir.Find('\\') );
	restDir = restDir.Right( restDir.GetLength() - restDir.Find('\\') - 1 );
	while ( !restDir.IsEmpty() )
	{
		//逐个创建
		index = restDir.Find( '\\' );
		if( index!=-1 )
		{

			tempDir += "\\";
			filename = restDir.Left( index );
		   tempDir += restDir.Left( index );
		   restDir = restDir.Right( restDir.GetLength() - index -1 );
		}
		else
		{
			//最后一个目录
			if( restDir.IsEmpty() )
			{
				break;
			}
			filename = restDir;
			tempDir += "\\";
			tempDir += restDir;
			restDir = "";
		}

		if (!((hFindDirFile = ::FindFirstFile(tempDir, &FindFileInfo)) != (HANDLE) INVALID_HANDLE_VALUE &&
			(FindFileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )&&
			_stricmp(FindFileInfo.cFileName, filename) == 0))
		{
			// 创建目录
			if (!::CreateDirectory(tempDir, (LPSECURITY_ATTRIBUTES) NULL))
			{
				::MessageBox(NULL,"加载目录创建错误，不能继续运行！", "错误信息", MB_OK | MB_ICONSTOP);	
				return false;
			}
		}
	}
	return true;
}


/**************************************************************
用    途:	获取磁盘可用空间，单位M
参    数:	
	csDisk[in]:		盘符
	dwSpace[out]:	剩余的空间
返 回 值:	TRUE-成功，FALSE-失败
***************************************************************/
BOOL _GenFuc::_File_GetDiskAviableSpace( CString csDisk , DWORD &dwSpace )
{
	if( csDisk.GetLength()<1 )
		return FALSE;
	ULARGE_INTEGER aviableBytes;
    ULARGE_INTEGER totalBytes;
    ULARGE_INTEGER freeBytes;
	CString disk;
	disk.Format("%c:", csDisk[0] );
    GetDiskFreeSpaceEx("e:",&aviableBytes,&totalBytes,&freeBytes );
	dwSpace = (DWORD)(aviableBytes.QuadPart/(1024*1024));
	return TRUE;
}

/**************************************************************
用    途:	获取可执行目录
参    数:	无
返 回 值:	可执行目录
***************************************************************/
CString _GenFuc::_File_GetExeFilePath()
{ 
	CString fullpath;
	fullpath=_T("");
	char path[256];	
	::GetModuleFileName(NULL,path,256);
	fullpath=(CString)path;
	fullpath=fullpath.Left((fullpath.ReverseFind('\\')+1)) ;	
	return fullpath;
}

/**************************************************************
用    途:	判断文件是否存在
参    数:	无
返 回 值:	TRUE-存在，FALSE-不存在
***************************************************************/
BOOL _GenFuc::_File_IsFileExist( CString fileName )
{
	CFileFind fileFind;
	return  fileFind.FindFile(fileName);
}


/**************************************************************
用    途:	生成可用的文件名
参    数:	
	srcFileName[in]:		原始文件名，如：name.txt
	usableFileName[out]:	可用的文件名，如：name_1.txt
返 回 值:	TRUE-成功，FALSE-失败
***************************************************************/
BOOL _GenFuc::_File_GetUsableFileName( CString srcFileName, CString &usableFileName )
{
	if( srcFileName.Find('\\')==-1 || srcFileName[srcFileName.GetLength()-1] == '\\' )
	{
		return FALSE;
	}
	if( !_File_IsFileExist( srcFileName ) )//不存在该文件名,该文件名可用
	{
		usableFileName = srcFileName;
		return TRUE;
	}
	
	int index = 1;
	CString shortFileName, filePath;
	CString tempFileName;
	shortFileName = srcFileName.Right( srcFileName.GetLength()-srcFileName.ReverseFind('\\')-1 );
	filePath = srcFileName.Left( srcFileName.ReverseFind('\\') + 1 );
	if( shortFileName.IsEmpty() )
	{
		return FALSE;
	}
	while( 1 )
	{
		if( shortFileName.Find('.')!=-1 )
		{
			tempFileName.Format("%s_%d%s",shortFileName.Left( shortFileName.Find('.') ), index++,\
				shortFileName.Right(shortFileName.GetLength() -shortFileName.ReverseFind('.')) );
		}
		else
		{
			tempFileName.Format("%s%d",shortFileName, index++ );
		}
		if( !_File_IsFileExist( filePath+tempFileName ) )
		{
			break;
		}
	}

	usableFileName = filePath+tempFileName;
	return TRUE;
}

/**************************************************************
用    途:	获取修改时间最晚的文件名称
参    数:	
	filePath[in]:		目录
	filter[in]:			过滤符，默认(*.*)
	fileName[out]:		文件名称
返 回 值:	TRUE-成功，FALSE-失败
***************************************************************/
BOOL _GenFuc::_File_GetLastFileByPath( CString filePath, CString &fileName, CString filter  )
{
	CStringArray arFileName;
	_File_GetAllFilesByPath( filePath, arFileName, filter );
	if( arFileName.GetSize()<=0 )
		return FALSE;
	fileName = arFileName.GetAt(0);
	
	CFileStatus fileSta;
	CTime lastTime=CTime( 0 );
	if( CFile::GetStatus( fileName, fileSta ) )
		lastTime = fileSta.m_ctime;
	for( int nFile=1; nFile<arFileName.GetSize(); nFile++ )
	{
		if( CFile::GetStatus( arFileName[nFile], fileSta ) && fileSta.m_ctime>lastTime ) 
		{
			fileName = arFileName[nFile];
			lastTime = fileSta.m_ctime;
		}
	}
	return TRUE;
}


/**************************************************************
用    途:	获取给定目录下的所有文件名称
参    数:	
	filePath[in]:		目录
	filter[in]:			过滤符，默认(*.*)
	arFileName[out]:	文件名称数组
返 回 值:	无
***************************************************************/
void _GenFuc::_File_GetAllFilesByPath( CString filePath, CStringArray &arFileName, CString filter )
{
	arFileName.RemoveAll();
	CFileFind finder;
	CString strWildcard(filePath);
	strWildcard += "\\"+filter;
	
	BOOL bWorking = finder.FindFile(strWildcard);
	if( !bWorking )
		return ;
	
	CString tempFileName;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		
		if ( finder.IsDots()||finder.IsDirectory() )
		{//非文件
			continue;
		}
		arFileName.Add( finder.GetFilePath() );	   
	}
	
	finder.Close();

}

/**************************************************************
用    途:	读取ini项
参    数:	
	lpszFile[in]:		文件名称
	lpszSection[in]:	section
	lpszKey[in]:		key
返 回 值:	值
***************************************************************/
CString _GenFuc::_ini_ReadStringFromIni(LPCSTR lpszFile, LPCSTR lpszSection, LPCSTR lpszKey)
{
	char cReturn[256];
	::GetPrivateProfileString(lpszSection, lpszKey, "", cReturn, 255, lpszFile);
	CString strVal = cReturn;
	return strVal;
}

/**************************************************************
用    途:	获取ini文件中所有的section名称
参    数:	
	lpszFile[in]:		文件名称
	filter[in]:			过滤符，默认为空
	arSection[out]:		section名称数组
返 回 值:	无
***************************************************************/
void _GenFuc::_ini_GetAllSectionsFromIni( LPCSTR lpszFile, CStringArray &arSection, CString filter )
{
	char buf[5000];
	long bufLen = 5000;
	memset( buf, 0, bufLen );
	int index=0;
	GetPrivateProfileString( NULL,NULL,"",buf,bufLen, lpszFile );
	CString section( buf );	
	while( !section.IsEmpty() )
	{
		if( (!filter.IsEmpty()&&section.Find( filter )!=-1) || filter.IsEmpty() )
			arSection.Add( section );

		index += section.GetLength()+1;
		section = CString( buf+index );
	}
}

/**************************************************************
用    途:	获取所有的key名称
参    数:	
	lpszFile[in]:		文件名称
	section[in]:		section名称
	filter[in]:			过滤符，默认为空
	arKeys[out]:		文件名称数组
返 回 值:	无
***************************************************************/
void _GenFuc::_ini_GetAllKeysFromIni( LPCSTR lpszFile, const CString &section, CStringArray &arKeys, \
					   CString filter )
{
	char buf[5000];
	long bufLen = 5000;
	memset( buf, 0, bufLen );
	int index=0;
	GetPrivateProfileString( section,NULL,"",buf,bufLen, lpszFile );
	CString key( buf );	
	while( !key.IsEmpty() )
	{
		if( (!filter.IsEmpty()&&key.Find( filter )!=-1) || filter.IsEmpty() )
			arKeys.Add( key );

		index += key.GetLength()+1;
		key = CString( buf+index );
	}
}

/**************************************************************
用    途:	获区表格中选中的第一行
参    数:	
	pList[in]:		列表指针
返 回 值:	选中的项，－1为为找到选择的项
***************************************************************/			
int _GenFuc::_List_GetFirstSelItem( CListCtrl *pList )
{
	POSITION pos = pList->GetFirstSelectedItemPosition();
	int nItem = pList->GetNextSelectedItem( pos );
	return nItem;
}

/**************************************************************
用    途:	获区表格中选中的所有行
参    数:	
	pList[in]:		列表指针
	pFlags[out]:	选中的项
返 回 值:	无
***************************************************************/			
void  _GenFuc::_List_GetAllSelItem( CListCtrl *pList, CArray<int, int> &arSelItem )
{
	POSITION pos = pList->GetFirstSelectedItemPosition();
	while( pos )
	{
		arSelItem.Add(pList->GetNextSelectedItem( pos )) ;
	}
}

/**************************************************************
用    途:	获取表格中鼠标点击的行
参    数:	
	pList[in]:		列表指针
	pFlags[in]:		标识
返 回 值:	点击的项
***************************************************************/			
int _GenFuc:: _List_GetHitItem( CListCtrl *pList, UINT * pFlags /* = NULL */)
{
	if( !pList->m_hWnd )
	{
		return -1;
	}
	CPoint Point;
#if 1
	::GetCursorPos(&Point);
	ScreenToClient( pList->m_hWnd, &Point);
#else
	GetCursorPos(&Point);
	ClientToScreen( pList->m_hWnd, &Point);
#endif
	UINT uFlags;
	int ItemIndex = pList->HitTest(Point, &uFlags);
	if (pFlags != NULL)
		* pFlags = uFlags;
	
	return ItemIndex;
}

/**************************************************************
用    途:	获取树上鼠标点击的节点
参    数:	
	pTree[in]:		树指针
	pFlags[in]:		标识
返 回 值:	点击的项
***************************************************************/		
HTREEITEM  _GenFuc::_Tree_GetHitItem( CTreeCtrl *pTree, UINT * pFlags /* = NULL */)
{
	if( !pTree->m_hWnd )
	{
		return NULL;
	}
	CPoint Point;
#if 1
	::GetCursorPos(&Point);
	ScreenToClient( pTree->m_hWnd, &Point);
#else
	GetCursorPos(&Point);
	ClientToScreen( pTree->m_hWnd, &Point);
#endif
	UINT uFlags;
	HTREEITEM hTreeItem = pTree->HitTest(Point, &uFlags);
	if (pFlags != NULL)
		* pFlags = uFlags;
	
	return hTreeItem;
}


/**************************************************************
用    途:	判断IP是否有效
参    数:	
	ip[in]:		ip字符串
返 回 值:	TRUE-有效, FALSE-无效
***************************************************************/
BOOL _GenFuc::_Com_IsIpValid( CString ip )
{
	int ind=0;
	int count = 3;
	long ipValue[4];
	while( count-- )
	{
		ind = ip.Find(".");
		if( -1==ind )
			return FALSE;
		CString str;
		str = ip.Left( ind );
		if( !_Com_IsNumber(str) || atol(str)<0 || atol(str)>255 )
			return FALSE;
		ip = ip.Right( ip.GetLength()-ind-1 );
		ipValue[4-count-2] = atol( str );
	}
	ipValue[3] = atol( ip );
	if( !_Com_IsNumber(ip) )
		return FALSE;

	if( 0==ipValue[0])
		return FALSE;
	return TRUE;
}


/**************************************************************
用    途:	判断是否是数字
参    数:	
	str[in]:		需要判断的字符串
返 回 值:	TRUE-是数字, FALSE-不是数字
***************************************************************/
BOOL _GenFuc::_Com_IsNumber( CString str )
{
	if( str.IsEmpty() )
		return FALSE;
	for( int nCh=0; nCh<str.GetLength(); nCh++ )
	{
		if( !isdigit( str[nCh] ) )
			return FALSE;
	}
	return TRUE;	
}

//**************************生成唯一ID函数*********************************8
//获取本机物理地址
CString _GenFuc::_ADR_GetMacAddress()
{
	CString macAddr;
	ASTAT Adapter;
	NCB Ncb;
	UCHAR uRetCode;
	LANA_ENUM lenum;
	
	memset( &Ncb, 0, sizeof(Ncb) );
	Ncb.ncb_command = NCBENUM;
	Ncb.ncb_buffer = (UCHAR *)&lenum;
	Ncb.ncb_length = sizeof(lenum);
	uRetCode = Netbios( &Ncb );
	
	if( lenum.length<=0 )
		return "";
	memset( &Ncb, 0, sizeof(Ncb) );
	Ncb.ncb_command = NCBRESET;
	Ncb.ncb_lana_num = lenum.lana[0];
	
	uRetCode = Netbios( &Ncb );
	
	memset( &Ncb, 0, sizeof (Ncb) );
	Ncb.ncb_command = NCBASTAT;
	Ncb.ncb_lana_num = lenum.lana[0];
	
	strcpy( (char*)Ncb.ncb_callname,  "*               " );
	Ncb.ncb_buffer = (unsigned char *) &Adapter;
	Ncb.ncb_length = sizeof(Adapter);
	
	uRetCode = Netbios( &Ncb );
	macAddr.Format("%02X%02X%02X%02X%02X%02X",Adapter.adapt.adapter_address[0],
		Adapter.adapt.adapter_address[1],
		Adapter.adapt.adapter_address[2],
		Adapter.adapt.adapter_address[3],
		Adapter.adapt.adapter_address[4],
		Adapter.adapt.adapter_address[5]);
	return macAddr;
}

//获取本机ip
CString _GenFuc::_ADR_GetLocalIpAddress()
{
	AfxSocketInit(NULL);
    WORD wVersionRequested;
    WSADATA wsaData;
    char name[255];
    CString ip;
    PHOSTENT hostinfo;
    wVersionRequested = MAKEWORD( 2, 0 );

    if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
    {

          if( gethostname ( name, sizeof(name)) == 0)
          {
                if((hostinfo = gethostbyname(name)) != NULL)
                {
                      ip = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                }
          }
        
          WSACleanup( );
    } 
	return ip;
}

//生成24位唯一ID
CString _GenFuc::_GUI_GetGUID24()
{
	/*
	CString guid;
//	guid = GetMacAddress();
	SYSTEMTIME systime;
	GetSystemTime( &systime );
	CTime cTime( systime );
	//获取当前时间
	CString tempStr;
	long lTime = (long)cTime.GetTime();
	tempStr.Format("%010ld%03d", lTime, systime.wMilliseconds );
	guid += tempStr;
	
	//生成两个随机数
	int randNum;
	randNum = rand();
	tempStr.Format("%05d", randNum%100000 );
	guid += tempStr;
	randNum = rand();
	tempStr.Format("%05d", randNum%100000 );
	guid += tempStr;
	*/
	CString strGuid = _GUI_GetGUID36();
	return strGuid.Left(24);
}	
//生成36位唯一ID
CString _GenFuc::_GUI_GetGUID36()
{
	GUID guid;
	CoCreateGuid( &guid );
	CString strGuid;
	strGuid.Format("%08x%04x%04x%02x%02x%02x%02x%02x%02x%02x%02x", guid.Data1, guid.Data2, guid.Data3, \
		guid.Data4[0],guid.Data4[1],guid.Data4[2],guid.Data4[3],guid.Data4[4],guid.Data4[5],guid.Data4[6],guid.Data4[7]);
	return strGuid;
}


#endif // !defined(AFX_GENERALVARFUN_H__865120EF_876C_432A_A6E4_1B34D9C81282__INCLUDED_)



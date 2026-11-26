
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the FILEENCRYPE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// FILEENCRYPE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef FILEENCRYPE_EXPORTS
#define FILEENCRYPE_API __declspec(dllexport)
#else
#define FILEENCRYPE_API __declspec(dllimport)
#endif

#define FER_OPEN_FILE  1
#define FER_READ_FILE  2
#define FER_WRITE_FILE 3
#define FER_MEMORY     4
#define FER_PASSWD	   5

EXTERN_C
{

FILEENCRYPE_API LPSTR WINAPI FE_Load(LPCTSTR pszFilePathName, LPCSTR pszKey, DWORD* pLen);

FILEENCRYPE_API BOOL WINAPI FE_Save(LPCTSTR pszFilePathName, LPCSTR pszData, UINT nLen, LPCSTR pszKey);

FILEENCRYPE_API void WINAPI FE_Free(LPSTR pszBuffer);

FILEENCRYPE_API UINT WINAPI FE_DecryptBuffer(CHAR* pBuf, UINT nCount);

FILEENCRYPE_API CHAR* WINAPI FE_EncryptBuffer(CHAR* pBuf, UINT* nCount);

};
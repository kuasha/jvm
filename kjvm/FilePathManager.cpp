#include "StdAfx.h"
#include "FilePathManager.h"
#include "shlwapi.h"
#pragma comment(lib,"shlwapi.lib")

FilePathManager::FilePathManager(void)
{
}

FilePathManager::~FilePathManager(void)
{
}

BOOL FilePathManager::GetAbsolutePath(CString strRelativePath, CString& strAbsolutePath)
{
	TCHAR path[MAX_PATH+1];

	GetCurrentDirectory(MAX_PATH, path);

	strAbsolutePath = path+(_T("\\")+strRelativePath);

	if(!PathFileExists(strAbsolutePath)) 
		return FALSE;

	return TRUE;
}

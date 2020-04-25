#pragma once

class FilePathManager
{
public:
	FilePathManager(void);
public:
	~FilePathManager(void);
public:
	BOOL GetAbsolutePath(CString strRelativePath, CString& strAbsolutePath);
};

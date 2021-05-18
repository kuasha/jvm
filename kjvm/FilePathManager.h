#pragma once
#include <string>

class FilePathManager
{
public:
	FilePathManager(void);
public:
	~FilePathManager(void);
public:
	bool GetAbsolutePath(std::string strRelativePath, std::string& strAbsolutePath);
};

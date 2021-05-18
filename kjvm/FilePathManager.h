#pragma once
#include <string>
#include <vector>

class FilePathManager
{
public:
	FilePathManager(void);
public:
	~FilePathManager(void);
public:
	bool GetAbsolutePath(std::string strRelativePath, std::string& strAbsolutePath, std::vector<std::string> &classRoots);
};

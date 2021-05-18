#include "FilePathManager.h"
#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

FilePathManager::FilePathManager(void)
{
}

FilePathManager::~FilePathManager(void)
{
}

bool FilePathManager::GetAbsolutePath(std::string strRelativePath, std::string& strAbsolutePath, std::vector<std::string> &classRoots)
{
	fs::path p = strRelativePath;
	strAbsolutePath = fs::absolute(p);

	if(fs::exists(p))
	{
		return true;
	}
	else if(p.is_absolute())
	{
		return false;
	}

	for (std::string& name: classRoots)
	{
   	   fs::path cp(name);
		cp.append(strRelativePath);
		if(fs::exists(cp)) 
		{
			strAbsolutePath = fs::absolute(cp);
			return true;
		}
    }

	return false;
}

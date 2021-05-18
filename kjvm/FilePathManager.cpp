#include "FilePathManager.h"
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

FilePathManager::FilePathManager(void)
{
}

FilePathManager::~FilePathManager(void)
{
}

bool FilePathManager::GetAbsolutePath(std::string strRelativePath, std::string& strAbsolutePath)
{
	fs::path p = strRelativePath;

	strAbsolutePath = fs::absolute(p);

	if(!fs::exists(p)) 
		return false;

	return true;
}

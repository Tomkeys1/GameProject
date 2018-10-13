
#pragma once
//EXTERNAL INCLUDES
#include <vector>
#include <string>
//INTERNAL INCLUDES
#include "typedefs/types.h"
#include "typedefs/winfile.h"

class Filesystem
{
public:
	Filesystem();

	void ListDirectories(const char* startPath, std::vector<std::string>& temp);
	std::string DirectoryPath(const char* directoryName);
	std::string FileInDirectory(const char* directoryName, const char* fileName);
private:
	std::vector<std::string> FilesInDirectory(const char* directoryName);
	std::vector<std::string> directories;
	std::vector<std::string> files;
};
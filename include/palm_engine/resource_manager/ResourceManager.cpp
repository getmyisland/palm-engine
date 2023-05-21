#include "ResourceManager.h"

#include <palm_engine/logger/Logger.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include <direct.h>
#define GET_CURRENT_DIR _getcwd

std::string PalmEngine::ResourceManager::GetProjectRootDirectory()
{
	char buff[FILENAME_MAX]; // Create string buffer to hold path
	char* content = GET_CURRENT_DIR(buff, FILENAME_MAX);
	if (content != NULL)
	{
		return std::string(content);
	}
	else
	{
		PE_LOGGER_LOG(PE_WARNING, "Could not get root directory");
		return std::string("");
	}
}

std::string PalmEngine::ResourceManager::GetFileContentAsString(std::string& filePath)
{
	std::ifstream file;

	// Ensure ifstream objects can throw exceptions
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// Open files
		file.open(filePath);
		std::stringstream fileStream;
		// Read file's buffer contents into streams
		fileStream << file.rdbuf();
		// Close file handlers
		file.close();
		// Convert stream into string
		return fileStream.str();
	}
	catch (std::ifstream::failure e)
	{
		PE_LOGGER_LOG(PE_ERROR, "FILE_NOT_SUCCESFULLY_READ::PATH::" + filePath);
		return std::string("");
	}
}
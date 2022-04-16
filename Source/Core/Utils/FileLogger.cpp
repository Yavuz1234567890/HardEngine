#include "FileLogger.h"
#include "Core/Time/Time.h"
#include "Core/File/FileSystem.h"

#include <string.h>

FileLogger::FileLogger()
{

}

FileLogger::~FileLogger()
{

}

void FileLogger::Init()
{
	String path = FileSystem::GetCurrentDir().PushBack("log.txt");
	if (!FileSystem::IsFile(path))
	{
		m_LogFile.Open(File::WRITABLE, path.CData());
	}
}

void FileLogger::Print(const char* out)
{
	m_LogFile.Write(out, strlen(out));
	m_LogFile.Write("\n", 1);
}

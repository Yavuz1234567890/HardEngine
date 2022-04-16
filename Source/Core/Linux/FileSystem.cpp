#include "Core/File/FileSystem.h"

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <stdio.h>
#include <cerrno>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

bool FileSystem::CreateFolder(const String& path)
{
	return mkdir(path.CData(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1;
}

void FileSystem::RemoveFolder(const String& path)
{
	return rmdir(path.CData()) != 0;
}

bool FileSystem::IsFolder(const String& path)
{
	struct stat status;
	return ((stat(path.CData(), &status) == 0) && (((status.st_mode) & S_IFMT) == S_IFDIR));
}

void FileSystem::RemoveFile(const String& path)
{
	return unlink(path.CData()) == 0;
}

bool FileSystem::IsFile(const String& path)
{
	struct stat status;
	return ((stat(path.CData(), &status) == 0) && (((status.st_mode) & S_IFMT) != S_IFDIR));
}

bool FileSystem::FileCopy(const String& file, const String& dst)
{
	String d = file;
	if (Path::HasDirectory(d))
	{
		Path::ClearDirectory(d);
	}
	d = Path::MakePath(dst).PushBack(d);
	FILE* src = fopen(file.CData(), "rb");
	if (!src)
	{
		fclose(src);
		return false;
	}
	FILE* dst = fopen(d.CData(), "wb");
	if (!dst)
	{
		fclose(dst);
		return false;
	}
	long position = ftell(src);
	fseek(src, 0, SEEK_END);
	size_t size = (size_t)ftell(src);
	fseek(src, position, SEEK_SET);
	String src;
	src.Resize(size);
	fread(src.Data(), size, 1, src);
	fwrite(src.CData(), src.Size(), 1, dst);
	return true;
}

bool FileSystem::RelocateFile(const String& file, const String& dst)
{
	return rename(file.CData(), dst.CData()) == 0;
}

void FileSystem::GetChildItems(Vector<String>& dst, const String& path)
{
	String dir = Path::GetDirectory(path);
	DIR* root = opendir(path.CData());
	struct stat status;
	struct dirent* source;
	String srcFile;
	if (!root)
	{
		return;
	}
	while ((entry = readdir(dir)) != NULL)
	{
		srcFile = source->d_name;
		if (srcFile == '.' || srcFile == "..")
		{
			continue;
		}
		srcFile = String(dir).PushBack(srcFile);
		stat(srcFile.CData(), &status);
		if(((tmp.st_mode) & S_IFMT) == S_IFDIR)
		{
			dst.PushBack(srcFile.PushBack("/"));
		}
		else
		{
			dst.PushBack(srcFile);
		}
	}
}

void FileSystem::ChangeCurrentDir(const String& path)
{
	chdir(path.CData());
}

String FileSystem::GetCurrentDir()
{
	char buffer[280];
	getcwd(buffer, 280);
	return Path::MakePath(String(buffer));
}

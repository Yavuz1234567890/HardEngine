#include "Core/File/FileSystem.h"
#include "Core/Core/PlatformDetection.h"

#include <windows.h>
#include <stdio.h>

bool FileSystem::CreateFolder(const String& path)
{
	return CreateDirectoryA(path.CData(), NULL);
}

void FileSystem::RemoveFolder(const String& path)
{
	RemoveDirectoryA(path.CData());
}

bool FileSystem::IsFolder(const String& path)
{
	DWORD dwAttrib = GetFileAttributes(path.CData());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void FileSystem::RemoveFile(const String& path)
{
	DeleteFileA(path.CData());
}

bool FileSystem::IsFile(const String& path)
{
	DWORD dwAttrib = GetFileAttributes(path.CData());
	return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

bool FileSystem::FileCopy(const String& file, const String& dst)
{
	String d = file;
	if (Path::HasDirectory(d))
	{
		Path::ClearDirectory(d);
	}
	if (CopyFile(file.CData(), Path::MakePath(dst).PushBack(d).CData(), TRUE) == false)
	{
		return false;
	}
	FILETIME ft;
	SYSTEMTIME st;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	HANDLE handle = CreateFile(file.CData(), GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFileTime(handle, (LPFILETIME)NULL, (LPFILETIME)NULL, &ft);
	CloseHandle(handle);
	return true;
}

bool FileSystem::RelocateFile(const String& file, const String& dst)
{
	return MoveFileEx(file.CData(), dst.CData(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED) != FALSE;
}

void FileSystem::GetChildItems(Vector<String>& dst, const String& path)
{
	String dir = Path::GetDirectory(path);
	WIN32_FIND_DATA source;
	HANDLE file = FindFirstFile(path.CData(), &source);
	String srcFile;
	if (file)
	{
		do
		{
			srcFile = source.cFileName;
			if (srcFile == '.' || srcFile == "..")
			{
				continue;
			}
			srcFile = String(dir).PushBack(srcFile);
			if (source.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				dst.PushBack(srcFile.PushBack("/"));
			}
			else
			{
				dst.PushBack(srcFile);
			}
		} while (FindNextFile(file, &source));
		FindClose(file);
	}
}

void FileSystem::ChangeCurrentDir(const String& path)
{
	SetCurrentDirectoryA(path.CData());
}

String FileSystem::GetCurrentDir()
{
	WCHAR dir[280];
	GetCurrentDirectoryW(280, dir);
	return Path::MakePath(String(dir));
}

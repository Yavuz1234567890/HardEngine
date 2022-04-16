#include "Path.h"

String Path::GetExtension(const String& path)
{
	const char* cpath = path.CData();
	do
	{
		++cpath;
	} while (*cpath != '.');
	if (*cpath == 0)
	{
		return "No Path";
	}
	return String(cpath);
}

String Path::GetDirectory(const String& path)
{
	const char* end = path.CData();
	UInt64 count = 0;
	do
	{
		++end;
		++count;
	} while (*end != '/');
	if (*end == 0)
	{
		return "./";
	}
	return String("./").PushBack(path.SubString(0, count + 1));
}

String Path::GetBaseName(const String& path)
{
	const char* begin = path.CData() + path.Size();
	UInt64 dirStart = 0;
	UInt64 extStart = 0;
	do
	{
		++dirStart;
		--begin;
	} while (*begin != '/');
	do
	{
		++extStart;
		++begin;
	} while (*begin != '.');
	return path.SubString(path.Size() - dirStart + 1, extStart - 1);
}

bool Path::HasDirectory(const String& path)
{
	UInt64 size = path.Size();
	const char* end = path.CData() + size;
	do
	{
		--end;
		--size;
	} while (*end);
	return size > 0;
}

void Path::ClearDirectory(String& path)
{
	const char* end = path.CData() + path.Size();
	UInt64 size = 0;
	do
	{
		++size;
		--end;
	} while (*end != '/');
	--size;
	path = path.SubString(path.Size() - size, path.Size());
}

String Path::MakePath(const String& path)
{
	UInt64 size = path.Size();
	const char* begin = path.CData() + size;
	while (*begin != '/' && *begin)
	{
		--size;
		--begin;
	}
	String d = path.SubString(0, size).PushBack(String('/'));
	for (int i = 0; i < d.Size(); i++)
	{
		if (d[i] == '\\')
		{
			d[i] = '/';
		}
	}
	return d;
}

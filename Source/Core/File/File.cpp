#include "File.h"
#include "Core/Core/PlatformDetection.h"

File::File()
	: m_Handle(nullptr)
{

}

File::~File()
{
	Close();
}

bool File::Open(const int mode, const char* path)
{
	if (mode == READABLE)
	{
		OpenReadable(path);
	}
	if (mode == WRITABLE)
	{
		OpenWritable(path);
	}
	return m_Handle != nullptr;
}

bool File::Write(const void* out, UInt64 size)
{
	UInt64 written = GetWrittenBytes(out, size);
#if defined(HA_PLATFORM_WINDOWS)
	return written != size;
#elif defined(HA_PLATFORM_LINUX)
	return written;
#endif
}

bool File::Read(void* in, UInt64 size)
{
	UInt64 readed = GetReadedBytes(in, size);
#if defined(HA_PLATFORM_WINDOWS)
	return readed != size;
#elif defined(HA_PLATFORM_LINUX)
	return readed;
#endif
}

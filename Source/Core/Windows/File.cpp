#include "Core/File/File.h"
#include "Core/Core/PlatformDetection.h"

#include <windows.h>

void File::Close()
{
	if (m_Handle)
	{
		CloseHandle(m_Handle);
		m_Handle = nullptr;
	}
}

void File::Flush()
{
	FlushFileBuffers(m_Handle);
}

bool File::Seek(UInt64 position)
{
	LARGE_INTEGER dist;
	dist.QuadPart = position;
	return SetFilePointer(m_Handle, dist.u.LowPart, &dist.u.HighPart, FILE_BEGIN) != INVALID_SET_FILE_POINTER;
}

UInt64 File::Size() const
{
	return GetFileSize(m_Handle, 0);
}

UInt64 File::Position()
{
	return SetFilePointer(m_Handle, 0, nullptr, FILE_CURRENT);
}

void File::OpenReadable(const char* path)
{
	m_Handle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
}

void File::OpenWritable(const char* path)
{
	m_Handle = CreateFileA(path, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
}

UInt64 File::GetWrittenBytes(const void* out, UInt64 size)
{
	DWORD written = 0;
	WriteFile(m_Handle, out, (DWORD)size, (LPDWORD)&written, nullptr);
	return (UInt64)written;
}

UInt64 File::GetReadedBytes(void* in, UInt64 size)
{
	DWORD readed = 0;
	ReadFile(m_Handle, in, (DWORD)size, (LPDWORD)&readed, nullptr);
	return (UInt64)readed;
}

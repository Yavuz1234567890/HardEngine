#include "Core/File/File.h"

#include <stdio.h>

void File::Close()
{
	if (m_Handle)
	{
		fclose((FILE*)m_Handle);
		m_Handle = nullptr;
	}
}

void File::Flush()
{
	fflush((FILE*)m_Handle);
}

bool File::Seek(UInt64 position)
{
	return fseek((FILE*)m_Handle, position, SEEK_SET) == 0;
}

UInt64 File::Size() const
{
	long position = ftell((FILE*)m_Handle);
	fseek((FILE*)m_Handle, 0, SEEK_END);
	size_t size = (size_t)ftell((FILE*)m_Handle);
	fseek((FILE*)m_Handle, position, SEEK_SET);
	return size;
}

UInt64 File::Position()
{
	return UInt64(ftell((FILE*)m_Handle));
}

void File::OpenReadable(const char* path)
{
	m_Handle = (void*)fopen(path, "rb");
}

void File::OpenWritable(const char* path)
{
	m_Handle = (void*)fopen(path, "wb");
}

UInt64 File::GetWrittenBytes(const void* out, UInt64 size)
{
	return fwrite(out, size, 1, (FILE*)m_Handle);
}

UInt64 File::GetReadedBytes(void* in, UInt64 size)
{
	return fread(in, size, 1, (FILE*)m_Handle);
}

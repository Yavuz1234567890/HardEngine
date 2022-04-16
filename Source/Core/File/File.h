#include "Core/Core/BasicTypes.h"

class File
{
public:
	enum
	{
		READABLE,
		WRITABLE
	};

	File();
	~File();

	bool Open(const int mode, const char* path);
	void Close();
	void Flush();
	bool Seek(UInt64 position);
	bool Write(const void* out, UInt64 size);
	bool Read(void* in, UInt64 size);
	UInt64 Size() const;
	UInt64 Position();
private:
	void OpenReadable(const char* path);
	void OpenWritable(const char* path);
	UInt64 GetWrittenBytes(const void* out, UInt64 size);
	UInt64 GetReadedBytes(void* in, UInt64 size);

	void* m_Handle;
};

#include "Core/Core/BasicTypes.h"
#include "Core/File/FileSystem.h"

class Image
{
public:
	Image();
	~Image();

	UInt8* GetData() const;
	bool Open(const String& path);
	int GetWidth() const;
	int GetHeight() const;
	int GetChannels() const;
private:
	UInt8* m_Data;
	int m_Width, m_Height;
	int m_Channels;
};

#include "Core/File/File.h"

class FileLogger
{
public:
	FileLogger();
	~FileLogger();

	void Init();
	void Print(const char* out);
private:
	File m_LogFile;
};

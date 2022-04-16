#include "Path.h"
#include "Core/Containers/Vector.h"

class FileSystem
{
public:
	static bool CreateFolder(const String& path);
	static void RemoveFolder(const String& path);
	static bool IsFolder(const String& path);
	static void RemoveFile(const String& path);
	static bool IsFile(const String& path);
	static bool FileCopy(const String& file, const String& dst);
	static bool RelocateFile(const String& file, const String& dst);
	static void GetChildItems(Vector<String>& dst, const String& path);
	static void ChangeCurrentDir(const String& path);
	static String GetCurrentDir();
};

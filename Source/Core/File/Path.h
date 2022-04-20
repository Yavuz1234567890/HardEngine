#ifndef PATH_H_
#define PATH_H_

#include "Core/Containers/String.h"

class Path
{
public:
	static String GetExtension(const String& path);
	static String GetDirectory(const String& path);
	static String GetBaseName(const String& path);
	static bool HasDirectory(const String& path);
	static void ClearDirectory(String& path);
	static String MakePath(const String& path);
};

#endif

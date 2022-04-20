#ifndef MEMORY_UTILS_H_
#define MEMORY_UTILS_H_

#include "Core/Core/BasicTypes.h"

class MemoryUtils
{
public:
	static void AddAllocation(UInt64 size);
	static void AddDeallocation(void* block);

	static UInt64 GetTotalUsed();
	static UInt64 GetUsedBytes();
	static UInt GetTotalAllocated();
	static UInt GetTotalFreed();
private:
	static UInt64 s_TotalUsed;
	static UInt64 s_UsedBytes;
	static UInt s_TotalAllocated;
	static UInt s_TotalFreed;
};

#endif

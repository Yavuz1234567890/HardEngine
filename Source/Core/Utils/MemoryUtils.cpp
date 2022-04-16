#include "MemoryUtils.h"

UInt64 MemoryUtils::s_TotalUsed = 0;
UInt64 MemoryUtils::s_UsedBytes = 0;
UInt MemoryUtils::s_TotalAllocated = 0;
UInt MemoryUtils::s_TotalFreed = 0;

void MemoryUtils::AddAllocation(UInt64 size)
{
	++s_TotalAllocated;
	s_TotalUsed += size;
	s_UsedBytes += size;
}

void MemoryUtils::AddDeallocation(void* block)
{
	++s_TotalFreed;
	s_UsedBytes -= *(UInt64*)(((UInt8*)block) - sizeof(UInt64));
}

UInt64 MemoryUtils::GetTotalUsed()
{
	return s_TotalUsed;
}

UInt64 MemoryUtils::GetUsedBytes()
{
	return s_UsedBytes;
}

UInt MemoryUtils::GetTotalAllocated()
{
	return s_TotalAllocated;
}

UInt MemoryUtils::GetTotalFreed()
{
	return s_TotalFreed;
}

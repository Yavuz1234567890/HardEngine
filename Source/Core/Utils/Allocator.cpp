#include "Allocator.h"
#include "MemoryUtils.h"

#include <malloc.h>
#include <memory.h>

#define MEM_ALIGN 16

void* Allocator::Alloc(UInt64 size)
{
	MemoryUtils::AddAllocation(size);
	return _aligned_malloc(size, MEM_ALIGN);
}

void* Allocator::Realloc(void* block, UInt64 size)
{
	MemoryUtils::AddAllocation(size);
	return _aligned_realloc(block, size, MEM_ALIGN);
}

void Allocator::Free(void* block)
{
	if (block)
	{
		MemoryUtils::AddDeallocation(block);
		_aligned_free(block);
	}
}

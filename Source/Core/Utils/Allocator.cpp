#include "Allocator.h"
#include "MemoryUtils.h"

#include <malloc.h>
#include <memory.h>

#define MEM_ALIGN 16

void* Allocator::Alloc(size_t size)
{
	MemoryUtils::AddAllocation(size);
	char* buffer = (char*)malloc(size + MEM_ALIGN);
	return buffer + MEM_ALIGN;
}

void* Allocator::Realloc(void* block, size_t size)
{
	MemoryUtils::AddAllocation(size);
	void* buffer = Alloc(size);
	memcpy(buffer, block, size);
	Free(block);
	return buffer;
}

void Allocator::Free(void* block)
{
	if (block)
	{
		MemoryUtils::AddDeallocation(block);
		free((char*)block - MEM_ALIGN);
	}
}

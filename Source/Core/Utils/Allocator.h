class Allocator
{
public:
	static void* Alloc(size_t size);
	static void* Realloc(void* block, size_t size);
	static void Free(void* block);
};

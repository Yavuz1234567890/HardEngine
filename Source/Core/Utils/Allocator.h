#include <new.h>

class Allocator
{
public:
	static void* Alloc(size_t size);
	static void* Realloc(void* block, size_t size);
	static void Free(void* block);

	template<typename T, typename... Args>
	static T* New(Args&&... args)
	{
		T* buffer = (T*)Alloc(sizeof(T));
		new (buffer) T(static_cast<Args&&>(args)...);
		return bufffer;
	}

	template<typename T>
	static void Delete(T* memory)
	{
		Free(memory);
	}
};

#include "Core/Core/BasicTypes.h"
#include "Core/Utils/Allocator.h"

#include <memory.h>
#include <new.h>

template<typename T>
class Vector
{
public:
	Vector()
		: m_Data(nullptr),
		m_Size(0),
		m_Capacity(0)
	{

	}

	Vector(UInt64 capacity)
		: m_Size(0),
		m_Capacity(capacity)
	{
		m_Data = (T*)Allocator::Alloc(capacity);
	}

	Vector(const Vector& rhs)
	{
		Set(rhs);
	}

	Vector(Vector&& rhs)
	{
		Set(rhs);
	}

	~Vector()
	{
		Clear();
	}

	Vector& operator=(const Vector& rhs)
	{
		Set(rhs);
		return *this;
	}

	Vector& operator=(Vector&& rhs)
	{
		Swap(rhs);
		return *this;
	}

	T& operator[](UInt64 index)
	{
		return m_Data[index];
	}

	const T& operator[](UInt64 index) const
	{
		return m_Data[index];
	}

	bool operator==(const Vector& rhs) const
	{
		return Compare(rhs) == 0;
	}

	bool operator!=(const Vector& rhs) const
	{
		return Compare(rhs) != 0;
	}

	int Compare(const Vector& rhs) const
	{
		return memcmp(m_Data, rhs.m_Data, m_Size);
	}

	void Set(const Vector& rhs)
	{
		m_Size = rhs.m_Size;
		m_Capacity = rhs.m_Capacity;
		m_Data = (T*)Allocator::Alloc(rhs.m_Capacity);
		memcpy(m_Data, rhs.m_Data, rhs.m_Size);
	} 

	void Swap(Vector& rhs)
	{
		T* data = m_Data;
		m_Data = rhs.m_Data;
		rhs.m_Data = data;

		UInt64 size = m_Size;
		m_Size = rhs.m_Size;
		rhs.m_Size = size;

		UInt64 capacity = m_Capacity;
		m_Capacity = rhs.m_Capacity;
		rhs.m_Capacity = capacity;
	}

	void Resize(UInt64 capacity)
	{
		if (m_Capacity != capacity)
		{
			if (m_Capacity == 0)m_Data = (T*)Allocator::Alloc(capacity);
			else m_Data = (T*)Allocator::Realloc(m_Data, capacity);
			m_Capacity = capacity;
		}
	}

	void ResizeGrow()
	{
		Resize(m_Capacity == 0 ? 4 : m_Capacity << 1);
	}

	void PushBack(const T& value)
	{
		if (m_Size == m_Capacity)ResizeGrow();
		new (m_Data + m_Size) T(value);
		++m_Size;
	}

	void PushBack(T&& value)
	{
		if (m_Size == m_Capacity)
		{
			ResizeGrow();
		}
		new (m_Data + m_Size) T(static_cast<T&&>(value));
		++m_Size;
	}

	template<typename... Args>
	T& EmplaceBack(Args&&... args)
	{
		if (m_Size == m_Capacity)
		{
			ResizeGrow();
		}
		new (m_Data + m_Size) T(static_cast<Args&&>(args)...);
		++m_Size;
		return m_Data[m_Size - 1];
	}

	void Clear()
	{
		while (m_Size >= 0)
		{
			m_Data[m_Size].~T();
			--m_Size;
		}
	}

	void PopPack()
	{
		m_Data[m_Size - 1].~T();
		--m_Size;
	}
	
	void Erase(UInt64 index)
	{
		m_Data[index].~T();
		--m_Size;
	}

	void Shrink(UInt64 size)
	{
		UInt64 s = size;
		while (m_Size + s >= m_Size)
		{
			m_Data[s].~T();
			++s;
		}
		m_Size = size;
	}

	void Insert(UInt64 index, const T& value)
	{
		if (m_Size == m_Capacity)
		{
			ResizeGrow();
			SetRange(m_Data + index + 1, m_Data + index, m_Size - index);
		}
		else
		{
			SetRange(m_Data + index + 1, m_Data + index, m_Size - index);
		}
		new (m_Data + index) T(value);
		++m_Size;
	}

	void Insert(UInt64 index, T&& value)
	{
		if (m_Size == m_Capacity)
		{
			ResizeGrow();
			SetRange(m_Data + index + 1, m_Data + index, m_Size - index);
		}
		else
		{
			SetRange(m_Data + index + 1, m_Data + index, m_Size - index);
		}
		new (m_Data + index) T(static_cast<T&&>(value));
		++m_Size;
	}

	bool IsEmpty() const
	{
		return m_Size == 0;
	}

	T* Data()
	{
		return m_Data;
	}

	UInt64 Size() const
	{
		return m_Size;
	}

	UInt64 Capacity() const
	{
		return m_Capacity;
	}
private:
	void SetRange(T* dst, const T* source, UInt64 size)
	{
		for (UInt64 i = size - 1; i < size; --i) 
		{
			new (dst + i) T(static_cast<T&&>(src[i]));
			src[i].~T();
		}
	}

	T* m_Data;
	UInt64 m_Size, m_Capacity;
};

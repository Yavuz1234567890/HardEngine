#include "Core/Core/BasicTypes.h"

class String
{
public:
	String();
	String(UInt64 size, const char* data);
	String(const char* data);
	String(const String& rhs);
	String(String&& rhs);
	String(const char value);
	String(const int value);
	String(const UInt value);
	String(const double value);
	String(const float value);
	String(const bool value);
	~String();
	String& operator=(const char* data);
	String& operator=(const String& rhs);
	String& operator=(String&& rhs);
	String& operator=(const char value);
	String& operator=(const int value);
	String& operator=(const UInt value);
	String& operator=(const double value);
	String& operator=(const float value);
	String& operator=(const bool value);
	String& operator+=(const char* data);
	String& operator+=(const String& rhs);
	String& operator+=(const char value);
	String& operator+=(const int value);
	String& operator+=(const UInt value);
	String& operator+=(const double value);
	String& operator+=(const float value);
	String& operator+=(const bool value);
	char& operator[](UInt64 index);
	const char& operator[](UInt64 index) const;
	bool operator==(const String& rhs) const;
	bool operator!=(const String& rhs) const;
	bool operator>(const String& rhs) const;
	bool operator<(const String& rhs) const;
	int Compare(const String& rhs) const;
	String SubString(UInt64 begin, UInt64 end);
	void Clear();
	void Set(UInt64 size, const char* data);
	void Set(const char* data);
	void Set(const String& rhs);
	void Swap(String& rhs);
	void Set(const char value);
	void Set(const int value);
	void Set(const UInt value);
	void Set(const double value);
	void Set(const float value);
	void Set(const bool value);
	void Resize(UInt64 size);
	void Add(UInt64 size, const char* data);
	void PushBack(const char value);
	void PopBack();
	void Erase(UInt64 index);
	void Shrink(UInt64 size);
	void Insert(UInt64 index, const char* value);
	void Reverse();
	bool StartsWith(const String& begin);
	bool EndsWith(const String& end);
	bool IsEmpty() const;
	const char* CData() const;
	char* Data();
	UInt64 Size() const;
private:
	char* m_Data;
	UInt64 m_Size;
};
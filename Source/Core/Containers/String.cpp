#include "String.h"
#include "Core/Utils/Allocator.h"

#include <string.h>
#include <memory.h>
#include <math.h>

namespace WString
{
	String FromWString(const WChar* source)
	{
		String d;
		const WChar* s = source;
		while (*s)
		{
			d += (char)*s;
			++s;
		}
		return d;
	}

	class WStrData
	{
	public:
		WStrData()
			: Data(nullptr)
		{

		}

		WStrData(const char* data)
		{
			const char* source = data;
			const UInt64 size = strlen(data);
			Data = (WChar*)Allocator::Alloc(size + 1);
			while (*source)
			{
				*Data = (WChar)*source;
				++source;
				++Data;
			}
			Data[size] = 0;
		}

		~WStrData()
		{
			Data[0] = 0;
		}

		WChar* Data;
	};
}

String::String()
	: m_Data(nullptr),
	m_Size(0)
{

}

String::String(UInt64 size, const char* data)
{
	Set(size, data);
}

String::String(UInt64 size, const WChar* data)
{
	Set(size, data);
}

String::String(const char* data)
{
	Set(data);
}

String::String(const WChar* data)
{
	Set(data);
}

String::String(const String& rhs)
{
	Set(rhs);
}

String::String(String&& rhs)
{
	Swap(rhs);
}

String::String(const char value)
{
	Set(value);
}

String::String(const WChar value)
{
	Set(value);
}

String::String(const int value)
{
	Set(value);
}

String::String(const UInt value)
{
	Set(value);
}

String::String(const double value)
{
	Set(value);
}

String::String(const float value)
{
	Set(value);
}

String::String(const bool value)
{
	Set(value);
}

String::~String()
{

}

String& String::operator=(const char* data)
{
	Set(data);
	return *this;
}

String& String::operator=(const WChar* data)
{
	Set(data);
	return *this;
}

String& String::operator=(const String& rhs)
{
	Set(rhs);
	return *this;
}

String& String::operator=(String&& rhs)
{
	Swap(rhs);
	return *this;
}

String& String::operator=(const char value)
{
	Set(value);
	return *this;
}

String& String::operator=(const WChar value)
{
	Set(value);
	return *this;
}

String& String::operator=(const int value)
{
	Set(value);
	return *this;
}

String& String::operator=(const UInt value)
{
	Set(value);
	return *this;
}

String& String::operator=(const double value)
{
	Set(value);
	return *this;
}

String& String::operator=(const float value)
{
	Set(value);
	return *this;
}

String& String::operator=(const bool value)
{
	Set(value);
	return *this;
}

String& String::operator+=(const char* data)
{
	Add(strlen(data), data);
	return *this;
}

String& String::operator+=(const WChar* data)
{
	*this += String(data);
	return *this;
}

String& String::operator+=(const String& rhs)
{
	Add(rhs.m_Size, rhs.m_Data);
	return *this;
}

String& String::operator+=(const char value)
{
	PushBack(value);
	return *this;
}

String& String::operator+=(const WChar value)
{
	*this += String(value);
	return *this;
}

String& String::operator+=(const int value)
{
	*this += String(value);
	return *this;
}

String& String::operator+=(const UInt value)
{
	*this += String(value);
	return *this;
}

String& String::operator+=(const double value)
{
	*this += String(value);
	return *this;
}

String& String::operator+=(const float value)
{
	*this += String(value);
	return *this;
}

String& String::operator+=(const bool value)
{
	*this += String(value);
	return *this;
}

char& String::operator[](UInt64 index)
{
	return m_Data[index];
}

const char& String::operator[](UInt64 index) const
{
	return m_Data[index];
}

bool String::operator==(const String& rhs) const
{
	return Compare(rhs) == 0;
}

bool String::operator!=(const String& rhs) const
{
	return Compare(rhs) != 0;
}

bool String::operator>(const String& rhs) const
{
	return Compare(rhs) == 1;
}

bool String::operator<(const String& rhs) const
{
	return Compare(rhs) == -1;
}

int String::Compare(const String& rhs) const
{
	return strcmp(m_Data, rhs.m_Data);
}

String String::SubString(UInt64 begin, UInt64 end) const
{
	return String(end, m_Data + begin);
}

void String::Clear()
{
	if (m_Size > 0)
	{
		m_Data[0] = 0;
		m_Size = 0;
	}
}

void String::Set(UInt64 size, const char* data)
{
	m_Data = (char*)Allocator::Alloc(size + 1);
	memcpy(m_Data, data, size);
	m_Data[size] = 0;
	m_Size = size;
}

void String::Set(UInt64 size, const WChar* data)
{
	Set(size, WString::FromWString(data).CData());
}

void String::Set(const char* data)
{
	Set(strlen(data), data);
}

void String::Set(const WChar* data)
{
	Set(WString::FromWString(data));
}

void String::Set(const String& rhs)
{
	Set(rhs.m_Size, rhs.m_Data);
}

void String::Swap(String& rhs)
{
	char* data = m_Data;
	m_Data = rhs.m_Data;
	rhs.m_Data = data;

	UInt64 size = m_Size;
	m_Size = rhs.m_Size;
	rhs.m_Size = size;
}

void String::Set(const char value)
{
	char* buffer = (char*)Allocator::Alloc(2);
	buffer[0] = value;
	buffer[1] = 0;
	Set(1, buffer);
}

void String::Set(const WChar value)
{
	WChar* buffer = (WChar*)Allocator::Alloc(2);
	buffer[0] = value;
	buffer[1] = 0;
	Set(1, buffer);
}

void String::Set(const int value)
{
	int v = value;
	bool negative = false;
	if (v < 0)
	{
		v *= -1;
		negative = true;
	}
	if (v == 0)
	{
		Set('0');
	}
	else
	{
		while (v > 0)
		{
			PushBack((v % 10) + '0');
			v /= 10;
		}
		if (negative)
		{
			PushBack('-');
		}
		Reverse();
	}
}

void String::Set(const UInt value)
{
	UInt v = value;
	if (v == 0)
	{
		Set('0');
	}
	else
	{
		while (v > 0)
		{
			PushBack((v % 10) + '0');
			v /= 10;
		}
		Reverse();
	}
}

String& String::PushBack(const String& rhs)
{
	*this += rhs;
	return *this;
}

void String::Set(const double value)
{
	double v = value;
	int after = 6;
	char digit = 0;
	double power = 0.0;
	if (v < 0.0)
	{
		PushBack('-');
		v *= -1.0;
	}
	int exponent = v == 0.0 ? 0 : int(log10(v));
	if (v < 1.0 && v > -1.0)
	{
		PushBack('0');
	}
	else
	{
		while (v >= 1.0 || exponent >= 0)
		{
			power = pow(10, double(exponent));
			digit = char(floor(v / power));
			v -= digit * power;
			PushBack(digit + '0');
			--exponent;
		}
	}
	PushBack('.');
	while (after > 0)
	{
		v *= 10.0;
		PushBack(char(v) + '0');
		v -= char(v);
		--after;
	}
}

void String::Set(const float value)
{
	Set(double(value));
}

void String::Set(const bool value)
{
	Set(value ? "true" : "false");
}

void String::AppendFormatArgs(const char* fmt, va_list args)
{
	const char* format = fmt;
	char currentFormat = 0, secondFormat = 0;
	while (*format)
	{
		if (*format != '%')
		{
			PushBack(*format);
		}
		else
		{
			currentFormat = *(format + 1);
			secondFormat = *(format + 2);
			if (currentFormat == 's')
			{
				char* arg = va_arg(args, char*);
				*this += arg;
			}
			if (currentFormat == 'c')
			{
				char arg = va_arg(args, char);
				*this += arg;
			}
			if (currentFormat == 'i')
			{
				int arg = va_arg(args, int);
				*this += arg;
			}
			if (currentFormat == 'u' && secondFormat == 'i')
			{
				UInt arg = va_arg(args, UInt);
				*this += arg;
				++format;
			}
			if (currentFormat == 'f')
			{
				double arg = va_arg(args, double);
				*this += arg;
			}
			if (currentFormat == 'b')
			{
				bool arg = va_arg(args, bool);
				*this += arg;
			}
			if (currentFormat == 'w')
			{
				if (secondFormat == 's')
				{
					WChar* arg = va_arg(args, WChar*);
					*this += arg;
				}
				if (secondFormat == 'c')
				{
					WChar arg = va_arg(args, WChar);
					*this += arg;
				}
				++format;
			}
			++format;
		}
		++format;
	}
}

void String::AppendFormat(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	AppendFormatArgs(fmt, args);
	va_end(args);
}

void String::Resize(UInt64 size)
{
	if (m_Size != size)
	{
		if (m_Size == 0)m_Data = (char*)Allocator::Alloc(size + 1);
		else m_Data = (char*)Allocator::Realloc(m_Data, size + 1);
		m_Size = size;
	}
	m_Data[size] = 0;
}

void String::Add(UInt64 size, const char* data)
{
	const UInt64 prevSize = m_Size;
	Resize(prevSize + size);
	memcpy(m_Data + prevSize, data, size);
}

void String::PushBack(const char value)
{
	*this += String(value);
}

void String::PopBack()
{
	--m_Size;
	m_Data[m_Size] = 0;
}

void String::Erase(UInt64 index)
{
	memmove(m_Data + index, m_Data + index + 1, m_Size - index - 1);
	--m_Size;
	m_Data[m_Size] = 0;
}

void String::Shrink(UInt64 size)
{
	m_Data[size] = 0;
	m_Size = size;
}

void String::Insert(UInt64 index, const char* value)
{
	char* data = m_Data;
	const UInt64 prevSize = m_Size;
	const UInt64 valueSize = strlen(value);
	Resize(prevSize + valueSize);
	memmove(data + index + valueSize, data + index, prevSize - index);
	memcpy(data + index, value, valueSize);
}

void String::Reverse()
{
	char* begin = m_Data;
	char* end = m_Data + m_Size - 1;
	while (begin < end)
	{
		const char prev = *begin;
		*begin = *end;
		*end = prev;
		--end;
		++begin;
	}
}

bool String::StartsWith(const String& begin)
{
	return String(begin.m_Size, m_Data) == begin;
}

bool String::EndsWith(const String& end)
{
	return String(end.m_Size, m_Data + m_Size - end.m_Size) == end;
}

bool String::IsEmpty() const
{
	return m_Size == 0;
}

const char* String::CData() const
{
	return m_Data;
}

const WChar* String::WData() const
{
	WString::WStrData wstr(m_Data);
	return wstr.Data;
}

char* String::Data()
{
	return m_Data;
}

UInt64 String::Size() const
{
	return m_Size;
}

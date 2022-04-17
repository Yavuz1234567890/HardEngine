#include "Image.h"
#include "stb_image.h"

Image::Image()
	: m_Width(0),
	m_Height(0),
	m_Channels(0),
	m_Data(nullptr)
{

}

Image::~Image()
{
	stbi_image_free(m_Data);
}

bool Image::Open(const String& path)
{
	stbi_set_flip_vertically_on_load(1);
	const char* p = FileSystem::GetCurrentDir().PushBack("Assets/Images/").PushBack(path).CData();
	m_Data = stbi_load(p, &m_Width, &m_Height, &m_Channels, 0);
	return m_Data != nullptr;
}

UInt8* Image::GetData() const
{
	return m_Data;
}

int Image::GetWidth() const
{
	return m_Width;
}

int Image::GetHeight() const
{
	return m_Height;
}

int Image::GetChannels() const
{
	return m_Channels;
}

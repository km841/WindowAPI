#include "pch.h"
#include "Texture.h"


Texture::Texture()
	: Res()
	, mBit(0)
{
}

Texture::Texture(const std::wstring& _key)
	: Res(_key)
	, mBit(0)
{
}

Texture::~Texture()
{
	DeleteObject(mBit);
	DeleteDC(mDC);
}

bool Texture::Load(const std::wstring& _path)
{
	mBit = (HBITMAP)LoadImage(
		nullptr
		,_path.c_str()
		, IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	if (mBit == 0)
		return false;
	
	BITMAP bitmap = {};
	GetObject(mBit, sizeof(bitmap), &bitmap);

	mWidth = bitmap.bmWidth;
	mHeight = bitmap.bmHeight;
	mSize = Vec2((float)mWidth, (float)mHeight);
	mDC = CreateCompatibleDC(BACK_BUF_DC);
	
	HBITMAP prevBit = (HBITMAP)SelectObject(mDC, mBit);
	DeleteObject(prevBit);

	return true;
}

Pixel Texture::GetPixel(int x, int y)
{
	COLORREF rgba = ::GetPixel(mDC, x, y);
	return Pixel(rgba);
}

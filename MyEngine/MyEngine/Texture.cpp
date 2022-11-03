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
	mDC = CreateCompatibleDC(BACK_BUF_DC);
	
	HBITMAP prevBit = (HBITMAP)SelectObject(mDC, mBit);
	DeleteObject(prevBit);

	return true;
}
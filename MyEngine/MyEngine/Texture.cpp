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

bool Texture::Load(HBITMAP _bitmap)
{
	mBit = _bitmap;

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

void Texture::ChangeColor(COLORREF _src, COLORREF _dst, int _boundary_x)
{
	Pixel srcColor = _src;

	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; x++)
		{
			if (_boundary_x > x)
				continue;

			Pixel pixel = GetPixel(x, y);
			
			if (srcColor == pixel)
			{
				SetPixel(mDC, x, y, _dst);
			}
		}
	}
}

void Texture::ChangeExceptColor(COLORREF _excep, COLORREF _dst)
{
	Pixel excColor = _excep;

	for (int y = 0; y < mHeight; ++y)
	{
		for (int x = 0; x < mWidth; x++)
		{
			Pixel pixel = GetPixel(x, y);

			if (excColor != pixel)
			{
				SetPixel(mDC, x, y, _dst);
			}
		}
	}
}

void Texture::SetAlphaValue(COLORREF _targetColor, int _alpha)
{
	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = mWidth;
	bmi.bmiHeader.biHeight = -mHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	void* pBits = NULL;
	HBITMAP hbmDIB = CreateDIBSection(mDC, &bmi, DIB_RGB_COLORS, &pBits, NULL, 0);

	GetDIBits(mDC, mBit, 0, mHeight, pBits, &bmi, DIB_RGB_COLORS);

	for (int y = 0; y < mHeight; y++) {
		for (int x = 0; x < mWidth; x++) {
			COLORREF color = ((UINT32*)pBits)[x + y * mWidth] & 0x00ffffff; // get the color of the pixel
			if (color == _targetColor) {
				// Set the alpha value of the pixel
				((UINT32*)pBits)[x + y * mWidth] = (_alpha << 24) | (0x00ffffff & ((UINT32*)pBits)[x + y * mWidth]);
			}
		}
	}

	SetDIBits(mDC, mBit, 0, mHeight, pBits, &bmi, DIB_RGB_COLORS);
	DeleteObject(hbmDIB);
}

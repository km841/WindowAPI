#include "pch.h"
#include "ResourceMgr.h"
#include "Res.h"
#include "Texture.h"

std::wstring ResourceMgr::mDefaultPath = L"..\\Resource\\";

ResourceMgr::~ResourceMgr()
{
	for (auto& res : mResMap)
	{
		delete res.second;
		res.second = nullptr;
	}
}


Texture* ResourceMgr::CreateTexture(const std::wstring _key, Vec2 _size)
{
	ResourceMap::iterator iter = mResMap.find(_key);
	if (iter != mResMap.end())
	{
		// 존재하는 키
		return nullptr;
	}

	Texture* tex = new Texture;
	tex->mBit = CreateCompatibleBitmap(BACK_BUF_DC, (int)_size.x, (int)_size.y);
	tex->mDC = CreateCompatibleDC(BACK_BUF_DC);
	tex->mWidth = (int)_size.x;
	tex->mHeight = (int)_size.y;
	tex->mSize = _size;
	tex->SetKey(_key);
	
	HBITMAP oldBit = (HBITMAP)SelectObject(tex->mDC, tex->mBit);
	DeleteObject(oldBit);

	mResMap.insert(std::make_pair(_key, tex));
	return tex;
}

Texture* ResourceMgr::CreateTexture(const std::wstring _key, HDC _dc, Vec2 _size)
{
	ResourceMap::iterator iter = mResMap.find(_key);
	if (iter != mResMap.end())
	{
		// 존재하는 키
		return nullptr;
	}

	Texture* tex = new Texture;
	tex->mBit = CreateCompatibleBitmap(_dc, (int)_size.x, (int)_size.y);
	tex->mDC = CreateCompatibleDC(_dc);
	tex->mWidth = (int)_size.x;
	tex->mHeight = (int)_size.y;
	tex->mSize = _size;
	tex->SetKey(_key);

	HBITMAP oldBit = (HBITMAP)SelectObject(tex->mDC, tex->mBit);
	DeleteObject(oldBit);

	mResMap.insert(std::make_pair(_key, tex));
	return tex;
}





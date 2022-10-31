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






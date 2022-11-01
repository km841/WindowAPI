#include "yaBgImageObject.h"
#include "yaResources.h"
#include "yaImage.h"
namespace ya
{
	BgImageObject::BgImageObject()
		: mImage(nullptr)
	{
		SetPos(Vector2::Zero);
		SetScale(Vector2::One);
	}

	BgImageObject::~BgImageObject()
	{
	}

	void BgImageObject::Initialize()
	{
	}

	void BgImageObject::Tick()
	{
		GameObject::Tick();
	}

	void BgImageObject::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		TransparentBlt(hdc
			, pos.x
			, pos.y
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetDC()
			, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, 0);
		GameObject::Render(hdc);
	}
	void BgImageObject::SetImage(const std::wstring& key, const std::wstring& imageName)
	{
	
		std::wstring path = L"..\\Resources\\Image\\";
		path += imageName;


		mImage = Resources::Load<Image>(key, path);
		
	}
}


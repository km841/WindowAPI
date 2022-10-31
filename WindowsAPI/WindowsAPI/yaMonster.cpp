#include "yaMonster.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaMissile.h"
#include "yaSceneManager.h"
#include "yaApplication.h"
#include "yaScene.h"
#include "yaImage.h"
#include "yaResources.h"
#include "yaAnimator.h"
#include "yaCollider.h"

namespace ya
{

	Monster::Monster()
		: mSpeed(1.f)
	{
		const auto& windowData = Application::GetInstance().GetWindowData();
		SetPos(Vector2{ float(windowData.width / 2 - 50), float(windowData.height - 300) });
		SetScale(Vector2{ 50.f, 50.f });

		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>(L"Monster", L"..\\Resources\\Image\\Monster.bmp");
		}

		AddComponent(new Animator());
		AddComponent(new Collider());

	}

	Monster::~Monster()
	{
	}

	void Monster::Tick()
	{
		GameObject::Tick();
		Vector2 pos = GetPos();


		SetPos(pos);
	}

	void Monster::Render(HDC hdc)
	{
		HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		Brush brush(hdc, blueBrush);

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		Pen pen(hdc, redPen);

		//숙제 : 얘를 이용해서 메테오 내려오는거 떨어지는애들을 펜색, 브러시색을 랜덤으로 바꾸기
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		//BitBlt(hdc
		//	, pos.x, pos.y
		//	, mImage->GetWidth()
		//	, mImage->GetHeight()
		//	, mImage->GetDC()
		//	, 0, 0
		//	, SRCCOPY);
		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() / 2.f);
		finalPos.y = (pos.y - mImage->GetHeight() / 2.f);


		TransparentBlt(hdc
			, finalPos.x
			, finalPos.y
			, mImage->GetWidth()
			, mImage->GetHeight()
			, mImage->GetDC()
			, 0, 0
			, mImage->GetWidth()
			, mImage->GetHeight()
			, RGB(255, 255, 255));

		GameObject::Render(hdc);
	}

}
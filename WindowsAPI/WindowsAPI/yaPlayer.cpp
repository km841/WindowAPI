#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaMissile.h"
#include "yaSceneManager.h"
#include "yaApplication.h"
#include "yaScene.h"

namespace ya
{

	Player::Player()
		: mSpeed(1.f)
	{
		const auto& windowData = Application::GetInstance().GetWindowData();
		SetPos(Vector2{ float(windowData.width / 2 - 50), float(windowData.height - 300) });
		SetScale(Vector2{ 50.f, 50.f });
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		Vector2 pos = GetPos();
		if (KEY_PRESSED(eKeyCode::W))
		{
			pos.y -= 1000.f * Time::DeltaTime();
		}

		if (KEY_PRESSED(eKeyCode::S))
		{
			pos.y += 1000.f * Time::DeltaTime();
		}

		if (KEY_PRESSED(eKeyCode::A))
		{
			pos.x -= 1000.f * Time::DeltaTime();
		}

		if (KEY_PRESSED(eKeyCode::D))
		{
			pos.x += 1000.f * Time::DeltaTime();
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Scene* scene = SceneManager::GetPlayScene();
			Missile* missile = new Missile();
			scene->AddGameObject(missile);

			Vector2 playerPos = GetPos();
			Vector2 playerScale = GetScale() / 2.f;

			Vector2 missileScale = missile->GetScale();

			missile->SetPos((playerPos + playerScale) - (missileScale / 2.f));

			//운석 피하기 게임
			//씬에 추가해주는 거 잊지 않기
		}

		SetPos(pos);
	}

	void Player::Render(HDC hdc)
	{
		HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		Brush brush(hdc, blueBrush);

		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		Pen pen(hdc, redPen);

		//숙제 : 얘를 이용해서 메테오 내려오는거 떨어지는애들을 펜색, 브러시색을 랜덤으로 바꾸기
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Rectangle(hdc
			, pos.x
			, pos.y
			, pos.x + scale.x
			, pos.y + scale.y);

	}

}
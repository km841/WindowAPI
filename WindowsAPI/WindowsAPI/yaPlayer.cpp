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
		: mSpeed(1.0f)
	{
		const auto& windowData = Application::GetInstance().GetWindowData();
		SetPos(Vector2{ float(windowData.width / 2 - 50), float(windowData.height - 300) });
		SetScale(Vector2{ 100.f, 100.f });
	}

	Player::~Player()
	{
	}

	void Player::Tick()
	{
		Vector2 pos = GetPos();
		if (KEY_PRESSED(eKeyCode::W))
		{
			pos.y -= 300.f * Time::DeltaTime();
		}

		if (KEY_PRESSED(eKeyCode::S))
		{
			pos.y += 300.f * Time::DeltaTime();
		}

		if (KEY_PRESSED(eKeyCode::A))
		{
			pos.x -= 300.f * Time::DeltaTime();
		}

		if (KEY_PRESSED(eKeyCode::D))
		{
			pos.x += 300.f * Time::DeltaTime();
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
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		Rectangle(hdc
			, pos.x
			, pos.y
			, pos.x + scale.x
			, pos.y + scale.y);

	}

}
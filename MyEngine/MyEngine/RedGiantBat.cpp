#include "pch.h"
#include "RedGiantBat.h"
#include "Collider.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Animation.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "CameraMgr.h"
#include "Player.h"
#include "RotateMissileEffect.h"
#include "EventRegisteror.h"

RedGiantBat::RedGiantBat()
{
	SetSize(Vec2(192.f, 192.f));

	GetCollider()->SetSize(Vec2(30.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -50.f));

	GetRigidBody()->SetMass(1.f);
	SetGravity(false);

	std::wstring idleAnimName = L"RedGiantBat_Move";
	SetIdleAnimName(idleAnimName);

	std::wstring moveAnimName = L"RedGiantBat_Move";
	SetMoveAnimName(moveAnimName);

	std::wstring attAnimName = L"RedGiantBat_Att";
	SetAttAnimName(attAnimName);

	Texture* animTex = ResourceMgr::GetInstance().Load<Texture>(L"RedGiantBatAnimTex", L"Texture\\red_giant_bat_animation.bmp");

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Left",
		animTex,
		Vec2(0.f, 0.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		7
	);

	GetAnimator()->RegisterAnimation(
		moveAnimName + L"Right",
		animTex,
		Vec2(0.f, 192.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		7
	);

	Animation* attAnimLeft = GetAnimator()->CreateAnimation(
		attAnimName + L"Left",
		animTex,
		Vec2(0.f, 384.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		10
	);

	Animation* attAnimRight = GetAnimator()->CreateAnimation(
		attAnimName + L"Right",
		animTex,
		Vec2(0.f, 576.f),
		Vec2(192.f, 192.f),
		Vec2(192.f, 0.f),
		0.1f,
		10
	);

	GetAnimator()->AddAnimation(attAnimName + L"Left", attAnimLeft);
	GetAnimator()->AddAnimation(attAnimName + L"Right", attAnimRight);


	GetAnimator()->SelectAnimation(idleAnimName + L"Left", true);

	RotateMissileEffect* effect = new RotateMissileEffect;
	effect->SetOwner(this);
	SetEffect(effect);
	
}

RedGiantBat::~RedGiantBat()
{
}

void RedGiantBat::Initialize()
{
	Monster::Initialize();
}

void RedGiantBat::Update()
{
	Monster::Update();
	if (nullptr != mEffect)
	{
		mEffect->Update();
	}




}

void RedGiantBat::Render()
{
	Monster::Render();


	// Update에서 미사일을 만들어내면 그 객체들은 씬에 들어가서 직접적으로 충돌해야 하므로
	// 그 미사일들을 Update하고 Render해줄 필요가 없다.

	//wchar_t batGravity[COMMENT_MAX_SIZE] = {};
	//swprintf_s(batGravity, L"targetVec.x : %f, targetVec.y : %f", mTargetVec.x, mTargetVec.y);
	//TextOut(BACK_BUF_DC, 10, 130, batGravity, (int)wcslen(batGravity));
}

void RedGiantBat::Destroy()
{
	Monster::Destroy();
}

void RedGiantBat::OnCollision(Collider* _other)
{
}

void RedGiantBat::OnCollisionEnter(Collider* _other)
{
	Monster::OnCollisionEnter(_other);
}

void RedGiantBat::OnCollisionExit(Collider* _other)
{
}

bool RedGiantBat::Attack()
{
	
	// 이펙트
	// 이펙트의 Attack을 통해 뭔가를 실행?
	// 이펙트의 

	// Effect의 Attack에게 특정 공격방식을 전달하면
	// Effect는 그 공격이 종료될 때까지 Update를 돈다
	// Effect가 공격이 다 끝나면 Attack에 False를 반환한다.

	// Attack은 AttackState의 Update에서 검사하며
	// Attack의 시작과 끝을 관리함
	// 시작은?  

	// Monster의 Update에서 Effect의 Update를 돌려주면
	// Effect의 Update안에서는 몬스터의 공격에서 해야 할 일들을 해야 한다
	// 탄들을 회전시키려면 Effect의 내부에서 for문을 돌며 탄들의 위치에 관여해야 함
	// 탄의 이동은 Effect의 Update에서 위치를 변경해주는 것


	// SwordEffect는 그냥충돌체만 껏다켰다해주면되는것에반해
	// MissileEffect는 실제 미사일을 만들어야 함
	// 그 얘기는 곧 Effect에게 공격의 주도권을 넘겨주어야 한다는 것
	// - Effect의 Update에서는 어떤?
	// - Missile을 만든다
	// - Missile을 만드는건 현재 Monster의 애니메이션 프레임과 직접적인 연관이 있음
	// - 회전탄과 같은 특정 발사방식은 어디서 정의해야하는가?
	// - MissileEffect의 멤버함수를 통해 실행
	// - MissileEffect는 그럼 모든 원거리 몬스터의 공격패턴을 보유하고 있어야 하나?
	// - 회전탄, 조준탄 등 단순한 탄들은 여기서 정의하고 Monster의 Attack안에서 실행됨
	// - Attack 안에서 특정 프레임에 맞춰서 실행하려면?
	// - 프레임이 유효하게 작용하려면 애니메이션 프레임 시작시점, 종료시점을 몬스터객체가 별도로 보관해야 함
	


	return mEffect->Attack();
}

bool RedGiantBat::DetectPlayer()
{
	float angle = 0.f;

	// 1. 몬스터에서 몬스터 + 인식범위까지의 벡터
	// 2. 몬스터에서 플레이어와의 벡터
	// 두 벡터를 비교해서 2번이 1번보다 각도도 작고 길이도 짧은 경우 인식한 걸로 처리
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 monsterPos = GetPos();
		Vec2 playerPos = player->GetPos();

		MonsterInfo info = GetMonsterInfo();

		// left= -150 ~ -180 (하단 150, 좌측면 180) // 우측도 마찬가지

		switch (mDir)
		{
		case DIR::LEFT:
		{
			Vec2 recogVec = Vec2(monsterPos.x - mInfo.mRecog, monsterPos.y);
			Vec2 detectVec = recogVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{

				//targetVec = RENDER_POS(targetVec);
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				// 플레이어 위치에서 내 위치를 뺀 벡터

				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				if (180.f >= angle && 90.f <= angle)
				{
					return true;
				}


			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 recogVec = Vec2(monsterPos.x + mInfo.mRecog, monsterPos.y);
			Vec2 detectVec = monsterPos - recogVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				//wchar_t szBuffer[256] = {};
				//swprintf_s(szBuffer, L"angle : %f", angle);
				//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);

				if (-180.f <= angle && -90.f >= angle)
				{
					return true;
				}
			}
		}
		break;
		}
	}

	return false;
}

bool RedGiantBat::DetectIntoAttRange()
{
	float angle = 0.f;

	// 1. 몬스터에서 몬스터 + 인식범위까지의 벡터
	// 2. 몬스터에서 플레이어와의 벡터
	// 두 벡터를 비교해서 2번이 1번보다 각도도 작고 길이도 짧은 경우 인식한 걸로 처리
	Player* player = Player::GetPlayer();

	if (nullptr != player)
	{
		Vec2 monsterPos = GetPos();
		Vec2 playerPos = player->GetPos();

		MonsterInfo info = GetMonsterInfo();

		// left= -140 ~ -180 (하단 150, 좌측면 180) // 우측도 마찬가지

		switch (mDir)
		{
		case DIR::LEFT:
		{
			Vec2 attRangeVec = Vec2(monsterPos.x - mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = attRangeVec - monsterPos;
			Vec2 targetVec = playerPos - monsterPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{

				//targetVec = RENDER_POS(targetVec);
				//  angle = arccos ( (a·b) / (|a|*|b|) ) 
				// 플레이어 위치에서 내 위치를 뺀 벡터

				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				if (180.f >= angle && 90.f <= angle)
				{
					return true;
				}


			}
		}

		break;
		case DIR::RIGHT:
		{
			Vec2 attRangeVec = Vec2(monsterPos.x + mInfo.mAttRange, monsterPos.y);
			Vec2 detectVec = monsterPos - attRangeVec;
			Vec2 targetVec = monsterPos - playerPos;

			float detectLen = detectVec.Len();
			float targetLen = targetVec.Len();
			if (targetLen < detectLen)
			{
				angle = atan2(targetVec.y, targetVec.x);
				angle = Math::RadianToDegree(angle);

				//wchar_t szBuffer[256] = {};
				//swprintf_s(szBuffer, L"angle : %f", angle);
				//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);

				if (-180.f <= angle && -90.f >= angle)
				{
					return true;
				}
			}
		}
		break;
		}
	}

	//wchar_t szBuffer[256] = {};
	//swprintf_s(szBuffer, L"angle : %f", angle);
	//SetWindowText(APP_INSTANCE.GetHwnd(), szBuffer);
	return false;
}

void RedGiantBat::RecogLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());

	Vec2 dirVec = {};
	Vec2 dirAngleVec = {};
	switch (mDir)
	{
	case DIR::LEFT:
		dirVec = Vec2(-1, 0);
		dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(10.f));
		break;

	case DIR::RIGHT:
		dirVec = Vec2(1, 0);
		dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(-10.f));
		break;
	}

	Pen pen(BACK_BUF_DC, _penType);
	dirAngleVec *= mInfo.mRecog;
	dirAngleVec = RENDER_POS(dirAngleVec + GetPos());

	dirVec *= mInfo.mRecog;
	dirVec = RENDER_POS(dirVec + GetPos());

	float offset = 30.f;

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)dirAngleVec.x, (int)(dirAngleVec.y - offset));

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y + mInfo.mRecog - offset));
}

void RedGiantBat::AttRangeLineRender(PEN_TYPE _penType)
{
	Vec2 monsterPos = RENDER_POS(GetPos());

	Vec2 dirVec = {};
	Vec2 dirAngleVec = {};
	switch (mDir)
	{
	case DIR::LEFT:
		dirVec = Vec2(-1, 0);
		dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(10.f));
		break;

	case DIR::RIGHT:
		dirVec = Vec2(1, 0);
		dirAngleVec = Math::RotateVector(dirVec, Math::DegreeToRadian(-10.f));
		break;
	}

	Pen pen(BACK_BUF_DC, _penType);
	dirAngleVec *= mInfo.mAttRange;
	dirAngleVec = RENDER_POS(dirAngleVec + GetPos());

	dirVec *= mInfo.mAttRange;
	dirVec = RENDER_POS(dirVec + GetPos());

	float offset = 30.f;

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)dirAngleVec.x, (int)(dirAngleVec.y - offset));

	MoveToEx(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y - offset), NULL);
	LineTo(BACK_BUF_DC, (int)monsterPos.x, (int)(monsterPos.y + mInfo.mAttRange - offset));
}

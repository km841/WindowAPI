#include "pch.h"
#include "HomingMissileEffect.h"
#include "KeyMgr.h"
#include "MouseMgr.h"
#include "MagicWandBullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "TimeMgr.h"
#include "EventRegisteror.h"
#include "Collider.h"
#include "Monster.h"
#include "Animation.h"
#include "Animator.h"
#include "CameraMgr.h"
#include "Item.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "LaraMagicWand.h"

HomingMissileEffect::HomingMissileEffect()
	: mAngleLimit(Math::DegreeToRadian(3.f))
	, mReload(false)
	, mReloadMaxDelay(1.0f)
	, mReloadDelay(0.f)
	, mAcc(0.f)
	, mVelocity(0.f)
	, mAnimStart(false)
{
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	mReloadBaseTex = ResourceMgr::GetInstance().Load<Texture>(L"ReloadBaseTex", L"Texture\\ReloadBase.bmp");
	mReloadTex = ResourceMgr::GetInstance().Load<Texture>(L"ReloadBarTex", L"Texture\\ReloadBar.bmp");

	Texture* reloadAnim = ResourceMgr::GetInstance().Load<Texture>(L"ReloadTex", L"Texture\\ReloadAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"ReloadAnim",
		reloadAnim,
		Vec2(0, 0),
		Vec2(81, 27),
		Vec2(81, 0),
		0.05f,
		4
	);


	mOffset = Vec2(0.f, -70.f);
	GetAnimator()->FindAnimation(L"ReloadAnim")->SetOffset(mOffset);
	GetAnimator()->FindAnimation(L"ReloadAnim")->SetEffectAnimation(true);
	mVelocity = (mReloadBaseTex->GetWidth() - 5) / mReloadMaxDelay;
}

HomingMissileEffect::~HomingMissileEffect()
{
}

void HomingMissileEffect::Update()
{
	Effect::Update();
	// ��Ŭ���� ������ źȯ �߻�

	LaraMagicWand* ownerItem = static_cast<LaraMagicWand*>(GetOwnerItem());
	if (ownerItem->GetCoolDownFlag())
	{
		float& curCoolDown = ownerItem->GetCurCoolDown();

		if (ownerItem->GetMaxCoolDown() < curCoolDown)
		{
			curCoolDown = 0.f;
			ownerItem->SetCoolDownFlag(false);

		}
		else
		{
			curCoolDown += DT;
		}
	}

	if (true == mAnimStart)
	{
		mReloadDelay = 0.f;
		mAcc = 0.f;
		mAnimStart = false;
		static_cast<Item*>(GetOwnerItem())->Reload();
	}

	if (mReload)
	{
		if (mReloadMaxDelay < mReloadDelay)
		{
			// �����ִϸ��̼�

			if (false == mAnimStart)
			{
				mAnimStart = true;
				mReload = false;
				GetAnimator()->SelectAnimation(L"ReloadAnim", false);
				GetAnimator()->GetCurAnimation()->Reset();
			}
		}

		else
		{
			mReloadDelay += DT;
			mAcc += mVelocity * DT;
		}
	}

	if (IS_JUST_LBUTTON_CLICKED && false == mReload)
	{
		GameObject* target = 
			SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);

		// �߻��� �������� �� ���ư��ٰ�
		// Ÿ���� ���� ����

		// ���콺��ġ - �÷��̾� ��ġ

		if (nullptr != target)
		{
			Item* owner = static_cast<Item*>(GetOwnerItem());
			ItemInfo& info = owner->GetItemInfo();

			if (0.f < info.mAmmo)
			{
				info.mAmmo--;

				MagicWandBullet* bullet = new MagicWandBullet;
				bullet->SetPos(GetPos());

				Vec2 mousePos = MOUSE_POS;
				Vec2 playerPos = RENDER_POS(Player::GetPlayer()->GetPos());

				Vec2 dirVec = mousePos - playerPos;
				dirVec.Norm();

				bullet->SetInitDirVector(dirVec);
				bullet->SetTarget(target);
				mBullets.push_back(bullet);
				EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
			}

			else if (0.f == info.mAmmo)
			{
				mReload = true;
			}			
		}
	}

	if (IS_JUST_PRESSED(KEY::Q) && false == ownerItem->GetCoolDownFlag())
	{
		

		GameObject* target =
			SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);

		// �߻��� �������� �� ���ư��ٰ�
		// Ÿ���� ���� ����

		// ���콺��ġ - �÷��̾� ��ġ

		if (nullptr != target)
		{
			ownerItem->SetCoolDownFlag(true);
			// 8����
			Vec2 dirArray[] = {
				Vec2(-1, -1),
				Vec2(0, -1),
				Vec2(1, -1),
				Vec2(1, 0),
				Vec2(1, 1),
				Vec2(0, 1),
				Vec2(-1, 1),
				Vec2(-1, 0),
			};

			for (int i = 0; i < std::size(dirArray); ++i)
			{
				MagicWandBullet* bullet = new MagicWandBullet;
				bullet->SetPos(GetPos());
				bullet->SetInitDirVector(dirArray[i]);
				bullet->SetTarget(target);
				mBullets.push_back(bullet);
				EventRegisteror::GetInstance().CreateObject(bullet, bullet->GetType());
			}

		}
	}


	std::vector<MagicWandBullet*>::iterator iter = mBullets.begin();
	for (; iter != mBullets.end();)
	{
		// �÷��̾� ��ġ�� ���� �����̻���
		// Ÿ���� �������� ��
		// ���� ����� ���͸� ã�� �� ���Ϳ��� �Ÿ��� ����
		// Ÿ���� ������� ���ο� Ÿ������ ����
		// ���� ��ġ

		if (BULLET_STATE::DEAD_ANIM == iter.operator*()->GetBulletState())
		{
			++iter;
			continue;
		}

		if (BULLET_STATE::DEAD == iter.operator*()->GetBulletState())
		{
			EventRegisteror::GetInstance().DeleteObject(*iter);
			iter = mBullets.erase(iter);
			continue;
		}

		Monster* monster = static_cast<Monster*>(iter.operator*()->GetTarget());

		if (monster->IsDead())
		{
			// Ÿ���� ���� ��� Ÿ�� ����
			iter.operator*()->SetTarget(nullptr);
			GameObject* target =
				SceneMgr::GetInstance().GetCurScene()->GetNearestObject(Player::GetPlayer(), OBJECT_TYPE::MONSTER);
			if (nullptr != target)
				iter.operator*()->SetTarget(target);
		}

		// Ÿ���� ������ �Ҹ�
		if (nullptr == iter.operator*()->GetTarget())
		{
			iter.operator*()->SetBulletState(BULLET_STATE::DEAD_ANIM);
			iter.operator*()->GetAnimator()->SelectAnimation(L"LaraBulletHit", false);
			break;
		}
		
		// Ÿ���� ���⺤�͸� ���ؼ� �Ѿ��� �ӵ��� ����
		float initCurDuration = iter.operator*()->GetInitCurDuration();
		float initMaxDuration = iter.operator*()->GetInitMaxDuration();

		Vec2 bulletPos = iter.operator*()->GetPos();
		float bulletSpeed = iter.operator*()->GetBulletInfo().mSpeed;

		Vec2 dir = iter.operator*()->GetSpeedVector();
		if (Vec2(0.f, 0.f) == dir)
		{
			dir = iter.operator*()->GetInitDirVector();
		}

		if (initCurDuration < initMaxDuration)
		{
			// initDir �������� ���ư���
			Vec2 initDir = iter.operator*()->GetInitDirVector();

			iter.operator*()->SetSpeedVector(initDir);
			bulletPos += initDir * bulletSpeed * DT;
			initCurDuration += DT;
			iter.operator*()->SetInitCurDuration(initCurDuration);
		}

		else
		{
			Vec2 targetPos = iter.operator*()->GetTarget()->GetCollider()->GetPos();
			Vec2 targetVec = targetPos - bulletPos;

			// ����
			float curAngle = atan2(dir.y, dir.x);
			float targetAngle = atan2(targetVec.y, targetVec.x);
			float distance = targetVec.Len();

			float limit = mAngleLimit;

			if (distance > WINDOW_WIDTH_SIZE * 0.75f)
			{
				dir += targetVec;
				dir.Norm();
			}

			else if (curAngle > targetAngle)
			{
				if (curAngle - targetAngle > limit)
				{
					dir = Math::RotateVector(dir, -limit);
				}

				else
				{
					dir = Math::RotateVector(dir, -(curAngle - targetAngle));
				}

			}
			else if (curAngle < targetAngle)
			{
				if (targetAngle - curAngle > limit)
				{
					dir = Math::RotateVector(dir, limit);
				}

				else
				{
					dir = Math::RotateVector(dir, (targetAngle - curAngle));
				}
			}

			bulletPos += dir * bulletSpeed * DT;
		}

		iter.operator*()->SetSpeedVector(dir);
		iter.operator*()->SetPos(bulletPos);
		++iter;
	}
	
}

void HomingMissileEffect::Render()
{
	Effect::Render();

	if (mReload)
	{
		Vec2 baseSize = mReloadBaseTex->GetSize();
		Vec2 barSize = mReloadTex->GetSize();

		Vec2 pos = RENDER_POS(GetPos());
		Vec2 reloadBasePos = pos + mOffset;

		BitBlt(
			BACK_BUF_DC,
			(int)(reloadBasePos.x - baseSize.x / 2.f),
			(int)(reloadBasePos.y - baseSize.y / 2.f),
			(int)(baseSize.x),
			(int)(baseSize.y),
			mReloadBaseTex->GetDC(),
			0, 0,
			SRCCOPY
		);

		BitBlt(
			BACK_BUF_DC,
			(int)((reloadBasePos.x - (baseSize.x / 2.f)) + mAcc),
			(int)((reloadBasePos.y - (barSize.y / 2.f))),
			(int)(barSize.x),
			(int)(barSize.y),
			mReloadBaseTex->GetDC(),
			0, 0,
			SRCCOPY
		);

		
		
	}

}

void HomingMissileEffect::Destroy()
{
}

void HomingMissileEffect::Change()
{
	std::vector<MagicWandBullet*>::iterator iter = mBullets.begin();

	for (; iter != mBullets.end();)
	{
		EventRegisteror::GetInstance().DeleteObject(*iter);
		iter = mBullets.erase(iter);
	}

	mBullets.clear();
}

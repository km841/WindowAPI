#include "pch.h"
#include "Weapon.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "MouseMgr.h"
#include "Animation.h"
#include "Animator.h"
#include "Effect.h"
#include "PlayerEffect.h"

Weapon::Weapon()
	: mState(SWORD_STATE::UP_STATE)
	, mPrevState(SWORD_STATE::UP_STATE)
	, mAngle(0.f)
	, mDuration(0.f)
	, mEffect(nullptr)
	, mTransTexture(nullptr)
	, mXAxisDirOffset{}
	, mYAxisOffset(0.f)
	, mAngleOffset(0.f)
	, mOffset{}
	, mRotatedVertices{}
	, mVertices{}
	, mDir(DIR::END)
	, mLeftTexture(nullptr)
	, mRightTexture(nullptr)
{
	
}

Weapon::~Weapon()
{

}

void Weapon::Initialize()
{
	Texture* tex = GetTexture();
	mVertices[(UINT)VERTICES_POINT::LEFT_TOP] = Vec2(0.f, 0.f);
	mVertices[(UINT)VERTICES_POINT::RIGHT_TOP] = Vec2(tex->GetSize().x , 0.f);
	mVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM] = Vec2(0.f, tex->GetSize().y);
}

void Weapon::Update()
{
	// pos를 정하는건? 플레이어 기준 offset
	// 마우스 위치에 따라 각도 변경
	Player* player = Player::GetPlayer();

	if (nullptr != player) {

		Texture* tex = GetTexture();
		Vec2 playerPos = player->GetPos();
		DIR playerDir = player->GetPlayerDir();

		Vec2 dirVec = { 0, 0 };
		float times = 1.f;
		switch (playerDir)
		{
		case DIR::LEFT:
			dirVec = Vec2(-100, 0);
			break;
		case DIR::RIGHT:
			dirVec = Vec2(100, 0);
			break;
		}
		Vec2 mouseRenVector = MOUSE_POS - RENDER_POS(playerPos);

		float angle = (float)atan2(mouseRenVector.y, mouseRenVector.x) * times;
		angle -= PI / 2.f;

		mAngle = angle + PI;

		if (SWORD_STATE::DOWN_STATE == mState)
		{
			switch (playerDir)
			{
			case DIR::LEFT:
				angle -= (float)(PI - (PI / 6.0));
				break;
			case DIR::RIGHT:
				angle += (float)(PI + (PI / 6.0));
				break;
			}
		}

		angle += mAngleOffset;

		if (DIR::END != mDir)
		{
			switch (mDir)
			{
			case DIR::LEFT:
				//angle += PI;
				break;

			case DIR::RIGHT:
				break;
			}
		}

		Vec2 rotOffset = GetOffset();
		rotOffset.Norm();

		float offsetDistance = 30.f;
		rotOffset = Math::RotateVector(rotOffset, angle);
		rotOffset = rotOffset * offsetDistance;

		Vec2 textureAnchor = tex->GetSize() / 2.f;

		for (int i = 0; i < (UINT)VERTICES_POINT::END; ++i)
		{
			mRotatedVertices[i] = mVertices[i] - textureAnchor;
		}
		
		float distances[(UINT)VERTICES_POINT::END] = {
			mRotatedVertices[(UINT)VERTICES_POINT::LEFT_TOP].Len(),
			mRotatedVertices[(UINT)VERTICES_POINT::RIGHT_TOP].Len(),
			mRotatedVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM].Len(),
		};

		for (int i = 0; i < (UINT)VERTICES_POINT::END; ++i)
		{
			mRotatedVertices[i].Norm();
			mRotatedVertices[i] = Math::RotateVector(mRotatedVertices[i], angle);
		}

		for (int i = 0; i < (UINT)VERTICES_POINT::END; ++i)
		{
			mRotatedVertices[i] = (mRotatedVertices[i] * distances[i]) + textureAnchor;
		}
		
		SetPos(playerPos + rotOffset);
	}

	//GameObject::Update();
}

void Weapon::Render()
{
	// 각도에 따라 렌더링
	Texture* tex = GetTexture();
	Texture* transTex = GetTransTexture();
	Vec2 size = GetSize();

	if (nullptr != tex && nullptr != transTex)
	{
		Brush brush(transTex->GetDC(), BRUSH_TYPE::MAGENTA);
		Rectangle(
			transTex->GetDC(), -1, -1
			, (int)(transTex->GetSize().x + 1)
			, (int)(transTex->GetSize().y + 1));

		POINT points[(UINT)VERTICES_POINT::END] = {
			mRotatedVertices[(UINT)VERTICES_POINT::LEFT_TOP],
			mRotatedVertices[(UINT)VERTICES_POINT::RIGHT_TOP],
			mRotatedVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM]
		};

		if (DIR::END != mDir)
		{
			if (DIR::LEFT == mDir)
			{
				PlgBlt(
					transTex->GetDC(),
					points,
					mLeftTexture->GetDC(),
					0, 0,
					(int)transTex->GetSize().x,
					(int)transTex->GetSize().y,
					NULL,
					0, 0
				);
			}

			else
			{
				PlgBlt(
					transTex->GetDC(),
					points,
					mRightTexture->GetDC(),
					0, 0,
					(int)transTex->GetSize().x,
					(int)transTex->GetSize().y,
					NULL,
					0, 0
				);
			}
		}

		else
		{
			PlgBlt(
				transTex->GetDC(),
				points,
				tex->GetDC(),
				0, 0,
				(int)transTex->GetSize().x,
				(int)transTex->GetSize().y,
				NULL,
				0, 0
			);
		}


		Player* player = Player::GetPlayer();
		DIR dir = player->GetPlayerDir();

		float offsetX = 0.f;
		float offsetY = GetYOffset();

		switch (dir)
		{
		case DIR::LEFT:
			offsetX = GetLeftDirOffset();
			break;

		case DIR::RIGHT:
			offsetX = GetRightDirOffset();
			break;
		}

		Vec2 pos = RENDER_POS(GetPos());
		TransparentBlt(
			BACK_BUF_DC,
			(int)(pos.x - size.x + offsetX),
			(int)(pos.y - size.y + offsetY),
			(int)size.x,
			(int)size.y,
			transTex->GetDC(),
			0, 0,
			(int)transTex->GetSize().x,
			(int)transTex->GetSize().y,
			RGB(255, 0, 255)
			
		);
	}
}

void Weapon::Destroy()
{
	
	if (nullptr != mEffect)
	{
		mEffect->Destroy();
		delete mEffect;
		mEffect = nullptr;
	}
}

void Weapon::ChangeSwordState()
{
	mState = (SWORD_STATE)(((UINT)mState + 1) % 2);
}

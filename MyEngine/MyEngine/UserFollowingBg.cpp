#include "pch.h"
#include "UserFollowingBg.h"
#include "Player.h"
#include "TimeMgr.h"
#include "Texture.h"
#include "CameraMgr.h"

UserFollowingBg::UserFollowingBg(bool _renderMode)
	:mSpeed(0.f)
	,mTimes(1.f)
	,mPlayer(nullptr)
	,mTexture(nullptr)
	,mRenderMode(_renderMode)
{
}

UserFollowingBg::~UserFollowingBg()
{
}

void UserFollowingBg::Initialize()
{
}

void UserFollowingBg::Update()
{
	if (nullptr != mPlayer)
	{ 
		Vec2 playerPos = mPlayer->GetPos();
		Vec2 playerPrevPos = mPlayer->GetPrevPos();
		Vec2 playerDir =  playerPos - playerPrevPos;

		float playerSpeed = mPlayer->GetPlayerSpeed();
		// 플레이어 속도 : 플레이어 이동거리 = 내 속도 : 내 이동거리
		Vec2 distance = (playerDir * mSpeed / playerSpeed);
		if (distance.y < 0.f)
		{
			int a = 0;
		}
		
		Vec2 pos = GetPos();
		pos += distance;

		SetPos(pos);
	}
}

void UserFollowingBg::Render()
{
	if (nullptr == GetTexture())
		return;

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	if (mRenderMode)
		pos = RENDER_POS(pos);


	TransparentBlt(
		BACK_BUF_DC,
		(int)pos.x,
		(int)pos.y,
		(int)size.x,
		(int)size.y,
		GetTexture()->GetDC(),
		0,
		0,
		(int)(size.x / mTimes),
		(int)(size.y / mTimes),
		RGB(255, 0, 255)
	);
}

void UserFollowingBg::Destroy()
{
}

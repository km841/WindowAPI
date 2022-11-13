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
		Vec2 playerPos = GetPos();
		Vec2 pos = GetPos();

		if (mPlayer->IsLeftMove())
			pos.x -= mSpeed * DT;

		if (mPlayer->IsRightMove())
			pos.x += mSpeed * DT;

		if (mPlayer->IsUpMove())
			pos.y -= (mSpeed * 2.f) * DT ;
		
		if (mPlayer->isDownMove())
			pos.y += (mSpeed * 2.f) * DT;

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

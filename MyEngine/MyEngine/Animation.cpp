#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"
#include "Texture.h"
#include "TimeMgr.h"

Animation::Animation()
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (mAnim.empty())
		return;

	mAccTime += DT;

	if (mAccTime >= mAnim[mCurFrm].mDuration)
	{
		++mCurFrm;

		if (mCurFrm >= mAnim.size())
			mCurFrm = 0;
		
		mAccTime = 0;
	}
}

void Animation::Render()
{
	if (mAnim.empty())
		return;

	GameObject* ownerObject = mOwner->GetOwner();
	Vec2		pos = ownerObject->GetPos();
	Vec2		scale = ownerObject->GetScale();

	TransparentBlt(
		BACK_BUF_DC
		, (int)(pos.x - (mAnim[mCurFrm].mSlice.x * scale.x) / 2.f)
		, (int)(pos.y - (mAnim[mCurFrm].mSlice.y * scale.y) / 2.f)
		, (int)(mAnim[mCurFrm].mSlice.x * scale.x)
		, (int)(mAnim[mCurFrm].mSlice.y * scale.y)
		, mTex->GetDC()
		, (int)(mAnim[mCurFrm].mLeftTop.x)
		, (int)(mAnim[mCurFrm].mLeftTop.y)
		, (int)(mAnim[mCurFrm].mSlice.x)
		, (int)(mAnim[mCurFrm].mSlice.y)
		, RGB(255, 0, 255)
	);
}

void Animation::Create(Texture* _tex, Vec2 _leftTop, Vec2 _slice, Vec2 _offset, float _duration, UINT _frmCount)
{
	mTex = _tex;
	AnimInfo anim = {};

	for (UINT i = 0; i < _frmCount; ++i)
	{
		anim.mLeftTop = _leftTop + (_offset * (float)i);
		anim.mSlice = _slice;
		anim.mDuration = _duration;
		
		mAnim.push_back(anim);
	}
}

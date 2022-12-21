#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "GameObject.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "CameraMgr.h"
#include "GameObject.h"
#include "EventRegisteror.h"
#include "Player.h"

Animation::Animation()
	: mFinish(false)
	, mOwner(nullptr)
	, mName{}
	, mAnim{}
	, mCurFrm(0)
	, mAccTime(0.f)
	, mRepeat(false)
	, mEffect(false)
	, mEvent{}
	, mDummyObj(nullptr)
	, mOffset(ZERO_VECTOR)
{
	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 255;
}

Animation::~Animation()
{
	if (nullptr != mEvent)
	{
		delete mEvent;
		mEvent = nullptr;
	}

	if (nullptr != mDummyObj)
	{
		delete mDummyObj;
		mDummyObj = nullptr;
	}
}

void Animation::Update()
{
	if (mFinish)
		return;

	if (mFix)
		return;

	if (mAnim.empty())
		return;

	mAccTime += DT;

	if (mAccTime >= mAnim[mCurFrm].mDuration)
	{
		++mCurFrm;

		if (mCurFrm >= mAnim.size())
		{
			switch (mRepeat)
			{
			case TRUE: mCurFrm = 0;
				break;

			case FALSE: mFinish = true;
				break;
			}

			if (nullptr != mDummyObj)
			{
				mDummyObj->GetAnimator()->SelectAnimation(mEvent->mEnter.mName);
			}
		}
		
		mAccTime = 0;
	}

	if (nullptr != mDummyObj)
	{
		Vec2 ownerPos = mOwner->GetOwner()->GetPos();
		
		mDummyObj->SetPos(ownerPos + mEvent->mEnter.mOffset);
		mDummyObj->Update();
	}
}

void Animation::Render()
{
	if (mFinish)
		return;

	if (mAnim.empty())
		return;

	GameObject* ownerObject = mOwner->GetOwner();
	Vec2		pos = ownerObject->GetPos();
	Vec2		offset = GetOffset();

	if (offset.x != 0.f || offset.y != 0.f)
	{
		pos += offset;
	}

	// Convert RenderPos
	pos = RENDER_POS(pos);
	float divideY = 1.f;
	if (mEffect)
	{
		divideY = 2.f;
	}

	// 알파블렌드로 출력하되 투명도만 다르도록
	// 피격중이면 flag를 통해 알리고 그 flag가 on이면 반투명
	//mBlendFunc.SourceConstantAlpha = 255;
	Player* player = Player::GetPlayer();
	if (mOwner->GetOwner() == player)
	{
		if (player->IsHit())
		{
			mBlendFunc.SourceConstantAlpha = 127;
			AlphaBlend(
				BACK_BUF_DC
				, (int)(pos.x - mAnim[mCurFrm].mSlice.x / 2.f)
				, (int)(pos.y - mAnim[mCurFrm].mSlice.y / divideY)
				, (int)(mAnim[mCurFrm].mSlice.x)
				, (int)(mAnim[mCurFrm].mSlice.y)
				, mTex->GetDC()
				, (int)(mAnim[mCurFrm].mLeftTop.x)
				, (int)(mAnim[mCurFrm].mLeftTop.y)
				, (int)(mAnim[mCurFrm].mSlice.x)
				, (int)(mAnim[mCurFrm].mSlice.y)
				, mBlendFunc
			);
		}


		else
		{
			mBlendFunc.SourceConstantAlpha = 255;
			TransparentBlt(
				BACK_BUF_DC
				, (int)(pos.x - mAnim[mCurFrm].mSlice.x / 2.f)
				, (int)(pos.y - mAnim[mCurFrm].mSlice.y / divideY)
				, (int)(mAnim[mCurFrm].mSlice.x)
				, (int)(mAnim[mCurFrm].mSlice.y)
				, mTex->GetDC()
				, (int)(mAnim[mCurFrm].mLeftTop.x)
				, (int)(mAnim[mCurFrm].mLeftTop.y)
				, (int)(mAnim[mCurFrm].mSlice.x)
				, (int)(mAnim[mCurFrm].mSlice.y)
				, RGB(255, 0, 255)
			);
		}
	}
	
	else
	{
		TransparentBlt(
   			BACK_BUF_DC
   			, (int)(pos.x - mAnim[mCurFrm].mSlice.x / 2.f)
   			, (int)(pos.y - mAnim[mCurFrm].mSlice.y / divideY)
   			, (int)(mAnim[mCurFrm].mSlice.x)
   			, (int)(mAnim[mCurFrm].mSlice.y)
   			, mTex->GetDC()
   			, (int)(mAnim[mCurFrm].mLeftTop.x)
   			, (int)(mAnim[mCurFrm].mLeftTop.y)
   			, (int)(mAnim[mCurFrm].mSlice.x)
   			, (int)(mAnim[mCurFrm].mSlice.y)
   			, RGB(255, 0, 255)
		   );
	}





	

	if (nullptr != mDummyObj)
	{
		mDummyObj->Render();
	}

	
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

void Animation::SetEnterEvent(EventAnimation _event)
{
	if (nullptr == mEvent)
	{
		mEvent = new Event;

		if (nullptr == mDummyObj)
		{
			mDummyObj = new GameObject;
			mDummyObj->CreateComponent(new Animator);
			_event.mAnim->mOwner = mDummyObj->GetAnimator();
			mDummyObj->GetAnimator()->SetOwner(mDummyObj);
			mDummyObj->GetAnimator()->AddAnimation(_event.mName, _event.mAnim);
			mDummyObj->GetAnimator()->SelectAnimation(_event.mName);

			Vec2 ownerPos = mOwner->GetOwner()->GetPos();
			mDummyObj->SetPos(ownerPos + _event.mOffset);
			mDummyObj->SetSize(_event.mSize);
		}
		else
		{
			mDummyObj->GetAnimator()->AddAnimation(_event.mName, _event.mAnim);
		}
		
	}
	mEvent->mEnter = _event; 
}

void Animation::SetExitEvent(EventAnimation _event)
{
	if (nullptr == mEvent)
	{
		mEvent = new Event;
		mDummyObj = new GameObject;
		mDummyObj->CreateComponent(new Animator);

		Vec2 ownerPos = mOwner->GetOwner()->GetPos();
		mDummyObj->SetPos(ownerPos + _event.mOffset);
		mDummyObj->SetSize(_event.mSize);
	}

	mEvent->mExit = _event;
}

void Animation::Reset()
{
	mCurFrm = 0;
	mFinish = false;
}

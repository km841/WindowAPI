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
	, mTransMode(TRANS_MODE::END)
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
	if (true == mFinish)
		return;

	if (true == mFix)
		return;

	if (mAnim.empty())
		return;

	mAccTime += DT;

	if (true == mTrans)
	{
		if (mTransMaxTime < mTransCurTime)
		{
			mTrans = false;
			mTransCurTime = 0.f;
			mTransMode = TRANS_MODE::END;
		}
		else
		{
			mTransCurTime += DT;
		}
		
	}

	if (mAccTime >= mAnim[mCurFrm].mDuration)
	{
		++mCurFrm;

		if (mCurFrm >= mAnim.size())
		{

			if (true == mRepeat)
			{
				mCurFrm = 0;
			}

			else
			{
				mFinish = true;
			}

			//if (true == mTrans)
			//{
			//	mTransCurTime = 0.f;
			//}

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

	if (false == offset.IsZero())
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
				, (int)(pos.x - (mAnim[mCurFrm].mSlice.x / 2.f) + mAnim[mCurFrm].mControl.x)
				, (int)(pos.y - (mAnim[mCurFrm].mSlice.y / divideY) + mAnim[mCurFrm].mControl.y)
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
				, (int)(pos.x - (mAnim[mCurFrm].mSlice.x / 2.f) + mAnim[mCurFrm].mControl.x)
				, (int)(pos.y - (mAnim[mCurFrm].mSlice.y / divideY) + mAnim[mCurFrm].mControl.y)
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
		// 애니메이션의 투명플래그가 true면 알파블렌드로 처리
		// 근데 알파값을 어떻게?
		// 알파값은 게임오브젝트의 변수에 있는 값을 사용
		// visible 설정과 함께 시간을 전달, 그럼 그 시간에 걸쳐 점차 투명해짐
		if (mTrans)
		{
			float ratio = 0.f;

			switch (mTransMode)
			{
			case TRANS_MODE::FADE_IN:
				ratio = mTransCurTime / mTransMaxTime;
				break;

			case TRANS_MODE::FADE_OUT:
				ratio = 1.f - (mTransCurTime / mTransMaxTime);
				break;
			}

			if (ratio < 0.f)
				ratio = 0.f;

			if (ratio > 255.f)
				ratio = 255.f;

			mBlendFunc.SourceConstantAlpha = (BYTE)(255.f * ratio);

			AlphaBlend(
				BACK_BUF_DC
				, (int)(pos.x - (mAnim[mCurFrm].mSlice.x / 2.f) + mAnim[mCurFrm].mControl.x)
				, (int)(pos.y - (mAnim[mCurFrm].mSlice.y / divideY) + mAnim[mCurFrm].mControl.y)
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
			TransparentBlt(
				BACK_BUF_DC
				, (int)(pos.x - (mAnim[mCurFrm].mSlice.x / 2.f) + mAnim[mCurFrm].mControl.x)
				, (int)(pos.y - (mAnim[mCurFrm].mSlice.y / divideY) + mAnim[mCurFrm].mControl.y)
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
		anim.mOffset = _offset;
		
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

void Animation::SetFrameControl(int _frame, Vec2 _control)
{
	if ((int)mAnim.size() <= (_frame - 1))
		return;

	AnimInfo& info = mAnim[_frame];
	info.mControl = _control;
}

void Animation::SetFrameDuration(int _frame, float _duration)
{
	if (mAnim.size() <= (_frame - 1))
		return;

	AnimInfo& info = mAnim[_frame];
	info.mDuration = _duration;
}

void Animation::SetTransMode(bool _flag, float _maxTime, TRANS_MODE _mode)
{
	mTransCurTime = 0.f;
	mTransMaxTime = _maxTime;
	mTrans = _flag;
	mTransMode = _mode;
}

void Animation::Reset()
{
	mCurFrm = 0;
	mFinish = false;
}

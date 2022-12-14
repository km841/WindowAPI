#include "pch.h"
#include "WalkState.h"
#include "Player.h"
#include "Animator.h"
#include "Animation.h"
#include "Effect.h"

WalkState::WalkState(Player* _obj)
	: State(_obj)
{
	mName = L"WALK";
}

void WalkState::Enter()
{
	Animation* anim = nullptr;

	if (IS_PLAYER)
	{
		switch (mPlayer->mDir)
		{
		case DIR::LEFT:
			anim = mPlayer->GetAnimator()->FindAnimation(L"PLAYER_WALK_LEFT");
			anim->Reset();
			mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_WALK_LEFT");
			break;

		case DIR::RIGHT:
			anim = mPlayer->GetAnimator()->FindAnimation(L"PLAYER_WALK_RIGHT");
			anim->Reset();
			mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_WALK_RIGHT");
			break;
		}

	}
	else
	{
		switch (mPlayer->mDir)
		{
		case DIR::LEFT:
			anim = mPlayer->GetAnimator()->FindAnimation(L"LASLEY_WALK_LEFT");
			anim->Reset();
			mPlayer->GetAnimator()->SelectAnimation(L"LASLEY_WALK_LEFT");
			break;

		case DIR::RIGHT:
			anim = mPlayer->GetAnimator()->FindAnimation(L"LASLEY_WALK_RIGHT");
			anim->Reset();
			mPlayer->GetAnimator()->SelectAnimation(L"LASLEY_WALK_RIGHT");
			break;
		}
	}

}

void WalkState::Exit()
{
}

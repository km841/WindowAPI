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

	switch (mPlayer->mDir)
	{
	case PLAYER_DIR::LEFT:
		anim = mPlayer->GetAnimator()->FindAnimation(L"PLAYER_WALK_LEFT");
		anim->Reset();
		mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_WALK_LEFT");
		break;

	case PLAYER_DIR::RIGHT:
		anim = mPlayer->GetAnimator()->FindAnimation(L"PLAYER_WALK_RIGHT");
		anim->Reset();
		mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_WALK_RIGHT");
		break;
	}
}

void WalkState::Exit()
{
}

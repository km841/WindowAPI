#include "pch.h"
#include "IdleState.h"
#include "Player.h"
#include "Animation.h"
#include "Animator.h"

IdleState::IdleState(Player* _obj)
	:State(_obj)
{
	mName = L"IDLE";
}

void IdleState::Enter()
{
	Animation* anim = nullptr;
	switch (mPlayer->mDir)
	{
	case PLAYER_DIR::LEFT:
		anim = mPlayer->GetAnimator()->FindAnimation(L"PLAYER_IDLE_LEFT");
		anim->Reset();
		mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_IDLE_LEFT");
		break;

	case PLAYER_DIR::RIGHT:
		anim = mPlayer->GetAnimator()->FindAnimation(L"PLAYER_IDLE_RIGHT");
		anim->Reset();
		mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
		break;
	}
}

void IdleState::Exit()
{

}

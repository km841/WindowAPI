#include "pch.h"
#include "JumpState.h"
#include "Player.h"
#include "Animation.h"
#include "Animator.h"

JumpState::JumpState(Player* _obj)
	:State(_obj)
{
}

void JumpState::Enter()
{
	Animation* anim = nullptr;
	switch (mPlayer->mDir)
	{
	case PLAYER_DIR::LEFT:
		mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_JUMP_LEFT");
		break;

	case PLAYER_DIR::RIGHT:
		mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_JUMP_RIGHT");
		break;
	}

	//mPlayer->SetGround(false);
	//mPlayer->SetGravity(true);
}

void JumpState::Exit()
{
	//mPlayer->SetGround(true);
	//mPlayer->SetGravity(false);
}

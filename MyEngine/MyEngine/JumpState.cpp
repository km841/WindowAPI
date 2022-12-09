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

	if (IS_PLAYER)
	{
		switch (mPlayer->mDir)
		{
		case DIR::LEFT:
			mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_JUMP_LEFT");
			break;

		case DIR::RIGHT:
			mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_JUMP_RIGHT");
			break;
		}
	}

	else
	{
		switch (mPlayer->mDir)
		{
		case DIR::LEFT:
			mPlayer->GetAnimator()->SelectAnimation(L"LASLEY_JUMP_LEFT");
			break;

		case DIR::RIGHT:
			mPlayer->GetAnimator()->SelectAnimation(L"LASLEY_JUMP_RIGHT");
			break;
		}
	}



	//mPlayer->SetGround(false);
	//mPlayer->SetGravity(true);
}

void JumpState::Exit()
{
	//mPlayer->SetGround(true);
	//mPlayer->SetGravity(false);
}

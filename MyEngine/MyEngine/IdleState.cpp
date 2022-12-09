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
	if (IS_PLAYER)
	{
		switch (mPlayer->mDir)
		{
		case DIR::LEFT:
			anim = mPlayer->GetAnimator()->FindAnimation(L"PLAYER_IDLE_LEFT");
			anim->Reset();
			mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_IDLE_LEFT");
			break;

		case DIR::RIGHT:
			anim = mPlayer->GetAnimator()->FindAnimation(L"PLAYER_IDLE_RIGHT");
			anim->Reset();
			mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_IDLE_RIGHT");
			break;
		}
	}

	else
	{
		switch (mPlayer->mDir)
		{
		case DIR::LEFT:
			anim = mPlayer->GetAnimator()->FindAnimation(L"LASLEY_IDLE_LEFT");
			anim->Reset();
			mPlayer->GetAnimator()->SelectAnimation(L"LASLEY_IDLE_LEFT");
			break;

		case DIR::RIGHT:
			anim = mPlayer->GetAnimator()->FindAnimation(L"LASLEY_IDLE_RIGHT");
			anim->Reset();
			mPlayer->GetAnimator()->SelectAnimation(L"LASLEY_IDLE_RIGHT");
			break;
		}
	}
	

}

void IdleState::Exit()
{

}

#include "pch.h"
#include "EatState.h"
#include "Player.h"
#include "Animation.h"
#include "Animator.h"

EatState::EatState(Player* _obj)
	:State(_obj)
{
}

void EatState::Enter()
{
	mPlayer->GetAnimator()->SelectAnimation(L"PLAYER_NONE_ANIM", false);
	mPlayer->SetStop(true);
}

void EatState::Exit()
{
}

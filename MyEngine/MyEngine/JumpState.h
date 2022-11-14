#pragma once
#include "State.h"
class JumpState :
    public State
{
public:
	JumpState(Player* _obj);
	virtual ~JumpState() {};

	virtual void Enter() override;
	virtual void Exit() override;

private:

};


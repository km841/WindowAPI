#pragma once
#include "State.h"
class WalkState :
    public State
{
public:
	WalkState(Player* _obj);
	virtual ~WalkState() {};

	virtual void Enter() override;
	virtual void Exit() override;

private:


};


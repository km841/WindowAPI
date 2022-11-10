#pragma once
#include "State.h"
class IdleState :
    public State
{
public:
	IdleState(Player* _obj);
	virtual ~IdleState() {};

	virtual void Enter() override;
	virtual void Exit() override;

private:

};


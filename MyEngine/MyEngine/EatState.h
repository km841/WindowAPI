#pragma once
#include "State.h"
class EatState :
    public State
{
public:
	EatState(Player* _obj);
	virtual ~EatState() {};

	virtual void Enter() override;
	virtual void Exit() override;

private:

};


#pragma once
class State
{
public:
	State() {};
	virtual ~State() {};

	virtual void Enter() = 0;
	virtual void Exit() = 0;

private:


};


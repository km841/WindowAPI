#pragma once

class Player;
class State
{
public:
	State(Player* _obj);
	virtual ~State() {};

	void operator()(Player* _obj) { mPlayer = _obj; }

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	inline const std::wstring& GetName() const { return mName; }

protected:
	Player* mPlayer;
	std::wstring mName;
};


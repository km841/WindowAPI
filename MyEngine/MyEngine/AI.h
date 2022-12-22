#pragma once

class Monster;
class MonsterState;
class AI
{
public:
	AI() {}
	~AI();


public:
	// AI는 여러 상태들을 갖고 있음
	// Monster는 AI를 통해 상태를 전달받고 그 상태의 Update에서 동작을 정의
	void Update();
	void Render();

public:
	void AddState(MonsterState* _state);

	template<typename ... Types>
	void AddStates(Types* ... _args)
	{
		auto unreferenced = { 0, (AddState(_args), 0)... };
	}

	MonsterState* FindState(MONSTER_STATE _eState);

	inline MonsterState* GetCurState() const { return mCurState; }

	void ChangeState(MONSTER_STATE _eState);

public:
	inline Monster* GetOwnerMonster() const { return mOwner; }
	inline void SetOwnerMonster(Monster* _monster) { mOwner = _monster; }
	

private:
	Monster* mOwner;
	MonsterState* mCurState;

	std::map<MONSTER_STATE, MonsterState*> mStateMap;

};


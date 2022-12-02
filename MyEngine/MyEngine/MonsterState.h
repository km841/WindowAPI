#pragma once
class AI;
class MonsterState
{
public:
	MonsterState(MONSTER_STATE _eState);
	virtual ~MonsterState() {}

public:
	virtual void Update() = 0;
	virtual void Render() {}

	virtual void Enter() = 0;
	virtual void Exit() = 0;

public:
	bool PlayerCheck(MONSTER_TYPE _type, float _angle, float _range);

public:
	inline MONSTER_STATE GetMonsterState() const { return mState; }

	inline void SetOwnerAI(AI* _ai) { mOwner = _ai; }
	inline AI*  GetOwnerAI() const { return mOwner; }


private:
	MONSTER_STATE mState;
	AI* mOwner;
};


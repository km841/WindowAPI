#pragma once
#include "EventObject.h"


class Monster;
class MonsterSpawnEvent :
    public EventObject
{
public:
    MonsterSpawnEvent(MONSTER_TYPE _monType);
    virtual ~MonsterSpawnEvent();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void Spawn() = 0;

public:
    inline void SetSpawnPos(Vec2 _pos) { mSpawnPos = _pos; };

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

    // 특정 오브젝트를 밟으면 몬스터 소환
    // 특정 프레임이 되면 애니메이션을 정지하고 몬스터를 소환한다.

protected:
    bool mFlag;
    int  mSpawnTiming;
    Vec2 mSpawnPos;
    MONSTER_TYPE mMonsterType;

};


#pragma once
#include "BossMonster.h"

class BelialHand;
class Belial :
    public BossMonster
{
public:
    Belial();
    virtual ~Belial();

    static constexpr MONSTER_TYPE TYPE = MONSTER_TYPE::BOSS_BELIAL;

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public: 
    virtual bool Skill();

private:
    BelialHand* mLeftHand;
    BelialHand* mRightHand;
};


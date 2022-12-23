#pragma once
#include "Monster.h"
class IceMage :
    public Monster
{
public:
    IceMage();
    virtual ~IceMage();

    static constexpr MONSTER_TYPE TYPE = MONSTER_TYPE::FLY_RANGE;

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
    virtual bool Attack();
    virtual bool DetectPlayer();
    virtual bool DetectIntoAttRange();
};


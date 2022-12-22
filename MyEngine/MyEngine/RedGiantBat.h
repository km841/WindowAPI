#pragma once
#include "Monster.h"
class RedGiantBat :
    public Monster
{
public:
    RedGiantBat();
    virtual ~RedGiantBat();

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
    virtual void Trace();
    virtual bool DetectPlayer();
    virtual bool DetectIntoAttRange();

public:
    virtual void RecogLineRender(PEN_TYPE _penType);
    virtual void AttRangeLineRender(PEN_TYPE _penType);

    virtual void Dead();

private:
    Vec2 mTargetVec;
};


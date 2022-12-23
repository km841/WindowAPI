#pragma once
#include "Monster.h"


class IceCubesMissileEffect;
class BigGrayIceSkullWarrior :
    public Monster
{
public:
    BigGrayIceSkullWarrior();
    virtual ~BigGrayIceSkullWarrior();

    static constexpr MONSTER_TYPE TYPE = MONSTER_TYPE::GROUND_SKILL;

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    void GroundStateUpdate();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    virtual bool Attack();
    virtual bool Skill();
    virtual void Trace();
    virtual bool DetectPlayer();
    virtual bool DetectIntoAttRange();

public:
    virtual void RecogLineRender(PEN_TYPE _penType);
    virtual void AttRangeLineRender(PEN_TYPE _penType);

public:
    virtual void Dead();

private:
    IceCubesMissileEffect* mSkillEffect;
};


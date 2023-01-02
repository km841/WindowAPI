#pragma once
#include "BossMonster.h"
#define SWORD_MAX_COUNT 5

class Sound;
class BelialHand;
class BelialSword;
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
    virtual bool Skill() override;
    bool BelialSwordSkill();
    bool BelialLaserSkill();

    virtual void Killed() override;
    virtual void Dead() override;

private:
    BELIAL_HAND_TYPE mHandType;
    BelialHand* mLeftHand;
    BelialHand* mRightHand;

    float mSwordSpawnMaxTime;
    float mSwordSpawnCurTime;

    int mSwordMaxCount;
    int mSwordCurCount;

    Sound* mSound;
    Sound* mHitSound;
    

    std::vector<BelialSword*> mSwords;
};
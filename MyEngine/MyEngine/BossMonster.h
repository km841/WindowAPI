#pragma once
#include "Monster.h"
class BossMonster :
    public Monster
{
public:
    BossMonster();
    virtual ~BossMonster();

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
    inline void SetCurSkill(BOSS_SKILL _skill) { mCurSkill = _skill; }
    inline BOSS_SKILL GetCurSkill() const { return mCurSkill; }

    inline void SetBossName(const std::wstring& _name) { mBossName = _name; }
    inline const std::wstring& GetBossName() const { return mBossName; }

    inline void SetBossComment(const std::wstring& _comment) { mComment = _comment; }
    inline const std::wstring& GetBossComment() const { return mComment; }


private:
    BOSS_SKILL mCurSkill;

    std::wstring mBossName;
    std::wstring mComment;
};


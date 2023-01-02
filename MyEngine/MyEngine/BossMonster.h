#pragma once
#include "Monster.h"
class Sound;
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

    inline void SetSkill01AnimName(const std::wstring& _name) { mSkill01AnimName = _name; }
    inline const std::wstring& GetSkill01AnimName() const { return mSkill01AnimName; }

    inline void SetSkill02AnimName(const std::wstring& _name) { mSkill02AnimName = _name; }
    inline const std::wstring& GetSkill02AnimName() const { return mSkill02AnimName; }

    inline void SetSkill03AnimName(const std::wstring& _name) { mSkill03AnimName = _name; }
    inline const std::wstring& GetSkill03AnimName() const { return mSkill03AnimName; }

    virtual void Killed() {}

private:
    BOSS_SKILL mCurSkill;
    Sound* mSound;
    Sound* mHitSound;
    std::wstring mBossName;
    std::wstring mComment;

    std::wstring mSkill01AnimName;
    std::wstring mSkill02AnimName;
    std::wstring mSkill03AnimName;

};


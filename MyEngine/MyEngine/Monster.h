#pragma once
#include "GameObject.h"


class MonsterEffect;
class Texture;
class AI;
class Monster :
    public GameObject
{
public:
    Monster();
    virtual ~Monster();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    inline void SetAI(AI* _ai) { mAI = _ai; }
    inline AI* GetAI() const { return mAI; }

    inline void SetDir(DIR _dir) { mDir = _dir; }
    inline DIR  GetDir() const { return mDir; }

    inline void SetPrevDir(DIR _prevDir) { mPrevDir = _prevDir; }
    inline DIR  GetPrevDir() const { return mPrevDir; }

    inline void ChangeDir() { mDir = (DIR)(((UINT)mDir + 1) % 2); }

    inline void        SetMonsterInfo(MonsterInfo _info) { mInfo = _info; }
    inline MonsterInfo GetMonsterInfo() const { return mInfo; }

    inline void                SetIdleAnimName(const std::wstring& _idleAnimName) { mIdleAnimName = _idleAnimName; }
    inline const std::wstring& GetIdleAnimName() const { return mIdleAnimName; }

    inline void                SetMoveAnimName(const std::wstring& _moveAnimName) { mMoveAnimName = _moveAnimName; }
    inline const std::wstring& GetMoveAnimName() const { return mMoveAnimName; }

    inline void                SetAttAnimName(const std::wstring& _attAnimName) { mAttAnimName = _attAnimName; }
    inline const std::wstring& GetAttAnimName() const { return mAttAnimName; }

public:
    inline void           SetEffect(MonsterEffect* _monsterEff) { mEffect = _monsterEff; }
    inline MonsterEffect* GetEffect() const { return mEffect; }

    inline void SetHPBarOffset(Vec2 _hpBarOffset) { mHPBarOffset = _hpBarOffset; }
    inline Vec2 GetHPBarOffset() const { return mHPBarOffset; }

    inline void  SetCurHP(float _hp) { mInfo.mCurHP = _hp; }
    inline float GetCurHP() const { return mInfo.mCurHP; }

    inline void  SetMaxHP(float _hp) { mInfo.mMaxHP = _hp; }
    inline float GetMaxHP() const { return mInfo.mMaxHP; }

    inline bool IsDead() const { return mDead; }


public:
    virtual bool Attack() { return true; }
    virtual bool DetectPlayer() { return false; }
    virtual bool DetectIntoAttRange() { return false; }

public:
    virtual void RecogLineRender(PEN_TYPE _penType) {};
    virtual void AttRangeLineRender(PEN_TYPE _penType) {};
    

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

protected:
    AI* mAI;
    MonsterInfo mInfo;
    DIR mDir;
    DIR mPrevDir;

    bool mDead;
    
    MonsterEffect* mEffect;


protected:
    static Texture* mHPBaseTex;
    static Texture* mHPTex;

    Vec2 mHPBarOffset;

private:
    std::wstring mIdleAnimName;
    std::wstring mMoveAnimName;
    std::wstring mAttAnimName;

};


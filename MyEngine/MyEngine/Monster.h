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

    friend class MonsterDeadState;
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    void HitUpdate();

    inline void SetAI(AI* _ai) { mAI = _ai; }
    inline AI* GetAI() const { return mAI; }

    inline void SetDir(DIR _dir) { mDir = _dir; }
    inline DIR  GetDir() const { return mDir; }

    inline void SetPrevDir(DIR _prevDir) { mPrevDir = _prevDir; }
    inline DIR  GetPrevDir() const { return mPrevDir; }

    inline void ChangeDir() { mDir = (DIR)(((UINT)mDir + 1) % 2); }

    inline void        SetMonsterInfo(MonsterInfo _info) { mInfo = _info; }
    inline MonsterInfo& GetMonsterInfo() { return mInfo; }

    inline void                SetIdleAnimName(const std::wstring& _idleAnimName) { mIdleAnimName = _idleAnimName; }
    inline const std::wstring& GetIdleAnimName() const { return mIdleAnimName; }

    inline void                SetMoveAnimName(const std::wstring& _moveAnimName) { mMoveAnimName = _moveAnimName; }
    inline const std::wstring& GetMoveAnimName() const { return mMoveAnimName; }

    inline void                SetAttAnimName(const std::wstring& _attAnimName) { mAttAnimName = _attAnimName; }
    inline const std::wstring& GetAttAnimName() const { return mAttAnimName; }

    inline void                SetSkillAnimName(const std::wstring& _skillAnimName) { mSkillAnimName = _skillAnimName; }
    inline const std::wstring& GetSkillAnimName() const { return mSkillAnimName; }

    inline void                SetAttAfterAnimName(const std::wstring& _attAfterAnimName) { mAttAfterAnimName = _attAfterAnimName; }
    inline const std::wstring& GetAttAfterAnimName() const { return mAttAfterAnimName; }

    inline void                SetTraceStateAnimName(const std::wstring& _traceAnimName) { mTraceStateAnimName = _traceAnimName; }
    inline const std::wstring& GetTraceStateAnimName() const { return mTraceStateAnimName; }

    inline void                SetPatrolStateAnimName(const std::wstring& _patrolAnimName) { mPatrolStateAnimName = _patrolAnimName; }
    inline const std::wstring& GetPatrolStateAnimName() const { return mPatrolStateAnimName; }

    inline void                SetAttStateAnimName(const std::wstring& _attAnimName) { mAttStateAnimName = _attAnimName; }
    inline const std::wstring& GetAttStateAnimName() const { return mAttStateAnimName; }
   

public:
    inline void           SetEffect(MonsterEffect* _monsterEff) { mEffect = _monsterEff; }
    inline MonsterEffect* GetEffect() const { return mEffect; }

    inline void SetHPBarOffset(Vec2 _hpBarOffset) { mHPBarOffset = _hpBarOffset; }
    inline Vec2 GetHPBarOffset() const { return mHPBarOffset; }

    inline void  SetCurHP(float _hp) { mInfo.mCurHP = _hp; }
    inline float GetCurHP() const { return mInfo.mCurHP; }

    inline void  SetMaxHP(float _hp) { mInfo.mMaxHP = _hp; }
    inline float GetMaxHP() const { return mInfo.mMaxHP; }

    inline void SetAttFixFrame(int _frame) { mAttFixFrame = _frame; }
    inline int  GetAttFixFrame() const { return mAttFixFrame; }

    inline void         SetMonsterType(MONSTER_TYPE _eType) { mMonType = _eType; }
    inline MONSTER_TYPE GetMonsterType() const { return mMonType; }

    inline bool GetMonsterAttFlag() const { return mAttFlag; }

    inline TOOL_ID GetMonsterID() const { return mToolID; }

    void SetHit();
    inline bool IsHit() const { return mHit; }

public:
    virtual void Trace() {}
    virtual bool Attack() { return true; }
    virtual bool Skill() { return true; }
    virtual bool DetectPlayer() { return false; }
    virtual bool DetectIntoAttRange() { return false; }

public:
    virtual void RecogLineRender(PEN_TYPE _penType) {};
    virtual void AttRangeLineRender(PEN_TYPE _penType) {};

    
    

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    static UINT GetKillCount() { return mKillCount; }

protected:
    AI* mAI;
    MonsterInfo mInfo;
    DIR mDir;
    DIR mPrevDir;

    Sound* mSound;
    Sound* mDieSound;
    
    MonsterEffect* mEffect;
    MONSTER_TYPE mMonType;

    int mMoney;
    int mAttFixFrame;

    bool  mHit;
    float mHitMaxTime;
    float mHitCurTime;

protected:
    static Texture* mHPBaseTex;
    static Texture* mHPTex;

    Vec2 mHPBarOffset;
    bool mAttFlag;

    static UINT mKillCount;
private:
    std::wstring mIdleAnimName;
    std::wstring mMoveAnimName;
    std::wstring mAttAnimName;
    std::wstring mAttAfterAnimName;
    std::wstring mSkillAnimName;

    std::wstring mTraceStateAnimName;
    std::wstring mPatrolStateAnimName;
    std::wstring mAttStateAnimName;

};


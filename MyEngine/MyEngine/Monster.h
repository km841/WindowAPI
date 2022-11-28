#pragma once
#include "GameObject.h"



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
    inline AI*  GetAI() const { return mAI; }

    inline void        SetMonsterInfo(MonsterInfo _info) { mInfo = _info; }
    inline MonsterInfo GetMonsterInfo() const { return mInfo; }

    inline DIR GetDir() const { return mDir; }
    inline DIR GetPrevDir() const { return mPrevDir; }

    inline void SetIdleAnimName(const std::wstring& _idleAnimName) { mIdleAnimName = _idleAnimName; }
    inline const std::wstring& GetIdleAnimName() const { return mIdleAnimName;}

    inline void SetWalkAnimName(const std::wstring& _walkAnimName) { mWalkAnimName = _walkAnimName; }
    inline const std::wstring& GetWalkAnimName() const { return mWalkAnimName; }

    inline void SetAttAnimName(const std::wstring& _attAnimName) { mAttAnimName = _attAnimName; }
    inline const std::wstring& GetAttAnimName() const { return mAttAnimName; }


public:
    

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

protected:
    AI* mAI;
    MonsterInfo mInfo;
    DIR mDir;
    DIR mPrevDir;

private:
    std::wstring mIdleAnimName;
    std::wstring mWalkAnimName;
    std::wstring mAttAnimName;

};


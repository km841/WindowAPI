#pragma once
#include "Component.h"
class Collider :
    public Component
{
public:
    Collider();
    virtual ~Collider();

public:
    virtual void Update();
    virtual void Render();

public:
    inline UINT GetID() const { return mID; }
    inline UINT GetColCnt() const { return mColCnt; }
    inline void DecreaseColCnt() { mColCnt--; }
    inline void ClearColCnt() { mColCnt = 0; }

public:
    void OnCollision(Collider* _other);
    void OnCollisionEnter(Collider* _other);
    void OnCollisionExit(Collider* _other);

public:
    inline void         SetColliderType(const std::wstring& _type) { mColliderType = _type; }
    inline std::wstring GetColliderType() const { return mColliderType; }
    inline void SetEnable(bool _flag) { mEnable = _flag; }
    inline bool GetEnable() const { return mEnable; }

protected:
    static UINT gID;
    UINT        mID;
    UINT        mColCnt;
    bool        mEnable;

protected:
    std::wstring mColliderType;
};


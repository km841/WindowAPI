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

public:
    void OnCollision(Collider* _other);
    void OnCollisionEnter(Collider* _other);
    void OnCollisionExit(Collider* _other);

private:
    static UINT gID;
    UINT        mID;
    UINT        mColCnt;

};


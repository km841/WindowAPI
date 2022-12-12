#pragma once
#include "Effect.h"
class MonsterEffect :
    public Effect
{
public:
    MonsterEffect();
    virtual ~MonsterEffect();

public:
    virtual void Update();
    virtual void Render() {}

public:
    virtual bool Attack() { return false; }

public:
    virtual void OnCollision(Collider* _other) {}
    virtual void OnCollisionEnter(Collider* _other) {}
    virtual void OnCollisionExit(Collider* _other) {}

public:
    inline void  SetAtt(float _att) { mAtt = _att; }
    inline float GetAtt() const { return mAtt; }

private:
    float mAtt;
};


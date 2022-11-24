#pragma once
#include "Component.h"
class RigidBody :
    public Component
{
public:
    RigidBody();
    virtual ~RigidBody();

public:
    virtual void Update();

public:
    inline void AddForce(Vec2 _force) { mForce += _force; }

public:
    inline void  SetMass(float _mass) { mMass = _mass; }
    inline float GetMass() const { return mMass; }

    inline void SetVelocity(Vec2 _velocity) { mVelocity = _velocity; }
    inline void AddVelocity(Vec2 _velocity) { mVelocity += _velocity; }
    inline Vec2 GetVelocity() const { return mVelocity; }

    inline void SetGravity() { mGravity = true; }

public:
    //Helper Function
    inline void SetVelocity_X_Zero() { mVelocity.x = 0.f; }
    inline void SetVelocity_Y_Zero() { mVelocity.x = 0.f; }
    inline void SetVelocity_Zero() { mVelocity = Vec2(0.f, 0.f); }

private:
    void Move();

private:
    Vec2 mForce;
    Vec2 mVelocity;
    Vec2 mAccel;
    Vec2 mGravityAcc;

    float mMass;
    bool  mGravity;

};


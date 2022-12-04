#pragma once
#include "Collider.h"
class LineCollider :
    public Collider
{
public:
    LineCollider();
    virtual ~LineCollider();

public:
    virtual void Update();
    virtual void Render();

public:
    inline void SetLeftDotPos(Vec2 _dotPos) { mLeftPos = _dotPos; }
    inline Vec2 GetLeftDotPos() const { return mLeftPos; }

    inline void SetRightDotPos(Vec2 _dotPos) { mRightPos = _dotPos; }
    inline Vec2 GetRightDotPos() const { return mRightPos; }

public:
    void OnCollision(Collider* _other);
    void OnCollisionEnter(Collider* _other);
    void OnCollisionExit(Collider* _other);

private:
    Vec2 mLeftPos;
    Vec2 mRightPos;
};


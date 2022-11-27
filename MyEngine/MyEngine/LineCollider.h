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

private:
    Vec2 mLeftPos;
    Vec2 mRightPos;
};


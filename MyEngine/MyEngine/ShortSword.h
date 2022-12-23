#pragma once
#include "Sword.h"
class ShortSword :
    public Sword
{
public:
    ShortSword();
    virtual ~ShortSword();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

    virtual void Change() override;

private:
    float mCurDuration;
    bool  mAttFlag;
    float mCurAngle;


};


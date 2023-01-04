#pragma once
#include "Weapon.h"
class Sound;
class ShortSword :
    public Weapon
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

    Sound* mSound;
};


#pragma once
#include "MonsterEffect.h"
class BelialLaser :
    public MonsterEffect
{
public:
    BelialLaser(BELIAL_LASER_TYPE _laserType, BELIAL_HAND_TYPE _handType);
    virtual ~BelialLaser();

public:
    virtual void Update();
    virtual void Render();


private:
    BELIAL_LASER_TYPE mLaserType;
    BELIAL_HAND_TYPE mHandType;

    std::wstring mLaserHeadAnimName;
    std::wstring mLaserBodyAnimName;
};


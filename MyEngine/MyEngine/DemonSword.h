#pragma once
#include "Sword.h"
class DemonSword :
    public Sword
{
public:
    DemonSword();
    virtual ~DemonSword();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    float mCurDuration;
};


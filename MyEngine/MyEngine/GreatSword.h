#pragma once
#include "Weapon.h"
class GreatSword :
    public Weapon
{
public:
    GreatSword();
    virtual ~GreatSword();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
};


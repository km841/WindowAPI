#pragma once
#include "Sword.h"
class GreatSword :
    public Sword
{
public:
    GreatSword();
    virtual ~GreatSword();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
};


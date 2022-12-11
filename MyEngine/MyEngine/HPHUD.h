#pragma once
#include "HUD.h"
class HPHUD :
    public HUD
{
public:
    HPHUD();
    virtual ~HPHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;
};


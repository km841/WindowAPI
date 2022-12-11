#pragma once
#include "HUD.h"
class DashCountHUD :
    public HUD
{
public:
    DashCountHUD();
    virtual ~DashCountHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

};


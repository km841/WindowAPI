#pragma once
#include "HUD.h"
class Texture;
class ItemGetHUD :
    public HUD
{
public:
    ItemGetHUD();
    virtual ~ItemGetHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

private:
};


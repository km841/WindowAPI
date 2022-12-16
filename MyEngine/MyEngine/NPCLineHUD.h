#pragma once
#include "HUD.h"

class Texture;
class NPCLineHUD :
    public HUD
{
public:
    NPCLineHUD();
    virtual ~NPCLineHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

private:
    Texture* mTex;
    Texture* mBaseTex;
};


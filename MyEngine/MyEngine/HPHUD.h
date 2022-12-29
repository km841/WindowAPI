#pragma once
#include "HUD.h"

class Texture;
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


private:
    Texture* mTex;
    Texture* mBaseTex;

};


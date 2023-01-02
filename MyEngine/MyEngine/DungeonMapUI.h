#pragma once
#include "UI.h"

class Texture;
class DungeonMapUI :
    public UI
{
public:
    DungeonMapUI();
    virtual ~DungeonMapUI();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

private:
    Texture* mBaseTex;
    Texture* mTex;
    BLENDFUNCTION mBlendFunc;
};


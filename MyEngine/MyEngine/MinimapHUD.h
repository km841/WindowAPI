#pragma once
#include "HUD.h"

class Texture;
class MinimapHUD :
    public HUD
{
public:
    MinimapHUD();
    virtual ~MinimapHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    void MonsterRender(RECT _limitSize);
    void TileRender(RECT _limitSize);
    void NPCRender(RECT _limitSize);
    void PlayerRender(RECT _limitSize);
    void DungeonObjectRender(RECT _limitSize);

public:
    Vec2 GetMinimapPos(RECT _limitRect, Vec2 _targetPos);


private:
    Texture* mTex;
    Texture* mBaseTex;

    Vec2 mMinimapSize;
    BLENDFUNCTION mBlendFunc;
};


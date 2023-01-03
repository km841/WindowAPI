#pragma once
#include "UI.h"

class Map;
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
    

    void DrawUnitMap(Map* _curMap, Vec2 _drawPos);

private:
    Texture* mBaseTex;
    Texture* mTex;
    Texture* mInfoTex;
    Texture* mUnitMapTex;
    Texture* mUnitMapLightTex;
    Texture* mFloorInfoTex;
    BLENDFUNCTION mBlendFunc;

    std::vector<Map*> mVisited;

    Vec2 mCenterPos;
};


#pragma once
#include "Singleton.h"

class GameObject;
class CameraMgr :
    public Singleton< CameraMgr >
{
public:
    void Initialize();
    void Update();

public:
    inline void SetLookPos(Vec2 _pos) { mLookPos = _pos; }
    inline void SetTrackingObject(GameObject* _obj) { mObject = _obj; }

    inline Vec2 GetRenderPos(Vec2 _objPos) { return _objPos - mDistance; }
    inline Vec2 GetWorldPos(Vec2 _renderPos) { return _renderPos + mDistance; }

public:
    void WorldToScreenCalc();


private:
    Vec2 mLookPos;
    Vec2 mDistance;
    float mAccTime;

    GameObject* mObject;
    
};


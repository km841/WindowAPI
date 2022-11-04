#pragma once
#include "Singleton.h"

enum class CAMERA_EFFECT
{
    FADE_IN,
    FADE_OUT,
    END,
};

class GameObject;
class Texture;
class CameraMgr :
    public Singleton< CameraMgr >
{
public:
    void Initialize();
    void Update();
    void Render();

public:
    inline void SetLookPos(Vec2 _pos) { mLookPos = _pos; }
    inline void SetTrackingObject(GameObject* _obj) { mObject = _obj; }

    inline Vec2 GetRenderPos(Vec2 _objPos) { return _objPos - mDistance; }
    inline Vec2 GetWorldPos(Vec2 _renderPos) { return _renderPos + mDistance; }

    

public:
    void WorldToScreenCalc();
    void SetEffect(CAMERA_EFFECT _effect, float _endTime);


private:
    Vec2 mLookPos;
    Vec2 mDistance;   
    float mAccTime;
    GameObject* mObject;

private:
    BLENDFUNCTION mBlendFunc;
    float mAlphaValue;
    Texture* mCutton;
    CAMERA_EFFECT mEffect;

    float mAlphaTime;
    float mEndTime;
};


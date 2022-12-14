#pragma once
#include "Singleton.h"
#define CAMERA_SPEED 600.f

enum class CAMERA_EFFECT
{
    FADE_IN,
    FADE_OUT,
    HIT,
    SHAKE,
    END,
};

struct CameraEffect
{
    CAMERA_EFFECT   mEffect;
    float           mAlphaTime;
    float           mEndTime;
    float           mDelayTime;
    float           mCurDelayTime;
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
    inline Vec2 GetLookPos() const { return mLookPos; }
    inline void SetTrackingObject(GameObject* _obj) { mObject = _obj; }

    inline Vec2 GetRenderPos(Vec2 _objPos) const { return _objPos - mDistance; }
    inline Vec2 GetWorldPos(Vec2 _renderPos) const { return _renderPos + mDistance; }
    Vec2 GetTileCoord(Vec2 _tilePos) const;
    Vec2 GetIconUIPos(Vec2 _uiPos, int _index) const;

    inline void SetCameraLimitRect(RECT _rect) { mCamLimitRect = _rect; }
    inline RECT GetCameraLimitRect() const { return mCamLimitRect; }


    inline bool IsEffectProgress() { return !mCamEffects.empty(); }

    bool OutOfScreen(Vec2 _pos);

    inline void SetBottomLimit(int _limit) { mBottomLimit = _limit; }
    inline int GetBottomLimit() const { return mBottomLimit; }

public:
    void WorldToScreenCalc();
    void SetEffect(CAMERA_EFFECT _effect, float _endTime, float _delayTime = 0.f);
    void RemoveEffect();
    

private:
    Vec2                    mLookPos;
    Vec2                    mPrevLookPos;
    Vec2                    mDistance;   
    float                   mAccTime;
    GameObject*             mObject;
    RECT                    mCamLimitRect;


private:
    BLENDFUNCTION           mBlendFunc;
    float                   mAlphaValue;
    Texture*                mCutton;
    Texture*                mHitCutton;

    std::list<CameraEffect> mCamEffects;
    CameraEffect            mCurEffect;

    int                   mBottomLimit;
};


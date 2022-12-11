#pragma once
#include "GameObject.h"
class HUD :
    public GameObject
{
public:
    HUD();
    virtual ~HUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    inline bool GetState() const { return mState; }
    inline void SetState(bool _state) { mState = _state; }

private:
    bool mState;
    
};


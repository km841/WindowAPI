#pragma once
#include "Singleton.h"

enum class MOUSE_STATE
{
    JUST_LBTN_CLICKED,
    LBTN_CLICKED,

    JUST_LBTN_RELEASED,
    LBTN_RELEASED,

    JUST_RBTN_CLICKED,
    RBTN_CLICKED,

    JUST_RBTN_RELEASED,
    RBTN_RELEASED,

    NONE,

    END,
};

class MouseMgr :
    public Singleton< MouseMgr >
{
public:
    MouseMgr();
    ~MouseMgr();

public:
    void Update();

public:
    inline MOUSE_STATE GetMouseState() const { return mState; }
    inline Vec2        GetMousePos()   const { return mCurPos; }

private:
    Vec2 mCurPos;
    Vec2 mLastLClickPos;
    Vec2 mLastRClickPos;
    MOUSE_STATE mState;
};


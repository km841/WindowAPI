#pragma once
#include "Singleton.h"

enum class KEY_STATE
{
    JUST_PRESSED,
    PRESSED,

    JUST_RELEASED,
    RELEASED,

    END

};

enum class KEY
{
    Q, W, E, R, T, Y, U ,I, O, P,
    A, S, D, F, G, H, J, K, L,
    Z, X, C, V, B, N, M,

    LCTRL,
    RCTRL,
    TAB,
    SPACE,
    ENTER,
    BACKSPACE,
    ESC,
    
    UP,
    DOWN,
    LEFT,
    RIGHT,

    LBUTTON,
    RBUTTON,

    END
};

static UINT KEY_CODE[(UINT)KEY::END]
{
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U' ,'I', 'O', 'P',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
    'Z', 'X', 'C', 'V', 'B', 'N', 'M',

    VK_LCONTROL,
    VK_RCONTROL,
    VK_TAB,
    VK_SPACE,
    VK_RETURN,
    VK_BACK,
    VK_ESCAPE,

    VK_UP,
    VK_DOWN,
    VK_LEFT,
    VK_RIGHT,

    VK_LBUTTON,
    VK_RBUTTON,
};


class KeyMgr :
    public Singleton< KeyMgr >
{
public:
    void Initialize();
    void Update();


public:
    inline KEY_STATE GetKeyState(KEY _ekey) const;
    inline Vec2      GetMousePos() const { return mMousePos; }

private:
    KEY_STATE mKeyStates[(UINT)KEY::END];
    Vec2      mMousePos;
};


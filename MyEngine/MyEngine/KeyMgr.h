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
};


class KeyMgr :
    public Singleton< KeyMgr >
{
public:
    void Initialize();
    void Update();


public:
    inline KEY_STATE GetKeyState(KEY _ekey) const;


private:
    KEY_STATE mKeyStates[(UINT)KEY::END];
};


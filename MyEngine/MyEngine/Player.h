#pragma once
#include "GameObject.h"

#define PLAYER_SPEED 350.f

class State;
class Effect;
class Texture;
class IdleState;
class WalkState;
class JumpState;
class Inventory;

struct PlayerState
{
    static IdleState* Idle;
    static WalkState* Walk;
    static JumpState* Jump;
};

enum class PLAYER_DIR
{
    LEFT,
    RIGHT,
};

class Player :
    public GameObject
{
public:
    Player();
    virtual ~Player();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    void MoveUpdate();
    void EffectUpdate();
    void StateUpdate();
    void AnimationUpdate();

    bool IsMove() const;
    bool IsLeftMove() const;
    bool IsRightMove() const;
    bool IsUpMove() const;
    bool IsDownMove() const;

    inline void    SetEffect(Effect* _effect) { mEffect = _effect; }
    inline Effect* GetEffect() const { return mEffect; }

    inline Vec2 GetPrevPos() const { return mPrevPos; }
    inline float GetPlayerSpeed() const { return PLAYER_SPEED; }

private:
    Texture*   mDefaultTexture;
    State*     mPrevState;
    State*     mState;
    Effect*    mEffect;
    Inventory* mInventory;

    Vec2       mPrevPos;
    PLAYER_DIR mPrevDir;
    PLAYER_DIR mDir;
    
public:
    float      mJumpYValue;
    float      mJumpXValue;
    float      mJumpXMaxValue;
    float      mJumpYMinValue;
    bool       mFall;

public:
    bool       mAccDash;
    float      mDashAccTime;
    float      mDashAccMaxTime;
    Vec2       mDashSpeed;

    bool       mDecDash;
    float      mDecTime;
    float      mDecMaxTime;


    friend class IdleState;
    friend class WalkState;
    friend class JumpState;
};


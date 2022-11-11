#pragma once
#include "GameObject.h"

#define PLAYER_SPEED 400.f

class State;
class Effect;
class Texture;
class IdleState;
class WalkState;

struct PlayerState
{
    static IdleState* Idle;
    static WalkState* Walk;
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
    void PlayerInput();
    void EffectInput();

    bool IsMove() const;
    bool IsLeftMove() const;
    bool IsRightMove() const;
    bool IsUpMove() const;
    bool isDownMove() const;

    inline void    SetEffect(Effect* _effect) { mEffect = _effect; }
    inline Effect* GetEffect() const { return mEffect; }

    inline Vec2 GetPrevPos() const { return mPrevPos; }

private:
    Texture*   mDefaultTexture;
    State*     mState;
    Effect*    mEffect;

    Vec2       mPrevPos;
    PLAYER_DIR mDir;

    friend class IdleState;
    friend class WalkState;
};


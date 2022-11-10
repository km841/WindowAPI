#pragma once
#include "GameObject.h"

#define PLAYER_SPEED 400.f

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
    bool IsMove() const;

private:
    Texture* mDefaultTexture;
    State* mState;

    Vec2 mPrevPos;
    PLAYER_DIR mDir;

    friend class IdleState;
    friend class WalkState;
};


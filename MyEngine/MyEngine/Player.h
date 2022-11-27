#pragma once
#include "GameObject.h"

#define PLAYER_SPEED 350.f
#define PLAYER_DASH_SPEED 1500.f

class State;
class Effect;
class DashEffect;
class Texture;
class IdleState;
class WalkState;
class JumpState;
class EatState;
class InventoryUI;
class Item;

struct PlayerState
{
    static IdleState* Idle;
    static WalkState* Walk;
    static JumpState* Jump;
    static EatState*  Eat;
};

enum class PLAYER_DIR
{
    LEFT,
    RIGHT,
    END,
};

class Player :
    public GameObject
{
public:
    Player();
    virtual ~Player();

    friend class IdleState;
    friend class WalkState;
    friend class JumpState;
    friend class EatState;

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

    inline bool NotInDash() const { return (!mAccDash && !mDecDash); }

    inline PLAYER_DIR GetPlayerDir() const { return mDir; }


public:
    void DashEffectReset();
    void DashDeceleration();
    void DashAcceleration();

    void InGround();
    void OutGround();

    inline State* GetState() const { return mState; }
    inline void SetState(State* _state) { mState = _state; }

    inline bool GetStop() const { return mStop; }
    inline void SetStop(bool _flag);


public:
    inline Item* GetEquipItem(EQUIP_TYPE _itemType) const { return mEquipItems[(UINT)_itemType]; }
    void         SetEquipItem(Item* _item);

    void EquipItemUpdate();
    void EquipItemRender();

public:
    inline void SetGroundType(TILE_TYPE _tileType) { mGroundType = _tileType; }
    inline TILE_TYPE GetGroundType() const { return mGroundType; }
    
public:
    static Player* GetPlayer() { return mPlayer; }

private:
    static Player* mPlayer;

private:
    Texture*       mDefaultTexture;
    Texture*       mDashTexture;
    State*         mPrevState;
    State*         mState;
    Effect*        mEffect;
    DashEffect*    mDashEffect[AFTER_IMAGE_TOTAL];
    Item*          mEquipItems[(UINT)EQUIP_TYPE::END];


    Vec2       mPrevPos;
    PLAYER_DIR mPrevDir;
    PLAYER_DIR mDir;

private:
    bool       mStop;

private:
    TILE_TYPE  mGroundType;
    
private:
    float      mJumpYValue;
    float      mJumpXValue;
    float      mJumpXMaxValue;
    float      mJumpYMinValue;
    bool       mFall;

private:
    bool       mAccDash;
    float      mDashAccTime;
    float      mDashAccMaxTime;
    Vec2       mDashSpeed;

    bool       mDecDash;
    float      mDecTime;
    float      mDecMaxTime;

    float      mImgDuration;
    float      mCurImgDuration;
    int        mImgCount;

    bool       mGroundFlag;

};


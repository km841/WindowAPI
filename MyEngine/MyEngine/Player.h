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
    void GroundStateUpdate();
    void MoveMapCoolDownUpdate();

    bool IsMove() const;
    bool IsLeftMove() const;
    bool IsRightMove() const;
    bool IsUpMove() const;
    bool IsDownMove() const;

    inline void    SetEffect(Effect* _effect) { mEffect = _effect; }
    inline Effect* GetEffect() const { return mEffect; }

    inline void       SetPlayerInfo(PlayerInfo _info) { mInfo = _info; }
    inline PlayerInfo GetPlayerInfo() const { return mInfo; }

    inline Vec2 GetPrevPos() const { return mPrevPos; }
    inline void SetPrevPos(Vec2 _prevPos) { mPrevPos = _prevPos; }

    inline float GetPlayerSpeed() const { return PLAYER_SPEED; }

    inline bool NotInDash() const { return (!mAccDash && !mDecDash); }

    inline DIR GetPlayerDir() const { return mDir; }

    inline PLAYER_CHARACTER GetCurCharacter() const { return mCharacter; }
    inline void             SetCurCharacter(PLAYER_CHARACTER _char) { mCharacter = _char; }


public:
    void DashEffectReset();
    void DashDeceleration();
    void DashAcceleration();

    void InGround();
    void OutGround();
    inline void SetFall(bool _flag) { mFall = _flag; }
    inline bool GetFall() const { return mFall;}

    inline State* GetState() const { return mState; }
    inline State* GetState() { return mState; }
    
    inline void   SetState(State* _state) { mState = _state; }

    inline bool GetStop() const { return mStop; }
    inline void SetStop(bool _flag);

    inline bool IsHit() const { return mHit; }

    inline int GetMoney() const { return mMoney; }
    inline void SetMoney(int _money) { mMoney = _money; }

    inline void SetPrevScene(SCENE_TYPE _type) { mPrevScene = _type; }
    inline SCENE_TYPE GetPrevScene() const { return mPrevScene; }

public:
    inline Item* GetEquipItem(EQUIP_TYPE _itemType) const { return mEquipItems[(UINT)_itemType]; }
    void         SetEquipItem(Item* _item);
    void         SetEquipItem(EQUIP_TYPE _itemType, Item* _item);

    void         ClearEquipItem(EQUIP_TYPE _itemType) { mEquipItems[(UINT)_itemType] = nullptr; }

    void EquipItemUpdate();
    void EquipItemRender();

    void AllCollisionExit();
    inline void SetMoveMapCoolDown() { mMoveMapCoolDown = true; }
    inline bool GetMoveMapCoolDown() { return mMoveMapCoolDown; }


    
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
    PlayerInfo     mInfo;

    PLAYER_CHARACTER mCharacter;

    SCENE_TYPE mPrevScene;

    Vec2       mPrevPos;
    DIR        mPrevDir;
    DIR        mDir;

private:
    bool       mStop;
    bool       mHit;
    float      mInvinMaxTime;
    float      mInvinTime;

private:
    TILE_TYPE  mGroundType;
private:
    float      mJumpYValue;
    float      mJumpXValue;
    float      mJumpXMaxValue;
    float      mJumpYMinValue;
    bool       mFall;

    float      mYSpeedLimit;

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

    bool       mUIState;
    int        mMoney;

    bool       mMoveMapCoolDown;
    float      mMoveMapMaxDuration;
    float      mMoveMapCurDuration;


private:
    float      mDashDuration;

};


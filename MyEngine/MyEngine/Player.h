#pragma once
#include "GameObject.h"

enum class PLAYER_DIR
{
    LEFT,
    RIGHT,
};

enum class PLAYER_STATE
{
    IDLE,
    WALK,
};

class Texture;
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
    Texture* GetTexture(const std::wstring& _key);
    inline Texture* GetCurTexture() const { return mCurTexture; }


    void SelectTexture(const std::wstring& _key);

private:
    Texture* mDefaultTexture;
    std::map<std::wstring, Texture*> mTextureMap;
    Texture* mCurTexture;

    PLAYER_DIR mDir;
    PLAYER_DIR mPrevDir;

    PLAYER_STATE mPrevState;
    PLAYER_STATE mState;
    Vec2 mPrevPos;
};


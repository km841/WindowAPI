#pragma once
#include "GameObject.h"
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
    void SelectTexture(const std::wstring& _key);

private:
    std::map<std::wstring, Texture*> mTextureMap;
    Texture* mCurTexture;
};


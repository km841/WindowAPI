#pragma once
#include "GameObject.h"

class Texture;
class Monster :
    public GameObject
{
public:
    Monster();
    virtual ~Monster();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

private:
    Texture* mTexture;
};


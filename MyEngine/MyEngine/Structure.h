#pragma once
#include "GameObject.h"

class Texture;
class Structure :
    public GameObject
{
public:
    Structure();
    virtual ~Structure();

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
    inline void SetTexture(Texture* _tex) { mTexture = _tex; }

private:
    Texture* mTexture;


};


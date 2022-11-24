#pragma once
#include "GameObject.h"

class Texture;
class NPC :
    public GameObject
{
public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;
    
public:
    inline void SetKeyTexture(Texture* _keyTex) { mKeyTexture = _keyTex; }
    inline Texture* GetKeyTexture() const { return mKeyTexture; }

    inline bool IsCollision() const { return mCollision; }

private:
    Texture* mKeyTexture;

protected:
    bool     mCollision;
};


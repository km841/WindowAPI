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
    inline void SetTexture(Texture* _tex) { mTexture = _tex; }
    inline void SetPixelTexture(Texture* _pixelTex) { mPixelTexture = _pixelTex; }

private:
    Texture* mTexture;
    Texture* mPixelTexture;


};


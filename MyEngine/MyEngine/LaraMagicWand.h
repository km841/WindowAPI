#pragma once
#include "Sword.h"
class LaraMagicWand :
    public Sword
{
public:
    LaraMagicWand();
    virtual ~LaraMagicWand();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void Change() override;

private:
    Texture* mSkillTex;
};


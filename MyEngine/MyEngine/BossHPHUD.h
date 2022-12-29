#pragma once
#include "HUD.h"
class Texture;
class Monster;
class BossHPHUD :
    public HUD
{
public:
    BossHPHUD();
    virtual ~BossHPHUD();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    inline void SetBossMonster(Monster* _boss) { mBoss = _boss; }

private:
    Texture* mTex;
    Texture* mBaseTex;

    Monster* mBoss;

};


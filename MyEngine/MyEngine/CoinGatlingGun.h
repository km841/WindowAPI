#pragma once
#include "Weapon.h"

class Sound;
class CoinGatlingGun :
    public Weapon
{
public:
    CoinGatlingGun();
    virtual ~CoinGatlingGun();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    Texture* mEquipTex;

    Sound* mReadySound;
    Sound* mShotSound;

    bool mReady;
    bool mReadyStart;
    float mReadyMaxTime;
    float mReadyCurTime;
    
    bool mAttDelay;
    float mAttMaxDelay;
    float mAttCurDelay;

};


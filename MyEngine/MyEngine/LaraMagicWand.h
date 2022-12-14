#pragma once
#include "Weapon.h"

class Sound;
class LaraMagicWand :
    public Weapon
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

public:
    inline float& GetCurCoolDown() { return mCurCoolDown; }
    inline float GetMaxCoolDown() { return mSkillCoolDown; }

    inline void SetCoolDownFlag(bool _flag) { mCoolDown = _flag; }
    inline bool GetCoolDownFlag() const { return mCoolDown; }

private:
    Texture* mSkillTex;
    Texture* mCoolSkillTex;
    Texture* mEquipTex;
    float    mSkillCoolDown;
    float    mCurCoolDown;
    bool     mCoolDown;

    Sound*   mSound;
};


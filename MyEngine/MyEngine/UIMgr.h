#pragma once
#include "Singleton.h"
class UI;
class HUD;
class UIMgr :
    public Singleton< UIMgr >
{
public:
    UIMgr();
    ~UIMgr();

public:
    void Initialize();
    void Update();
    void Destroy();

public:
    void DisableUI(UI_TYPE _type);
    void EnableUI(UI_TYPE _type);
    UI*  ActiveUI(UI_TYPE _type);
    bool GetUIState(UI_TYPE _type);

    UI* GetUI(UI_TYPE _type);

    void DisableHUD(HUD_TYPE _type);
    void EnableHUD(HUD_TYPE _type);
    HUD* ActiveHUD(HUD_TYPE _type);
    bool GetHUDState(HUD_TYPE _type);

    HUD* GetHUD(HUD_TYPE _type);


private:
    std::map<UI_TYPE, UI*>   mUIMap;
    std::map<HUD_TYPE, HUD*> mHUDMap;
};


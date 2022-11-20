#pragma once
#include "Singleton.h"
class UI;
class UIMgr :
    public Singleton< UIMgr >
{
public:
    UIMgr();
    ~UIMgr();

public:
    void Initialize();
    void Update();

public:
    void DisableUI(UI_TYPE _type);
    void EnableUI(UI_TYPE _type);
    UI* ActiveUI(UI_TYPE _type);
    bool GetUIState(UI_TYPE _type);

    inline UI* GetUI(UI_TYPE _type) { return mUIMap[_type]; }

private:
    std::map<UI_TYPE, UI*> mUIMap;
};


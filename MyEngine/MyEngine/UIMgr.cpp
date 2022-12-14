#include "pch.h"
#include "UIMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "UI.h"
#include "EventRegisteror.h"
#include "InventoryUI.h"
#include "DungeonMapUI.h"
#include "HUD.h"
#include "HPHUD.h"
#include "DashCountHUD.h"
#include "NPCLineHUD.h"
#include "EquipedHUD.h"
#include "ItemGetHUD.h"
#include "ItemInfoHUD.h"
#include "MinimapHUD.h"
#include "BossHPHUD.h"
#include "BossAppearHUD.h"
#include "DungeonClearUI.h"
#include "GuideHUD.h"

UIMgr::UIMgr()
{
}

UIMgr::~UIMgr()
{

}

void UIMgr::Initialize()
{
	DisableUI(UI_TYPE::INVENTORY);
	DisableUI(UI_TYPE::DUNGEON_MAP);
	DisableUI(UI_TYPE::DUNGEON_CLEAR);
	EnableHUD(HUD_TYPE::HP);
	EnableHUD(HUD_TYPE::DASH_GAUGE);
	EnableHUD(HUD_TYPE::EQUIPED);
	EnableHUD(HUD_TYPE::MINIMAP);
	DisableHUD(HUD_TYPE::NPC_LINE);
	DisableHUD(HUD_TYPE::ITEM_GET);
	DisableHUD(HUD_TYPE::ITEM_INFO);
	DisableHUD(HUD_TYPE::BOSS_HP);
	DisableHUD(HUD_TYPE::BOSS_APPEAR);
	DisableHUD(HUD_TYPE::GUIDE);
}

void UIMgr::Update()
{
	const std::vector<GameObject*>& uiGroup =
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::UI);

	const std::vector<GameObject*>& uniqueUIGroup =
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::UNIQUE_UI);

	for (int i = 0; i < uiGroup.size(); ++i)
	{
		UI* ui = static_cast<UI*>(uiGroup[i]);

		if (ui->OnMouse())   
			ui->mOnMouse = true;
		else			     
			ui->mOnMouse = false;


		if (ui->OnClicked()) 
			ui->mOnClicked = true;
		else				 
			ui->mOnClicked = false;
	}

	for (int i = 0; i < uniqueUIGroup.size(); ++i)
	{
		UI* ui = static_cast<UI*>(uniqueUIGroup[i]);

		if (ui->OnMouse())
			ui->mOnMouse = true;
		else
			ui->mOnMouse = false;


		if (ui->OnClicked())
			ui->mOnClicked = true;
		else
			ui->mOnClicked = false;
	}




}

void UIMgr::Destroy()
{
	for (int i = 0; i < (UINT)UI_TYPE::END; ++i)
	{
		if (nullptr != mUIMap[(UI_TYPE)i])
		{
			delete mUIMap[(UI_TYPE)i];
			mUIMap[(UI_TYPE)i] = nullptr;
		}
	}

	for (int i = 0; i < (UINT)HUD_TYPE::END; ++i)
	{
		if (nullptr != mHUDMap[(HUD_TYPE)i])
		{
			delete mHUDMap[(HUD_TYPE)i];
			mHUDMap[(HUD_TYPE)i] = nullptr;
		}
	}
}



void UIMgr::DisableUI(UI_TYPE _type)
{
	UI* ui = mUIMap[_type];
	if (nullptr == ui)
	{
		ui = ActiveUI(_type);
		ui->SetState(false);
		mUIMap[_type] = ui;

	}

	else
	{
		ui->SetState(false);
	}
}

void UIMgr::EnableUI(UI_TYPE _type)
{
	UI* ui = mUIMap[_type];
	if (nullptr == ui)
	{
		ui = ActiveUI(_type);
		ui->SetState(true);
		mUIMap[_type] = ui;

	}

	else
	{
		ui->SetState(true);
	}
}

UI* UIMgr::ActiveUI(UI_TYPE _type)
{
	UI* ui = mUIMap[_type];
	if (nullptr == ui)
	{
		switch (_type)
		{

		case UI_TYPE::INVENTORY:
			ui = new InventoryUI;
			ui->Initialize();
			ui->SetState(true);
			break;

		case UI_TYPE::DUNGEON_MAP:
			ui = new DungeonMapUI;
			ui->Initialize();
			ui->SetState(true);
			break;

		case UI_TYPE::DUNGEON_CLEAR:
			ui = new DungeonClearUI;
			ui->Initialize();
			ui->SetState(true);
			break;


		case UI_TYPE::TOOL:
			break;
		}
	}
	return ui;
}

bool UIMgr::GetUIState(UI_TYPE _type)
{
	UI* ui = mUIMap[_type];
	if (nullptr != ui)
		return ui->GetState();

	return false;
}

UI* UIMgr::GetUI(UI_TYPE _type)
{
	std::map<UI_TYPE, UI*>::iterator iter = mUIMap.find(_type);
	if (mUIMap.end() != iter)
	{
		return iter->second;
	}
	
	return nullptr;
}

void UIMgr::DisableHUD(HUD_TYPE _type)
{
	HUD* hud = mHUDMap[_type];
	if (nullptr == hud)
	{
		hud = ActiveHUD(_type);
		hud->SetState(false);
		mHUDMap[_type] = hud;

	}

	else
	{
		hud->SetState(false);
	}
}

void UIMgr::EnableHUD(HUD_TYPE _type)
{
	HUD* hud = mHUDMap[_type];
	if (nullptr == hud)
	{
		hud = ActiveHUD(_type);
		hud->SetState(true);
		mHUDMap[_type] = hud;

	}

	else
	{
		hud->SetState(true);
	}
}

HUD* UIMgr::ActiveHUD(HUD_TYPE _type)
{
	HUD* hud = mHUDMap[_type];
	if (nullptr == hud)
	{
		switch (_type)
		{
		case HUD_TYPE::HP:
			hud = new HPHUD;
			hud->Initialize();
			hud->SetState(true);
			break;
		case HUD_TYPE::DASH_GAUGE:
			hud = new DashCountHUD;
			hud->Initialize();
			hud->SetState(true);
			break;

		case HUD_TYPE::NPC_LINE:
			hud = new NPCLineHUD;
			hud->Initialize();
			hud->SetState(true);
			break;

		case HUD_TYPE::EQUIPED:
			hud = new EquipedHUD;
			hud->Initialize();
			hud->SetState(true);
			break;

		case HUD_TYPE::ITEM_GET:
			hud = new ItemGetHUD;
			hud->Initialize();
			hud->SetState(true);
			break;

		case HUD_TYPE::ITEM_INFO:
			hud = new ItemInfoHUD;
			hud->Initialize();
			hud->SetState(true);
			break;

		case HUD_TYPE::MINIMAP:
			hud = new MinimapHUD;
			hud->Initialize();
			hud->SetState(true);
			break;

		case HUD_TYPE::BOSS_HP:
			hud = new BossHPHUD;
			hud->Initialize();
			hud->SetState(true);
			break;

		case HUD_TYPE::BOSS_APPEAR:
			hud = new BossAppearHUD;
			hud->Initialize();
			hud->SetState(true);
			break;

		case HUD_TYPE::GUIDE:
			hud = new GuideHUD;
			hud->Initialize();
			hud->SetState(true);
			break;
		}
	}
	return hud;
}

bool UIMgr::GetHUDState(HUD_TYPE _type)
{
	HUD* hud = mHUDMap[_type];
	if (nullptr != hud)
		return hud->GetState();

	return false;
}

HUD* UIMgr::GetHUD(HUD_TYPE _type)
{
	std::map<HUD_TYPE, HUD*>::iterator iter = mHUDMap.find(_type);
	if (mHUDMap.end() != iter)
	{
		return iter->second;
	}

	return nullptr;
}

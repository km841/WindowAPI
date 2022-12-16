#include "pch.h"
#include "UIMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "UI.h"
#include "EventRegisteror.h"
#include "InventoryUI.h"
#include "HUD.h"
#include "HPHUD.h"
#include "DashCountHUD.h"
#include "NPCLineHUD.h"

UIMgr::UIMgr()
{
}

UIMgr::~UIMgr()
{

}

void UIMgr::Initialize()
{
	DisableUI(UI_TYPE::INVENTORY);
	EnableHUD(HUD_TYPE::HP);
	EnableHUD(HUD_TYPE::DASH_GAUGE);
	DisableHUD(HUD_TYPE::NPC_LINE);
}

void UIMgr::Update()
{
	const std::vector<GameObject*>& uiGroup =
		SceneMgr::GetInstance().GetCurScene()->GetObjectGroup(OBJECT_TYPE::UI);

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

		case HUD_TYPE::MINIMAP:

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

#include "pch.h"
#include "UIMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "UI.h"
#include "EventRegisteror.h"
#include "InventoryUI.h"

UIMgr::UIMgr()
{
}

UIMgr::~UIMgr()
{

}

void UIMgr::Initialize()
{
	DisableUI(UI_TYPE::INVENTORY);
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
		case UI_TYPE::HP:
			break;
		case UI_TYPE::DASH_GAUGE:
			break;
		case UI_TYPE::MINIMAP:
			break;

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

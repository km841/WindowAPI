#include "pch.h"
#include "UI.h"
#include "KeyMgr.h"
#include "MouseMgr.h"

UI::UI(bool _camMode)
	: mCamMode(_camMode)
	, mState(false)
{
	
}

UI::~UI()
{
	for (int i = 0; i < mChildUI.size(); ++i)
	{
		if (nullptr != mChildUI[i])
		{
			delete mChildUI[i];
			mChildUI[i] = nullptr;
		}
	}
}

UI::UI(const UI& _other)
	:GameObject(_other)
{
}

void UI::Initialize()
{
}

void UI::Update()
{
	for (const auto& childUI : mChildUI)
	{
		childUI->Update();
	}
}

void UI::Render()
{
	for (const auto& childUI : mChildUI)
	{
		childUI->Render();
	}
}

void UI::Destroy()
{
}

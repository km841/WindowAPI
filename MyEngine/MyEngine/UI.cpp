#include "pch.h"
#include "UI.h"
#include "KeyMgr.h"
#include "MouseMgr.h"

UI::UI(bool _camMode)
	: mCamMode(_camMode)
{
	
}

UI::~UI()
{
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
}

void UI::Render()
{
}

void UI::Destroy()
{
}

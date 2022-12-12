#include "pch.h"
#include "HUD.h"

HUD::HUD()
{
	SetType(OBJECT_TYPE::HUD);
}

HUD::~HUD()
{
}

void HUD::Initialize()
{
	GameObject::Initialize();
}

void HUD::Update()
{
	GameObject::Update();
}

void HUD::Render()
{
	GameObject::Render();
}

void HUD::Destroy()
{
	GameObject::Destroy();
}

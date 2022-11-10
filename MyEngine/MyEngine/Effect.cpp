#include "pch.h"
#include "Effect.h"

void Effect::Initialize()
{
}

void Effect::Update()
{
	Vec2 ownerPos = mOwner->GetPos();
	SetPos(ownerPos + mOffset);
	GameObject::Update();
}

void Effect::Render()
{
	GameObject::Render();
}

void Effect::Destroy()
{
}

#include "pch.h"
#include "Effect.h"

Effect::Effect()
	: mMinAtt(0.f)
	, mMaxAtt(0.f)
	, mOwner(nullptr)
	, mTexture(nullptr)
{
	//SetType(OBJECT_TYPE::EFFECT);

}

Effect::~Effect()
{
}

void Effect::Initialize()
{
	GameObject::Initialize();
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

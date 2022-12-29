#include "pch.h"
#include "BelialCore.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animator.h"

BelialCore::BelialCore()
{
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	Texture* tex = ResourceMgr::GetInstance().Load<Texture>(L"Belial_Back_Tex", L"Texture\\Belial_Back_Anim.bmp");

	GetAnimator()->RegisterAnimation(
		L"BelialBackAnim",
		tex,
		Vec2(0, 0),
		Vec2(150, 150),
		Vec2(150, 0),
		0.1f,
		10
	);

	GetAnimator()->SelectAnimation(L"BelialBackAnim", true);
}

BelialCore::~BelialCore()
{
}

void BelialCore::Update()
{
	//Particle Update
	Effect::Update();
}

void BelialCore::Render()
{
	//Particle Render
	GameObject::Render();

}

bool BelialCore::Attack()
{
	return false;
}

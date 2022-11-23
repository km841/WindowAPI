#include "pch.h"
#include "BlackSmithNPC.h"
#include "Animation.h"
#include "Animator.h"
#include "ResourceMgr.h"
#include "Texture.h"

BlackSmithNPC::BlackSmithNPC()
{
	SetType(OBJECT_TYPE::NPC);
	CreateComponent(new Animator);
	GetAnimator()->SetOwner(this);

	mDefaultTexture = 
		ResourceMgr::GetInstance().Load<Texture>(L"BLACKSMITH_ANIMATION", L"Texture\\blacksmith_animation.bmp");
	
	SetSize(Vec2( 26*3, 24*3));

	GetAnimator()->RegisterAnimation(
		L"BlackSmithAnim",
		mDefaultTexture,
		Vec2(0.f, 0.f),
		Vec2(24.f, 26.f),
		Vec2(24.f, 0.f),
		0.1f,
		6
	);

	GetAnimator()->SelectAnimation(L"BlackSmithAnim", true);


}

BlackSmithNPC::~BlackSmithNPC()
{
}

void BlackSmithNPC::Initialize()
{
}

void BlackSmithNPC::Update()
{
	GameObject::Update();
}

void BlackSmithNPC::Render()
{
	GameObject::Render();
}

void BlackSmithNPC::Destroy()
{
}

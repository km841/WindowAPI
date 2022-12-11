#include "pch.h"
#include "GoldBar.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "RigidBody.h"
#include "ResourceMgr.h"
#include "Texture.h"

GoldBar::GoldBar()
{
	GetRigidBody()->SetMass(5.f);

	mTexture = ResourceMgr::GetInstance().Load<Texture>(L"GoldBarTex", L"Texture\\GoldBarAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"GoldBarAnim",
		mTexture,
		Vec2(0, 0),
		Vec2(60, 27),
		Vec2(60, 0),
		0.1f,
		7
	);

	GetAnimator()->SelectAnimation(L"GoldBarAnim", true);

}

GoldBar::~GoldBar()
{
}

void GoldBar::Initialize()
{
	Gold::Initialize();
}

void GoldBar::Update()
{
	Gold::Update();
}

void GoldBar::Render()
{
	Gold::Render();
}

void GoldBar::Destroy()
{
	Gold::Destroy();
}

void GoldBar::OnCollision(Collider* _other)
{
}

void GoldBar::OnCollisionEnter(Collider* _other)
{
}

void GoldBar::OnCollisionExit(Collider* _other)
{
}

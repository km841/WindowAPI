#include "pch.h"
#include "Coin.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "RigidBody.h"
#include "ResourceMgr.h"
#include "Texture.h"

Coin::Coin()
{
	GetRigidBody()->SetMass(1.f);
	
	mTexture = LOAD_TEXTURE(L"CoinTex", L"Texture\\CoinAnim.bmp");
	GetAnimator()->RegisterAnimation(
		L"CoinAnim",
		mTexture,
		Vec2(0, 0),
		Vec2(21, 21),
		Vec2(21, 0),
		0.05f,
		8
	);

	GetAnimator()->SelectAnimation(L"CoinAnim", true);
	
	// 애니메이션 작업

}

Coin::~Coin()
{
}

void Coin::Initialize()
{
	Gold::Initialize();
}

void Coin::Update()
{
	Gold::Update();
}

void Coin::Render()
{
	Gold::Render();
}

void Coin::Destroy()
{
	Gold::Destroy();
}

void Coin::OnCollision(Collider* _other)
{
}

void Coin::OnCollisionEnter(Collider* _other)
{
}

void Coin::OnCollisionExit(Collider* _other)
{
}

#include "pch.h"
#include "Monster.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"

Monster::Monster()
{
	SetPos(Vec2{ 900.f, 700.f });
	SetScale(Vec2{ 2.f, 2.f });
	SetType(OBJECT_TYPE::MONSTER);
	mTexture = ResourceMgr::GetInstance().Load<Texture>(L"Monster_Image", L"Texture\\Monster.bmp");
	assert(nullptr != mTexture);

	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
}

Monster::~Monster()
{

}

void Monster::Initialize()
{

}

void Monster::Update()
{
	GameObject::Update();
}

void Monster::Render()
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	// Convert Render Pos
	pos = RENDER_POS(pos);

	TransparentBlt(BACK_BUF_DC
		, (int)(pos.x - (mTexture->GetWidth() * scale.x) / 2.f)
		, (int)(pos.y - (mTexture->GetHeight() * scale.y) / 2.f)
		, (int)(mTexture->GetWidth() * scale.x)
		, (int)(mTexture->GetHeight() * scale.y)
		, mTexture->GetDC()
		, 0, 0
		, mTexture->GetWidth()
		, mTexture->GetHeight()
		, RGB(255, 0, 255)
	);

	GameObject::Render();
}

void Monster::Destroy()
{
}

void Monster::OnCollision(Collider* _other)
{
}

void Monster::OnCollisionEnter(Collider* _other)
{
	if (_other->GetOwner()->GetType() == OBJECT_TYPE::PLAYER)
		EventRegisteror::GetInstance().DeleteObject(this);
}

void Monster::OnCollisionExit(Collider* _other)
{
}

#include "pch.h"
#include "MonsterSwordEffect.h"
#include "Collider.h"
#include "Player.h"
#include "Monster.h"
#include "AI.h"
#include "EventRegisteror.h"

MonsterSwordEffect::MonsterSwordEffect()
{
	CreateComponent(new Collider);
	GetCollider()->SetOwner(this);
}

MonsterSwordEffect::~MonsterSwordEffect()
{
}

void MonsterSwordEffect::Initialize()
{
	
}

void MonsterSwordEffect::Update()
{
	//GameObject::Update();
	MonsterEffect::Update();
}

void MonsterSwordEffect::Render()
{
	Effect::Render();
}

void MonsterSwordEffect::OnCollision(Collider* _other)
{
}

void MonsterSwordEffect::OnCollisionEnter(Collider* _other)
{	
	
}

void MonsterSwordEffect::OnCollisionExit(Collider* _other)
{
}

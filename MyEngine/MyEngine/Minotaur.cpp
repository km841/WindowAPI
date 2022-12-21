#include "pch.h"
#include "Minotaur.h"
#include "Collider.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"
#include "EventRegisteror.h"
#include "CameraMgr.h"
#include "MonsterSwordEffect.h"
#include "CollisionMgr.h"
#include "Player.h"

Minotaur::Minotaur()
{
}

Minotaur::~Minotaur()
{
}

void Minotaur::Initialize()
{
}

void Minotaur::Update()
{
}

void Minotaur::Render()
{
}

void Minotaur::Destroy()
{
}

void Minotaur::GroundStateUpdate()
{
}

void Minotaur::OnCollision(Collider* _other)
{
}

void Minotaur::OnCollisionEnter(Collider* _other)
{
}

void Minotaur::OnCollisionExit(Collider* _other)
{
}

bool Minotaur::Attack()
{
    return false;
}

bool Minotaur::DetectPlayer()
{
    return false;
}

bool Minotaur::DetectIntoAttRange()
{
    return false;
}

void Minotaur::RecogLineRender(PEN_TYPE _penType)
{
}

void Minotaur::AttRangeLineRender(PEN_TYPE _penType)
{
}

void Minotaur::Dead()
{
}

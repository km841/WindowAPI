#include "pch.h"
#include "MonsterMissileEffect.h"

MonsterMissileEffect::MonsterMissileEffect()
{
}

MonsterMissileEffect::~MonsterMissileEffect()
{
}

void MonsterMissileEffect::Initialize()
{
	MonsterEffect::Initialize();
}

void MonsterMissileEffect::Update()
{
	// 공격 타입에 대한 Bullet 위치 변경
	MonsterEffect::Update();
}

void MonsterMissileEffect::Render()
{
}

bool MonsterMissileEffect::Attack()
{
	return true;
}

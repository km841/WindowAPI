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
	// ���� Ÿ�Կ� ���� Bullet ��ġ ����
	Effect::Update();
}

void MonsterMissileEffect::Render()
{
}

bool MonsterMissileEffect::Attack()
{
	return true;
}
#include "pch.h"
#include "MonsterEffect.h"
#include "Monster.h"

MonsterEffect::MonsterEffect()
{
	SetType(OBJECT_TYPE::MONSTER_EFFECT);
}

MonsterEffect::~MonsterEffect()
{
}

void MonsterEffect::Update()
{
	Effect::Update();
	Monster* monster= static_cast<Monster*>(GetOwner());
	mAtt = monster->GetMonsterInfo().mAtt;
}

void MonsterEffect::Render()
{
	Effect::Render();
}

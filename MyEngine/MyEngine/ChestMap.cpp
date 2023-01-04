#include "pch.h"
#include "ChestMap.h"
#include "Chest.h"
#include "EventRegisteror.h"

ChestMap::ChestMap(const std::wstring& _path)
	:Map(_path)
{
}

ChestMap::~ChestMap()
{
}

void ChestMap::Initialize()
{
	Map::Initialize();
}

void ChestMap::Update()
{
	Map::Update();
}

void ChestMap::Render()
{
}

void ChestMap::Destroy()
{
	Map::Destroy();
}

void ChestMap::Enter()
{
	Map::Enter();

	Chest* chest = new Chest;
	chest->SetPos(Vec2(350, 1155));

	EventRegisteror::GetInstance().CreateObject(chest, chest->GetType());
}

void ChestMap::Exit()
{
	Map::Exit();
}

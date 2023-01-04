#pragma once
#include "Map.h"
class ChestMap :
    public Map
{
public:
	ChestMap(const std::wstring& _path);
	virtual ~ChestMap();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	virtual void Enter();
	virtual void Exit();
};


#pragma once
#include "Scene.h"

class Tile;
class ToolScene :
	public Scene
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();

public:
	virtual void Enter();
	virtual void Exit();

public:
	void RemoveTile(Vec2 _pos);

public:
	void Save();
	void Load();

private:
	BLENDFUNCTION   mBlendFunc;

};
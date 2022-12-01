#pragma once
#include "Scene.h"

class Tile;
class UI;
class ToolScene :
	public Scene
{
public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destory();

public:
	virtual void Enter();
	virtual void Exit();

public:
	void RemoveTile(Vec2 _pos);
	IconUI* CutTile(UI* _parentUI, Vec2 _ltPos, Vec2 _slice);
	void    CutTiles(UI* _parentUI, Vec2 _ltPos, Vec2 _offset, Vec2 _slice, int _tileCount);

public:
	void GuideCircle();

public:
	void Save();
	void Load();

private:
	BLENDFUNCTION   mBlendFunc;

};
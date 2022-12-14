#pragma once
#include "Scene.h"

class Tile;
class UI;
class CheckButtonUI;
class ToolScene :
	public Scene
{
public:
	ToolScene();
	virtual ~ToolScene();

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
	void RemoveObject(Vec2 _pos);

public:
	inline void SetObjectType(OBJECT_TYPE _objType) { mCheckedObjectType = _objType; }
	inline void SetTileType(TILE_TYPE _tileType) { mCheckedTileType = _tileType; }
	void SetupTile();

	void AuxLineRender();

public:
	void GuideCircle();
	void GuideText();

	bool IsTileableArea(Vec2 _tilePos);

public:
	void Save();
	void Load();

private:
	BLENDFUNCTION   mBlendFunc;
	CheckButtonUI*  mNoneCheckBtn;

	OBJECT_TYPE     mCheckedObjectType;
	TILE_TYPE	    mCheckedTileType;
	TOOL_ID			mCurToolID;
};
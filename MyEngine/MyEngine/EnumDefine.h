#pragma once

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	WHITE,
	GRAY,
	END,
};

enum class RES_TYPE
{
	IMAGE,
	SOUND,
	END,
};

enum class SCENE_TYPE
{
	TITLE,
	TOOL,
	PLAY,
	TOWN,
	DUNGEON1,

	END,
};

enum class OBJECT_TYPE
{
	BACKGROUND_FIRST,
	BACKGROUND_MIDDLE,
	BACKGROUND_LAST,
	TILE,
	STRUCTURE,
	MONSTER,
	PLAYER,
	DUMMY,
	WALL,
	MISSILE_FROM_MONSTER,
	MISSILE_FROM_PLAYER,
	UI = 15,
	END = 16,
};

enum class EVENT_TYPE
{
	OBJECT_CREATE,
	// lParam : Object Pointer, wParam : Object Type

	OBJECT_DELETE,
	// lParam : Object Pointer, wParam : No used

	SCENE_CHANGE,
	// lParam : No used, wParam : Scene Type
};

enum class RELATION_TYPE
{
	COLLISION,
};
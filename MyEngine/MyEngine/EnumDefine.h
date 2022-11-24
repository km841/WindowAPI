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
	MAGENTA,
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
	STRUCTURE,
	TILE,
	NPC,
	EVENT_OBJECT,
	PLAYER,
	MONSTER,
	DUMMY,
	WALL,
	FOOTHOLD,
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

	OBJECT_TRANSFORT,
	// lParam : Object Pointer, wParam : Scepe Type

	SCENE_CHANGE,
	// lParam : No used, wParam : Scene Type

	ENABLE_UI,
	// lParam : No used, wParam : UI Type

	DISABLE_UI,
	// lParam : No used, wParam : UI Type

};

enum class RELATION_TYPE
{
	COLLISION,
};

enum class EQUIP_TYPE
{
	WEAPON_1,
	SHIELD_1,
	WEAPON_2,
	SHIELD_2,
	ACCESSORIES_1,
	ACCESSORIES_2,
	ACCESSORIES_3,
	ACCESSORIES_4,
	END
};

enum class ITEM_TYPE
{
	WEAPON,
	SECONDARY,
	ACCESSORIES,
};

enum class INVENTORY_SLOT
{
	LEFT_SLOT,
	RIGHT_SLOT
};

enum class VERTICES_POINT
{
	LEFT_TOP,
	RIGHT_TOP,
	LEFT_BOTTOM,
	END,
};

enum class SWORD_STATE
{
	UP_STATE,
	DOWN_STATE,
	END,
};

enum class UI_TYPE
{
	HP,
	DASH_GAUGE,
	MINIMAP,
	INVENTORY,
	TOOL,



	END
};

enum class TILE_TYPE
{
	WALL,
	FOOTHOLD,
	NONE,



	END
};
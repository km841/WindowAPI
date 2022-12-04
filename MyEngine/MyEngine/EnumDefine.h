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

#define OBJECT_TYPE_MAX 32
enum class OBJECT_TYPE
{
	BACKGROUND_FIRST,
	BACKGROUND_MIDDLE,
	BACKGROUND_LAST,
	STRUCTURE,
	TILE,
	NPC,
	EVENT_OBJECT,
	MONSTER,
	PLAYER,
	MONSTER_EFFECT,
	PLAYER_EFFECT,
	DUMMY,
	WALL,
	FOOTHOLD,
	MISSILE_FROM_MONSTER,
	MISSILE_FROM_PLAYER,
	UNIQUE_UI,
	UI = OBJECT_TYPE_MAX - 1,
	END = OBJECT_TYPE_MAX,
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

	MONSTER_STATE_CHANGE,
	// lParam : AI Pointer, wParam : Monster State Type

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
	END,
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

enum class MONSTER_STATE
{
	IDLE,
	TRACE,
	PATROL,
	DEAD,
	ATTACK,


	END,
};

enum class MONSTER_TYPE
{
	GROUND_MELEE,
	GROUND_RANGE,
	FLY_MELEE,
	FLY_RANGE,
	MELEE_FAST,
	RANGE_FAST,
	BOSS_1STAGE,
	BOSS_2STATE,

	END
};

enum class DIR
{
	LEFT,
	RIGHT,
	END,
};

enum class MONSTER_ATTACK_TYPE
{
	ROTATE,
	AIMING,
	END
};

enum class COLLISION_TYPE
{
	NONE,
	NORMAL,
	LINE,
	END
};
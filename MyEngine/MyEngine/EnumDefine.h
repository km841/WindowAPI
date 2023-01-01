#pragma once



enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	WHITE,
	GRAY,
	BLACK,
	NULL_COLOR,
	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	DUNGEON_BLACK,
	BLACK,
	WHITE,
	YELLOW,
	GRAY,
	MAGENTA,
	BLUE,
	RED,
	GREEN,
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
	DUNGEON,
	END,
};

#define OBJECT_TYPE_MAX 32
enum class OBJECT_TYPE
{
	BACKGROUND_FIRST,
	BACKGROUND_MIDDLE,
	BACKGROUND_LAST,
	STRUCTURE,
	TILE_BG,
	TILE,
	NPC,
	DUNGEON_OBJECT,
	DROP_GOLD,
	DROP_ITEM,
	PARTICLE,
	EVENT_OBJECT,
	DUMMY,
	MONSTER,
	MONSTER_EFFECT,
	PLAYER,
	PLAYER_EFFECT,
	WALL,
	FOOTHOLD,
	MISSILE_FROM_MONSTER,
	MISSILE_FROM_PLAYER,
	UNIQUE_UI = OBJECT_TYPE_MAX - 3,
	UI = OBJECT_TYPE_MAX - 2,
	HUD = OBJECT_TYPE_MAX - 1,
	END = OBJECT_TYPE_MAX,
};

enum class EVENT_TYPE
{
	OBJECT_CREATE,
	// lParam : Object Pointer, wParam : Object Type

	OBJECT_DELETE,
	// lParam : Object Pointer, wParam : No used

	OBJECT_DELETE_FROM_SCENE,
	// lParam : Object Pointer, wParam : No used

	OBJECT_TRANSFORT,
	// lParam : Object Pointer, wParam : Scepe Type

	SCENE_CHANGE,
	// lParam : No used, wParam : Scene Type

	ENABLE_UI,
	// lParam : No used, wParam : UI Type

	DISABLE_UI,
	// lParam : No used, wParam : UI Type

	ENABLE_HUD,
	// lParam : No used, wParam : HUD Type

	DISABLE_HUD,
	// lParam : No used, wParam : HUD Type

	MONSTER_STATE_CHANGE,
	// lParam : AI Pointer, wParam : Monster State Type

	TRANSITION_TO_MAP,
	// lParam : Next Map Pointer, wParam : Owner Stage Pointer

	STAGE_CHANGE,
	// lParam : No used, wParam : Stage Type
};

enum class RELATION_TYPE
{
	COLLISION,
};

enum class EQUIP_TYPE
{
	WEAPON_LEFT,
	SHIELD_LEFT,
	WEAPON_RIGHT,
	SHIELD_RIGHT,
	ACCESSORIES_1,
	ACCESSORIES_2,
	ACCESSORIES_3,
	ACCESSORIES_4,
	END
};

enum class INVENTORY_SLOT_TYPE
{
	INVEN_R1_C1,
	INVEN_R1_C2,
	INVEN_R1_C3,
	INVEN_R1_C4,
	INVEN_R1_C5,
	INVEN_R2_C1,
	INVEN_R2_C2,
	INVEN_R2_C3,
	INVEN_R2_C4,
	INVEN_R2_C5,
	INVEN_R3_C1,
	INVEN_R3_C2,
	INVEN_R3_C3,
	INVEN_R3_C4,
	INVEN_R3_C5,
	END,
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
	INVENTORY,
	TOOL,



	END
};

enum class HUD_TYPE
{
	HP,
	DASH_GAUGE,
	MINIMAP,
	NPC_LINE,
	EQUIPED,
	ITEM_GET,
	ITEM_INFO,
	BOSS_HP,
	BOSS_APPEAR,
	END,
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
	ATTACK_AFTER,
	SKILL,
	BOSS_IDLE,
	BOSS_SKILL,


	END,
};

enum class MONSTER_TYPE
{
	GROUND_MELEE,
	GROUND_OP_CHARGE,
	GROUND_CHARGE,
	GROUND_RANGE,
	GROUND_SKILL,
	FLY_MELEE,
	FLY_RANGE,
	MELEE_FAST,
	RANGE_FAST,
	BOSS_BELIAL,
	BOSS_NIFLHEIM,

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

enum class LINE_TYPE
{
	FLAT,
	DEGREE_45,
	DEGREE_135,
	FLAT_WALL,
	DEGREE_45_WALL,
	DEGREE_135_WALL,
	END,
};

enum class CHECK_TYPE
{
	COLLISION,
	TILE,
	NONE,
	END,
};

enum class OBJECT_STATE
{
	ALIVE,
	DEAD_ANIM,
	DEAD,
	END
};

enum class PLAYER_CHARACTER
{
	PLAYER,
	LASLEY,
	END
};

enum class ID
{
	WALL,
	FOOTHOLD,
	EMPTY,
	BACKGROUND,
	SURFACE,
};

enum class ANGLE_TYPE
{
	DEGREE_0_TYPE,
	DEGREE_90_TYPE,
	DEGREE_180_TYPE,
	DEGREE_270_TYPE,
};

enum class EQUIPED_CHANGING_STATE
{
	NONE,
	CHANGING,
	COMPLETE,
};

enum class RARITY
{
	NORMAL,
	RARE,
	UNIQUE,
	END,
};

enum class WEAPON_TYPE
{
	ONE_HAND,
	TWO_HAND,
	NONE,
	END,
};

enum class BULLET_WAY_TYPE
{
	LINEAR,
	ROTATE,
	END,
};

enum class MINOTAUR_STATE
{
	NONE,
	CHARGE,
	ATTACK,
	END,
};

enum class STAGE_TYPE
{
	PRISON,
	SNOW_MOUNTAIN,
	END,
};

enum class WARP_POINT
{
	LEFT,
	RIGHT,
	TOP,
	BOTTOM,
	END,
};

enum class MAP_TYPE
{
	NORMAL,
	BOSS_SIDE,
	BOSS,
	BOSS_NEXT,
	END,
};

enum class TOOL_ID
{
	BTN_RED_GIANT_BAT,
	BTN_GIANT_BAT,
	BTN_GIANT_SKULL,
	BTN_BANSHEE,
	BTN_ICE_GRAY_SKULL,
	BTN_MINOTAUR,
	BTN_ICE_MAGE,
	BTN_OVIBOS,
	BTN_DOOR_0DEG,
	BTN_DOOR_90DEG,
	BTN_DOOR_180DEG,
	BTN_DOOR_270DEG,
	BTN_BELIAL_DOOR,
	BTN_NIFLHEIM_DOOR,
	END,
};

enum class MONSTER_ENUM
{
	RED_GIANT_BAT,
	GIANT_BAT,
	GIANT_SKULL,
	ICE_GRAY_SKULL,
	MINOTAUR,
	BANSHEE,
	ICEMAGE,
	END,

};

enum class FONT_TYPE
{
	NORMAL,
	SEMI_BOLD,
	BOLD,
	END,
};

enum class DOOR_STATE
{
	OPEN,
	CLOSE,
	END,
};

enum class BOSS_SKILL
{
	SKILL_1,
	SKILL_2,
	SKILL_3,
	END,
};

enum class TRANS_MODE
{
	FADE_IN,
	FADE_OUT,
	END,
};

enum class BELIAL_HAND_TYPE
{
	LEFT_HAND,
	RIGHT_HAND,
	END,
};

enum class BELIAL_LASER_TYPE
{
	HEAD,
	BODY,
	END,
};
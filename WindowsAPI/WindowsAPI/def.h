#pragma once

#define KEY_PRESSED(KEY) Input::GetKeyState(KEY) == eKeyState::PRESSED
#define KEY_DOWN(KEY) Input::GetKeyState(KEY) == eKeyState::DOWN
#define KEY_UP(KEY) Input::GetKeyState(KEY) == eKeyState::UP
#define KEY_NONE(KEY) Input::GetKeyState(KEY) == eKeyState::NONE

enum class eSceneType
{
	Logo,
	Title,
	Play,
	End,
	Max,
};

enum class ePenColor
{
	Red,
	Blue,
	Green,




	End,
};

enum class eBrushColor
{
	Transparent,
	Black,
	Gray, // 167 0 67
	White,
	End,
};

enum class eComponentType
{
	Animator,
	Collider,
	Sound,


	End,
};

#define _COLLIDER_LAYER 16

enum class eColliderLayer
{
	Default,
	Background,
	Tile,
	Player,
	Player_Projecttile,
	Monster,
	Monster_Projecttile,

	UI = _COLLIDER_LAYER - 1,
	End = _COLLIDER_LAYER
};

union ColliderID
{
	struct {
		UINT32 left;
		UINT32 right;
	};

	UINT64 ID;
};
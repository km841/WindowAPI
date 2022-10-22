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

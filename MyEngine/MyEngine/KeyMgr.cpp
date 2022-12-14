#include "pch.h"
#include "KeyMgr.h"
#include "Player.h"

void KeyMgr::Initialize()
{
	for (int i = 0; i < (UINT)KEY::END; ++i)
	{
		mKeyStates[i] = KEY_STATE::RELEASED;
	}
}

void KeyMgr::Update()
{
	if (GetFocus())
	{
		for (int i = 0; i < (UINT)KEY::END; ++i)
		{
			if (GetAsyncKeyState(KEY_CODE[i]) & 0x8000)
			{
				switch (mKeyStates[i])
				{
				case KEY_STATE::JUST_PRESSED:
					mKeyStates[i] = KEY_STATE::PRESSED;
					break;

				case KEY_STATE::PRESSED:
					break;

				case KEY_STATE::JUST_RELEASED:
					mKeyStates[i] = KEY_STATE::JUST_PRESSED;
					break;

				case KEY_STATE::RELEASED:
					mKeyStates[i] = KEY_STATE::JUST_PRESSED;
					break;
				}
			}

			else
			{
				switch (mKeyStates[i])
				{
				case KEY_STATE::JUST_PRESSED:
					mKeyStates[i] = KEY_STATE::JUST_RELEASED;
					break;

				case KEY_STATE::PRESSED:
					mKeyStates[i] = KEY_STATE::JUST_RELEASED;
					break;

				case KEY_STATE::JUST_RELEASED:
					mKeyStates[i] = KEY_STATE::RELEASED;
					break;

				case KEY_STATE::RELEASED:
					break;
				}
			}
		}
	}
	
}

KEY_STATE KeyMgr::GetKeyState(KEY _ekey) const
{
	return mKeyStates[(UINT)_ekey];
}
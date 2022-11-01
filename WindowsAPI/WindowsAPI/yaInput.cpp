#include "yaInput.h"

namespace ya
{
	std::vector<Input::Key> Input::mKeys;
	int ASCII[(UINT)eKeyCode::End] =
	{
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		MK_LBUTTON, MK_RBUTTON,

		VK_NUMPAD0,
		VK_NUMPAD1,
		VK_NUMPAD2,
		VK_NUMPAD3,
		VK_NUMPAD4,
		VK_NUMPAD5,
		VK_NUMPAD6,
		VK_NUMPAD7,
		VK_NUMPAD8,
		VK_NUMPAD9,

		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	};



	void Input::Initialize()
	{
		for (int i = 0; i < (UINT)eKeyCode::End; i++)
		{
			Key key;
			key.keyCode = (eKeyCode)ASCII[i];
			key.state = eKeyState::NONE;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}

	void Input::Tick()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::End; i++)
		{
			// 해당 키가 눌려져 있는 경우
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (mKeys[i].bPressed)
				{
					mKeys[i].state = eKeyState::PRESSED;
				}
				else
				{
					mKeys[i].state = eKeyState::DOWN;
				}

				mKeys[i].bPressed = true;
			}

			else
			{

				if (mKeys[i].bPressed)
				{
					mKeys[i].state = eKeyState::UP;
				}
				else
				{
					mKeys[i].state = eKeyState::NONE;
				}

				mKeys[i].bPressed = false;
			}
			

			// 눌려 있지 않은 경우
		}
	}

	void Input::Render(HDC hdc)
	{

	}

	eKeyState Input::GetKeyState(eKeyCode keyCode)
	{
		return mKeys[(UINT)keyCode].state;
	}

}
#include "pch.h"
#include "MouseMgr.h"
#include "KeyMgr.h"

MouseMgr::MouseMgr()
	: mState(MOUSE_STATE::NONE)
	, mLastLClickPos{}
	, mLastRClickPos{}
{

}

MouseMgr::~MouseMgr()
{
}

void MouseMgr::Update()
{
	if (GetFocus())
	{
		POINT point = {};
		GetCursorPos(&point);
		ScreenToClient(APP_INSTANCE.GetHwnd(), &point);
		mCurPos = Vec2((float)(point.x), (float)(point.y));

		if (IS_PRESSED(KEY::LBUTTON))
		{
			switch (mState)
			{
			case MOUSE_STATE::NONE:
				mState = MOUSE_STATE::JUST_LBTN_CLICKED;
				break;

			case MOUSE_STATE::JUST_LBTN_CLICKED:
				mState = MOUSE_STATE::LBTN_CLICKED;
				mLastLClickPos = mCurPos;
				break;
			}

		}

		else if (IS_PRESSED(KEY::RBUTTON))
		{
			switch (mState)
			{
			case MOUSE_STATE::NONE:
				mState = MOUSE_STATE::JUST_RBTN_CLICKED;
				break;

			case MOUSE_STATE::JUST_RBTN_CLICKED:
				mState = MOUSE_STATE::RBTN_CLICKED;
				mLastRClickPos = mCurPos;
				break;
			}
		}

		else
		{
			switch (mState)
			{
			case MOUSE_STATE::JUST_LBTN_CLICKED:
				mState = MOUSE_STATE::JUST_LBTN_RELEASED;
				break;

			case MOUSE_STATE::LBTN_CLICKED:
				mState = MOUSE_STATE::JUST_LBTN_RELEASED;
				break;

			case MOUSE_STATE::JUST_RBTN_CLICKED:
				mState = MOUSE_STATE::JUST_RBTN_RELEASED;
				break;

			case MOUSE_STATE::RBTN_CLICKED:
				mState = MOUSE_STATE::JUST_RBTN_RELEASED;
				break;

			default:
				mState = MOUSE_STATE::NONE;
				break;

			}
		}
	}

}

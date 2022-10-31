#include "pch.h"
#include "EventRegisteror.h"
#include "EventMgr.h"

void EventRegisteror::CreateObject(GameObject* _obj, OBJECT_TYPE _eType)
{
	Event event = {};
	event.eType = EVENT_TYPE::OBJECT_CREATE;
	event.lParam = (DWORD_PTR)_obj;
	event.wParam = (DWORD_PTR)_eType;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::DeleteObject(GameObject* _obj)
{
	Event event = {};
	event.eType = EVENT_TYPE::OBJECT_DELETE;
	event.lParam = (DWORD_PTR)_obj;
	event.wParam = 0;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::ChangeScene(SCENE_TYPE _eType)
{
	Event event = {};
	event.eType = EVENT_TYPE::SCENE_CHANGE;
	event.wParam = (DWORD_PTR)_eType;
	event.lParam = 0;
	
	EventMgr::GetInstance().AddEvent(event);
}

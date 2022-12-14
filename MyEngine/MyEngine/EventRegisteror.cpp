#include "pch.h"
#include "EventRegisteror.h"
#include "EventMgr.h"
#include "Stage.h"
#include "Map.h"

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

void EventRegisteror::DeleteObjectFromScene(GameObject* _obj)
{
	Event event = {};
	event.eType = EVENT_TYPE::OBJECT_DELETE_FROM_SCENE;
	event.lParam = (DWORD_PTR)_obj;
	event.wParam = 0;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::TransfortObject(GameObject* _obj, SCENE_TYPE _eType)
{
	Event event = {};
	event.eType = EVENT_TYPE::OBJECT_TRANSFORT;
	event.lParam = (DWORD_PTR)_obj;
	event.wParam = (DWORD_PTR)_eType;

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

void EventRegisteror::ChangeStage(STAGE_TYPE _eType)
{
	Event event = {};
	event.eType = EVENT_TYPE::STAGE_CHANGE;
	event.wParam = (DWORD_PTR)_eType;
	event.lParam = 0;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::ChangeMonsterState(AI* _ai, MONSTER_STATE _eState)
{
	Event event = {};
	event.eType = EVENT_TYPE::MONSTER_STATE_CHANGE;
	event.lParam = (DWORD_PTR)_ai;
	event.wParam = (DWORD_PTR)_eState;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::TransitionToMap(Stage* _stage, Map* _map)
{
	Event event = {};
	event.eType = EVENT_TYPE::TRANSITION_TO_MAP;
	event.wParam = (DWORD_PTR)_stage;
	event.lParam = (DWORD_PTR)_map;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::EnableUI(UI_TYPE _eType)
{
	Event event = {};
	event.eType = EVENT_TYPE::ENABLE_UI;
	event.wParam = (DWORD_PTR)_eType;
	event.lParam = 0;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::DisableUI(UI_TYPE _eType)
{
	Event event = {};
	event.eType = EVENT_TYPE::DISABLE_UI;
	event.wParam = (DWORD_PTR)_eType;
	event.lParam = 0;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::EnableHUD(HUD_TYPE _eType)
{
	Event event = {};
	event.eType = EVENT_TYPE::ENABLE_HUD;
	event.wParam = (DWORD_PTR)_eType;
	event.lParam = 0;

	EventMgr::GetInstance().AddEvent(event);
}

void EventRegisteror::DisableHUD(HUD_TYPE _eType)
{
	Event event = {};
	event.eType = EVENT_TYPE::DISABLE_HUD;
	event.wParam = (DWORD_PTR)_eType;
	event.lParam = 0;

	EventMgr::GetInstance().AddEvent(event);
}

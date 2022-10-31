#include "pch.h"
#include "EventMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Collider.h"
#include "GameObject.h"

void EventMgr::Initialize()
{
}

void EventMgr::Update()
{
	for (UINT i = 0; i < mEvents.size(); ++i)
	{
		Execute(mEvents[i]);
	}
	mEvents.clear();
}

void EventMgr::Execute(Event _event)
{
	switch (_event.eType)
	{
	case EVENT_TYPE::OBJECT_CREATE:
	{
		Scene* scene = SceneMgr::GetInstance().GetCurScene();
		scene->AddGameObject((GameObject*)_event.lParam, (OBJECT_TYPE)_event.wParam);
	}
		break;

	case EVENT_TYPE::OBJECT_DELETE:
	{
		GameObject* obj = (GameObject*)_event.lParam;
		// 나와 연결된 충돌 제거
		CollisionClear(obj);
		// 오브젝트 제거
		DeleteObject(obj, obj->GetType());
	}
		break;

	case EVENT_TYPE::SCENE_CHANGE:
		SceneMgr::GetInstance().ChangeScene((SCENE_TYPE)_event.wParam);
		break;
	}
}

void EventMgr::CollisionClear(GameObject* _obj)
{
	std::set<Relation>& relSet = _obj->GetRelations();
	for (auto& rel : relSet)
	{
		//상대의 관계도를 가져옴
		GameObject* other = rel.mOther;
		std::set<Relation>& otherRelSet = other->GetRelations();
		std::set<Relation>::iterator otherIter = otherRelSet.begin();

		//상대의 관계도를 돌며 내가 있다면 충돌을 해제하고 나를 삭제
		for (; otherIter != otherRelSet.end();)
		{
			if (otherIter->mOther == _obj)
			{
				other->GetCollider()->OnCollisionExit(_obj->GetCollider());
				otherIter = otherRelSet.erase(otherIter);
			}
			else
				otherIter++;
		}
	}
}

bool EventMgr::DeleteObject(GameObject* _obj, OBJECT_TYPE _eType)
{
	Scene* scene = SceneMgr::GetInstance().GetCurScene();
	std::vector<GameObject*>& group = scene->mObjects[(UINT)_eType];
	std::vector<GameObject*>::iterator iter = group.begin();

	while (_obj != *iter && iter != group.end())
		iter++;

	if (iter != group.end())
	{
		group.erase(iter);
		delete _obj;
		_obj = nullptr;
		return true;
	}

	return false;
}

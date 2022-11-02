#include "pch.h"
#include "Collider.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "GameObject.h"


void CollisionMgr::Initialize()
{
}

void CollisionMgr::Update()
{
	for (int y = 0; y < (UINT)OBJECT_TYPE::END; ++y)
	{
		for (int x = 0; x < (UINT)OBJECT_TYPE::END; ++x)
		{
			if (mBits[y][x] == true)
			{

				Scene* scene = SceneMgr::GetInstance().GetCurScene();

				std::vector<GameObject*> rowGroup = scene->GetObjectGroup((OBJECT_TYPE)y);
				std::vector<GameObject*> colGroup = scene->GetObjectGroup((OBJECT_TYPE)x);

				CheckGroup(rowGroup, colGroup);

			}
		}
	}
}

void CollisionMgr::SetCollision(OBJECT_TYPE _first, OBJECT_TYPE _second)
{
	UINT row = (UINT)_first;
	UINT col = (UINT)_second;
	if (row > col)
	{
		row = col;
		col = (UINT)_first;
	}

	mBits[row][col].flip();
}

void CollisionMgr::CheckGroup(std::vector<GameObject*>& _row, std::vector<GameObject*>& _col)
{
	for (UINT left = 0; left < _row.size(); ++left)
	{
		if (nullptr == _row[left]->GetCollider())
			continue;

		for (UINT right = 0; right < _col.size(); ++right)
		{
			GameObject* leftObj = _row[left];
			GameObject* rightObj = _col[right];
			Collider* leftCol = leftObj->GetCollider();
			Collider* rightCol = rightObj->GetCollider();

			if (nullptr == rightCol)
				continue;

			if (leftObj == rightObj)
				continue;

			// 이전 프레임의 상태를 가져오는 중
			COLLISION_ID id = {};
			id.LID = leftCol->GetID();
			id.RID = rightCol->GetID();

			std::map<ULONGLONG, bool>::iterator iter = mColMap.find(id.ID);

			if (mColMap.end() == iter)
			{
				mColMap.insert(std::make_pair(id.ID, false));
				iter = mColMap.find(id.ID);
			}

			if (IsCollision(leftCol, rightCol))
			{

				// 이전에도 충돌중이었음
				if (iter->second)
				{
					leftCol->OnCollision(rightCol);
					rightCol->OnCollision(leftCol);
				}

				// 첫 충돌
				else
				{
					leftCol->OnCollisionEnter(rightCol);
					rightCol->OnCollisionEnter(leftCol);
					iter->second = true;

					leftObj->AddRelation(rightObj, RELATION_TYPE::COLLISION);
					rightObj->AddRelation(leftObj, RELATION_TYPE::COLLISION);
				}
			}

			else
			{
				if (iter->second)
				{
					leftCol->OnCollisionExit(rightCol);
					rightCol->OnCollisionExit(leftCol);
					iter->second = false;

					leftObj->SeverRelation(rightObj, RELATION_TYPE::COLLISION);
					rightObj->SeverRelation(leftObj, RELATION_TYPE::COLLISION);
				}

				else
				{

				}
			}

		}
	}
}

bool CollisionMgr::IsCollision(Collider* _left, Collider* _right)
{
	Vec2 leftPos = _left->GetPos();
	Vec2 rightPos = _right->GetPos();

	Vec2 leftSize = _left->GetSize();
	Vec2 rightSize = _right->GetSize();

	if (abs(leftPos.x - rightPos.x) < (leftSize.x + rightSize.x) / 2.f &&
		abs(leftPos.y - rightPos.y) < (leftSize.y + rightSize.y) / 2.f)
	{
		return true;
	}

	return false;
}

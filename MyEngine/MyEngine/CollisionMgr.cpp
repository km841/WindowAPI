#include "pch.h"
#include "Collider.h"
#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "GameObject.h"
#include "Tile.h"
#include "Wall.h"
#include "Foothold.h"
#include "LineCollider.h"


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

void CollisionMgr::Render()
{
	wchar_t playerPos[COMMENT_MAX_SIZE] = {};
	swprintf_s(playerPos, L"linelength : %f, totallength : %f", debug1, debug2);
	TextOut(BACK_BUF_DC, 10, 90, playerPos, (int)wcslen(playerPos));
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

			if (!leftCol->GetEnable() || !rightCol->GetEnable())
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
					leftObj->AddRelation(rightObj, RELATION_TYPE::COLLISION);
					rightObj->AddRelation(leftObj, RELATION_TYPE::COLLISION);
					leftCol->OnCollisionEnter(rightCol);
					rightCol->OnCollisionEnter(leftCol);
					iter->second = true;

				}
			}

			else
			{
				if (iter->second)
				{
					leftObj->SeverRelation(rightObj, RELATION_TYPE::COLLISION);
					rightObj->SeverRelation(leftObj, RELATION_TYPE::COLLISION);
					leftCol->OnCollisionExit(rightCol);
					rightCol->OnCollisionExit(leftCol);
					iter->second = false;

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


	COLLISION_TYPE leftColType = _left->GetColliderType();
	COLLISION_TYPE rightColType = _right->GetColliderType();

	//충돌체 사각형의 점 하나라도 들어오면?

	// 충돌체의 상하좌우 모서리를 검사?

	if (COLLISION_TYPE::LINE == leftColType)
	{
		// 두 점을 가져온다.
		// 두 점과 나머지 콜라이더의 pos를 비교
		LineCollider* lineCollider = static_cast<LineCollider*>(_left);

		Vec2 leftDot = lineCollider->GetLeftDotPos();
		Vec2 rightDot = lineCollider->GetRightDotPos();

		// 사각형의 네 변에 대한 선충돌

		Vec2 leftTop = Vec2(leftPos.x - leftSize.x / 2.f, leftPos.y - leftSize.y / 2.f);
		Vec2 rightTop = Vec2(leftPos.x + leftSize.x / 2.f, leftPos.y - leftSize.y / 2.f);
		Vec2 leftBottom = Vec2(leftPos.x - leftSize.x / 2.f, leftPos.y + leftSize.y / 2.f);
		Vec2 rightBottom = Vec2(leftPos.x + leftSize.x / 2.f, leftPos.y + leftSize.y / 2.f);

		bool isLeft = LineToLineCollision(leftDot, rightDot, leftBottom, leftTop);
		bool isRight = LineToLineCollision(leftDot, rightDot, rightBottom, rightTop);
		bool isTop = LineToLineCollision(leftDot, rightDot, leftTop, rightTop);
		bool isBottom = LineToLineCollision(leftDot, rightDot, leftBottom, rightBottom);

		if (isLeft || isRight || isTop || isBottom)
		{
			return true;
		}

	}

	else if (COLLISION_TYPE::LINE == rightColType)
	{
		LineCollider* lineCollider = static_cast<LineCollider*>(_right);

		Vec2 leftDot = lineCollider->GetLeftDotPos();
		Vec2 rightDot = lineCollider->GetRightDotPos();

		// 사각형의 네 변에 대한 선충돌

		Vec2 leftTop = Vec2(leftPos.x - leftSize.x / 2.f, leftPos.y - leftSize.y / 2.f);
		Vec2 rightTop = Vec2(leftPos.x + leftSize.x / 2.f, leftPos.y - leftSize.y / 2.f);
		Vec2 leftBottom = Vec2(leftPos.x - leftSize.x / 2.f, leftPos.y + leftSize.y / 2.f);
		Vec2 rightBottom = Vec2(leftPos.x + leftSize.x / 2.f, leftPos.y + leftSize.y / 2.f);

		bool isLeft = LineToLineCollision(leftDot, rightDot, leftBottom, leftTop);
		bool isRight = LineToLineCollision(leftDot, rightDot, rightBottom, rightTop);
		bool isTop = LineToLineCollision(leftDot, rightDot, leftTop, rightTop);
		bool isBottom = LineToLineCollision(leftDot, rightDot, leftBottom, rightBottom);

		if (isLeft || isRight || isTop || isBottom)
		{
			return true;
		}
	}

	else
	{
		if (abs(leftPos.x - rightPos.x) <= (leftSize.x + rightSize.x) / 2.f &&
			abs(leftPos.y - rightPos.y) <= (leftSize.y + rightSize.y) / 2.f)
		{
			return true;
		}
	}

	return false;
}

bool CollisionMgr::LineToLineCollision(Vec2 _v1, Vec2 _v2, Vec2 _v3, Vec2 _v4)
{

	// calculate the distance to intersection point
	float det = ((_v4.y - _v3.y) * (_v2.x - _v1.x) - (_v4.x - _v3.x) * (_v2.y - _v1.y));
	float uA = ((_v4.x - _v3.x) * (_v1.y - _v3.y) - (_v4.y - _v3.y) * (_v1.x - _v3.x)) / det;
	float uB = ((_v2.x - _v1.x) * (_v1.y - _v3.y) - (_v2.y - _v1.y) * (_v1.x - _v3.x)) / det;

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) 
	{
		return true;
	}
	return false;

}

void CollisionMgr::CollisionForceQuit(Collider* _left, Collider* _right)
{
	COLLISION_ID colID = {};
	colID.LID = _left->GetID();
	colID.RID = _right->GetID();

	std::map<ULONGLONG, bool>::iterator iter = mColMap.find(colID.ID);
	
	if (mColMap.end() != iter)
	{
		_left->OnCollisionExit(_right);
		_right->OnCollisionExit(_left);
		
		_left->GetOwner()->SeverRelation(_right->GetOwner(), RELATION_TYPE::COLLISION);
		_right->GetOwner()->SeverRelation(_left->GetOwner(), RELATION_TYPE::COLLISION);

		mColMap.erase(iter);
	}
}

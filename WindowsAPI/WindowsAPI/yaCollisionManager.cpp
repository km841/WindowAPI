#include "yaCollisionManager.h"
#include "yaScene.h"
#include "yaSceneManager.h"
#include "yaGameObject.h"
#include "yaCollider.h"

namespace ya
{
	WORD CollisionManager::mMatrix[_COLLIDER_LAYER] = {};
	std::bitset<_COLLIDER_LAYER> CollisionManager::mMatrix2 = {};




	void CollisionManager::Tick()
	{
		Scene* playScene = SceneManager::GetPlayScene();

		for (size_t row = 0; row < _COLLIDER_LAYER; row++)
		{
			for (size_t col = 0; col < _COLLIDER_LAYER; col++)
			{
				if (mMatrix[row] & (1 << col))
				{
					LayerCollision(playScene, (eColliderLayer)row, (eColliderLayer)col);
				}
			}
		}


	}

	void CollisionManager::SetLayer(eColliderLayer left, eColliderLayer right, bool value)
	{
		// 더 작은 수를 행으로
		UINT row = 0;
		UINT col = 0;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft < iRight)
		{
			row = (UINT)left;
			col = (UINT)right;
		}

		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}
		
		if (value == true)
			mMatrix[row] |= (1 << col);
		
		else
			mMatrix[row] &= ~(1 << col);

		
		

	}

	void CollisionManager::LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right)
	{
		std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (auto leftObject : lefts)
		{
			if (leftObject->GetComponent<Collider>() == nullptr)
				continue;

			for (auto rightObject : rights)
			{
				if (rightObject->GetComponent<Collider>() == nullptr)
					continue;

				if (leftObject == rightObject)
					continue;

				if (Intersect(leftObject->GetComponent<Collider>(), rightObject->GetComponent<Collider>()))
				{
					int a = 0;
				}

				else
				{
					int a = 0;
				}
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->GetPos();
		Vector2 leftScale = left->GetScale();

		Vector2 rightPos = right->GetPos();
		Vector2 rightScale = right->GetScale();

		if (fabs(leftPos.x - rightPos.x) < fabs(leftScale.x + rightScale.x / 2.f)
			&& fabs(leftPos.y - rightPos.y) < fabs(leftScale.y + rightScale.y / 2.f))
		{
			return true;
		}

		return false;
	}

}
#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class GameObject;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);
		
		void AddGameObject(GameObject* object);
		//void Destroy();


	private:
		std::vector<GameObject*> mObjects;

	};
}



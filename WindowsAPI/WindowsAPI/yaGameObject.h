#pragma once
#include "Common.h"
#include "yaEntity.h"
#include "yaComponent.h"

namespace ya
{
	class Collider;
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		// ĳ������ pos�� �߹� �߾��� �������� ����
		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() const { return mPos; }

		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() const { return mScale; }

		void AddComponent(Component* component)
		{
			if (nullptr == component)
				return;
			mComponents.push_back(component);
			component->mOwner = this;
		}

		template<typename T>
		_forceinline T* GetComponent()
		{
			T* returnComp;
			for (Component* component : mComponents)
			{
				returnComp = dynamic_cast<T*>(component);
				if (returnComp != nullptr)
					return returnComp;
			}

			return nullptr;
		}

	/*	void SetHdc(HDC hdc) { mHdc = hdc; }
		HDC GetHdc() const  { return mHdc; }*/



	private:
		// �ɼ��� ���ҽ� ũ�⺯�������ʰ� �״�� ���°� ���� ����
		std::vector<Component*> mComponents;
		Vector2 mPos;
		Vector2 mScale;
		//HDC mHdc;

	};
}



#include "yaGameObject.h"



namespace ya
{

	GameObject::GameObject()
		: mPos(Vector2{ 0.f, 0.f })
		, mScale(Vector2{ 1.0f, 1.0f })
	{

	}

	GameObject::~GameObject()
	{
		for (Component* component : mComponents)
		{
			if (nullptr == component)
				continue;

			delete component;
			component = nullptr;
		}
	}

	void GameObject::Initialize()
	{


	}

	void GameObject::Tick()
	{
		for (Component* component : mComponents)
		{
			if (nullptr == component)
				continue;

			component->Tick();
		}

	}

	void GameObject::Render(HDC hdc)
	{
		for (Component* component : mComponents)
		{
			if (nullptr == component)
				continue;
			component->Render(hdc);
		}

	}

	void GameObject::OnCollisionEnter(Collider* other)
	{
	}

	void GameObject::OnCollisionStay(Collider* other)
	{
	}

	void GameObject::OnCollisionExit(Collider* other)
	{
	}

}
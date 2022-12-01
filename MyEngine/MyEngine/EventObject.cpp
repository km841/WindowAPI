#include "pch.h"
#include "EventObject.h"


EventObject::EventObject()
{
	SetType(OBJECT_TYPE::EVENT_OBJECT);
}

EventObject::~EventObject()
{
}

void EventObject::Initialize()
{
}

void EventObject::Update()
{
	GameObject::Update();
}

void EventObject::Render()
{
	GameObject::Render();
}

void EventObject::Destroy()
{
}

void EventObject::OnCollision(Collider* _other)
{
}

void EventObject::OnCollisionEnter(Collider* _other)
{

}

void EventObject::OnCollisionExit(Collider* _other)
{
}

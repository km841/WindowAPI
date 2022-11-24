#pragma once
#include "GameObject.h"
class EventObject :
    public GameObject
{
public:
    EventObject();
    virtual ~EventObject();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);


};


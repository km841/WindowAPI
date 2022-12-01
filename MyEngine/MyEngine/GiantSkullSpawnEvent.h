#pragma once
#include "MonsterSpawnEvent.h"
class GiantSkullSpawnEvent :
    public MonsterSpawnEvent
{
public:
    GiantSkullSpawnEvent();
    virtual ~GiantSkullSpawnEvent();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void Spawn();

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);


};


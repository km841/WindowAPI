#pragma once
#include "CollisionComponent.h"
class Tile;
class Wall :
    public CollisionComponent
{
public:
    Wall();
    virtual ~Wall();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:

private:

};


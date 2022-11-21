#pragma once
#include "GameObject.h"

class Tile;
class CollisionComponent :
    public GameObject
{
public:
    CollisionComponent();
    virtual ~CollisionComponent();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    inline void SetOwner(Tile* _tile) { mOwner = _tile; }
    inline Tile* GetOwner() const { return mOwner; }

private:
    Tile* mOwner;

};


#pragma once
#include "Singleton.h"

union COLLISION_ID
{
    struct
    {
        UINT LID;
        UINT RID;
    };

    ULONGLONG ID;
};
class Collider;
class GameObject;
class CollisionMgr :
    public Singleton< CollisionMgr >
{
public:
    void Initialize();
    void Update();
    void Render();

public:
    void SetCollision(OBJECT_TYPE _first, OBJECT_TYPE _second);
    void CheckGroup(std::vector<GameObject*>& _row, std::vector<GameObject*>& _col);
    bool IsCollision(Collider* _left, Collider* _right);
    bool LineToLineCollision(Vec2 _v1, Vec2 _v2, Vec2 _v3, Vec2 _v4);

public:
    void CollisionForceQuit(Collider* _left, Collider* _right);

private:
    std::bitset<(UINT)OBJECT_TYPE::END> mBits[(UINT)OBJECT_TYPE::END];
    std::map<ULONGLONG, bool>           mColMap;

private:
    float debug1;
    float debug2;
};


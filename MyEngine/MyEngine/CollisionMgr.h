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
    using CollisionSet = std::pair<OBJECT_TYPE, OBJECT_TYPE>;
public:
    void Initialize();
    void Update();

    void SetCollision(OBJECT_TYPE _first, OBJECT_TYPE _second);
    void CheckGroup(std::vector<GameObject*>& _row, std::vector<GameObject*>& _col);
    bool IsCollision(Collider* _left, Collider* _right);

private:
    std::bitset<(UINT)OBJECT_TYPE::END> mBits[(UINT)OBJECT_TYPE::END];
    std::map<ULONGLONG, bool> mColMap;


};


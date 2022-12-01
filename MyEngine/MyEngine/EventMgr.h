#pragma once
#include "Singleton.h"


class GameObject;
class EventMgr :
    public Singleton< EventMgr >
{
public:
    void Initialize();
    void Update();
    void Destroy();

public:
    void Execute(Event _event);

public:
    inline void AddEvent(Event _event) { mEvents.push_back(_event); }
    const std::vector<Event>& GetEvents() { return mEvents; }

private:
    void CollisionClear(GameObject* _obj);
    bool DeleteObject(GameObject* _obj, OBJECT_TYPE _eType);

private:
    std::vector<Event> mEvents;

};


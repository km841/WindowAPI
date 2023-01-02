#pragma once
#include "EventObject.h"

class Sound;
class DungeonEatEvent :
    public EventObject
{
public:
    DungeonEatEvent();
    virtual ~DungeonEatEvent();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;
    virtual void Destroy() override;

public:
    virtual void OnCollision(Collider* _other);
    virtual void OnCollisionEnter(Collider* _other);
    virtual void OnCollisionExit(Collider* _other);

public:
    inline void SetFixPos(Vec2 _fixPos) { mFixPos = _fixPos; }
    inline Vec2 GetFixPos() const { return mFixPos; }

private:
    Vec2 mFixPos;
    Sound* mSound;

};


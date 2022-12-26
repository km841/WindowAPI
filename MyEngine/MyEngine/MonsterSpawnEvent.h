#pragma once
#include "EventObject.h"
#include "EventRegisteror.h"
#include "MonsterFactory.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "Monster.h"

class Monster;

template<typename T>
class MonsterSpawnEvent :
    public EventObject
{
public:
    MonsterSpawnEvent()
        :mFlag(false)
        , mSpawnTiming(4)
    {
        CreateComponent(new Collider);
        GetCollider()->SetOwner(this);

        GetCollider()->SetSize(Vec2(30.f, 30.f));
        GetCollider()->SetOffset(Vec2(0.f, -15.f));

        CreateComponent(new Animator);
        GetAnimator()->SetOwner(this);

        Texture* spawnAnimTex =
            ResourceMgr::GetInstance().Load<Texture>(L"MONSTER_SPAWN_TEX", L"Texture\\monster_spawn_animation.bmp");

        GetAnimator()->RegisterAnimation(
            L"MONSTER_SPAWN_ANIM",
            spawnAnimTex,
            Vec2(0.f, 0.f),
            Vec2(93, 93),
            Vec2(93, 0),
            0.06f,
            15
        );

        SetSize(Vec2(93, 93));
    }



    virtual ~MonsterSpawnEvent() {}

public:
    void Update()
    {
        EventObject::Update();
        if (mSpawnPos.IsZero())
        {
            GetAnimator()->SelectAnimation(L"MONSTER_SPAWN_ANIM", false);
            mFlag = true;
            mSpawnPos = GetPos();
        }

        if (true == mFlag)
        {
            Animation* curAnim = GetAnimator()->GetCurAnimation();
            int curFrame = curAnim->GetCurFrame();

            if (curFrame == mSpawnTiming)
            {
                Spawn();
                EventRegisteror::GetInstance().DeleteObject(this);
            }
        }
    }
    void Render()
    {
        EventObject::Render();
    }

public:

    void Spawn()
    {
        T* monster =
            static_cast<T*>(MonsterFactory::CreateMonster<T>(T::TYPE, mSpawnPos));
        monster->Initialize();

        EventRegisteror::GetInstance().CreateObject(monster, monster->GetType());
    }

public:
    inline void SetSpawnPos(Vec2 _pos) { mSpawnPos = _pos; };

public:
    void OnCollisionEnter(Collider* _other)
    {
        if (OBJECT_TYPE::PLAYER == _other->GetOwner()->GetType())
        {
            mFlag = true;
            GetAnimator()->SelectAnimation(L"MONSTER_SPAWN_ANIM", false);
            SetPos(mSpawnPos);
        }
    }

    // 특정 오브젝트를 밟으면 몬스터 소환
    // 특정 프레임이 되면 애니메이션을 정지하고 몬스터를 소환한다.

protected:
    bool mFlag;
    int  mSpawnTiming;
    Vec2 mSpawnPos;
    MONSTER_TYPE mMonsterType;

};


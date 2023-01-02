#include "pch.h"
#include "BoomEffect.h"
#include "Animator.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Animation.h"

BoomEffect::BoomEffect()
{
    SetType(OBJECT_TYPE::MONSTER_EFFECT);

    CreateComponent(new Animator);
    GetAnimator()->SetOwner(this);

    Texture* monsterDeadTex = LOAD_TEXTURE(L"MonsterDeadTex", L"Texture\\MonsterDeadTex.bmp");

    Animation* deadAnim = GetAnimator()->CreateAnimation(
        L"MonsterDeadAnim",
        monsterDeadTex,
        Vec2(0.f, 0.f),
        Vec2(192.f, 192.f),
        Vec2(192.f, 0.f),
        0.05f,
        11
    );

    deadAnim->SetOffset(Vec2(0.f, 50.f));

    GetAnimator()->AddAnimation(L"MonsterDeadAnim", deadAnim);

    GetAnimator()->SelectAnimation(L"MonsterDeadAnim", false);
}

BoomEffect::~BoomEffect()
{
}

void BoomEffect::Initialize()
{
    GameObject::Initialize();
}

void BoomEffect::Update()
{
    GameObject::Update();
    
    Animation* anim = GetAnimator()->GetCurAnimation();
    if (nullptr != anim)
    {
        if (anim->IsFinished())
        {
            SetObjState(OBJECT_STATE::DEAD);
        }
    }
}

void BoomEffect::Render()
{
    GameObject::Render();
}

void BoomEffect::Destroy()
{
    GameObject::Destroy();
}

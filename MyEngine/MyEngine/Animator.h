#pragma once
#include "Component.h"

class Texture;
class Animation;

class Animator :
    public Component
{
public:
    Animator();
    virtual ~Animator();

public:
    virtual void Update();
    virtual void Render();

public:
    void CreateAnimation(const std::wstring& _animName, Texture* _tex, Vec2 _leftTop
                             , Vec2 _slice, Vec2 _offset, float _duration, UINT _frmCount);

    Animation* FindAnimation(const std::wstring& _animName);
    void SelectAnimation(const std::wstring& _animName);

private:
    std::map<std::wstring, Animation*> mAnimMap;
    Animation*                         mCurAnim;
};


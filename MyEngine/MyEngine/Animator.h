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
    Animation* CreateAnimation(const std::wstring& _animName, Texture* _tex, Vec2 _leftTop
                             , Vec2 _slice, Vec2 _offset, float _duration, UINT _frmCount);

    void AddAnimation(const std::wstring& _animName, Animation* _anim) { mAnimMap.insert(std::make_pair(_animName, _anim)); }
    void RegisterAnimation(const std::wstring& _animName, Texture* _tex, Vec2 _leftTop
                            , Vec2 _slice, Vec2 _offset, float _duration, UINT _frmCount);

    Animation* FindAnimation(const std::wstring& _animName);
    void SelectAnimation(const std::wstring& _animName, bool _repeat = true);
    void RotSelectAnimation(const std::wstring& _animName, float _angle, bool _repeat = true);

    inline Animation* GetCurAnimation() const { return mCurAnim; }

    

private:
    std::map<std::wstring, Animation*> mAnimMap;
    Animation*                         mCurAnim;
};


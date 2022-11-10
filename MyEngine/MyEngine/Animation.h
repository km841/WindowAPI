#pragma once

class Animator;
class Texture;
class GameObject;

struct AnimInfo
{
    Vec2 mLeftTop;
    Vec2 mSlice;
    Vec2 mOffset;
    float mDuration;
};

class Animation
{
public:
    Animation();
    virtual ~Animation();
    friend class Animator;

    struct EventAnimation
    {
        Animation*   mAnim;
        Vec2         mOffset;
        Vec2         mSize;
        std::wstring mName;

        EventAnimation()
            : mAnim(nullptr)
        {}

        EventAnimation(const std::wstring& _name, Animation* _anim, Vec2 _offset, Vec2 _size)
            : mAnim(_anim)
            , mOffset(_offset)
            , mSize(_size)
        {}
    };

    struct Event
    {
        EventAnimation mEnter;
        EventAnimation mExit;
    };

public:
    virtual void Update();
    virtual void Render();

public:
    void Create(Texture* _tex, Vec2 _leftTop, Vec2 _slice, Vec2 _offset, float _duration, UINT _frmCount);
    inline void SetName(const std::wstring& _name) { mName = _name; }
    inline const std::wstring& GetName() const { return mName; }

    void SetEnterEvent(EventAnimation _event); 
    void SetExitEvent(EventAnimation _event);

private:
    Animator*             mOwner;
    Texture*              mTex;
    std::wstring          mName;
    
    std::vector<AnimInfo> mAnim;
    int                   mCurFrm;
    float                 mAccTime;
    bool                  mRepeat;

private:
    Event*                mEvent;
    GameObject*           mDummyObj;
};


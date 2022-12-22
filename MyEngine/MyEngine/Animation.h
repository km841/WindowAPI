#pragma once

class Animator;
class Texture;
class GameObject;

struct AnimInfo
{
    Vec2 mLeftTop;
    Vec2 mSlice;
    Vec2 mOffset;
    Vec2 mControl;
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

    inline void                SetName(const std::wstring& _name) { mName = _name; }
    inline const std::wstring& GetName() const { return mName; }

    inline void SetOffset(Vec2 _offset) { mOffset = _offset; }
    inline Vec2 GetOffset() const { return mOffset; }

    void SetEnterEvent(EventAnimation _event); 
    void SetExitEvent(EventAnimation _event);

    inline int  GetCurFrame() const { return mCurFrm; }
    inline void SetCurFrame(int _frm) { mCurFrm = _frm; }

    inline void     SetTexture(Texture* _tex) { mTex = _tex; }
    inline Texture* GetTexture() const { return mTex; }

    inline bool IsFinished() const { return mFinish; }

    inline void SetOwner(Animator* _anim) { mOwner = _anim; }

    inline void SetRepeat(bool _repeat) { mRepeat = _repeat; }

    inline void SetEffectAnimation(bool _effect) { mEffect = _effect; }

    inline void SetFrameFix(bool _flag) { mFix = _flag; }
    inline bool GetFrameFix() const { return mFix; }

    void SetFrameControl(int _frame, Vec2 _control);
    void SetFrameDuration(int _frame, float _duration);

    void SetTransMode(bool _flag, float _maxTime);

    inline const std::vector<AnimInfo>& GetAnimInfo() const { return mAnim; }

    void Reset();

private:
    Animator*             mOwner;
    Texture*              mTex;
    std::wstring          mName;
    Vec2                  mOffset;
    
    std::vector<AnimInfo> mAnim;
    int                   mCurFrm;
    float                 mAccTime;
    bool                  mRepeat;
    bool                  mFinish;
    bool                  mEffect;
    bool                  mFix;

    bool                  mTrans;
    float                 mTransCurTime;
    float                 mTransMaxTime;


private:
    Event*                mEvent;
    GameObject*           mDummyObj;
    BLENDFUNCTION         mBlendFunc;
};


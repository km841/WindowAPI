#pragma once

class Animator;
class Texture;

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

public:
    virtual void Update();
    virtual void Render();

public:
    void Create(Texture* _tex, Vec2 _leftTop, Vec2 _slice, Vec2 _offset, float _duration, UINT _frmCount);
    inline void SetName(const std::wstring& _name) { mName = _name; }
    inline const std::wstring& GetName() const { return mName; }

private:
    Animator*             mOwner;
    Texture*              mTex;

    std::wstring          mName;
    
    std::vector<AnimInfo> mAnim;
    int                   mCurFrm;
    float                 mAccTime;
};


#pragma once
class TimeMgr :
    public Singleton< TimeMgr >
{
public:
    void Initialize();
    void Update();
    void Render();

public:
    inline float GetDT() const { return mDT; };


private:
    LARGE_INTEGER mPrevCount;
    LARGE_INTEGER mCurCount;
    LARGE_INTEGER mPrequency;

    float mDT;
    double mAcc;
    UINT mCallCount;
    UINT mFPS;
};


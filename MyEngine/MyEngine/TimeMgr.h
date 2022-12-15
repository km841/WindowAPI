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
    std::wstring GetCurTime();


private:
    LARGE_INTEGER mPrevCount;
    LARGE_INTEGER mCurCount;
    LARGE_INTEGER mFrequency;

    float mDT;
    double mAcc;
    UINT mCallCount;
    UINT mFPS;


};


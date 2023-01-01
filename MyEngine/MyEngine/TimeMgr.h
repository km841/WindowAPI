#pragma once
class TimeMgr :
    public Singleton< TimeMgr >
{
public:
    TimeMgr();
    ~TimeMgr();

public:
    void Initialize();
    void Update();
    void Render();

public:
    inline float GetDT() const { return mDT; };
    std::wstring GetCurTime();

    void SetDeltaTime(float _magn, float _maxTime);
    inline bool IsDTChange() const { return mDTChange; }

private:
    LARGE_INTEGER mPrevCount;
    LARGE_INTEGER mCurCount;
    LARGE_INTEGER mFrequency;

    bool mDTChange;

    float mMagnification;
    float mSettingMaxTime;
    float mSettingCurTime;

    float mDT;
    double mAcc;
    UINT mCallCount;
    UINT mFPS;


};


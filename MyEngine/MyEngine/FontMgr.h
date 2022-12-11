#pragma once
#include "Singleton.h"

class Texture;
class FontObject;

struct TextInfo
{
    Vec2 mLTPos;
    Vec2 mSlice;
};

class FontMgr :
    public Singleton< FontMgr >
{
public:
    void Initialize();
    void Update();
    void Render();
    void Destroy();

public:
    // Number
    Texture* GetTextTexture(const std::wstring& _key, const std::wstring& _text);
    Texture* GetTextTexture_Gold(const std::wstring& _key, const std::wstring& _text);
    TextInfo GetTextInfo(wchar_t _text);

public:
    // 위치정보를 적어서 mDamage에 푸시해줌
    // DamageObject는 서서히 이동하며 사라진다

    void OutputDamage(int _damage, Vec2 _pos);
    void OutputGold(int _gold, Vec2 _pos);
    void FontUpdate();
    void FontRender();

private:
    // 문자에 대한 좌표를 던져준다.
    std::map<wchar_t, TextInfo> mTextMap;
    Texture* mTex;
    Texture* mGoldTex;

    // 데미지 오브젝트는 타원운동을 함
    // 알파블렌딩으로 희미해지며..
    std::vector<FontObject*> mFonts;
};


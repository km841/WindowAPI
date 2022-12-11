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
    // ��ġ������ ��� mDamage�� Ǫ������
    // DamageObject�� ������ �̵��ϸ� �������

    void OutputDamage(int _damage, Vec2 _pos);
    void OutputGold(int _gold, Vec2 _pos);
    void FontUpdate();
    void FontRender();

private:
    // ���ڿ� ���� ��ǥ�� �����ش�.
    std::map<wchar_t, TextInfo> mTextMap;
    Texture* mTex;
    Texture* mGoldTex;

    // ������ ������Ʈ�� Ÿ����� ��
    // ���ĺ������� ���������..
    std::vector<FontObject*> mFonts;
};


#pragma once
#include "Singleton.h"

class Texture;
class DamageObject;

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

public:
    // Number
    Texture* GetTextTexture(const std::wstring& _key, const std::wstring& _text);
    TextInfo GetTextInfo(wchar_t _text);

public:
    // ��ġ������ ��� mDamage�� Ǫ������
    // DamageObject�� ������ �̵��ϸ� �������

    void OutputDamage(int _damage, Vec2 _pos);
    void DamageUpdate();
    void DamageRender();

private:
    // ���ڿ� ���� ��ǥ�� �����ش�.
    std::map<wchar_t, TextInfo> mTextMap;
    Texture* mTex;

    // ������ ������Ʈ�� Ÿ����� ��
    // ���ĺ������� ���������..
    std::vector<DamageObject*> mDamages;

};


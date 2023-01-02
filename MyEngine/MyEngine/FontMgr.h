#pragma once
#include "Singleton.h"

class Texture;
class FontObject;
class Sound;


class FontMgr :
    public Singleton< FontMgr >
{
public:
    FontMgr();
    ~FontMgr();

public:
    void Initialize();
    void Update();
    void Render();
    void Destroy();

public:
    // Number
    Texture* GetTextTexture(const std::wstring& _key, const std::wstring& _text, HDC _dc = BACK_BUF_DC);
    Texture* GetTextTexture(const std::wstring& _key, wchar_t _text);
    Texture* GetTextTexture_Gold(const std::wstring& _key, const std::wstring& _text);
    Texture* GetTextTexture_Damage(const std::wstring& _key, const std::wstring& _text);
   
    TextInfo GetTextInfo(wchar_t _text);
    TextInfo GetDamageTextInfo(wchar_t _text);

public:
    // ��ġ������ ��� mDamage�� Ǫ������
    // DamageObject�� ������ �̵��ϸ� �������

    void OutputDamage(int _damage, Vec2 _pos);
    void OutputGold(int _gold, Vec2 _pos);
    void FontUpdate();
    void FontRender();

    // Output NPC Line
    void OutputNPCLine(const std::wstring& _text, Vec2 _pos);
    void NPCLineUpdate();
    void NPCLineRender();
    void NPCLineClear();

private:
    // ���ڿ� ���� ��ǥ�� �����ش�.
    std::map<wchar_t, TextInfo> mTextMap;
    std::map<wchar_t, TextInfo> mObjectTextMap;
    Texture* mTex;
    Texture* mGoldTex;
    Texture* mBlackSmithLineTex;
    Texture* mObjectTex;

    Sound* mSound;

    int mNPCLineIdx;

    // ������ ������Ʈ�� Ÿ����� ��
    // ���ĺ������� ���������..
    std::vector<FontObject*> mFonts;
    std::vector<FontObject*> mNPCLines;
};


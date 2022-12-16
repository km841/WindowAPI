#include "pch.h"
#include "FontMgr.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "FontObject.h"
#include "TimeMgr.h"


FontMgr::FontMgr()
   : mTex(nullptr)
   , mGoldTex(nullptr)
   , mBlackSmithLineTex(nullptr)
   , mNPCLineIdx(0)
{
}

FontMgr::~FontMgr()
{
}

void FontMgr::Initialize()
{
    mTex = ResourceMgr::GetInstance().Load<Texture>(L"TextTex", L"Texture\\TextTex.bmp");
    mGoldTex = ResourceMgr::GetInstance().Load<Texture>(L"TextTex_Gold", L"Texture\\TextTex_Gold.bmp");
    mBlackSmithLineTex = ResourceMgr::GetInstance().Load<Texture>(L"BlackSmith_Line", L"Texture\\BlackSmith_Line.bmp");
    
    wchar_t buf[COMMENT_MAX_SIZE] = L"0123456789G";
    size_t textSize = wcslen(buf);
    for (int i = 0; i < textSize; ++i)
    {
        TextInfo info = {};
        info.mLTPos = Vec2(14 * i, 0);
        info.mSlice = Vec2(14, 22);

        mTextMap.insert(std::make_pair(buf[i], info));
    }

    int space[] = { 2, 5, 9, 15, 19 };
    Vec2 spaceSlice = Vec2(10.5f, 27.f);
    Vec2 otherSlice = Vec2(21, 27);
    std::wstring blackSmithLine = L"�׸� ���� ������ �ƴ�����. ������ �ɰɼ�!";

    int ltOffset = 0;
    for (int i = 0; i < blackSmithLine.size(); ++i)
    {   
        TextInfo info = {};
        auto iter = std::find(std::begin(space), std::end(space), i);
        if (iter == std::end(space))
             info.mSlice = otherSlice;

        else
            info.mSlice = spaceSlice;

        info.mLTPos = Vec2(ltOffset, 22);
        ltOffset += (int)info.mSlice.x;

        mTextMap.insert(std::make_pair(blackSmithLine[i], info));
    }
}

void FontMgr::Update()
{
    FontUpdate();
    NPCLineUpdate();

}

void FontMgr::Render()
{
    FontRender();
    NPCLineRender();
}

void FontMgr::Destroy()
{
    for (int i = 0; i < mFonts.size(); ++i)
    {
        if (nullptr != mFonts[i])
        {
            delete mFonts[i];
            mFonts[i] = nullptr;
        }
    }

    mFonts.clear();
}

Texture* FontMgr::GetTextTexture(const std::wstring& _key, const std::wstring& _text)
{
    int textureWidth = 0;
    int textureHeight = 0;

    for (int i = 0; i < _text.size(); ++i)
    {
        TextInfo info = GetTextInfo(_text[i]);
        textureWidth += (int)info.mSlice.x;
        textureHeight = (int)info.mSlice.y;
    }

    Texture* tex = static_cast<Texture*>(ResourceMgr::GetInstance().FindTexture(_key));
    if (nullptr != tex)
        return tex;

    tex = ResourceMgr::GetInstance().CreateTexture(_key, Vec2(textureWidth, textureHeight));

    int x_pos = 0;
    for (int i = 0; i < _text.size(); ++i)
    {
        TextInfo info = GetTextInfo(_text[i]);
        // ���� �ؽ�Ʈ ��ġ
        BitBlt(
            tex->GetDC(),
            (int)x_pos, 0,
            (int)info.mSlice.x,
            (int)info.mSlice.y,
            mTex->GetDC(),
            (int)info.mLTPos.x,
            (int)info.mLTPos.y,
            SRCCOPY
        );

        x_pos += (int)info.mSlice.x;
    }
    
    return tex;
}

Texture* FontMgr::GetTextTexture(const std::wstring& _key, wchar_t _text)
{
    TextInfo info = GetTextInfo(_text);
    float textureWidth = info.mSlice.x;
    float textureHeight = info.mSlice.y;


    Texture* tex = static_cast<Texture*>(ResourceMgr::GetInstance().FindTexture(_key));
    if (nullptr != tex)
        return tex;

    tex = ResourceMgr::GetInstance().CreateTexture(_key, Vec2(textureWidth, textureHeight));

    // ���� �ؽ�Ʈ ��ġ
    BitBlt(
        tex->GetDC(),
        0, 0,
        (int)info.mSlice.x,
        (int)info.mSlice.y,
        mTex->GetDC(),
        (int)info.mLTPos.x,
        (int)info.mLTPos.y,
        SRCCOPY
    );

    return tex;
}

Texture* FontMgr::GetTextTexture_Gold(const std::wstring& _key, const std::wstring& _text)
{
    int textureWidth = 0;
    int textureHeight = 0;

    std::wstring goldText = _text + L"G";

    for (int i = 0; i < goldText.size(); ++i)
    {
        TextInfo info = GetTextInfo(goldText[i]);
        textureWidth += (int)info.mSlice.x;
        textureHeight = (int)info.mSlice.y;
    }

    Texture* tex = static_cast<Texture*>(ResourceMgr::GetInstance().FindTexture(_key));
    if (nullptr != tex)
        return tex;

    tex = ResourceMgr::GetInstance().CreateTexture(_key, Vec2(textureWidth, textureHeight));

    int x_pos = 0;
    for (int i = 0; i < goldText.size(); ++i)
    {
        TextInfo info = GetTextInfo(goldText[i]);
        // ���� �ؽ�Ʈ ��ġ
        BitBlt(
            tex->GetDC(),
            (int)x_pos, 0,
            (int)info.mSlice.x,
            (int)info.mSlice.y,
            mGoldTex->GetDC(),
            (int)info.mLTPos.x,
            (int)info.mLTPos.y,
            SRCCOPY
        );

        x_pos += (int)info.mSlice.x;
    }

    return tex;
}

TextInfo FontMgr::GetTextInfo(wchar_t _text)
{
    std::map<wchar_t, TextInfo>::iterator iter = mTextMap.find(_text);

    if (mTextMap.end() != iter)
    {
        return iter->second;
    }

    TextInfo info = {};
    info.mSlice = Vec2(0, 0);

    return info;
}

void FontMgr::OutputDamage(int _damage, Vec2 _pos)
{
    // ����� �ϴµ�... y�δ� �ݸ� ��
    // �׳� pos�� �޾Ƽ� 
    
    // ��� ������Ʈ�Ϸ��� �갡 FontMgr�� ������Ʈ�Ǿ�� ��
    // �����̴°� ��� ������...
    // �� ������ Update���� ����
    
    // ����� �Ϸ���..
    // x = r x cos, y = r x sin 
    // ���� ������ �־�� ��
    // ������ �����ָ鼭.....
    // �� �굵 fontmgr�� ��������

    FontObject* fontObj = new FontObject;

    wchar_t buff[COMMENT_MAX_SIZE] = {};
    _itow_s(_damage, buff, 10);
    Texture* fontTex = GetTextTexture(buff, buff);

    _pos.x += 10.f;
    // �������� ����Ű�� ���͸� ���� �� 
    // 135����ŭ ������ �ű⿡ 10�� ���Ѵ�

    Vec2 dir = Vec2(1, 0);
    float angle = 225.f;
    float radius = 10.f;
    dir = Math::RotateVector(dir, angle);
    dir *= radius;

    fontObj->SetTexture(fontTex);
    fontObj->SetCenter(_pos);
    fontObj->SetPos(_pos + dir);
    fontObj->SetAngle(angle);
    fontObj->SetRadius(radius);
    // ������ �ʱⰪ���� 135

    mFonts.push_back(fontObj);
}

void FontMgr::OutputGold(int _gold, Vec2 _pos)
{
    FontObject* fontObj = new FontObject;

    wchar_t buff[COMMENT_MAX_SIZE] = {};
    _itow_s(_gold, buff, 10);
    Texture* fontTex = GetTextTexture_Gold(buff, buff);

    _pos.x += 10.f;
    // �������� ����Ű�� ���͸� ���� �� 
    // 135����ŭ ������ �ű⿡ 10�� ���Ѵ�

    Vec2 dir = Vec2(1, 0);
    float angle = 225.f;
    float radius = 10.f;
    dir = Math::RotateVector(dir, angle);
    dir *= radius;

    fontObj->SetTexture(fontTex);
    fontObj->SetCenter(_pos);
    fontObj->SetPos(_pos + dir);
    fontObj->SetAngle(angle);
    fontObj->SetRadius(radius);
    // ������ �ʱⰪ���� 135

    mFonts.push_back(fontObj);
}

void FontMgr::FontUpdate()
{
    std::vector<FontObject*>::iterator iter = mFonts.begin();

    for (; iter != mFonts.end(); )
    {
        float angle = iter.operator*()->GetAngle();
 
        if (!(iter.operator*()->IsDead()))
        {
            Vec2 pos = iter.operator*()->GetPos();
            Vec2 center = iter.operator*()->GetCenter();
            float radius = iter.operator*()->GetRadius();

            float omega_x = 180.f * (DT);
            float omega_y = 90.f * (DT);
            angle += omega_x;
            
            float angle_x = Math::DegreeToRadian(angle + omega_x);
            float angle_y = Math::DegreeToRadian(angle + omega_y);
            
            pos.x = center.x + radius * cos(angle_x);
            pos.y = center.y + radius * sin(angle_y);

            iter.operator*()->SetAngle(angle);
            iter.operator*()->SetPos(pos);

            iter.operator*()->Update();
            ++iter;
        }

        else
        {
            delete *iter;
            iter = mFonts.erase(iter);
        }

       
    }

}

void FontMgr::FontRender()
{
    for (int i = 0; i < mFonts.size(); ++i)
    {
        if (nullptr != mFonts[i])
        {
            mFonts[i]->Render();
        }
    }
}

void FontMgr::OutputNPCLine(const std::wstring& _text, Vec2 _pos)
{
    for (int i = 0; i < _text.size(); ++i)
    {
        TextInfo info = GetTextInfo(_text[i]);
        info.mDuration = 0.f;

        FontObject* font = new FontObject;

        font->SetPos(_pos);
        _pos.x += info.mSlice.x;
        font->SetTextInfo(info);

        std::wstring temp(1, _text[i]);
        font->SetTexture(GetTextTexture(temp, _text[i]));
        mNPCLines.push_back(font);
    }
}

void FontMgr::NPCLineUpdate()
{
    for (int i = 0; i < mNPCLines.size(); ++i)
    {
        if (mNPCLines.size() > mNPCLineIdx && 
            i == mNPCLineIdx)
        {
            TextInfo& info = mNPCLines[i]->GetTextInfo();
            if (0.1f < info.mDuration)
            {
                ++mNPCLineIdx;
                info.mDuration = 0.f;
                break;
            }

            else
            {
                info.mDuration += DT;
            }
        }
    }
}

void FontMgr::NPCLineRender()
{
    for (int i = 0; i < mNPCLines.size(); ++i)
    {
        if (i <= mNPCLineIdx)
        {
            Texture* curTex = mNPCLines[i]->GetTexture();
            Vec2 pos = mNPCLines[i]->GetPos();
            Vec2 size = curTex->GetSize();

            TransparentBlt(
                BACK_BUF_DC,
                (int)pos.x,
                (int)pos.y,
                (int)size.x,
                (int)size.y,
                curTex->GetDC(),
                0, 0,
                (int)size.x,
                (int)size.y,
                RGB(255, 0, 255)
            );
        }
    }
}

void FontMgr::NPCLineClear()
{
    mNPCLineIdx = 0;
    for (int i = 0; i < mNPCLines.size(); ++i)
    {
        if (nullptr != mNPCLines[i])
        {
            delete mNPCLines[i];
            mNPCLines[i] = nullptr;
        }
    }

    mNPCLines.clear();
}

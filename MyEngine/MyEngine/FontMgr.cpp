#include "pch.h"
#include "FontMgr.h"
#include "ResourceMgr.h"
#include "Texture.h"
#include "DamageObject.h"
#include "TimeMgr.h"


void FontMgr::Initialize()
{
    mTex = ResourceMgr::GetInstance().Load<Texture>(L"TextTex", L"Texture\\TextTex.bmp");
    
    wchar_t buf[COMMENT_MAX_SIZE] = L"0123456789G";
    size_t textSize = wcslen(buf);
    for (int i = 0; i < textSize; ++i)
    {
        TextInfo info = {};
        info.mLTPos = Vec2(14 * i, 0);
        info.mSlice = Vec2(14, 22);

        mTextMap.insert(std::make_pair(buf[i], info));
    }
}

void FontMgr::Update()
{
    DamageUpdate();


}

void FontMgr::Render()
{
    DamageRender();
}

void FontMgr::Destroy()
{
    for (int i = 0; i < mDamages.size(); ++i)
    {
        if (nullptr != mDamages[i])
        {
            delete mDamages[i];
            mDamages[i] = nullptr;
        }
    }

    mDamages.clear();
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

    DamageObject* damageObj = new DamageObject;

    wchar_t buff[COMMENT_MAX_SIZE] = {};
    _itow_s(_damage, buff, 10);
    Texture* damageTex = GetTextTexture(buff, buff);

    _pos.x += 10.f;
    // �������� ����Ű�� ���͸� ���� �� 
    // 135����ŭ ������ �ű⿡ 10�� ���Ѵ�

    Vec2 dir = Vec2(1, 0);
    float angle = 225.f;
    float radius = 10.f;
    dir = Math::RotateVector(dir, angle);
    dir *= radius;

    damageObj->SetTexture(damageTex);
    damageObj->SetCenter(_pos);
    damageObj->SetPos(_pos + dir);
    damageObj->SetAngle(angle);
    damageObj->SetRadius(radius);
    // ������ �ʱⰪ���� 135

    mDamages.push_back(damageObj);
}

void FontMgr::DamageUpdate()
{
    std::vector<DamageObject*>::iterator iter = mDamages.begin();

    for (; iter != mDamages.end(); )
    {
        float angle = iter.operator*()->GetAngle();
 
        if (!(iter.operator*()->IsDead()))
        {
            Vec2 pos = iter.operator*()->GetPos();
            Vec2 center = iter.operator*()->GetCenter();
            float radius = iter.operator*()->GetRadius();

            float omega_x = 180.f * (DT / 2.f);
            float omega_y = 90.f * (DT / 2.f);
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
            iter = mDamages.erase(iter);
        }

       
    }

}

void FontMgr::DamageRender()
{
    for (int i = 0; i < mDamages.size(); ++i)
    {
        if (nullptr != mDamages[i])
        {
            mDamages[i]->Render();
        }
    }
}

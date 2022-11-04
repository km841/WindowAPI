#pragma once
#include "Res.h"
class Texture :
    public Res
{
public:
    Texture();
    Texture(const std::wstring& _key);
    virtual ~Texture();

    virtual bool Load(const std::wstring& _path);

    inline HBITMAP GetBitmap() const { return mBit; }
    inline UINT GetWidth() const { return mWidth; }
    inline UINT GetHeight() const { return mHeight; }
    inline Vec2 GetSize() const { return mSize; }
    inline HDC GetDC() const { return mDC; }

private:
    HDC          mDC;
    HBITMAP      mBit;
    Vec2         mSize;
    UINT         mWidth;
    UINT         mHeight;

};


#pragma once
#include "Item.h"
class Sword :
    public Item
{
public:
    Sword();
    virtual ~Sword();

public:
    virtual void Initialize() override;
    virtual void Update() override;
    virtual void Render() override;

public:
    inline void SetLeftTopVertex(Vec2 _lt) { mVertices[(UINT)VERTICES_POINT::LEFT_TOP] = _lt; }
    inline void SetRightTopVertex(Vec2 _rt) { mVertices[(UINT)VERTICES_POINT::RIGHT_TOP] = _rt; }
    inline void SetLeftBottomVertex(Vec2 _lb) { mVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM] = _lb; }

    inline POINT GetLeftTopVertex() const { return mVertices[(UINT)VERTICES_POINT::LEFT_TOP]; }
    inline POINT GetRightTopVertex() const { return mVertices[(UINT)VERTICES_POINT::RIGHT_TOP]; }
    inline POINT GetLeftBottomVertex() const  { return mVertices[(UINT)VERTICES_POINT::LEFT_BOTTOM]; }

    inline void SetTransTexture(Texture* _maskTex) { mTransTexture = _maskTex; }
    inline Texture* GetTransTexture() const { return mTransTexture; }

    inline void SetOffset(Vec2 _offset) { mOffset = _offset; }
    inline Vec2 GetOffset() const { return mOffset; }

private:
    Vec2 mVertices[(UINT)VERTICES_POINT::END];
    Vec2 mOffset;
    Texture* mTransTexture;

};


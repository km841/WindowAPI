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

    inline void SetLeftDirOffset(float _offset) { mXAxisDirOffset[(UINT)PLAYER_DIR::LEFT] = _offset; }
    inline void SetRightDirOffset(float _offset) { mXAxisDirOffset[(UINT)PLAYER_DIR::RIGHT] = _offset; }
    inline float GetLeftDirOffset() const { return mXAxisDirOffset[(UINT)PLAYER_DIR::LEFT]; }
    inline float GetRightDirOffset() const { return mXAxisDirOffset[(UINT)PLAYER_DIR::RIGHT]; }

    inline float GetYOffset() const { return mYAxisOffset; }
    inline void SetYOffset(float _offset) { mYAxisOffset = _offset; }



private:
    Vec2 mVertices[(UINT)VERTICES_POINT::END];
    Vec2 mRotatedVertices[(UINT)VERTICES_POINT::END];
    Vec2 mOffset;
    float mXAxisDirOffset[(UINT)PLAYER_DIR::END];
    float mYAxisOffset;

    Texture* mTransTexture;

};


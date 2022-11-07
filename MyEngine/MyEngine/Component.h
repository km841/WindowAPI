#pragma once
class GameObject;

class Component
{

public:
	Component();
	virtual ~Component() {}

public:
	inline GameObject* GetOwner() const { return mOwner; }
	inline void		   SetOwner(GameObject* _obj) { mOwner = _obj; }

	inline Vec2	GetPos() const { return mPos; }
	inline void	SetPos(Vec2 _pos) { mPos = _pos; }
				
	inline Vec2	GetSize() const { return mSize; }
	inline void	SetSize(Vec2 _size) { mSize = _size; }
				
	inline Vec2	GetScale() const { return mScale; }
	inline void	SetScale(Vec2 _scale) { mScale = _scale; }
				
	inline Vec2	GetOffset() const { return mOffset; }
	inline void	SetOffset(Vec2 _offset)  {  mOffset = _offset; }

public:
	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	GameObject* mOwner;

private:
	Vec2 mPos;
	Vec2 mSize;
	Vec2 mScale;
	Vec2 mOffset;
};


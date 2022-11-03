#pragma once

class Collider;
class Animator;
class GameObject;

struct Components
{
	Collider* mCollider;
	Animator* mAnimator;
};

struct Relation
{
	GameObject* mOther;
	RELATION_TYPE mRelType;

	bool operator< (const Relation& _other) const 
	{
		return mRelType < _other.mRelType;
	}

};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

public:
	virtual void Initialize() = 0;
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline const Vec2& GetPos() const { return mPos; }
	inline void SetPos(const Vec2& _pos) { mPos = _pos; }

	inline const Vec2& GetSize() const { return mSize; }
	inline void SetSize(const Vec2& _size) { mSize = _size; }

	inline const Vec2& GetScale() const { return mScale; }
	inline void SetScale(const Vec2& _scale) { mScale = _scale; }

	inline OBJECT_TYPE GetType() const { return mType; }
	inline void SetType(OBJECT_TYPE _type) { mType = _type; }

	inline std::set<Relation>& GetRelations() { return mRelations; }
	inline void AddRelation(GameObject* _obj, RELATION_TYPE _relType) { mRelations.insert(Relation{ _obj, _relType }); }
	void SeverRelation(GameObject* _obj, RELATION_TYPE _relType) { mRelations.erase(Relation{ _obj, _relType }); }
	
	void CreateComponent(Collider* _collider);
	void CreateComponent(Animator* _animator);

	inline Collider* GetCollider() const { return mComponents.mCollider; }
	inline Animator* GetAnimator() const { return mComponents.mAnimator; }

public:
	virtual void OnCollision(Collider* _other) {};
	virtual void OnCollisionEnter(Collider* _other) {};
	virtual void OnCollisionExit(Collider* _other) {};

private:
	Vec2				mPos;
	Vec2				mSize;
	Vec2				mScale;
	Components			mComponents;
	OBJECT_TYPE			mType;

	std::set<Relation>  mRelations;
};
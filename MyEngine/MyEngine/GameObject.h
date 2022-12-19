#pragma once

class Collider;
class RigidBody;
class Animator;
class Animation;
class GameObject;

struct Components
{
	Collider* mCollider;
	Animator* mAnimator;
	RigidBody* mRigidBody;
};



class GameObject
{
public:
	struct Relation
	{
		GameObject* mOther;
		RELATION_TYPE mRelType;

		bool operator< (const Relation& _other) const
		{
			return mOther->GetPos() < _other.mOther->GetPos();
			//	return mRelType < _other.mRelType;
		}

	};

public:
	GameObject();
	virtual ~GameObject();

	GameObject(const GameObject& _other);
	GameObject(GameObject&& _other) = default;
	
public:
	GameObject& operator= (const GameObject& _other);


public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline const Vec2& GetPos() const { return mPos; }
	inline void		   SetPos(const Vec2& _pos) { mPos = _pos; }

	inline const Vec2& GetSize() const { return mSize; }
	inline void		   SetSize(const Vec2& _size) { mSize = _size; }

	inline const Vec2& GetScale() const { return mScale; }
	inline void		   SetScale(const Vec2& _scale) { mScale = _scale; }

	inline OBJECT_TYPE GetType() const { return mType; }
	inline void		   SetType(OBJECT_TYPE _type) { mType = _type; }

	inline bool		   GetGravity() const { return mGravity; }
	inline void		   SetGravity(bool _gravity) { mGravity = _gravity; }

	inline bool		   GetGround() const { return mGround; }
	inline void		   SetGround(bool _ground) { mGround = _ground; mGravity = !(_ground); }

	inline std::vector<Relation>& GetRelations() { return mRelations; }
	inline void AddRelation(GameObject* _obj, RELATION_TYPE _relType) { mRelations.push_back(Relation{ _obj, _relType }); }
	void SeverRelation(GameObject* _obj, RELATION_TYPE _relType);
	inline void ClearRelation() { mRelations.clear(); }
	
	void CreateComponent(Collider* _collider);
	void CreateComponent(Animator* _animator);
	void CreateComponent(RigidBody* _rigidBody);

	inline Collider*  GetCollider() const { return mComponents.mCollider; }
	inline Animator*  GetAnimator() const { return mComponents.mAnimator; }
	inline RigidBody* GetRigidBody() const { return mComponents.mRigidBody; }

	inline void           SetCollisionType(COLLISION_TYPE _type) { mCollisionType = _type; }
	inline COLLISION_TYPE GetCollisionType() const { return mCollisionType; }

	inline void SetDirectionVector(Vec2 _dirVec) { mDirectionVec = _dirVec; }
	inline Vec2 GetDirectionVector() const { return mDirectionVec; }

	inline bool IsDead() const { return mDead; }
	void SetDead(bool _flag);
	
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

	bool				mGravity;
	bool				mGround;
	bool			    mDead;

	Vec2				mDirectionVec;

private:
	COLLISION_TYPE		mCollisionType;

	std::vector<Relation>  mRelations;
};

#pragma once
#include "GameObject.h"
class Texture;
class InfRepeatBg :
    public GameObject
{
public:
	InfRepeatBg();
	~InfRepeatBg();

	InfRepeatBg(const InfRepeatBg& _other);

	InfRepeatBg* Clone() {
		InfRepeatBg* clone = new InfRepeatBg(*this);
		return clone;
	}

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetSpeed(float _speed) { mSpeed = _speed; }
	inline float GetSpeed() const { return mSpeed; }
	
	inline void		SetTexture(Texture* _tex) { mTexture = _tex; }
	inline Texture* GetTexture() const { return mTexture; }

private:
	Texture* mTexture;
	InfRepeatBg* mChild;
	float mSpeed;
};


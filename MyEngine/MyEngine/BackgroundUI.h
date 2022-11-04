#pragma once
#include "UI.h"
class Texture;
class BackgroundUI :
    public UI
{
public:
	BackgroundUI();
	~BackgroundUI();

	BackgroundUI(const BackgroundUI& _other);

	BackgroundUI* Clone() {
		BackgroundUI* clone = new BackgroundUI(*this);
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
	

private:
	BackgroundUI* mChild;
	float mSpeed;
};


#pragma once
#include "GameObject.h"

class Texture;
class UI
	: public GameObject
{
public:
	UI(bool _camMode);
	~UI();

	UI(const UI& _other);

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetTexture(Texture* _tex) { mTexture = _tex; }
	inline Texture* GetTexture() const { return mTexture; }


private:
	std::vector<UI*> mChildUI;
	Texture*		 mTexture;
	bool			 mCamMode;
};


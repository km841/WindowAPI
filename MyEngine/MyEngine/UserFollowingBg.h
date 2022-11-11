#pragma once
#include "GameObject.h"
class Texture;
class Player;
class UserFollowingBg :
	public GameObject
{
public:
	UserFollowingBg(bool _renderMode);
	~UserFollowingBg();

public:
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	virtual void Destroy();

public:
	inline void SetSpeed(float _speed) { mSpeed = _speed; }
	inline float GetSpeed() const { return mSpeed; }

	inline void SetPlayer(Player* _player) { mPlayer = _player; }
	inline Player* GetPlayer() const { return mPlayer; }

	inline void		SetTexture(Texture* _tex) { mTexture = _tex; }
	inline Texture* GetTexture() const { return mTexture; }

	inline void SetTimes(float _time) { mTimes = _time; }
	inline float GetTimes() const { return mTimes; }

	



private:
	Texture* mTexture;
	Player* mPlayer;
	float mSpeed;
	float mTimes;

	bool mRenderMode;
};
#pragma once
#include "yaGameObject.h"

namespace ya
{
	const int METEOR_MAX_COUNT = 100;

	class Meteor : public GameObject
	{
	public:
		Meteor();
		virtual ~Meteor();

		virtual void Tick()		     override;
		virtual void Render(HDC hdc) override;

	public:
		void SetSpeed(int speed) { mSpeed = speed; }



	private:
		float mSpeed;


	};



}



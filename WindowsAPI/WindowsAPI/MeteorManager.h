#pragma once
#include "Common.h"
#include "Meteor.h"
namespace ya
{
	class GameObject;
	class MeteorManager
	{
	public:
		static MeteorManager& GetInstance()
		{
			static MeteorManager instance;
			return instance;
		}

	public:
		void Initialize();
		void Tick();
		void Render(HDC hdc);
			
	private:
		MeteorManager() = default;
		~MeteorManager() = default;

		MeteorManager(const MeteorManager&) = delete;
		MeteorManager& operator=(const MeteorManager&) = delete;


	private:
		GameObject* mMeteors[METEOR_MAX_COUNT] = {};
		UINT bottom = 0;

	};

}


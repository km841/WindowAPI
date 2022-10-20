#pragma once
#include "yaScene.h"


namespace ya
{
	class LogoScene :
		public Scene
	{

	public:

		LogoScene();
		virtual ~LogoScene();
		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:

		
	};
}



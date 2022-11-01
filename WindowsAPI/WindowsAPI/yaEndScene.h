#pragma once
#include "yaScene.h"


namespace ya
{
	class EndScene :
		public Scene
	{

	public:

		EndScene();
		virtual ~EndScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:


	};
}



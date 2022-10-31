#pragma once
#include "yaScene.h"

namespace ya
{
	class TitleScene :
		public Scene
	{

	public:

		TitleScene();
		virtual ~TitleScene();
		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:


	};
}



#pragma once
#include "yaComponent.h"

namespace ya
{
	class Sound :
		public Component
	{
	public:
		Sound();
		virtual ~Sound();

	private:
		virtual void Tick();
		virtual void Render(HDC hdc);



	};
}



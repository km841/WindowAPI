#pragma once
#include "Common.h"

namespace ya
{
	// ���� ���α׷��� �� �༮
	class Application
	{
	public:

		static Application& GetInstance()
		{
			static Application mInstance;
			return mInstance;
		}

		Application();
		~Application();

		void Initialize(WindowData data);
		void Tick();


	private:
		WindowData mWindowData;
	};
}



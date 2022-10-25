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

		
		const WindowData& GetWindowData() const { return mWindowData; };
		void Initialize(WindowData data);
		void Tick();

		WindowData GetWindowData() { return mWindowData; }

	private:
		Application();
		~Application();

		void InitializeWindow(WindowData data);

	private:
		WindowData mWindowData;
	};
}



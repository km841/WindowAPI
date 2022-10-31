#pragma once
#include "Common.h"

namespace ya
{
	// 메인 프로그램이 될 녀석
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
		HPEN GetPen(ePenColor color) { return mPens[(UINT)color]; }
		HBRUSH GetBrush(eBrushColor color) { return mBrushes[(UINT)color]; }

	private:
		Application();
		~Application();

		void InitializeWindow(WindowData data);

	private:
		WindowData mWindowData;
		HPEN mPens[(UINT)ePenColor::End];
		HBRUSH mBrushes[(UINT)eBrushColor::End];
	};
}



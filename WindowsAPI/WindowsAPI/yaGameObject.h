#pragma once
#include "Common.h"
#include "yaEntity.h"

namespace ya
{
	class GameObject : public Entity
	{
	public:
		GameObject();
		virtual ~GameObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		// 캐릭터의 pos는 발밑 중앙을 기준으로 삼음
		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() const { return mPos; }

		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() const { return mScale; }

	/*	void SetHdc(HDC hdc) { mHdc = hdc; }
		HDC GetHdc() const  { return mHdc; }*/



	private:
		// 될수록 리소스 크기변경하지않고 그대로 쓰는게 가장 좋음
		Vector2 mPos;
		Vector2 mScale;
		//HDC mHdc;

	};
}



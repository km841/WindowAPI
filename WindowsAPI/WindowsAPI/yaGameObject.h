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

		// ĳ������ pos�� �߹� �߾��� �������� ����
		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() const { return mPos; }

		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() const { return mScale; }

	/*	void SetHdc(HDC hdc) { mHdc = hdc; }
		HDC GetHdc() const  { return mHdc; }*/



	private:
		// �ɼ��� ���ҽ� ũ�⺯�������ʰ� �״�� ���°� ���� ����
		Vector2 mPos;
		Vector2 mScale;
		//HDC mHdc;

	};
}



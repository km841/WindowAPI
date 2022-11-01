#pragma once
#include "yaComponent.h"

namespace ya
{
	class Collider
		: public Component
	{
	public:
		Collider();
		virtual ~Collider();

	public:
		void SetScale(Vector2 scale) { mScale = scale; }
		void SetPos(Vector2 pos) { mPos = pos; }
		void SetOffset(Vector2 offset) { mOffset = offset; }

		Vector2 GetScale() { return mScale; }
		Vector2 GetPos() { return mPos; }
		Vector2 GetOffset() { return mOffset; }
	public:
		virtual void Tick() override;
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* _other);
		virtual void OnCollisionStay(Collider* _other);
		virtual void OnCollisionExit(Collider* _other);


	private:
		Vector2 mOffset;
		Vector2 mPos;
		Vector2 mScale;

		UINT mCollisionCount;

	};
}



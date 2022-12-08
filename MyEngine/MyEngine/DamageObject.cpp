#include "pch.h"
#include "DamageObject.h"
#include "CameraMgr.h"
#include "Texture.h"

DamageObject::DamageObject()
{
	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = (BYTE)255.f;
}

DamageObject::~DamageObject()
{
}

void DamageObject::Initialize()
{

}

void DamageObject::Update()
{
	// ���İ� ���� ������ 135�� ������ �� ������ ��
	// 1-RATIO�� ���ؼ� ���� �������� ��������
	float ratio = mAngle / 135.f;
	mBlendFunc.SourceConstantAlpha = (BYTE)(ratio * 255.f);
}

void DamageObject::Render()
{
	Vec2 pos = RENDER_POS(GetPos());
	// �������� ����Ϸ��� Texture�� �־�� ��

	Vec2 size = mTex->GetSize();

	//Rectangle(BACK_BUF_DC,
	//	pos.x - 15,
	//	pos.y - 15,
	//	pos.x + 15,
	//	pos.y + 15);

	//BitBlt(
	//	BACK_BUF_DC,
	//	pos.x - 15,
	//	pos.y - 15,
	//	size.x,
	//	size.y,
	//	mTex->GetDC(),
	//	0, 0,
	//	SRCCOPY
	//);

	AlphaBlend(
		BACK_BUF_DC,
		(int)(pos.x - size.x / 2.f),
		(int)(pos.y - size.y / 2.f),
		(int)(size.x),
		(int)(size.y),
		mTex->GetDC(),
		0, 0,
		(int)size.x,
		(int)size.y,
		mBlendFunc
	);
}

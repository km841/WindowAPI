#include "pch.h"
#include "Particle.h"
#include "TimeMgr.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "CameraMgr.h"
#include "EventRegisteror.h"

Particle::Particle()
	:mCurDuration(0.f)
	,mMaxDuration(.5f)
{
	SetType(OBJECT_TYPE::PARTICLE);

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 127;

	Texture* size_1_particle = ResourceMgr::GetInstance().Load<Texture>(L"size_1_particle", L"Texture\\size_1_particle.bmp");
	Texture* size_3_particle = ResourceMgr::GetInstance().Load<Texture>(L"size_3_particle", L"Texture\\size_3_particle.bmp");
	Texture* size_5_particle = ResourceMgr::GetInstance().Load<Texture>(L"size_5_particle", L"Texture\\size_5_particle.bmp");
	Texture* size_7_particle = ResourceMgr::GetInstance().Load<Texture>(L"size_7_particle", L"Texture\\size_7_particle.bmp");

	mParticles.push_back(size_1_particle);
	mParticles.push_back(size_3_particle);
	mParticles.push_back(size_5_particle);
	mParticles.push_back(size_7_particle);

	int randomValue = rand() % mParticles.size();
	mCurTex = mParticles[randomValue];
}

Particle::~Particle()
{
}

void Particle::Initialize()
{

	GameObject::Initialize();
}

void Particle::Update()
{
	if (mCurDuration > mMaxDuration)
	{
		mCurDuration = mMaxDuration;
		//EventRegisteror::GetInstance().DeleteObject(this);
	}
	else
	{
		mCurDuration += DT;
		float ratio = mCurDuration / mMaxDuration;
		mBlendFunc.SourceConstantAlpha = (BYTE)((1.f - ratio) * 255.f);

		int randValue = 1 + (rand() % 100);

		Vec2 pos = GetPos();
		pos += mDir * (float)randValue * DT;
		SetPos(pos);
	}
}

void Particle::Render()
{
	if (mCurDuration < mMaxDuration)
	{
		// 그려주기
		
		Vec2 pos = RENDER_POS(GetPos());
		Vec2 size = mCurTex->GetSize();

		AlphaBlend(
			BACK_BUF_DC,
			(int)(pos.x - size.x / 2.f),
			(int)(pos.y - size.y / 2.f),
			(int)(size.x),
			(int)(size.y),
			mCurTex->GetDC(),
			0, 0,
			(int)size.x,
			(int)size.y,
			mBlendFunc
		);
	}

}

void Particle::Destroy()
{
	GameObject::Destroy();
}

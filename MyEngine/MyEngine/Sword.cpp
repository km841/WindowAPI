#include "pch.h"
#include "Sword.h"

Sword::Sword()
{

}

Sword::~Sword()
{
	if (mTransTexture)
		delete mTransTexture;

	mTransTexture = nullptr;
}

void Sword::Initialize()
{
	
}

void Sword::Update()
{
	// 마우스 위치에 따라 각도 변경

}

void Sword::Render()
{
	// 각도에 따라 렌더링
}

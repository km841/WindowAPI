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
	// ���콺 ��ġ�� ���� ���� ����

}

void Sword::Render()
{
	// ������ ���� ������
}

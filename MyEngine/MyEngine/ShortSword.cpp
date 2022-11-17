#include "pch.h"
#include "ShortSword.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "Player.h"
#include "TimeMgr.h"
#include "CameraMgr.h"

ShortSword::ShortSword()
{
	SetOffset(Vec2(40.f, -2.f));
	SetItemType(ITEM_TYPE::WEAPON_1);
	SetLeftDirOffset(8.f);
	SetRightDirOffset(51.f);
	SetYOffset(8.f);
}

ShortSword::~ShortSword()
{
}

void ShortSword::Initialize()
{
	Texture* texture = ResourceMgr::GetInstance().Load<Texture>(L"ShortSword", L"Texture\\ShortSword3.bmp");
	Texture* transTexture = ResourceMgr::GetInstance().CreateTexture(L"ShortSwordTrans", texture->GetSize());
	
	SetTexture(texture);
	SetTransTexture(transTexture);
	Sword::Initialize();

	Player* player = Player::GetPlayer();
	if (nullptr != player)
	{
		Vec2 playerPos = player->GetPos();
		SetPos(playerPos + GetOffset());
	}

	SetSize(texture->GetSize());
}

void ShortSword::Update()
{
	// �ִϸ��̼� ������Ʈ
	// X, Y��ǥ �˾ƾ� ��
	// Į ���� �������� �̵��� ����

	Sword::Update();
}

void ShortSword::Render()
{

	// �ִϸ��̼� ����
	Sword::Render();
}

#include "pch.h"
#include "Item.h"

Item::Item()
	: mItemType(ITEM_TYPE::END)
	, mItemInfo{}
	, mTexture(nullptr)
	, mIconTexture(nullptr)
	, mEquipedTex(nullptr)
{
}

Item::~Item()
{

}

void Item::Initialize()
{
}

void Item::Update()
{
}

void Item::Render()
{
}

void Item::Destroy()
{
}

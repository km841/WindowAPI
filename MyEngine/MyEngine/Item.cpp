#include "pch.h"
#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
	if (nullptr != mTexture)
		delete mTexture;

	if (nullptr != mIconTexture)
		delete mIconTexture;

	mTexture = nullptr;
	mIconTexture = nullptr;
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

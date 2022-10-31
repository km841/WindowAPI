#include "pch.h"
#include "TitleScene.h"
#include "Player.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "EventRegisteror.h"
#include "KeyMgr.h"

void TitleScene::Initialize()
{
	mBgTexture = ResourceMgr::GetInstance().Load<Texture>(L"TitleBackground", L"Texture\\Title.bmp");
	assert(mBgTexture != nullptr);

}

void TitleScene::Update()
{
	if (IS_JUST_PRESSED(KEY::ENTER))
	{
		EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::PLAY);
	}
	Scene::Update();
}

void TitleScene::Render()
{
	BitBlt(BACK_BUF_DC, 0, 0
		, mBgTexture->GetWidth()
		, mBgTexture->GetHeight()
		, mBgTexture->GetDC()
		, 0, 0, SRCCOPY);

	Scene::Render();
}

void TitleScene::Enter()
{

}

void TitleScene::Exit()
{

}

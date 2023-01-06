#include "pch.h"
#include "EndingScene.h"
#include "CameraMgr.h"
#include "ResourceMgr.h"
#include "Texture.h"

EndingScene::EndingScene()
	:mBackground(nullptr)
	, mCameraBegin(false)
{
	mBackground = LOAD_TEXTURE(L"EndingBG", L"Texture\\TownSky.bmp");

	mSceneType = SCENE_TYPE::ENDING;

	mBlendFunc = {};
	mBlendFunc.BlendFlags = 0;
	mBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mBlendFunc.BlendOp = AC_SRC_OVER;
	mBlendFunc.SourceConstantAlpha = 127;
}

EndingScene::~EndingScene()
{
}

void EndingScene::Initialize()
{
	Scene::Initialize();
}

void EndingScene::Update()
{
	Scene::Update();

	//if (false == mCameraBegin)
	//{
	//	mCameraBegin = true;

	//	Vec2 curLookPos = CameraMgr::GetInstance().GetLookPos();
	//	curLookPos.y += 500.f;
	//	CameraMgr::GetInstance().SetLookPos(curLookPos);
	//}
}

void EndingScene::Render()
{
	Background_Black();

	Scene::Render();
}

void EndingScene::Destroy()
{
	Scene::Destroy();
}

void EndingScene::Enter()
{

	// ��� �÷��̾ ����
	// �� �ٱ����� NPC���� �ɾ�´�
	// ��ǳ������ '�����մϴ�'
	// �������� �÷��̾ �����մϴ� �ϸ� ������
	
}

void EndingScene::Exit()
{
}

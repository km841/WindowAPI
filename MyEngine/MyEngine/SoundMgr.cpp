#include "pch.h"
#include "SoundMgr.h"
#include "ResourceMgr.h"
#include "Sound.h"

SoundMgr::SoundMgr()
	:mBGMSound(nullptr)
{
}

SoundMgr::~SoundMgr()
{
}

bool SoundMgr::Initialize()
{
	if (FAILED(DirectSoundCreate8(NULL, &mSoundDevice, NULL)))
	{
		MessageBox(NULL, L"�������̽���������", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	// ���� ����̽� �������� ����.
	HWND hWnd = APP_INSTANCE.GetHwnd();
	if (FAILED(mSoundDevice->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE))) // Flag�� ����
	{
		MessageBox(NULL, L"�������̽� �������� ����", L"SYSTEM ERROR", MB_OK);
		return false;
	}

	return true;
}

void SoundMgr::ChangeBGM(SCENE_TYPE _type)
{
	if (nullptr != mBGMSound)
	{
		mBGMSound->Stop(true);
	}

	switch (_type)
	{
	case SCENE_TYPE::TOWN:
		mBGMSound = ResourceMgr::GetInstance().Load<Sound>(L"TownThema", L"Sound\\TownBGM.wav");
		break;

	case SCENE_TYPE::DUNGEON:
		mBGMSound = ResourceMgr::GetInstance().Load<Sound>(L"DungeonThema", L"Sound\\PrisonBGM.wav");
		break;
	}

	mBGMSound->Play(true);
}

void SoundMgr::ChangeBGM(Sound* _sound)
{
	if (nullptr != mBGMSound)
	{
		mBGMSound->Stop(true);
	}

	mBGMSound = _sound;
	mBGMSound->Play(true);
}

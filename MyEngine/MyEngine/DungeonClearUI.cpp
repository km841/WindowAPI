#include "pch.h"
#include "DungeonClearUI.h"
#include "Texture.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Sound.h"
#include "SoundMgr.h"
#include "FontMgr.h"
#include "ButtonUI.h"
#include "EventRegisteror.h"


DungeonClearUI::DungeonClearUI()
	: UI(false)
	, mTex(nullptr)
	, mSuccessTex(nullptr)
	, mBaseTex(nullptr)
	, mClearLogBegin(false)
	, mSuccessUIBegin(false)
	, mSuccessUIShowComplete(false)
	, mSuccessUIStayComplete(false)
	, mSuccessUIMoveComplete(false)
	, mDistance(0.f)
	, mSpeed(0.f)
	, mSuccessUIShowMaxTime(2.f)
	, mSuccessUIShowCurTime(0.f)
	, mSuccessUIMoveMaxTime(1.f)
	, mSuccessUIMoveCurTime(0.f)
	, mClearLogShowMaxTime(1.f)
	, mClearLogShowCurTime(0.f)
	, mSuccessUIStayMaxTime(3.f)
	, mSuccessUIStayCurTime(0.f)
	, mClearUIComplete(false)
	, mSound(nullptr)
	, mMoneyTex(nullptr)
	, mKillTex(nullptr)
	, mTimeTex(nullptr)
	, mPlaceTex(nullptr)
	, mBossNameTex(nullptr)
{
	SetType(OBJECT_TYPE::UNIQUE_UI);
	SetUIType(UI_TYPE::DUNGEON_CLEAR);

	mSound = LOAD_SOUND(L"DungeonClearSound", L"Sound\\DungeonClear.wav");

	mSuccessUIBlendFunc = {};
	mSuccessUIBlendFunc.BlendFlags = 0;
	mSuccessUIBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mSuccessUIBlendFunc.BlendOp = AC_SRC_OVER;
	mSuccessUIBlendFunc.SourceConstantAlpha = 0;

	mLogUIBlendFunc = {};
	mLogUIBlendFunc.BlendFlags = 0;
	mLogUIBlendFunc.AlphaFormat = AC_SRC_ALPHA;
	mLogUIBlendFunc.BlendOp = AC_SRC_OVER;
	mLogUIBlendFunc.SourceConstantAlpha = 0;

	mBaseBlendFunc = {};
	mBaseBlendFunc.BlendFlags = 0;
	mBaseBlendFunc.AlphaFormat = 0;
	mBaseBlendFunc.BlendOp = AC_SRC_OVER;
	mBaseBlendFunc.SourceConstantAlpha = 200;

	mTex = LOAD_TEXTURE(L"DungeonClearTex", L"Texture\\DungeonClear_UI.bmp");
	mSuccessTex = LOAD_TEXTURE(L"DungeonSuccessTex", L"Texture\\DungeonSuccessTex.bmp");
	mBaseTex = ResourceMgr::GetInstance().CreateTexture(L"DungeonClearBase", Vec2(WINDOW_WIDTH_SIZE, WINDOW_HEIGHT_SIZE));

	mSuccessUIPos = Vec2(0.f, WINDOW_HEIGHT_SIZE / 2.f - mSuccessTex->GetHeight() / 2.f);
	mSpeed = mSuccessUIPos.y / mSuccessUIMoveMaxTime;

	Texture* exitButtonTex = LOAD_TEXTURE(L"ExitButtonTex", L"Texture\\ExitButtonTex.bmp");

	ButtonUI* exitButton = new ButtonUI;
	exitButton->SetPos(Vec2(1147, 712));
	exitButton->SetTexture(exitButtonTex);
	exitButton->SetSize(Vec2(exitButtonTex->GetWidth() / 2, exitButtonTex->GetHeight()));
	exitButton->TextureProcessing(Vec2(0, 0)
		, Vec2(exitButtonTex->GetWidth() / 2, 0)
		, Vec2(exitButtonTex->GetWidth() / 2, exitButtonTex->GetHeight()));

	// Ending Scene
	exitButton->SetEvent([]() {EventRegisteror::GetInstance().ChangeScene(SCENE_TYPE::TITLE); });

	AddChild(exitButton);
}

DungeonClearUI::~DungeonClearUI()
{
}

void DungeonClearUI::Initialize()
{
}

void DungeonClearUI::Update()
{
	if (GetState())
	{
		if (false == mSuccessUIBegin &&
			false == mSuccessUIShowComplete)
		{
			mSuccessUIBegin = true;
			SoundMgr::GetInstance().StopBGM();
			if (nullptr != mSound)
			{
				mSound->Play(false);
			}

		}

		else
		{
			if (mSuccessUIShowMaxTime < mSuccessUIShowCurTime)
			{
				mSuccessUIShowComplete = true;
				mSuccessUIBlendFunc.SourceConstantAlpha = (BYTE)255.f;
			}

			else
			{
				float ratio = mSuccessUIShowCurTime / mSuccessUIShowMaxTime;
				mSuccessUIBlendFunc.SourceConstantAlpha = (BYTE)(255.f * ratio);
				mSuccessUIShowCurTime += DT;
				// 알파값 조절
			}
		}

		if (false == mSuccessUIStayComplete &&
			true == mSuccessUIShowComplete)
		{
			if (mSuccessUIStayMaxTime < mSuccessUIStayCurTime)
			{
				mSuccessUIStayComplete = true;
			}

			else
			{
				mSuccessUIStayCurTime += DT;
				// ui 움직이기
			}
		}


		if (false == mSuccessUIMoveComplete &&
			true == mSuccessUIStayComplete)
		{
			if (mSuccessUIMoveMaxTime < mSuccessUIMoveCurTime)
			{
				mSuccessUIMoveComplete = true;
			}

			else
			{
				mSuccessUIMoveCurTime += DT;
				mSuccessUIPos.y -= mSpeed * DT;
				// ui 움직이기
			}
		}

		if (false == mClearUIComplete &&
			true == mSuccessUIMoveComplete)
		{
			if (false == mClearLogBegin)
			{
				mClearLogBegin = true;
			}

			else
			{
				if (mClearLogShowMaxTime < mClearLogShowCurTime)
				{
					mClearLogShowCurTime = mClearLogShowMaxTime;
					mClearUIComplete = true;
				}
				else
				{
					float ratio = mClearLogShowCurTime / mClearLogShowMaxTime;
					mLogUIBlendFunc.SourceConstantAlpha = (BYTE)(255.f * ratio);
					mClearLogShowCurTime += DT;
					// 알파값 조절
				}
			}
		}

		UI::Update();
	}
	



}

void DungeonClearUI::Render()
{
	if (GetState())
	{
		if (nullptr != mBaseTex && nullptr != mTex)
		{
			Vec2 baseSize = mBaseTex->GetSize();
			Vec2 texSize = mTex->GetSize();
			Vec2 successSize = mSuccessTex->GetSize();

			AlphaBlend(
				BACK_BUF_DC,
				0, 0,
				(int)baseSize.x,
				(int)baseSize.y,
				mBaseTex->GetDC(),
				0, 0,
				(int)baseSize.x,
				(int)baseSize.y,
				mBaseBlendFunc
			);

			if (mClearLogBegin)
			{
				AlphaBlend(
					BACK_BUF_DC,
					0, 0,
					(int)texSize.x,
					(int)texSize.y,
					mTex->GetDC(),
					0, 0,
					(int)texSize.x,
					(int)texSize.y,
					mLogUIBlendFunc
				);

				if (nullptr != mTimeTex)
				{
					Vec2 timeOrgTexSize = mTimeTex->GetSize();
					Vec2 timeTexSize = timeOrgTexSize * 1.5f;
					
					AlphaBlend(
						BACK_BUF_DC,
						410, 160,
						(int)timeTexSize.x,
						(int)timeTexSize.y,
						mTimeTex->GetDC(),
						0, 0,
						(int)timeOrgTexSize.x,
						(int)timeOrgTexSize.y,
						mLogUIBlendFunc
					);

				}


				if (nullptr != mPlaceTex)
				{
					Vec2 placeOrgTexSize = mPlaceTex->GetSize();
					Vec2 placeTexSize = placeOrgTexSize * 1.5f;

					AlphaBlend(
						BACK_BUF_DC,
						330, 232,
						(int)placeTexSize.x,
						(int)placeTexSize.y,
						mPlaceTex->GetDC(),
						0, 0,
						(int)placeOrgTexSize.x,
						(int)placeOrgTexSize.y,
						mLogUIBlendFunc
					);
				}

				if (nullptr != mMoneyTex)
				{
					Vec2 moneyOrgTexSize = mMoneyTex->GetSize();
					Vec2 moneyTexSize = moneyOrgTexSize * 1.5f;

					int diff = (int)moneyTexSize.x - 57;

					AlphaBlend(
						BACK_BUF_DC,
						572 - diff, 313,
						(int)moneyTexSize.x,
						(int)moneyTexSize.y,
						mMoneyTex->GetDC(),
						0, 0,
						(int)moneyOrgTexSize.x,
						(int)moneyOrgTexSize.y,
						mLogUIBlendFunc
					);
				}

				// 시간
				// 위치
				// 돈
				// 아이템
				// 활동

				if (nullptr != mKillTex)
				{
					Vec2 killOrgTexSize = mKillTex->GetSize();
					Vec2 killTexSize = killOrgTexSize * 1.5f;

					AlphaBlend(
						BACK_BUF_DC,
						672, 242,
						(int)killTexSize.x,
						(int)killTexSize.y,
						mKillTex->GetDC(),
						0, 0,
						(int)killOrgTexSize.x,
						(int)killOrgTexSize.y,
						mLogUIBlendFunc
					);
				}

				if (nullptr != mBossNameTex)
				{
					Vec2 bossNameOrgTexSize = mBossNameTex->GetSize();
					Vec2 bossNameTexSize = bossNameOrgTexSize * 1.5f;

					AlphaBlend(
						BACK_BUF_DC,
						672, 292,
						(int)bossNameTexSize.x,
						(int)bossNameTexSize.y,
						mBossNameTex->GetDC(),
						0, 0,
						(int)bossNameOrgTexSize.x,
						(int)bossNameOrgTexSize.y,
						mLogUIBlendFunc
					);
				}

				if (mClearUIComplete)
				{
					UI::Render();
				}

			}

			if (mSuccessUIBegin)
			{
				AlphaBlend(
					BACK_BUF_DC,
					(int)mSuccessUIPos.x,
					(int)mSuccessUIPos.y,
					(int)successSize.x,
					(int)successSize.y,
					mSuccessTex->GetDC(),
					0, 0,
					(int)successSize.x,
					(int)successSize.y,
					mSuccessUIBlendFunc
				);
			}
		}


		
	}
}

bool DungeonClearUI::OnMouse()
{
	const std::vector<UI*>& buttonUI = GetChildUI();
	for (int i = 0; i < buttonUI.size(); ++i)
	{
		if (buttonUI[i]->OnMouse())
			buttonUI[i]->SetOnMouseState(true);
		else
			buttonUI[i]->SetOnMouseState(false);
	}

	return false;
}

bool DungeonClearUI::OnClicked()
{
	const std::vector<UI*>& buttonUI = GetChildUI();
	for (int i = 0; i < buttonUI.size(); ++i)
	{
		if (buttonUI[i]->OnClicked())
			buttonUI[i]->SetOnClickedState(true);
		else
			buttonUI[i]->SetOnClickedState(false);
	}

	return false;
}

void DungeonClearUI::SetupTexture(UINT _time, UINT _killCount, int _money)
{
	
	std::wstring szMoney = std::to_wstring(_money) + L" G";
	std::wstring szKillCount = L"-몬스터 " + std::to_wstring(_killCount) + L"마리 처치";

	int hour = _time / 3600;
	int min = _time % 3600 / 60;
	int sec = _time % 3600 % 60;

	std::wstring szHour = std::to_wstring(hour) + L"h ";
	std::wstring szMin = std::to_wstring(min) + L"m ";
	std::wstring szSec = std::to_wstring(sec) + L"s";

	szHour.insert(szHour.begin(), L'0');
	if (10 > min)
	{
		szMin.insert(szMin.begin(), L'0');
	}

	if (10 > sec)
	{
		szSec.insert(szSec.begin(), L'0');
	}

	std::wstring szTime = szHour + szMin + szSec;

	mMoneyTex = FontMgr::GetInstance().GetTextTexture(szMoney, szMoney);
	mKillTex = FontMgr::GetInstance().GetTextTexture(szKillCount, szKillCount);
	mTimeTex = FontMgr::GetInstance().GetTextTexture(szTime, szTime);
	mPlaceTex = FontMgr::GetInstance().GetTextTexture(L"2층 : 벨리알의 관문", L"2층 : 벨리알의 관문");
	mBossNameTex = FontMgr::GetInstance().GetTextTexture(L"-벨리알 처치", L"-벨리알 처치");
}

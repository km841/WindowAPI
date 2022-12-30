#pragma once
#define _CRT_SECURE_NO_WARNINGS
/*STL*/
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <algorithm>
#include <bitset>
#include <list>
#include <map>
#include <set>
#include <functional>
#include <fstream>

/*C STYLE HEADER*/
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <assert.h>
#include <time.h>
#include <direct.h>

/*USER DEFINE LIBRARY*/
#include "MathLib.h"
#include "EnumDefine.h"
#include "UtilLib.h"
#include "Application.h"

/*TransparentBlt ฐüทร*/
#pragma comment(lib, "Msimg32.lib")

/*MANAGER MACRO*/
#define APP_INSTANCE Application::GetInstance()
#define TOOL_INSTANCE ToolWindows::GetInstance()

#define MAIN_DC APP_INSTANCE.GetMainDC()
#define BACK_BUF_DC APP_INSTANCE.GetBackBufDC()

#define TOOL_MAIN_DC TOOL_INSTANCE.GetMainDC()
#define TOOL_BACK_BUF_DC TOOL_INSTANCE.GetBackBufDC()

#define DT TimeMgr::GetInstance().GetDT()
#define RENDER_POS(POS) CameraMgr::GetInstance().GetRenderPos(POS)
#define WORLD_POS(POS) CameraMgr::GetInstance().GetWorldPos(POS)
#define MOUSE_POS MouseMgr::GetInstance().GetMousePos()
#define GET_INVENTORY_UI static_cast<InventoryUI*>(UIMgr::GetInstance().GetUI(UI_TYPE::INVENTORY))
#define GET_HP_HUD static_cast<HPHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::HP))
#define GET_DASH_HUD static_cast<DashCountHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::DASH_GAUGE))
#define GET_NPCLINE_HUD static_cast<NPCLineHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::NPC_LINE))
#define GET_EQUIPED_HUD static_cast<EquipedHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::EQUIPED))
#define GET_ITEMGET_HUD static_cast<ItemGetHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::ITEM_GET))
#define GET_ITEMINFO_HUD static_cast<ItemInfoHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::ITEM_INFO))
#define GET_MINIMAP_HUD static_cast<MinimapHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::MINIMAP))
#define GET_BOSSHP_HUD static_cast<BossHPHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::BOSS_HP))
#define GET_BOSS_APPEAR_HUD static_cast<BossAppearHUD*>(UIMgr::GetInstance().GetHUD(HUD_TYPE::BOSS_APPEAR))
#define ZERO_VECTOR Math::ZeroVector()
#define IS_PLAYER Player::GetPlayer()->GetCurCharacter() == PLAYER_CHARACTER::PLAYER
#define IS_LASLEY Player::GetPlayer()->GetCurCharacter() == PLAYER_CHARACTER::LASLEY
#define BOTTOM_LIMIT CameraMgr::GetInstance().GetBottomLimit()
#define RGB_WHITE RGB(255, 255, 255)
#define RGB_MAGENTA RGB(255, 0, 255)
#define RGB_GRAY RGB(147, 144, 158)
#define RGB_PHONE_MAGENTA RGB(255, 0, 254)
#define RGB_BLUE RGB(0, 0, 255)
#define RGB_YELLOW RGB(223, 233, 85)
#define RGB_BLACK RGB(0, 0, 0)
#define RGB_RED RGB(255, 0, 0)



/*KEY CHECK MACRO*/
#define IS_JUST_PRESSED(THIS_KEY) KeyMgr::GetInstance().GetKeyState(THIS_KEY) == KEY_STATE::JUST_PRESSED
#define IS_PRESSED(THIS_KEY) KeyMgr::GetInstance().GetKeyState(THIS_KEY) == KEY_STATE::PRESSED
#define IS_JUST_RELEASED(THIS_KEY) KeyMgr::GetInstance().GetKeyState(THIS_KEY) == KEY_STATE::JUST_RELEASED
#define IS_RELEASED(THIS_KEY) KeyMgr::GetInstance().GetKeyState(THIS_KEY) == KEY_STATE::RELEASED

/*MOUSE CHECK MACRO*/
#define IS_JUST_LBUTTON_CLICKED MouseMgr::GetInstance().GetMouseState() == MOUSE_STATE::JUST_LBTN_CLICKED
#define IS_LBUTTON_CLICKED MouseMgr::GetInstance().GetMouseState() == MOUSE_STATE::LBTN_CLICKED
#define IS_JUST_RBUTTON_CLICKED MouseMgr::GetInstance().GetMouseState() == MOUSE_STATE::JUST_RBTN_CLICKED
#define IS_RBUTTON_CLICKED MouseMgr::GetInstance().GetMouseState() == MOUSE_STATE::RBTN_CLICKED

constexpr auto EPSILON = 0.00001;

/*WINDOW DEFAULT SIZE*/
constexpr auto WINDOW_WIDTH_SIZE = 1280;
constexpr auto WINDOW_HEIGHT_SIZE = 768;
constexpr auto ASSISTANT_LINE_X = 100000;
constexpr auto ASSISTANT_LINE_Y = 100000;

constexpr auto FILENAME_MAX_SIZE = 512;
constexpr auto IMAGE_TILE_SIZE_X = 16;
constexpr auto IMAGE_TILE_SIZE_Y = 16;
constexpr auto TILE_SIZE = 48;
constexpr auto TIMES = 3.f;
constexpr auto AFTER_IMAGE_TOTAL = 4;
constexpr auto COMMENT_MAX_SIZE = 256;
constexpr auto TILE_OFFSET = TILE_SIZE / 2.f;

constexpr auto GROUND_STANDARD = TILE_SIZE * 24;

constexpr auto HIT_MAX = 6;

constexpr auto INDEX_OFFSET = 3;



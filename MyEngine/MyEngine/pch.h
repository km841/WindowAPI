#pragma once

/*STL*/
#include <iostream>
#include <vector>
#include <string>
#include <type_traits>
#include <algorithm>
#include <bitset>
#include <map>
#include <set>

/*C STYLE HEADER*/
#include <windows.h>
#include <tchar.h>
#include <assert.h>

/*USER DEFINE LIBRARY*/
#include "MathLib.h"
#include "EnumDefine.h"
#include "UtilLib.h"
#include "Application.h"

/*TransparentBlt ฐüทร*/
#pragma comment(lib, "Msimg32.lib")

/*MANAGER MACRO*/
#define APP_INSTANCE Application::GetInstance()
#define MAIN_DC APP_INSTANCE.GetMainDC()
#define BACK_BUF_DC APP_INSTANCE.GetBackBufDC()

#define DT TimeMgr::GetInstance().GetDT()
#define RENDER_POS(POS) CameraMgr::GetInstance().GetRenderPos(POS);
#define WORLD_POS(POS) CameraMgr::GetInstance().GetWorldPos(POS);

/*KEY CHECK MACRO*/
#define IS_JUST_PRESSED(THIS_KEY) KeyMgr::GetInstance().GetKeyState(THIS_KEY) == KEY_STATE::JUST_PRESSED
#define IS_PRESSED(THIS_KEY) KeyMgr::GetInstance().GetKeyState(THIS_KEY) == KEY_STATE::PRESSED
#define IS_JUST_RELEASED(THIS_KEY) KeyMgr::GetInstance().GetKeyState(THIS_KEY) == KEY_STATE::JUST_RELEASED
#define IS_RELEASED(THIS_KEY) KeyMgr::GetInstance().GetKeyState(THIS_KEY) == KEY_STATE::RELEASED

/*WINDOW DEFAULT SIZE*/
#define WINDOW_WIDTH_SIZE 1600
#define WINDOW_HEIGHT_SIZE 900


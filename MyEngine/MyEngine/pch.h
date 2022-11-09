#pragma once

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

/*C STYLE HEADER*/
#include <windows.h>
#include <tchar.h>
#include <assert.h>

/*USER DEFINE LIBRARY*/
#include "MathLib.h"
#include "EnumDefine.h"
#include "UtilLib.h"
#include "Application.h"

/*TransparentBlt ����*/
#pragma comment(lib, "Msimg32.lib")

/*MANAGER MACRO*/
#define APP_INSTANCE Application::GetInstance()
#define MAIN_DC APP_INSTANCE.GetMainDC()
#define BACK_BUF_DC APP_INSTANCE.GetBackBufDC()

#define DT TimeMgr::GetInstance().GetDT()
#define RENDER_POS(POS) CameraMgr::GetInstance().GetRenderPos(POS)
#define WORLD_POS(POS) CameraMgr::GetInstance().GetWorldPos(POS)
#define MOUSE_POS MouseMgr::GetInstance().GetMousePos()


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

#define EPSILON 0.00001

/*WINDOW DEFAULT SIZE*/
#define WINDOW_WIDTH_SIZE 1280 
#define WINDOW_HEIGHT_SIZE 768
#define ASSISTANT_LINE_X 100000
#define ASSISTANT_LINE_Y 100000

#define FILENAME_MAX_SIZE 512
#define IMAGE_TILE_SIZE 80
#define TILE_SIZE 48
#define HEIGHT_CORRECT 28
#define WIDTH_CORRECT 18



#include "pch.h"
#include "MyEngine.h"
#include "Player.h"
#include "InventoryUI.h"
#include "UIMgr.h"
#include "SceneMgr.h"
#include "ToolScene.h"
#include "EquipedHUD.h"

#define MAX_LOADSTRING 100

HINSTANCE hInst;                             
WCHAR szTitle[MAX_LOADSTRING];               
WCHAR szWindowClass[MAX_LOADSTRING];         

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(4700);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MYENGINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYENGINE));

    MSG msg;

    while (true)
    {
        if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        else
        {
            APP_INSTANCE.Tick();
        }
    }

    APP_INSTANCE.Destroy();
    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYENGINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   LONG style = WS_OVERLAPPEDWINDOW;
   style &= ~WS_THICKFRAME;
   style &= ~WS_MAXIMIZEBOX;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, style,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   WindowData winData = {};
   winData.hWnd = hWnd;
   winData.hInst = hInstance;
   winData.iWidth = WINDOW_WIDTH_SIZE;
   winData.iHeight = WINDOW_HEIGHT_SIZE;

   

   APP_INSTANCE.Initialize(winData);

   return TRUE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            int a = 0;

            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;

            case (int)ID::WALL:
            {
                CheckMenuRadioItem(APP_INSTANCE.GetColMenuHandle(), 0, 2, 0, MF_BYPOSITION);
                static_cast<ToolScene*>(SceneMgr::GetInstance().GetCurScene())->SetTileType(TILE_TYPE::WALL);
            }
                break;

            case (int)ID::FOOTHOLD:
            {
                CheckMenuRadioItem(APP_INSTANCE.GetColMenuHandle(), 0, 2, 1, MF_BYPOSITION);
                static_cast<ToolScene*>(SceneMgr::GetInstance().GetCurScene())->SetTileType(TILE_TYPE::FOOTHOLD);
            }
                break;

            case (int)ID::EMPTY:
            {
                CheckMenuRadioItem(APP_INSTANCE.GetColMenuHandle(), 0, 2, 2, MF_BYPOSITION);
                static_cast<ToolScene*>(SceneMgr::GetInstance().GetCurScene())->SetTileType(TILE_TYPE::NONE);
            }
                break;

            case (int)ID::BACKGROUND:
            {
                CheckMenuRadioItem(APP_INSTANCE.GetTypeMenuHandle(), 0, 1, 0, MF_BYPOSITION);
                static_cast<ToolScene*>(SceneMgr::GetInstance().GetCurScene())->SetObjectType(OBJECT_TYPE::TILE_BG);
            }
                break;

            case (int)ID::SURFACE:
            {
                CheckMenuRadioItem(APP_INSTANCE.GetTypeMenuHandle(), 0, 1, 1, MF_BYPOSITION);
                static_cast<ToolScene*>(SceneMgr::GetInstance().GetCurScene())->SetObjectType(OBJECT_TYPE::TILE);
            }
                break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_MOUSEWHEEL:
    {
        Player* player = Player::GetPlayer();
        if (nullptr != player)
        {
            InventoryUI* inventory = 
                static_cast<InventoryUI*>(UIMgr::GetInstance().GetUI(UI_TYPE::INVENTORY));
            
            EquipedHUD* equipedHUD = GET_EQUIPED_HUD;

            switch (equipedHUD->GetChangingState())
            {
            case EQUIPED_CHANGING_STATE::NONE:
                equipedHUD->SetChangingState(EQUIPED_CHANGING_STATE::CHANGING);
                break;

            case EQUIPED_CHANGING_STATE::COMPLETE:
                
                equipedHUD->SetChangingState(EQUIPED_CHANGING_STATE::NONE);
                equipedHUD->ChangeDirSign();
                break;
        
            }
        }
    }
    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

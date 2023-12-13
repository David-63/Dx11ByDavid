#include "pch.h"
#include "Client.h"

#include <Engine/CDevice.h>
#include "CEditorMgr.h"
#include "ImGuiMgr.h"

#include "TestLevel.h"


HINSTANCE           g_hInst;
HWND                g_hWnd;
std::wstring        g_windowClass;
std::wstring        g_windowTitle;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// 메모리 릭 체크
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc();


    // 초기화
    MyRegisterClass(hInstance);
    InitInstance(hInstance, nCmdShow);
    CEngine::GetInst()->init(g_hWnd, 1280, 768);
	CEditorMgr::GetInst()->init();
	ImGuiMgr::GetInst()->init(g_hWnd);

	// 레벨 생성
	CreateTestLevel();



    MSG msg;
    ZeroMemory(&msg, sizeof(MSG)); // Initialize the message structure.
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            CEngine::GetInst()->progress();
            CEditorMgr::GetInst()->progress();

            ImGuiMgr::GetInst()->progress();
            CDevice::GetInst()->Present();
        }
    }    

	return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    g_windowClass = L"DavidClass";
    g_windowTitle = L"David's game project";

    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;// MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName = g_windowClass.c_str();
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    g_hInst = hInstance;    
    g_hWnd = CreateWindowW(g_windowClass.c_str(), g_windowTitle.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!g_hWnd)
    {
        MessageBox(nullptr, L"hwnd 생성 실패", L"에러", MB_OK);
        return FALSE;
    }

    //m_hWnd = CreateWindowW(
    //	_windowClass.c_str()				// 클래스
    //	, _windowTitle.c_str()				// 타이틀
    //	, WS_OVERLAPPEDWINDOW				// 스타일
    //	, windRect.left						// x위치
    //	, windRect.top						// y위치
    //	, windRect.right - windRect.left	// 너비
    //	, windRect.bottom - windRect.top	// 높이
    //	, nullptr							// 부모 윈도우
    //	, nullptr							// 메뉴 핸들
    //	, _hInstance						// 인스턴스 핸들
    //	, nullptr);							// 추가 파라미터

    ShowWindow(g_hWnd, SW_SHOW);

    return TRUE;
}


extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_DPICHANGED:
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_DpiEnableScaleViewports)
        {
            //const int dpi = HIWORD(wParam);
            //printf("WM_DPICHANGED to %d (%.0f%%)\n", dpi, (float)dpi / 96.0f * 100.0f);
            const RECT* suggested_rect = (RECT*)lParam;
            SetWindowPos(hWnd, NULL, suggested_rect->left, suggested_rect->top, suggested_rect->right - suggested_rect->left, suggested_rect->bottom - suggested_rect->top, SWP_NOZORDER | SWP_NOACTIVATE);
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
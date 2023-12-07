#include "pch.h"
#include "CRenderWindow.h"
#include "CWindowContainer.h"

bool CRenderWindow::Initialize(CWindowContainer* _pWindowContainer, HINSTANCE _hInstance, std::wstring _windowTitle, std::wstring _windowClass, UINT _width, UINT _height)
{
	m_hWndInst = _hInstance;
	m_width = _width;
	m_height = _height;
	m_winTitle = _windowTitle;
	m_winClass = _windowClass;

	RegisterWindowClass();

	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - m_width / 2;
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - m_height / 2;


	RECT windowRectangle;
	windowRectangle.left = centerScreenX;
	windowRectangle.top = centerScreenY;
	windowRectangle.right = windowRectangle.left + m_width;
	windowRectangle.bottom = windowRectangle.top + m_height;

	AdjustWindowRect(&windowRectangle, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	m_hWnd =
		CreateWindowEx(0, //Extended Windows style - we are using the default. For other options, see: https://msdn.microsoft.com/en-us/library/windows/desktop/ff700543(v=vs.85).aspx
			m_winClass.c_str(), //Window class name
			m_winTitle.c_str(), //Window Title
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, //Windows style - See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx
			windowRectangle.left, //Window X Position
			windowRectangle.top, //Window Y Position
			windowRectangle.right - windowRectangle.left, //Window Width
			windowRectangle.bottom - windowRectangle.top, //Window Height
			NULL, //Handle to parent of this window. Since this is the first window, it has no parent window.
			NULL, //Handle to menu or child window identifier. Can be set to NULL and use menu in WindowClassEx if a menu is desired to be used.
			m_hWndInst, //Handle to the instance of module to be used with this window
			_pWindowContainer); //Param to create window

	if (NULL == m_hWnd)
	{
		MessageBox(nullptr, L"CreateWindowEX Failed for window", L"에러", MB_OK);
		return false;
	}

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hWnd, SW_SHOW);
	SetForegroundWindow(m_hWnd);
	SetFocus(m_hWnd);

	return true;
}

bool CRenderWindow::ProcessMessages()
{
	// Handle the windows messages.
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // Initialize the message structure.

	while (PeekMessage(&msg, //Where to store message (if one exists) See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
		m_hWnd, //Handle to window we are checking messages for
		0,    //Minimum Filter Msg Value - We are not filtering for specific messages, but the min/max could be used to filter only mouse messages for example.
		0,    //Maximum Filter Msg Value
		PM_REMOVE))//Remove message after capturing it via PeekMessage. For more argument options, see: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
	{
		TranslateMessage(&msg); //Translate message from virtual key messages into character messages so we can dispatch the message. See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644955(v=vs.85).aspx
		DispatchMessage(&msg); //Dispatch message to our Window Proc for this window. See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644934(v=vs.85).aspx
	}

	// Check if the window was closed
	if (msg.message == WM_NULL)
	{
		if (!IsWindow(m_hWnd))
		{
			m_hWnd = NULL; //Message processing loop takes care of destroying this window
			UnregisterClass(m_winClass.c_str(), m_hWndInst);
			return false;
		}
	}

	return true;
}

HWND CRenderWindow::GetHWND() const
{
	return m_hWnd;
}

CRenderWindow::~CRenderWindow()
{
	if (NULL != m_hWnd)
	{
		UnregisterClass(m_winClass.c_str(), m_hWndInst);
		DestroyWindow(m_hWnd);
	}
}
LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		// All other messages
	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;
	default:
	{
		// retrieve ptr to window class
		CWindowContainer* const pWindow = reinterpret_cast<CWindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		CWindowContainer* pWindow = reinterpret_cast<CWindowContainer*>(pCreate->lpCreateParams);
		if (nullptr == pWindow) //Sanity check
		{
			MessageBox(nullptr, L"Critical Error: Pointer to window container is null during WM_NCCREATE.", L"에러", MB_OK);
			exit(-1);
		}
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
		return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
void CRenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc; //Our Window Class (This has to be filled before our window can be created) See: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; //Flags [Redraw on m_width/m_height change from resize/movement] See: https://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
	wc.lpfnWndProc = HandleMessageSetup; //Pointer to Window Proc function for handling messages from this window
	wc.cbClsExtra = 0; //# of extra bytes to allocate following the window-class structure. We are not currently using this.
	wc.cbWndExtra = 0; //# of extra bytes to allocate following the window instance. We are not currently using this.
	wc.hInstance = m_hWndInst; //Handle to the instance that contains the Window Procedure
	wc.hIcon = NULL;   //Handle to the class icon. Must be a m_hWnd to an icon resource. We are not currently assigning an icon, so this is null.
	wc.hIconSm = NULL; //Handle to small icon for this class. We are not currently assigning an icon, so this is null.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Default Cursor - If we leave this null, we have to explicitly set the cursor's shape each time it enters the window.
	wc.hbrBackground = NULL; //Handle to the class background brush for the window's background color - we will leave this blank for now and later set this to black. For stock brushes, see: https://msdn.microsoft.com/en-us/library/windows/desktop/dd144925(v=vs.85).aspx
	wc.lpszMenuName = NULL; //Pointer to a null terminated character string for the menu. We are not using a menu yet, so this will be NULL.
	wc.lpszClassName = m_winClass.c_str(); //Pointer to null terminated string of our class name for this window.
	wc.cbSize = sizeof(WNDCLASSEX); //Need to fill in the size of our struct for cbSize
	RegisterClassEx(&wc); // Register the class so that it is usable.
}

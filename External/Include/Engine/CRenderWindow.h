#pragma once

class CWindowContainer;

class CRenderWindow
{
public:
	bool Initialize(CWindowContainer* _pWindowContainer, HINSTANCE _hInstance, std::wstring _windowTitle, std::wstring _windowClass, UINT _width, UINT _height);
	bool ProcessMessages();
	HWND GetHWND() const;
	~CRenderWindow();

private:
	void RegisterWindowClass();
	HWND m_hWnd = NULL; //Handle to this window
	HINSTANCE m_hWndInst = NULL; //Handle to application instance
	std::wstring m_winTitle = L"";
	std::wstring m_winClass = L"";
	int m_width = 0;
	int m_height = 0;
};


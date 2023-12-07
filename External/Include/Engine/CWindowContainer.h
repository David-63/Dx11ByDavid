#pragma once
#include "CRenderWindow.h"

class CWindowContainer
{
protected:
	CRenderWindow m_renderWindow;

public:
	CWindowContainer();
	int WindowProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam);

};


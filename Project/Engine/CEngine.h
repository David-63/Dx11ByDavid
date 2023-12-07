#pragma once
#include "CWindowContainer.h"

class CEngine : CWindowContainer, public CSingleton<CEngine>
{
private:
	HWND m_hWnd = nullptr;
	Vec2 m_vResolution;

public:
	Vec2 GetWindowResolution() const { return m_vResolution; }
	HWND GetHWnd() const { return m_hWnd; }

public:
	int init(HINSTANCE _hInstance, wstring _windowTitle, wstring _windowClass, UINT _width, UINT _height);
	bool ProcessMessages();
	void progress();

private:
	void tick();
	void render();
};


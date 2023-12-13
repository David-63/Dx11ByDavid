#pragma once
#include "CWindowContainer.h"

class CEngineT : CWindowContainer, public CSingleton<CEngineT>
{
public:
	Vec2 GetWindowResolution() const { return m_renderWindow.GetResolution(); }
	HWND GetHWnd() const { return m_renderWindow.GetHWND(); }

public:
	int init(HINSTANCE _hInstance, wstring _windowTitle, wstring _windowClass, UINT _width, UINT _height);
	bool ProcessMessages();
	void progress();

private:
	void tick();
	void render();
};


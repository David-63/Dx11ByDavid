#pragma once

class CEngine : public CSingleton<CEngine>
{
	SINGLE(CEngine)
private:
	HWND	m_hWnd = nullptr;
	Vec2	m_vResolution;

public:
	HWND GetMainWnd() { return m_hWnd; }
	Vec2 GetWindowResolution() { return m_vResolution; }

public:
	int init(HWND _hWnd, UINT _iWidth, UINT _iHeight);
	void progress();

private:
	void tick();
	void render();

};


#include "pch.h"
#include "CEngine.h"

int CEngine::init(HINSTANCE _hInstance, wstring _windowTitle, wstring _windowClass, UINT _width, UINT _height)
{
    // ������ ����
    if (!m_renderWindow.Initialize(this, _hInstance, _windowTitle, _windowClass, _width, _height))
        return false;
    //// ����̽� �ʱ�ȭ
    //if (!Device::GetInstance()->Initialize(this->render_window.GetHWND(), width, height))
    //{
    //    return false;
    //}
}

bool CEngine::ProcessMessages()
{
    return m_renderWindow.ProcessMessages();
}

void CEngine::progress()
{
    tick();

    render();
}

void CEngine::tick()
{
}

void CEngine::render()
{
}

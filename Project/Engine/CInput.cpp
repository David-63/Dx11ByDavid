#include "pch.h"
#include "CInput.h"

void CInput::Initialize()
{
    m_keyboard.Initialize();
}

INPUT_TYPE CInput::GetKeyState(const unsigned char keycode)
{
    return m_keyboard.GetKeyState(keycode);
}

INPUT_TYPE CInput::GetLeftState()
{
    return m_mouse.GetLeftState();
}

INPUT_TYPE CInput::GetRightState()
{
    return m_mouse.GetRightState();
}

INPUT_TYPE CInput::GetMiddleState()
{
    return m_mouse.GetMiddleState();
}

Vec2 CInput::GetPos()
{
    return m_mouse.GetPos();
}

void CInput::OnKeyHold(const unsigned char keycode)
{
    m_keyboard.OnKeyHold(keycode);
}

void CInput::OnKeyPressed(const unsigned char keycode)
{
    m_keyboard.OnKeyPressed(keycode);
}

void CInput::OnKeyInvalided(const unsigned char keycode)
{
    m_keyboard.OnKeyInvalided(keycode);
}

void CInput::OnKeyReleased(const unsigned char keycode)
{
    m_keyboard.OnKeyReleased(keycode);
}

void CInput::OnChar(const unsigned char keycode)
{
    m_keyboard.OnChar(keycode);
}

void CInput::OnMouseMove(int x, int y)
{
    m_mouse.OnMouseMove(x, y);
}

void CInput::OnLeftPressed(int x, int y)
{
    m_mouse.OnLeftPressed(x, y);
}

void CInput::OnLeftHold(int x, int y)
{
    m_mouse.OnLeftHold(x, y);
}

void CInput::OnLeftReleased(int x, int y)
{
    m_mouse.OnLeftReleased(x, y);
}

void CInput::OnLeftInvalid(int x, int y)
{
    m_mouse.OnLeftInvalid(x, y);
}

void CInput::OnRightPressed(int x, int y)
{
    m_mouse.OnRightPressed(x, y);
}

void CInput::OnRightHold(int x, int y)
{
    m_mouse.OnRightHold(x, y);
}

void CInput::OnRightReleased(int x, int y)
{
    m_mouse.OnRightReleased(x, y);
}

void CInput::OnRightInvalid(int x, int y)
{
    m_mouse.OnRightInvalid(x, y);
}

void CInput::OnMiddlePressed(int x, int y)
{
    m_mouse.OnMiddlePressed(x, y);
}

void CInput::OnMiddleHold(int x, int y)
{
    m_mouse.OnMiddleHold(x, y);
}

void CInput::OnMiddleReleased(int x, int y)
{
    m_mouse.OnMiddleReleased(x, y);
}

void CInput::OnMiddleInvalid(int x, int y)
{
    m_mouse.OnMiddleInvalid(x, y);
}

void CInput::OnWheelUp(int x, int y)
{
    m_mouse.OnWheelUp(x, y);
}

void CInput::OnWheelDown(int x, int y)
{
    m_mouse.OnWheelDown(x, y);
}

void CInput::OnMouseMoveRaw(int x, int y)
{
    m_mouse.OnMouseMoveRaw(x, y);
}

bool CInput::KeyBufferIsEmpty()
{
    return m_keyboard.KeyBufferIsEmpty();
}

bool CInput::CharBufferIsEmpty()
{
    return m_keyboard.CharBufferIsEmpty();
}

CKeyboardEvent CInput::ReadKeyEvent()
{
    return m_keyboard.ReadKeyEvent();
}

unsigned char CInput::ReadChar()
{
    return m_keyboard.ReadChar();
}

bool CInput::MouseBufferIsEmpty()
{
    return m_mouse.MouseBufferIsEmpty();
}

CMouseEvent CInput::ReadMouseEvent()
{
    return m_mouse.ReadMouseEvent();
}

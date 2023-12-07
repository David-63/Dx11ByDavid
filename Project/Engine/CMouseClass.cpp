#include "pch.h"
#include "CMouseClass.h"


void CMouseClass::OnLeftPressed(int x, int y)
{
    m_lBtnState = INPUT_TYPE::Press;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::LPress, x, y));
}

void CMouseClass::OnLeftHold(int x, int y)
{
    m_lBtnState = INPUT_TYPE::Hold;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::LHold, x, y));
}

void CMouseClass::OnLeftReleased(int x, int y)
{
    m_lBtnState = INPUT_TYPE::Release;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::LRelease, x, y));
}

void CMouseClass::OnLeftInvalid(int x, int y)
{
    m_lBtnState = INPUT_TYPE::Invalid;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::Invalid, x, y));
}

void CMouseClass::OnRightPressed(int x, int y)
{
    m_rBtnState = INPUT_TYPE::Press;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::RHold, x, y));
}

void CMouseClass::OnRightHold(int x, int y)
{
    m_rBtnState = INPUT_TYPE::Hold;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::RPress, x, y));
}

void CMouseClass::OnRightReleased(int x, int y)
{
    m_rBtnState = INPUT_TYPE::Release;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::RRelease, x, y));
}

void CMouseClass::OnRightInvalid(int x, int y)
{
    m_rBtnState = INPUT_TYPE::Invalid;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::Invalid, x, y));
}

void CMouseClass::OnMiddlePressed(int x, int y)
{
    m_mBtnState = INPUT_TYPE::Press;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::MPress, x, y));
}

void CMouseClass::OnMiddleHold(int x, int y)
{
    m_mBtnState = INPUT_TYPE::Hold;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::MHold, x, y));
}

void CMouseClass::OnMiddleReleased(int x, int y)
{
    m_mBtnState = INPUT_TYPE::Release;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::MRelease, x, y));
}

void CMouseClass::OnMiddleInvalid(int x, int y)
{
    m_mBtnState = INPUT_TYPE::Invalid;
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::Invalid, x, y));
}

void CMouseClass::OnWheelUp(int x, int y)
{
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::WheelUp, x, y));
}

void CMouseClass::OnWheelDown(int x, int y)
{
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::WheelDown, x, y));
}

void CMouseClass::OnMouseMove(int x, int y)
{
    m_mousePos = Vec2(static_cast<float>(x), static_cast<float>(y));
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::Move, x, y));
}

void CMouseClass::OnMouseMoveRaw(int x, int y)
{
    mouse_event_buffer.push(CMouseEvent(CMouseEvent::MOUSE_TYPE::RAW_MOVE, x, y));
}

INPUT_TYPE CMouseClass::GetLeftState()
{
    return m_lBtnState;
}

INPUT_TYPE CMouseClass::GetRightState()
{
    return m_rBtnState;
}

INPUT_TYPE CMouseClass::GetMiddleState()
{
    return m_mBtnState;
}

Vec2 CMouseClass::GetPos()
{
    return m_mousePos;
}

bool CMouseClass::MouseBufferIsEmpty()
{
    return mouse_event_buffer.empty();
}

CMouseEvent CMouseClass::ReadMouseEvent()
{
    if (mouse_event_buffer.empty())
        return CMouseEvent();
    else
    {
        CMouseEvent mouseEvent = mouse_event_buffer.front();  // Get first event from buffer
        mouse_event_buffer.pop();    // Remove first event from buffer
        return mouseEvent;
    }
}
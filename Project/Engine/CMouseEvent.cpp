#include "pch.h"
#include "CMouseEvent.h"


CMouseEvent::CMouseEvent() { }
CMouseEvent::CMouseEvent(const MOUSE_TYPE m_type, const int x, const int y)
    : m_type(m_type), m_mousePos(static_cast<float>(x), static_cast<float>(y))
{ }


bool CMouseEvent::IsValid() const
{
    return m_type != MOUSE_TYPE::Invalid;
}

CMouseEvent::MOUSE_TYPE CMouseEvent::GetType() const
{
    return m_type;
}

Vec2 CMouseEvent::GetPos() const
{
    return m_mousePos;
}

int CMouseEvent::GetPosX() const
{
    return m_mousePos.x;
}

int CMouseEvent::GetPosY() const
{
    return m_mousePos.y;
}
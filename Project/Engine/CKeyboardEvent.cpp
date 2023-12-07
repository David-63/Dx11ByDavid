#include "pch.h"
#include "CKeyboardEvent.h"

CKeyboardEvent::CKeyboardEvent()
{
}

CKeyboardEvent::CKeyboardEvent(const INPUT_TYPE m_type, const unsigned char m_key)
    : m_type(m_type), m_key(m_key)
{
}

bool CKeyboardEvent::IsPress() const
{
    return m_type == INPUT_TYPE::Press;
}

bool CKeyboardEvent::IsHold() const
{
    return m_type == INPUT_TYPE::Hold;
}

bool CKeyboardEvent::IsRelease() const
{
    return m_type == INPUT_TYPE::Release;
}

bool CKeyboardEvent::IsValid() const
{
    return m_type != INPUT_TYPE::Invalid;
}

unsigned char CKeyboardEvent::GetKeyCode() const
{
    return m_key;
}

INPUT_TYPE CKeyboardEvent::GetType() const
{
    return m_type;
}

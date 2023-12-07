#include "pch.h"
#include "CKeyboardClass.h"

void CKeyboardClass::Initialize()
{
	for (size_t index = 0; index < 256; ++index)
		Key_States[index] = INPUT_TYPE::Invalid;	// Initialize all key states to off
}

INPUT_TYPE CKeyboardClass::GetKeyState(const unsigned char keycode)
{
	return Key_States[keycode];
}

bool CKeyboardClass::KeyBufferIsEmpty()
{
	return key_buffer.empty();
}

bool CKeyboardClass::CharBufferIsEmpty()
{
	return char_buffer.empty();
}

CKeyboardEvent CKeyboardClass::ReadKeyEvent()
{
	if (key_buffer.empty()) // If no keys to be read?
	{
		return CKeyboardEvent(); // return empty keyboard event
	}
	else
	{
		CKeyboardEvent retEvent = key_buffer.front();	// Get first keyboard event from queue
		key_buffer.pop();	// remove first item from queue
		return retEvent;	// returns keyboard event
	}
}

unsigned char CKeyboardClass::ReadChar()
{
	if (char_buffer.empty()) // If no chars to be read?
	{
		return 0u; // return 0 (null char)
	}
	else
	{
		unsigned char retChar = char_buffer.front();	// Get first char from queue
		char_buffer.pop();	// remove first char from queue
		return retChar;	// returns char 
	}
}

void CKeyboardClass::OnKeyPressed(const unsigned char keycode)
{
	Key_States[keycode] = INPUT_TYPE::Press;
	key_buffer.push(CKeyboardEvent(INPUT_TYPE::Press, keycode));
}

void CKeyboardClass::OnKeyHold(const unsigned char m_key)
{
	Key_States[m_key] = INPUT_TYPE::Hold;
	key_buffer.push(CKeyboardEvent(INPUT_TYPE::Hold, m_key));
}

void CKeyboardClass::OnKeyReleased(const unsigned char m_key)
{
	Key_States[m_key] = INPUT_TYPE::Release;
	key_buffer.push(CKeyboardEvent(INPUT_TYPE::Release, m_key));
}

void CKeyboardClass::OnKeyInvalided(const unsigned char m_key)
{
	Key_States[m_key] = INPUT_TYPE::Invalid;
	key_buffer.push(CKeyboardEvent(INPUT_TYPE::Invalid, m_key));
}

void CKeyboardClass::OnChar(const unsigned char m_key)
{
	char_buffer.push(m_key);
}

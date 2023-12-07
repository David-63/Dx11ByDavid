#pragma once
#include "CKeyboardEvent.h"

class CKeyboardClass
{
private:
	INPUT_TYPE Key_States[256];
	std::queue<CKeyboardEvent> key_buffer;
	std::queue<unsigned char> char_buffer;

public:
	void Initialize();	// 루프 돌면서 키 버퍼 확인

public:
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();
	CKeyboardEvent ReadKeyEvent();
	unsigned char ReadChar();


public:	// WinProc를 통해서 키를 queue 버퍼에 추가
	void OnKeyPressed(const unsigned char m_key);
	void OnKeyHold(const unsigned char m_key);
	void OnKeyReleased(const unsigned char m_key);
	void OnKeyInvalided(const unsigned char m_key);
	void OnChar(const unsigned char m_key);

public:
	INPUT_TYPE GetKeyState(const unsigned char keycode);
};


#pragma once
#include "CKeyboardClass.h"
#include "CMouseClass.h"

class CInput : public CSingleton<CInput>
{
private:
	CKeyboardClass m_keyboard;
	CMouseClass m_mouse;
public:
	void Initialize();

	// �Է� Ȯ��
public:
	INPUT_TYPE GetKeyState(const unsigned char keycode);
	INPUT_TYPE GetLeftState();
	INPUT_TYPE GetRightState();
	INPUT_TYPE GetMiddleState();

	Vec2 GetPos();

	// Ű���� �Է� ����
public:
	void OnKeyHold(const unsigned char keycode);
	void OnKeyPressed(const unsigned char keycode);
	void OnKeyInvalided(const unsigned char keycode);
	void OnKeyReleased(const unsigned char keycode);

	void OnChar(const unsigned char keycode);

	// ���콺 �Է� ����
public:
	void OnMouseMove(int x, int y);

	void OnLeftPressed(int x, int y);
	void OnLeftHold(int x, int y);
	void OnLeftReleased(int x, int y);
	void OnLeftInvalid(int x, int y);

	void OnRightPressed(int x, int y);
	void OnRightHold(int x, int y);
	void OnRightReleased(int x, int y);
	void OnRightInvalid(int x, int y);

	void OnMiddlePressed(int x, int y);
	void OnMiddleHold(int x, int y);
	void OnMiddleReleased(int x, int y);
	void OnMiddleInvalid(int x, int y);

	void OnWheelUp(int x, int y);
	void OnWheelDown(int x, int y);

	void OnMouseMoveRaw(int x, int y);

	// Ű���� ����
public:
	bool KeyBufferIsEmpty();
	bool CharBufferIsEmpty();

	CKeyboardEvent ReadKeyEvent();
	unsigned char ReadChar();

	// ���콺 ����
public:
	bool MouseBufferIsEmpty();

	CMouseEvent ReadMouseEvent();
};


#pragma once
#include "CKeyboardClass.h"
#include "CMouseClass.h"

enum class KEY
{
	UP,		// VK_UP
	DOWN,
	LEFT,
	RIGHT,

	SPACE,
	ENTER,
	ESC,
	LALT,
	LCTRL,
	LSHIFT,
	TAB,
	END,
};

struct tKeyInfo
{
	KEY			key;
	INPUT_TYPE	state;
	bool		bPrev;
};

class CInput : public CSingleton<CInput>
{
private:
	CKeyboardClass		m_keyboard;
	CMouseClass			m_mouse;
	vector<tKeyInfo>	m_vecFuncKey;

public:
	void init();
	void tick();
	// �Է� Ȯ��
public:
	INPUT_TYPE GetFuncState(const KEY _keycode);
	INPUT_TYPE GetKeyState(const unsigned char _keycode);
	INPUT_TYPE GetLeftState();
	INPUT_TYPE GetRightState();
	INPUT_TYPE GetMiddleState();

	Vec2 GetPos();
	Vec2 GetDir();

	// Ű���� �Է� ����
public:
	void OnKeyHold(const unsigned char _keycode);
	void OnKeyPressed(const unsigned char _keycode);
	void OnKeyInvalided(const unsigned char _keycode);
	void OnKeyReleased(const unsigned char _keycode);

	void OnChar(const unsigned char _keycode);

	// ���콺 �Է� ����
public:
	void OnMouseMove(int _x, int _y);

	void OnLeftPressed(int _x, int _y);
	void OnLeftHold(int _x, int _y);
	void OnLeftReleased(int _x, int _y);
	void OnLeftInvalid(int _x, int _y);

	void OnRightPressed(int _x, int _y);
	void OnRightHold(int _x, int _y);
	void OnRightReleased(int _x, int _y);
	void OnRightInvalid(int _x, int _y);

	void OnMiddlePressed(int _x, int _y);
	void OnMiddleHold(int _x, int _y);
	void OnMiddleReleased(int _x, int _y);
	void OnMiddleInvalid(int _x, int _y);

	void OnWheelUp(int _x, int _y);
	void OnWheelDown(int _x, int _y);

	void OnMouseMoveRaw(int _x, int _y);

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


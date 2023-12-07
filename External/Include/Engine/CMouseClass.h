#pragma once
#include "CMouseEvent.h"

class CMouseClass
{
private:
	std::queue<CMouseEvent> mouse_event_buffer;

	INPUT_TYPE m_lBtnState = INPUT_TYPE::Invalid;
	INPUT_TYPE m_rBtnState = INPUT_TYPE::Invalid;
	INPUT_TYPE m_mBtnState = INPUT_TYPE::Invalid;

	Vec2 m_mousePos;

public:
	INPUT_TYPE GetLeftState();
	INPUT_TYPE GetRightState();
	INPUT_TYPE GetMiddleState();

	Vec2 GetPos();

public:
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
	void OnMouseMove(int x, int y);
	void OnMouseMoveRaw(int x, int y);

	bool MouseBufferIsEmpty();
	CMouseEvent ReadMouseEvent();


};

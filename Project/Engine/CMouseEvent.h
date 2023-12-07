#pragma once
class CMouseEvent
{
public:
	enum MOUSE_TYPE
	{
		LPress,
		LHold,
		LRelease,
		RPress,
		RHold,
		RRelease,
		MPress,
		MHold,
		MRelease,
		WheelUp,
		WheelDown,
		Move,
		RAW_MOVE,
		Invalid,
	};

public:
	CMouseEvent();
	CMouseEvent(const MOUSE_TYPE m_type, const int x, const int y);

	bool IsValid() const;

	MOUSE_TYPE GetType() const;
	Vec2 GetPos() const;
	int GetPosX() const;
	int GetPosY() const;

private:
	MOUSE_TYPE m_type = MOUSE_TYPE::Invalid;
	Vec2 m_mousePos = Vec2::Zero;
};


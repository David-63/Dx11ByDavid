#pragma once
class CKeyboardEvent
{
private:
	INPUT_TYPE m_type = INPUT_TYPE::Invalid;
	unsigned char m_key = 0u;

public:
	CKeyboardEvent();
	CKeyboardEvent(const INPUT_TYPE m_type, const unsigned char m_key);

	bool IsPress() const;
	bool IsHold() const;
	bool IsRelease() const;
	bool IsValid() const;

	unsigned char GetKeyCode() const;
	INPUT_TYPE GetType() const;
};


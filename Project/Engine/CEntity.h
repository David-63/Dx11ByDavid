#pragma once

class CEntity
{
private:
	static UINT g_nextID;

private:
	wstring		m_name;
	const UINT  m_ID;

public:
	void SetName(const wstring& _strName) { m_name = _strName; }
	const wstring& GetName() { return m_name; }
	UINT GetID() { return m_ID; }

public:
	virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _other);
	virtual ~CEntity();
};


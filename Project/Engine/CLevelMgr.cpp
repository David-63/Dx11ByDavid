#include "pch.h"
#include "CLevelMgr.h"


#include "CLevel.h"
#include "CLayer.h"

CLevelMgr::CLevelMgr() { }

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_curLevel)
		delete m_curLevel;
}

void CLevelMgr::init()
{
	m_curLevel = new CLevel;
	m_curLevel->ChangeState(LEVEL_STATE::STOP);
}

void CLevelMgr::tick()
{
	m_curLevel->clear();

	if (LEVEL_STATE::PLAY == m_curLevel->GetState())
	{
		m_curLevel->tick();
	}

	m_curLevel->finaltick();
}


CGameObject* CLevelMgr::FindObjectByName(const wstring& _strName)
{
	return m_curLevel->FindObjectByName(_strName);
}

void CLevelMgr::FindObjectByName(const wstring& _strName, vector<CGameObject*>& _vec)
{
	m_curLevel->FindObjectByName(_strName, _vec);
}

void CLevelMgr::ChangeLevel(CLevel* _NextLevel)
{
	if (nullptr != m_curLevel)
	{
		delete m_curLevel;
		m_curLevel = nullptr;
	}

	m_curLevel = _NextLevel;
}

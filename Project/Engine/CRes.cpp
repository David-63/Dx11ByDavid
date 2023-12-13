#include "pch.h"
#include "CRes.h"

CRes::CRes(RES_TYPE _type, bool _isEngine)
	: m_resType(_type), m_isEngine(_isEngine)
{ }
CRes::CRes(const CRes& _Other)
	: CEntity(_Other)
	, m_resType(_Other.m_resType)	
	, m_key(_Other.m_key)
	, m_relativePath(_Other.m_relativePath)
{ }
CRes::~CRes()
{ }


void CRes::Release()
{
	--m_refCount;

	if (0 == m_refCount)
	{
		delete this;
	}
}

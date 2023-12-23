#pragma once
#include "CEntity.h"

#include "CTexture.h"
#include "ptr.h"

class CMRT : public CEntity
{
private:
	Ptr<CTexture>	m_arrRT[8];
	UINT			m_RTCount = 0;
	Ptr<CTexture>	m_DSTex;
	Vec4			m_ClearColor[8];

public:
	void Create(Ptr<CTexture>* _arrRTTex, UINT _RTCount, Ptr<CTexture> _DSTex);
	void SetClearColor(Vec4 _clearColor, UINT _RTIdx) { m_ClearColor[_RTIdx] = _clearColor; }
	void ClearTarget();

	// 이전 MRT의 DepthTargetTex 적용
	void OMSet(bool _isStay = false);

public:
	CLONE_DISABLE(CMRT);

public:
	CMRT();
	~CMRT();
};


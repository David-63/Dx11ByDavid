#include "pch.h"
#include "CRenderComp.h"

CRenderComp::CRenderComp(COMPONENT_TYPE _type) : CComponent(_type)
{ }
CRenderComp::~CRenderComp() { }

void CRenderComp::SetMaterial(Ptr<CMaterial> _Mtrl)
{
	m_sharedMtrl = _Mtrl;
	m_currentMtrl = m_sharedMtrl;
}

Ptr<CMaterial> CRenderComp::GetSharedMaterial()
{
	if (m_currentMtrl != m_sharedMtrl)
	{
		m_currentMtrl = m_sharedMtrl;
		m_dynamicMtrl = nullptr;
	}

	return m_sharedMtrl;
}

Ptr<CMaterial> CRenderComp::GetDynamicMaterial()
{
	// 원본 재질이 없다 -> Nullptr 반환
	if (nullptr == m_sharedMtrl)
	{
		m_currentMtrl = nullptr;
		return m_currentMtrl;
	}

	// 동적 재질 최초 요청시 제작 해서 준다.
	if (nullptr == m_dynamicMtrl)
	{
		m_dynamicMtrl = m_sharedMtrl->Clone();
	}

	// 동적 재질을 현재 사용재질로 지정한다.
	m_currentMtrl = m_dynamicMtrl;


	return m_currentMtrl;
}

void CRenderComp::SaveToLevelFile(FILE* _File)
{
	SaveResRef(m_mesh.Get(), _File);
	SaveResRef(m_sharedMtrl.Get(), _File);
}

void CRenderComp::LoadFromLevelFile(FILE* _File)
{
	LoadResRef(m_mesh, _File);
	LoadResRef(m_sharedMtrl, _File);

	SetMaterial(m_sharedMtrl);
}

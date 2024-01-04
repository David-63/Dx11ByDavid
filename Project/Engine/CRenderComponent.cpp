#include "pch.h"
#include "CRenderComponent.h"

#include "CTransform.h"
#include "CResMgr.h"
#include "CMaterial.h"

CRenderComponent::CRenderComponent(COMPONENT_TYPE _type)
	: CComponent(_type), m_isFrustumCheck(true)
{
}

CRenderComponent::~CRenderComponent()
{
}

void CRenderComponent::render_shadowmap()
{
	Ptr<CMaterial> shadowmapMtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"ShadowMapMtrl");
	Transform()->UpdateData();
	shadowmapMtrl->UpdateData();
	GetMesh()->render();
}

void CRenderComponent::SetMaterial(Ptr<CMaterial> _Mtrl)
{
	m_pSharedMtrl = _Mtrl;
	m_pCurrentMtrl = m_pSharedMtrl;
}

Ptr<CMaterial> CRenderComponent::GetSharedMaterial()
{
	if (m_pCurrentMtrl != m_pSharedMtrl)
	{
		m_pCurrentMtrl = m_pSharedMtrl;
		m_pDynamicMtrl = nullptr;
	}

	return m_pSharedMtrl;
}

Ptr<CMaterial> CRenderComponent::GetDynamicMaterial()
{
	// 원본 재질이 없다 -> Nullptr 반환
	if (nullptr == m_pSharedMtrl)
	{
		m_pCurrentMtrl = nullptr;
		return m_pCurrentMtrl;
	}

	// 동적 재질 최초 요청시 제작 해서 준다.
	if (nullptr == m_pDynamicMtrl)
	{		
		m_pDynamicMtrl = m_pSharedMtrl->Clone();		
	}

	// 동적 재질을 현재 사용재질로 지정한다.
	m_pCurrentMtrl = m_pDynamicMtrl;


	return m_pCurrentMtrl;
}

void CRenderComponent::SaveToLevelFile(FILE* _File)
{
	SaveResRef(m_pMesh.Get(), _File);
	SaveResRef(m_pSharedMtrl.Get(), _File);
	fwrite(&m_isFrustumCheck, sizeof(bool), 1, _File);
}

void CRenderComponent::LoadFromLevelFile(FILE* _File)
{
	LoadResRef(m_pMesh, _File);
	LoadResRef(m_pSharedMtrl, _File);
	fread(&m_isFrustumCheck, sizeof(bool), 1, _File);

	SetMaterial(m_pSharedMtrl);
}

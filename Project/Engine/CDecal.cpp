#include "pch.h"
#include "CDecal.h"

#include "CResMgr.h"
#include "CMesh.h"
#include "CMaterial.h"

#include "CTransform.h"

CDecal::CDecal()
	: CRenderComponent(COMPONENT_TYPE::DECAL)
	, m_bDeferred(false)
	, m_bEmissive(false)
{
	SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));		
	SetDeferredDecal(m_bDeferred);	
}

CDecal::~CDecal()
{

}


void CDecal::finaltick()
{	
	DrawDebugCube(Transform()->GetWorldMat(), Vec4(0.f, 1.f, 0.f, 1.f), 0.f, true);
}

void CDecal::render()
{
	if (nullptr == GetMaterial() || nullptr == GetMesh())
		return;

	Transform()->UpdateData();

	int IsEmissive = m_bEmissive;
	GetMaterial()->SetScalarParam(INT_0, &IsEmissive);
	GetMaterial()->UpdateData();

	GetMesh()->render();	
}

void CDecal::SaveToLevelFile(FILE* _File)
{
	CRenderComponent::SaveToLevelFile(_File);
	SaveResRef(m_DecalTex.Get(), _File);
	fwrite(&m_bDeferred, sizeof(bool), 1, _File);
	fwrite(&m_bEmissive, sizeof(bool), 1, _File);
}

void CDecal::LoadFromLevelFile(FILE* _File)
{
	CRenderComponent::LoadFromLevelFile(_File);
	LoadResRef(m_DecalTex, _File);
	fread(&m_bDeferred, sizeof(bool), 1, _File);
	fread(&m_bEmissive, sizeof(bool), 1, _File);
}



void CDecal::SetDeferredDecal(bool _bDeferred)
{
	m_bDeferred = _bDeferred;

	if (m_bDeferred)
	{
		SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DeferredDecalMtrl"));
	}
	else
	{
		SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"DecalMtrl"));
	}

	GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"PositionTargetTex"));

}
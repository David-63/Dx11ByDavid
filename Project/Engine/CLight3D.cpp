#include "pch.h"
#include "CLight3D.h"

#include "CRenderMgr.h"
#include "CTransform.h"
#include "CResMgr.h"

CLight3D::CLight3D() : CComponent(COMPONENT_TYPE::LIGHT3D)
{
	SetLightType(LIGHT_TYPE::DIRECTIONAL);
}
CLight3D::~CLight3D() { }

void CLight3D::finaltick()
{
	m_LightInfo.vWorldPos = Transform()->GetWorldPos();
	m_LightInfo.vWorldDir = Transform()->GetWorldDir(DIR_TYPE::FRONT);

	m_LightIdx = CRenderMgr::GetInst()->RegisterLight3D(this, m_LightInfo);
}

void CLight3D::render()
{
	Transform()->UpdateData();

	m_Mtrl->SetScalarParam(INT_0, &m_LightIdx);
	m_Mtrl->UpdateData();
	m_Mesh->render();
}

void CLight3D::SetLightType(LIGHT_TYPE _type)
{
	m_LightInfo.LightType = (int)_type;

	if (LIGHT_TYPE::DIRECTIONAL == (LIGHT_TYPE)m_LightInfo.LightType)
	{
		// 광원을 렌더링 할 때, 광원의 영향범위를 형상화 할 수 있는 메쉬(볼륨메쉬) 를 선택
		m_Mesh = CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh");
		m_Mtrl = CResMgr::GetInst()->FindRes<CMaterial>(L"DirectionalLightMtrl");
		m_Mtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"NormalTargetTex"));
		m_Mtrl->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"PositionTargetTex"));
	}

	else if (LIGHT_TYPE::POINT == (LIGHT_TYPE)m_LightInfo.LightType)
	{
		m_Mesh = CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh");
	}

	else
	{
		m_Mesh = CResMgr::GetInst()->FindRes<CMesh>(L"ConeMesh");	// 아직 구현 안함
	}
}


void CLight3D::SaveToLevelFile(FILE* _File)
{
	fwrite(&m_LightInfo, sizeof(tLightInfo), 1, _File);
}

void CLight3D::LoadFromLevelFile(FILE* _File)
{
	fread(&m_LightInfo, sizeof(tLightInfo), 1, _File);
}
#include "CAnim3D.h"

#include "CTimeMgr.h"
#include "CGameObject.h"
#include "CAnimator3D.h"
#include "CAnimation3DShader.h"
#include "CResMgr.h"
#include "CMeshRender.h"

CAnim3D::CAnim3D()
: m_Owner(nullptr), m_strAnimName()
, m_AnimClipIdx(0), m_iFrameCount(30)
, m_StartTime(0.f), m_EndTime(0.f), m_AnimUpdateTime()
, m_CurFrameIdx(0), m_NextFrameIdx(0), m_Ratio(0.f)
, m_pBoneFinalMatBuffer(nullptr)
, m_bFinalMatUpdate(false), m_Finish(false)
{
	m_pBoneFinalMatBuffer = new CStructuredBuffer;
}

CAnim3D::~CAnim3D()
{
	if (nullptr != m_pBoneFinalMatBuffer)
		delete m_pBoneFinalMatBuffer;
}

void CAnim3D::finaltick()
{
	if (nullptr == m_Owner)
		return;

	// m_AnimUpdateTime[m_AnimClipIdx] 이 변수는 CreateAnim 단계에서 StartTime 값으로 초기화 되어야함

	m_AnimUpdateTime[m_AnimClipIdx] += DT;	
	if (m_AnimUpdateTime[m_AnimClipIdx] >= m_EndTime)
	{
		m_AnimUpdateTime[m_AnimClipIdx] = m_StartTime;
	}

	
	double dFrameIdx = m_AnimUpdateTime[m_AnimClipIdx] * (double)m_iFrameCount;
	m_CurFrameIdx = (int)(dFrameIdx);

	if (m_CurFrameIdx >= m_Owner->GetAnimClip()->at(m_AnimClipIdx).iFrameLength - 1)
		m_NextFrameIdx = m_CurFrameIdx;
	else
		m_NextFrameIdx = m_CurFrameIdx + 1;

	m_Ratio = (float)(dFrameIdx - (double)m_NextFrameIdx);

	m_bFinalMatUpdate = false;
}

void CAnim3D::UpdateData()
{
	if (!m_bFinalMatUpdate)
	{
		// Animation3D Update Compute Shader
		CAnimation3DShader* pUpdateShader = (CAnimation3DShader*)CResMgr::GetInst()->FindRes<CComputeShader>(L"Animation3DUpdateCS").Get();

		// Bone Data
		Ptr<CMesh> pMesh = m_Owner->MeshRender()->GetMesh();
		check_mesh(pMesh);

		pUpdateShader->SetFrameDataBuffer(pMesh->GetBoneFrameDataBuffer());
		pUpdateShader->SetOffsetMatBuffer(pMesh->GetBoneOffsetBuffer());
		pUpdateShader->SetOutputBuffer(m_pBoneFinalMatBuffer);

		
		UINT iBoneCount = m_Owner->GetBoneCount();
		pUpdateShader->SetBoneCount(iBoneCount);
		pUpdateShader->SetFrameIndex(m_CurFrameIdx);
		pUpdateShader->SetNextFrameIdx(m_NextFrameIdx);
		pUpdateShader->SetFrameRatio(m_Ratio);

		// 업데이트 쉐이더 실행
		pUpdateShader->Execute();

		m_bFinalMatUpdate = true;
	}

	// t30 레지스터에 최종행렬 데이터(구조버퍼) 바인딩		
	m_pBoneFinalMatBuffer->UpdateData(30, PIPELINE_STAGE::PS_VERTEX);
}

void CAnim3D::ClearData()
{
	m_pBoneFinalMatBuffer->Clear();

	UINT iMtrlCount = m_Owner->MeshRender()->GetMtrlCount();
	Ptr<CMaterial> pMtrl = nullptr;
	for (UINT i = 0; i < iMtrlCount; ++i)
	{
		pMtrl = m_Owner->MeshRender()->GetSharedMaterial(i);
		if (nullptr == pMtrl)
			continue;

		pMtrl->SetAnim3D(false); // Animation Mesh 알리기
		pMtrl->SetBoneCount(0);
	}
}

void CAnim3D::check_mesh(Ptr<CMesh> _pMesh)
{
	UINT iBoneCount = _pMesh->GetBoneCount();
	if (m_pBoneFinalMatBuffer->GetElementCount() != iBoneCount)
	{
		m_pBoneFinalMatBuffer->Create(sizeof(Matrix), iBoneCount, SB_TYPE::READ_WRITE, false, nullptr);
	}
}

void CAnim3D::CreateAnimation3D(const wstring& _strAnimName, int _clipIdx, float _startTime, float _endTime)
{
	m_strAnimName = _strAnimName;
	m_AnimClipIdx = _clipIdx;
	m_StartTime = _startTime;
	m_EndTime = _endTime;
	m_AnimUpdateTime.resize(m_Owner->GetAnimClip()[m_AnimClipIdx].size());
	m_AnimUpdateTime[m_AnimClipIdx] = m_StartTime;
}

void CAnim3D::CreateAnimation3D(const wstring& _strAnimName, int _clipIdx, int _startFrame, int _endFrame)
{
	// 안쓸듯?
}

void CAnim3D::SaveToLevelFile(FILE* _File)
{
}

void CAnim3D::LoadFromLevelFile(FILE* _File)
{
}

#include "pch.h"
#include "CAnim3D.h"

#include "CTimeMgr.h"
#include "CAnimation3DShader.h"
#include "CMeshRender.h"
#include "CAnimator3D.h"
#include "CResMgr.h"
#include "CStructuredBuffer.h"

void CAnim3D::finaltick()
{
	if (m_Finish)
		return;

	// 시작시간으로 초기화
	m_AccTime = m_StartTime;
	// 현재 재생중인 Clip 의 시간을 진행한다.
	m_AnimUpdateTime += DT;

	if (m_AnimUpdateTime >= m_EndTime)
	{
		m_AnimUpdateTime = m_StartTime;
		m_Finish = true;
	}

	// 시작시간에 업데이트 시간 적용
	m_AccTime = m_AnimUpdateTime;

	// 현재 프레임 인덱스 구하기
	double dFrameIdx = m_AccTime * (double)m_iFrameCount;
	m_CurFrameIdx = (int)(dFrameIdx);

	// 다음 프레임 인덱스
	if (m_CurFrameIdx >= m_pVecClip->at(0).iFrameLength - 1)
		m_NextFrameIdx = m_CurFrameIdx;	// 끝이면 현재 인덱스를 유지
	else
		m_NextFrameIdx = m_CurFrameIdx + 1;

	// 프레임간의 시간에 따른 비율을 구해준다.
	m_Ratio = (float)(m_NextFrameIdx - (double)m_CurFrameIdx);

	// 컴퓨트 쉐이더 연산여부
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

		UINT iBoneCount = (UINT)m_pVecBones->size();
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

void CAnim3D::CreateAnimation3D(const wstring& _strAnimName, const vector<tMTBone>* _bones, const vector<tMTAnimClip>* _clip
	, int _clipIdx, float _startTime, float _endTime)
{
	m_pVecBones = _bones;
	m_vecFinalBoneMat.resize(m_pVecBones->size());
	m_pVecClip = _clip;

	m_AnimClipIdx = _clipIdx;

	//m_pVecClip->at(m_AnimClipIdx).dStartTime;
	m_StartTime = _startTime;
	m_EndTime = _endTime;
}

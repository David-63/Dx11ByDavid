#pragma once
#include "CEntity.h"

#include "ptr.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CMesh.h"

class CAnimator3D;
class CStructuredBuffer;
class CAnim3D : public CEntity
{
private:
    // Animator에서 제공?
    CAnimator3D*                m_Owner;
	const vector<tMTBone>*      m_pVecBones;            // 매쉬의 뼈 정보
	const vector<tMTAnimClip>*  m_pVecClip;             // 매쉬의 원본 애니메이션 클립

    wstring                     m_strAnimName;
    int							m_iFrameCount;          // 현재 프레임 (30 기준)
    vector<Matrix>				m_vecFinalBoneMat;      // 뼈 개수만큼 행렬 생성


    // 애니메이션 정보
    int                         m_AnimClipIdx;          // 애니메이션 클립 인덱스 (직접 만들어서 사용)
    float                       m_StartTime;            // 애니메이션 클립의 시작시간
    float                       m_EndTime;              // 애니메이션 클립의 종료시간

    float                       m_AnimUpdateTime;       // 애니메이션 진행 누적시간
    double						m_AccTime;              // 클립 기준 시작시간에 진행중인 시간을 누적한 값
    int							m_CurFrameIdx;          // 현재 진행중인 프레임
    int							m_NextFrameIdx;         // 다음 프레임 인덱스
    float						m_Ratio;                // 두 프레임간 진행도 비율

    bool                        m_Finish;


    // CS 전달 구조화 버퍼
	CStructuredBuffer*          m_pBoneFinalMatBuffer;  // CS로 전달할 뼈 행렬 정보
    bool						m_bFinalMatUpdate;      // 업데이트 체크용

public:
    void finaltick();
    void UpdateData();
    void ClearData();
    // 만들 애니메이션 클립 이름
    // 뼈랑 뭐 그런것들
    // 시작 프레임
    // 종료 프레임
    void CreateAnimation3D(const wstring& _strAnimName, const vector<tMTBone>* _bones, const vector<tMTAnimClip>* _clip, 
        int _clipIdx, float _startTime, float _endTime);
    
    void SetBones(const vector<tMTBone>* _vecBones) { m_pVecBones = _vecBones; m_vecFinalBoneMat.resize(m_pVecBones->size()); }
    void SetAnimClip(const vector<tMTAnimClip>* _vecAnimClip) { m_pVecClip = _vecAnimClip; }


    const int& GetCurFrame() { return m_CurFrameIdx; }

    bool IsFinish() { return m_Finish; }
    void Reset()
    {
        m_CurFrameIdx = 0;
        m_AnimUpdateTime = m_StartTime;
        m_Finish = false;
    }

private:
    void check_mesh(Ptr<CMesh> _pMesh)
    {
        UINT iBoneCount = _pMesh->GetBoneCount();
        if (m_pBoneFinalMatBuffer->GetElementCount() != iBoneCount)
        {
            m_pBoneFinalMatBuffer->Create(sizeof(Matrix), iBoneCount, SB_TYPE::READ_WRITE, false, nullptr);
        }
    }

public:

    CStructuredBuffer* GetFinalBoneMat() { return m_pBoneFinalMatBuffer; }
    UINT GetBoneCount() { return (UINT)m_pVecBones->size(); }

    void SaveToLevelFile(FILE* _File);
    void LoadFromLevelFile(FILE* _File);


    CLONE(CAnim3D);
public:
    CAnim3D();
    ~CAnim3D();

    friend class CAnimator3D;
};


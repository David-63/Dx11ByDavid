#pragma once
#include "CEntity.h"

#include "ptr.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CMesh.h"
#include "CStructuredBuffer.h"

class CAnimator3D;
class CStructuredBuffer;
class CAnim3D : public CEntity
{
private:    
    CAnimator3D*                m_Owner;                // Owner를 알아야 컴포넌트에 접근 가능함
    wstring                     m_strAnimName;          // 애니메이션 Key Name


    int							m_iFrameCount;          // 현재 프레임 (30 기준)

    // 애니메이션 정보
    int                         m_AnimClipIdx;          // 이 애니메이션의 클립 인덱스 (직접 만들어서 사용)
    float                       m_StartTime;            // 애니메이션 클립의 시작시간
    float                       m_EndTime;              // 애니메이션 클립의 종료시간
    vector<float>				m_AnimUpdateTime;       // 애니메이션 진행 누적시간

    int							m_CurFrameIdx;          // 현재 진행중인 프레임
    int							m_NextFrameIdx;         // 다음 프레임 인덱스
    float						m_Ratio;                // 두 프레임간 진행도 비율

    bool                        m_Finish;


    vector<Matrix>				m_vecFinalBoneMat;      // 뼈 개수만큼 행렬 생성
    CStructuredBuffer*          m_pBoneFinalMatBuffer;  // CS로 전달할 뼈 행렬 정보
    bool						m_bFinalMatUpdate;      // 업데이트 체크용

public:
    void finaltick();
    void UpdateData();
    void ClearData();
    void check_mesh(Ptr<CMesh> _pMesh);


public:
    void CreateAnimation3D(const wstring& _strAnimName, int _clipIdx, float _startTime, float _endTime);
    void CreateAnimation3D(const wstring& _strAnimName, int _clipIdx, int _startFrame, int _endFrame); // 안씀

public:
    const wstring& GetAnimName() { return m_strAnimName; }
    int GetAnimClipIdx() { return m_AnimClipIdx; }    
    CStructuredBuffer* GetFinalBoneMat() { return m_pBoneFinalMatBuffer; }
    const int& GetCurFrame() { return m_CurFrameIdx; }
    const int& GetCurTime() { return m_AnimUpdateTime[m_AnimClipIdx]; }
    bool IsFinish() { return m_Finish; }
    void Reset()
    {
        m_CurFrameIdx = 0; // 이런 방식으로 초기화되면 안됨 (시작위치가 0이 아닐 수 있음)
        m_AnimUpdateTime[m_CurFrameIdx] = m_StartTime;
        m_Finish = false;
    }

public:

    void SaveToLevelFile(FILE* _File);
    void LoadFromLevelFile(FILE* _File);


    CLONE(CAnim3D);
public:
    CAnim3D();
    ~CAnim3D();

    friend class CAnimator3D;
};


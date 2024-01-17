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
    // Animator���� ����?
    CAnimator3D*                m_Owner;
	const vector<tMTBone>*      m_pVecBones;            // �Ž��� �� ����
	const vector<tMTAnimClip>*  m_pVecClip;             // �Ž��� ���� �ִϸ��̼� Ŭ��

    wstring                     m_strAnimName;
    int							m_iFrameCount;          // ���� ������ (30 ����)
    vector<Matrix>				m_vecFinalBoneMat;      // �� ������ŭ ��� ����


    // �ִϸ��̼� ����
    int                         m_AnimClipIdx;          // �ִϸ��̼� Ŭ�� �ε��� (���� ���� ���)
    float                       m_StartTime;            // �ִϸ��̼� Ŭ���� ���۽ð�
    float                       m_EndTime;              // �ִϸ��̼� Ŭ���� ����ð�

    float                       m_AnimUpdateTime;       // �ִϸ��̼� ���� �����ð�
    double						m_AccTime;              // Ŭ�� ���� ���۽ð��� �������� �ð��� ������ ��
    int							m_CurFrameIdx;          // ���� �������� ������
    int							m_NextFrameIdx;         // ���� ������ �ε���
    float						m_Ratio;                // �� �����Ӱ� ���൵ ����

    bool                        m_Finish;


    // CS ���� ����ȭ ����
	CStructuredBuffer*          m_pBoneFinalMatBuffer;  // CS�� ������ �� ��� ����
    bool						m_bFinalMatUpdate;      // ������Ʈ üũ��

public:
    void finaltick();
    void UpdateData();
    void ClearData();
    // ���� �ִϸ��̼� Ŭ�� �̸�
    // ���� �� �׷��͵�
    // ���� ������
    // ���� ������
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


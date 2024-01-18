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
    CAnimator3D*                m_Owner;                // Owner�� �˾ƾ� ������Ʈ�� ���� ������
    string                     m_strAnimName;          // �ִϸ��̼� Key Name


    int							m_iFrameCount;          // ���� ������ (30 ����)

    // �ִϸ��̼� ����
    int                         m_AnimClipIdx;          // �� �ִϸ��̼��� Ŭ�� �ε��� (���� ���� ���)
    float                       m_StartTime;            // �ִϸ��̼� Ŭ���� ���۽ð�
    float                       m_EndTime;              // �ִϸ��̼� Ŭ���� ����ð�
    vector<float>				m_AnimUpdateTime;       // �ִϸ��̼� ���� �����ð�

    int							m_CurFrameIdx;          // ���� �������� ������
    int							m_NextFrameIdx;         // ���� ������ �ε���
    float						m_Ratio;                // �� �����Ӱ� ���൵ ����

    bool                        m_Finish;


    vector<Matrix>				m_vecFinalBoneMat;      // �� ������ŭ ��� ����
    CStructuredBuffer*          m_pBoneFinalMatBuffer;  // CS�� ������ �� ��� ����
    bool						m_bFinalMatUpdate;      // ������Ʈ üũ��

public:
    void finaltick();
    void UpdateData();
    void ClearData();
    void check_mesh(Ptr<CMesh> _pMesh);


public:
    void CreateAnimation3D(const string& _strAnimName, int _clipIdx, float _startTime, float _endTime);
    void CreateAnimation3D(const string& _strAnimName, int _clipIdx, int _startFrame, int _endFrame); // �Ⱦ�

public: // GUI�� �����Ű�� �Լ�
    const string& GetAnimName() { return m_strAnimName; }
    int GetAnimClipIdx() { return m_AnimClipIdx; }    
    CStructuredBuffer* GetFinalBoneMat() { return m_pBoneFinalMatBuffer; }
    const float& GetStartTime() { return m_StartTime; }
    const float& GetEndTime() { return m_EndTime; }
    const int& GetCurTime() { return m_AnimUpdateTime[m_AnimClipIdx]; }
    const int& GetCurFrame() { return m_CurFrameIdx; }

public: // �ִϸ����Ϳ��� ����ϴ� �Լ�
    bool IsFinish() { return m_Finish; }
    void Reset() { m_AnimUpdateTime[m_AnimClipIdx] = m_StartTime; m_Finish = false; }

public:

    void SaveToLevelFile(FILE* _File);
    void LoadFromLevelFile(FILE* _File);


    CLONE(CAnim3D);
public:
    CAnim3D();
    ~CAnim3D();

    friend class CAnimator3D;
};


#pragma once
#include "CComponent.h"

#include "ptr.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CMesh.h"

class CAnim3D;
class CStructuredBuffer;
class CAnimator3D : public CComponent
{
private:
	const vector<tMTBone>*		m_pVecBones;
	const vector<tMTAnimClip>*	m_pVecClip;

	map<wstring, CAnim3D*>		m_mapAnim;  // Animation 목록
	CAnim3D*					m_pCurAnim; // 현재 재생중인 Animation
	bool						m_bRepeat;  // 반복

private:
	

	vector<float>				m_vecClipUpdateTime;
	vector<Matrix>				m_vecFinalBoneMat;
	int							m_iFrameCount;
	double						m_dCurTime;
	int							m_iCurClip;

	int							m_iFrameIdx;
	int							m_iNextFrameIdx;
	float						m_fRatio;

	CStructuredBuffer*			m_pBoneFinalMatBuffer;
	bool						m_bFinalMatUpdate;

public:
	virtual void finaltick() override;
	void UpdateData();
	void ClearData();



public:
	void CreateAnimation3D(const wstring& _strAnimName, const vector<tMTBone>* _bones, const vector<tMTAnimClip>* _clip,
		// 클립 인덱스, 시작 타임라인, 종료 타임라인
		int _clipIdx, float _startTime, float _endTime);


public:
	void SetBones(const vector<tMTBone>* _vecBones) { m_pVecBones = _vecBones; m_vecFinalBoneMat.resize(m_pVecBones->size()); }
	void SetAnimClip(const vector<tMTAnimClip>* _vecAnimClip);

	// 사용 안하고 있음
	void SetClipTime(int _iClipIdx, float _fTime) { m_vecClipUpdateTime[_iClipIdx] = _fTime; }

	CStructuredBuffer* GetFinalBoneMat() { return m_pBoneFinalMatBuffer; }
	UINT GetBoneCount() { return (UINT)m_pVecBones->size(); }

private:
	void check_mesh(Ptr<CMesh> _pMesh);

public:
	virtual void SaveToLevelFile(FILE* _pFile) override;
	virtual void LoadFromLevelFile(FILE* _pFile) override;
	CLONE(CAnimator3D);
public:
	CAnimator3D();
	CAnimator3D(const CAnimator3D& _origin);
	~CAnimator3D();
};


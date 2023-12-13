#pragma once
#include "CRes.h"

class CMesh : public CRes
{
private:
	ComPtr<ID3D11Buffer>	m_VB;
	D3D11_BUFFER_DESC		m_VBDesc = {};
	UINT					m_VtxCount = 0;

	ComPtr<ID3D11Buffer>	m_IB;
	D3D11_BUFFER_DESC		m_IBDesc = {};
	UINT					m_IdxCount = 0;

	// 시스템메모리
	void* m_pVtxSys = nullptr;
	void* m_pIdxSys = nullptr;

public:
	void Create(void* _VtxSysMem, UINT _iVtxCount, void* _IdxSysMem, UINT _IdxCount);

public:
	void render();
	void render_particle(UINT _iParticleCount);

private:
	virtual void UpdateData() override;

private:
	virtual int Load(const wstring& _strFilePath) { return S_OK; }
public:
	virtual int Save(const wstring& _strRelativePath) { return S_OK; }

public:
	CMesh(bool _bEngine = false);
	~CMesh();
};


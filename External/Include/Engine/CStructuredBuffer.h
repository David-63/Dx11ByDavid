#pragma once
#include "CEntity.h"

class CStructuredBuffer : public CEntity
{
private:
    ComPtr<ID3D11Buffer>                m_SB;   // register binding
    ComPtr<ID3D11ShaderResourceView>    m_SRV;
    ComPtr<ID3D11UnorderedAccessView>   m_UAV;

    ComPtr<ID3D11Buffer>                m_SB_CPU_Read;  // GPU -> Sys
    ComPtr<ID3D11Buffer>                m_SB_CPU_Write; // Sys -> GPU

    D3D11_BUFFER_DESC                   m_desc;

    UINT                                m_elementSize = 0;
    UINT                                m_elementCount = 0;

    SB_TYPE                             m_SBType;
    bool                                m_isSysAccess;

    UINT                                m_recentRegisterNum;

public:
    void Create(UINT _iElementSize, UINT _iElementCount, SB_TYPE _Type, bool _bUseSysAccess, void* _pSysMem = nullptr);
    void SetData(void* _pSrc, UINT _iSize = 0);
    void GetData(void* _pDst);

    // PIPELINE_STAGE
    void UpdateData(UINT _iRegisterNum, UINT _iPipeLineStage);
    void UpdateData_CS(UINT _iRegisterNum, bool _IsShaderRes);

    void Clear();
    void Clear_CS(bool _IsShaderRes);

    UINT GetElementSize() { return m_elementSize; }
    UINT GetElementCount() { return m_elementCount; }
    UINT GetBufferSize() { return m_elementSize * m_elementCount; }


    CLONE_DISABLE(CStructuredBuffer);
public:
    CStructuredBuffer();
    ~CStructuredBuffer();
};


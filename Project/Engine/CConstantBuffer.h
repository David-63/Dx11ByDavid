#pragma once
#include "CEntity.h"

class CConstantBuffer : public CEntity
{
private:
    ComPtr<ID3D11Buffer>    m_CB;
    D3D11_BUFFER_DESC       m_desc = {};
    const UINT              m_registerNum;

    UINT                    m_elementSize = 0;
    UINT                    m_elementCount = 0;


public:
    void Create(UINT _iElementSize, UINT _iElementCount);
    void SetData(void* _pSrc, UINT _iSize = 0);
    void UpdateData();
    void UpdateData_CS();



    CLONE_DISABLE(CConstantBuffer);
public:
    CConstantBuffer(UINT _iRegisterNum);
    ~CConstantBuffer();
};


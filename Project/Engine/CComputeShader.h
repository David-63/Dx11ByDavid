#pragma once
#include "CShader.h"

class CComputeShader : public CShader
{
private:
    ComPtr<ID3D11ComputeShader>     m_CS;
    ComPtr<ID3DBlob>                m_CSBlob;

protected:
    // 쉐이더에 전달할 상수 데이터
    tMtrlConst                      m_Const;

    // 그룹 개수
    UINT                            m_iGroupX = 1;
    UINT                            m_iGroupY = 1;
    UINT                            m_iGroupZ = 1;

    // 그룹 1개당 스레드 개수
    UINT                            m_iGroupPerThreadX = 1;
    UINT                            m_iGroupPerThreadY = 1;
    UINT                            m_iGroupPerThreadZ = 1;

public:
    void CreateComputeShader(const wstring& _strFileName, const string& _strFuncName);
    void Execute();

private:
    virtual void UpdateData() = 0;
    virtual void Clear() = 0;


    CLONE_DISABLE(CComputeShader);
public:
    CComputeShader();
    ~CComputeShader();
};


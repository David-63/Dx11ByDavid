#pragma once
#include "CShader.h"

class CComputeShader : public CShader
{
private:
    ComPtr<ID3D11ComputeShader>     m_CS;
    ComPtr<ID3DBlob>                m_CSBlob;

protected:
    // ���̴��� ������ ��� ������
    tMtrlConst                      m_Const;

    // �׷� ����
    UINT                            m_iGroupX = 1;
    UINT                            m_iGroupY = 1;
    UINT                            m_iGroupZ = 1;

    // �׷� 1���� ������ ����
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


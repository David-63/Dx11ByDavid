#pragma once
#include "CRes.h"

#include "ptr.h"
#include "CTexture.h"
#include "CGraphicsShader.h"

class CMaterial : public CRes
{
private:
    Ptr<CTexture>           m_arrTex[TEX_END];
    Ptr<CGraphicsShader>    m_shader;
    tMtrlConst              m_const = {};



public:
    void SetScalarParam(SCALAR_PARAM _Param, const void* _Src);
    void SetTexParam(TEX_PARAM _Param, const Ptr<CTexture>& _Tex);

    void GetScalarParam(SCALAR_PARAM _param, void* _pData);
    Ptr<CTexture> GetTexParam(TEX_PARAM _param) { return m_arrTex[(UINT)_param]; }



    void SetShader(Ptr<CGraphicsShader> _Shader) { m_shader = _Shader; }
    Ptr<CGraphicsShader> GetShader() { return m_shader; }

    virtual void UpdateData() override;

private:
    virtual int Load(const wstring& _strFilePath);
public:
    virtual int Save(const wstring& _strRelativePath);

public:
    CLONE(CMaterial);

public:
    CMaterial(bool _bEngine = false);
    ~CMaterial();
};


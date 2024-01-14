#pragma once
#include "CRenderComponent.h"

class CDecal :
    public CRenderComponent
{
private:
    Ptr<CTexture>   m_DecalTex;

    bool            m_bDeferred;
    bool            m_bEmissive;


public:
    // 지연렌더링 설정에 다라 Mtrl 변경
    void SetDeferredDecal(bool _bDeferred);

    // 데칼을 광원으로 취급할것인지 아닌지
    void ActivateEmissive(bool _bActivate) { m_bEmissive = _bActivate; }

public:
    virtual void finaltick() override;
    virtual void render() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CDecal);
public:
    CDecal();
    ~CDecal();
};


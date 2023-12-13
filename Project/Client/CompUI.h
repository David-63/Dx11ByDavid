#pragma once
#include "UI.h"

#include <Engine\ptr.h>
#include <Engine\CRes.h>

class CGameObject;
class CompUI : public UI
{
private:
    CGameObject*            m_Target = nullptr;
    const COMPONENT_TYPE    m_compType;

public:
    void SetTarget(CGameObject* _Target);

    CGameObject* GetTarget() { return m_Target; }

    COMPONENT_TYPE GetCompType() { return m_compType; }

    void GetResKey(Ptr<CRes> _Res, char* _Buff, size_t _BufferSize);

public:
    virtual int render_update() override;


public:
    CompUI(const string& _Name, COMPONENT_TYPE _Type);
    ~CompUI();
};

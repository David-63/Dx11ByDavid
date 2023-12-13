#pragma once
#include "UI.h"

#include <Engine/ptr.h>
#include <Engine/CRes.h>

class CGameObject;
class CompUI;
class ResUI;
class ScriptUI;
class InspectorUI : public UI
{
private:
    CGameObject*        m_pTargetObj = nullptr;

    CompUI*        m_arrComUI[(UINT)COMPONENT_TYPE::END] = {};
    ResUI*              m_arrResUI[(UINT)RES_TYPE::END] = {};
    Ptr<CRes>           m_pTargetRes;
    vector<ScriptUI*>   m_vecScriptUI;

public:
    virtual void init() override;
    virtual void tick() override;
    virtual int render_update() override;

public:
    void SetTargetObject(CGameObject* _Target);
    void SetTargetResource(Ptr<CRes> _Res);

private:
    void ClearTargetObject();
    void ClearTargetResource();

public:
    InspectorUI();
    ~InspectorUI();
};

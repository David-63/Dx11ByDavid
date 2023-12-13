#pragma once
#include "CompUI.h"

#include <Engine/CScript.h>

class ScriptUI : public CompUI
{
private:
    CScript*    m_pTargetScript = nullptr;
    string      m_strScriptName;

public:
    virtual int render_update() override;

public:
    void SetScript(CScript* _Script);

public:
    ScriptUI();
    ~ScriptUI();
};


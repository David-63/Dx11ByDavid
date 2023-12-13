#pragma once
#include "UI.h"

class MenuUI : public UI
{
public:
    virtual void finaltick() override;
    virtual int render_update() override;

private:
    void CreateEmptyObject();
    void CreateEmptyMaterial();
    void AddComponent(COMPONENT_TYPE _type);
    void AddScript(const wstring& _strScriptName);

public:
    MenuUI();
    ~MenuUI();
};

#pragma once
#include "ResUI.h"

class MaterialUI : public ResUI
{
private:
    TEX_PARAM m_eSelected = TEX_PARAM::TEX_0;

public:
    virtual int render_update() override;

public:
    void SelectTexture(DWORD_PTR _Key);

private:
    void SelectShader(DWORD_PTR _data);

public:
    MaterialUI();
    ~MaterialUI();
};


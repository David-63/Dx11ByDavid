#pragma once
#include "CompUI.h"

class MeshRenderUI : public CompUI
{
public:
    virtual int render_update() override;

public:
    void SelectMesh(DWORD_PTR _Key);
    void SelectMaterial(DWORD_PTR _Key);

public:
    MeshRenderUI();
    ~MeshRenderUI();
};

#pragma once
#include "CRenderComp.h"

class CMeshRender : public CRenderComp
{
public:
    virtual void finaltick() override;
    virtual void render() override;

    CLONE(CMeshRender);
public:
    CMeshRender();
    ~CMeshRender();
};


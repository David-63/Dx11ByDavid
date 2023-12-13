#pragma once
#include "CompUI.h"

class CGameObject;
class TransformUI : public CompUI
{
public:
    virtual int render_update() override;

public:
    TransformUI();
    ~TransformUI();
};


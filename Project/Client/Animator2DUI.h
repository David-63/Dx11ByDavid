#pragma once
#include "CompUI.h"

class Animator2DUI : public CompUI
{
public:
    virtual int render_update() override;

public:
    Animator2DUI();
    ~Animator2DUI();
};


#pragma once
#include "CompUI.h"

class Light2DUI : public CompUI
{
public:
    virtual int render_update() override;

public:
    Light2DUI();
    ~Light2DUI();
};


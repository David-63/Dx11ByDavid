#pragma once
#include "CompUI.h"

class Collider2DUI : public CompUI
{
public:
    virtual int render_update() override;

public:
    Collider2DUI();
    ~Collider2DUI();
};


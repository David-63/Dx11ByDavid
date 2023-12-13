#pragma once
#include "CompUI.h"

class TilemapUI : public CompUI
{
public:
    virtual int render_update() override;

public:
    TilemapUI();
    ~TilemapUI();
};


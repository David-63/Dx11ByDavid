#pragma once
#include "CompUI.h"

class CameraUI : public CompUI
{
public:
    virtual int render_update() override;

public:
    CameraUI();
    ~CameraUI();
};


#pragma once
#include "CompUI.h"
class ParticleSystemUI : public CompUI
{
public:
    virtual int render_update() override;

public:
    ParticleSystemUI();
    ~ParticleSystemUI();
};


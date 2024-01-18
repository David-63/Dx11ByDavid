#pragma once
#include "ComponentUI.h"

class Animator3DUI : public ComponentUI
{
private:
    vector<const char*> m_Anims;
public:
    virtual int render_update() override;

public:
    void AnimList();

public:
    Animator3DUI();
    ~Animator3DUI();
};

#include "pch.h"
#include "ParticleSystemUI.h"

ParticleSystemUI::ParticleSystemUI() : CompUI("##ParticleSystem", COMPONENT_TYPE::TILEMAP)
{
    SetName("ParticleSystem");
}
ParticleSystemUI::~ParticleSystemUI() { }

int ParticleSystemUI::render_update()
{
    if (FALSE == CompUI::render_update())
        return FALSE;
    return TRUE;
}

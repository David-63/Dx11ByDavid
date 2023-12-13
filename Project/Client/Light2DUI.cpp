#include "pch.h"
#include "Light2DUI.h"

Light2DUI::Light2DUI() 
    : CompUI("##Light2D", COMPONENT_TYPE::LIGHT2D)
{
    SetName("Light2D");
}
Light2DUI::~Light2DUI() 
{ }

int Light2DUI::render_update()
{
    if (FALSE == CompUI::render_update())
        return FALSE;

    return TRUE;
}
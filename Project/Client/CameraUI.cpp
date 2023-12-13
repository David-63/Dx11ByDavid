#include "pch.h"
#include "CameraUI.h"

CameraUI::CameraUI() : CompUI("##Camera", COMPONENT_TYPE::CAMERA)
{
    SetName("Camera");
}
CameraUI::~CameraUI() { }

int CameraUI::render_update()
{
    if (FALSE == CompUI::render_update())
        return FALSE;

    return TRUE;
}

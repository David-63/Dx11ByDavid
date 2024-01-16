#include "pch.h"
#include "Animator3DUI.h"


Animator3DUI::Animator3DUI() : ComponentUI("##Animator3D", COMPONENT_TYPE::ANIMATOR3D)
{
	SetName("Animator3D");
}

Animator3DUI::~Animator3DUI()
{
}

int Animator3DUI::render_update()
{
	if (FALSE == ComponentUI::render_update())
		return FALSE;



	return TRUE;
}
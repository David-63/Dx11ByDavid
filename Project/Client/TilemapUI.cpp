#include "pch.h"
#include "TilemapUI.h"

TilemapUI::TilemapUI() : CompUI("##Tilemap", COMPONENT_TYPE::TILEMAP)
{
	SetName("Tilemap");
}
TilemapUI::~TilemapUI() { }

int TilemapUI::render_update()
{
	if (FALSE == CompUI::render_update())
		return FALSE;

	return TRUE;
}

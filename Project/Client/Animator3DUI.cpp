#include "pch.h"
#include "Animator3DUI.h"


#include <Engine\CGameObject.h>
#include <Engine/CAnimator3D.h>

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

	int iClipCount = GetTarget()->Animator3D()->GetAnimClip()->size();
	tMTAnimClip  iClip = GetTarget()->Animator3D()->GetCurClip();
	float fCurTime = GetTarget()->Animator3D()->GetCurTime();
	int curFrame = GetTarget()->Animator3D()->GetCurFrame();

	ImGui::Text("AnimClipCount %i", iClipCount);
	ImGui::Text("TimeLength %f", static_cast<float>(iClip.dTimeLength));
	ImGui::Text("StartTime %f", static_cast<float>(iClip.dStartTime));
	ImGui::Text("EndTime %f", static_cast<float>(iClip.dEndTime));
	ImGui::Text("UpdateTime %f", static_cast<float>(fCurTime));
		
	ImGui::Text("FrameLenght %i", iClip.iFrameLength);
	ImGui::Text("StratFrame %i", iClip.iStartFrame);
	ImGui::Text("EndFrame %i", iClip.iEndFrame);
	ImGui::Text("UpdateFrame %i", curFrame);

	return TRUE;
}
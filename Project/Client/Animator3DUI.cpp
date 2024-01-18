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

	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "Select Anims");
	AnimList();

	tMTAnimClip  iClip = GetTarget()->Animator3D()->GetCurClip();


	int iClipCount = GetTarget()->Animator3D()->GetAnimClip()->size();
	float fStartTime = GetTarget()->Animator3D()->GetStartTime();
	float fEndTime = GetTarget()->Animator3D()->GetEndTime();
	float fCurTime = GetTarget()->Animator3D()->GetCurTime();
	int curFrame = GetTarget()->Animator3D()->GetCurFrame();

	if (ImGui::TreeNode("Animation Info"))
	{
		ImGui::Text("Start : %.1f | End : %.1f", fStartTime, fEndTime);
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "UpdateTime	%.1f", fCurTime);
		ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "UpdateFrame % i", curFrame);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("Clip Info"))
	{
		ImGui::Text("AnimClipCount %i", iClipCount);
		ImGui::Text("Clip TimeLength %.1f", static_cast<float>(iClip.dTimeLength));
		ImGui::Text("Clip FrameLenght %i", iClip.iFrameLength);
		ImGui::TreePop();
	}

	return TRUE;
}

void Animator3DUI::AnimList()
{
	map<string, CAnim3D*> anims = GetTarget()->Animator3D()->GetAnims();
	for (const auto& anim : anims)
	{
		m_Anims.push_back(anim.second->GetAnimName().c_str());
	}

	static int item_current_idx = 0; // Here we store our selection data as an index.
	const char* combo_preview_value = m_Anims[item_current_idx];  // Pass in the preview value visible before opening the combo (it could be anything)
	if (ImGui::BeginCombo("Anim Key List", combo_preview_value))
	{
		for (int idx = 0; idx < m_Anims.size(); idx++)
		{
			const bool is_selected = (item_current_idx == idx);
			if (ImGui::Selectable(m_Anims[idx], is_selected))
			{
				item_current_idx = idx;
				GetTarget()->Animator3D()->Play(m_Anims[idx], true);
			}

			// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	m_Anims.clear();
}

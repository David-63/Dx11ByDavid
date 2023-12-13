#include "pch.h"
#include "CompUI.h"

#include <Engine\CGameObject.h>

CompUI::CompUI(const string& _Name, COMPONENT_TYPE _Type)
	: UI(_Name), m_compType(_Type) { }
CompUI::~CompUI(){ }

int CompUI::render_update()
{
	if (nullptr == m_Target || nullptr == m_Target->GetComponent(m_compType))
		return FALSE;

	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f / 7.0f, 0.6f, 0.6f));
	ImGui::Button(GetName().c_str());
	ImGui::PopStyleColor(3);
	ImGui::PopID();

	return TRUE;
}


void CompUI::SetTarget(CGameObject* _Target)
{
	m_Target = _Target;

	if (nullptr == m_Target)
	{
		SetActive(false);
		return;
	}

	if (nullptr == m_Target->GetComponent(m_compType))
	{
		SetActive(false);
	}
	else
	{
		SetActive(true);
	}
}

void CompUI::GetResKey(Ptr<CRes> _Res, char* _Buff, size_t _BufferSize)
{
	memset(_Buff, 0, sizeof(char) * _BufferSize);

	if (nullptr == _Res)
		return;

	wstring wstrKey = _Res->GetKey();
	string	strKey = string(wstrKey.begin(), wstrKey.end());
	memcpy(_Buff, strKey.data(), sizeof(char) * strKey.length());
}
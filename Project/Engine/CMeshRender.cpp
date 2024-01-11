#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"
#include "CAnimator2D.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)		
{
}

CMeshRender::~CMeshRender()
{
}

void CMeshRender::finaltick()
{
}

void CMeshRender::render()
{	
	if (nullptr == GetMesh() || nullptr == GetMaterial(0))
		return;

	// Transform �� UpdateData ��û
	Transform()->UpdateData();

	// Animator2D ������Ʈ�� �ִٸ�
	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}

	for (size_t idx = 0; idx < GetMtrlCount(); ++idx)
	{
		// ���� ������Ʈ
		GetMaterial(idx)->UpdateData();

		// ����
		GetMesh()->render(idx);
	}

	// Animation ���� ���� ����
	if (Animator2D())
		Animator2D()->Clear();
}
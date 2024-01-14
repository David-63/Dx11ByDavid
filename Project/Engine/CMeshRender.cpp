#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"
#include "CAnimator2D.h"
#include "CAnimator3D.h"

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

	// Transform 에 UpdateData 요청
	Transform()->UpdateData();

	// Animator2D 컴포넌트가 있다면
	if (Animator2D())
	{
		Animator2D()->UpdateData();
	}
	
	if (Animator3D())
	{
		Animator3D()->UpdateData();

		for (UINT idx = 0; idx < GetMtrlCount(); ++idx)
		{
			if (nullptr == GetMaterial(idx))
				continue;

			GetMaterial(idx)->SetAnim3D(true);
			GetMaterial(idx)->SetBoneCount(Animator3D()->GetBoneCount());
		}
	}

	UINT iSubsetCount = GetMesh()->GetSubsetCount();

	for (size_t idx = 0; idx < iSubsetCount; ++idx)
	{
		if (nullptr != GetMaterial(idx))
		{
			// 재질 업데이트
			GetMaterial(idx)->UpdateData();

			// 렌더
			GetMesh()->render(idx);
		}		
	}

	// Animation 관련 정보 제거
	if (Animator2D())
		Animator2D()->Clear();
	if (Animator3D())
		Animator3D()->ClearData();
}
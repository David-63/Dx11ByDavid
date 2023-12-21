#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>
//
//#include <Script\CPlayerScript.h>
//#include <Script\CMonsterScript.h>

//#include "CLevelSaveLoad.h"


//#include <Engine/CSetColorShader.h>


void CreateTestLevel()
{
	//Ptr<CSound> pSound = CResMgr::GetInst()->FindRes<CSound>(L"sound\\BGM_Stage1.wav");
	//pSound->Play(1, 0.5f, false);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Background");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"TestObj");
	pCurLevel->GetLayer(31)->SetName(L"ViewPort UI");


	// Main Camera Object 생성
	{
		CGameObject* pMainCam = new CGameObject;
		pMainCam->SetName(L"MainCamera");

		pMainCam->AddComponent(new CTransform);
		pMainCam->AddComponent(new CCamera);

		pMainCam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
		pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
		pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.

		SpawnGameObject(pMainCam, Vec3(0.f, 0.f, 0.f), L"Default");
		// UI cameara
		CGameObject* pUICam = new CGameObject;
		pUICam->SetName(L"UICamera");

		pUICam->AddComponent(new CTransform);
		pUICam->AddComponent(new CCamera);

		pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		pUICam->Camera()->SetCameraIndex(1);		// Sub 카메라로 지정
		pUICam->Camera()->SetLayerMask(31, true);	// 31번 레이어만 체크

		SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), L"Default");
	}

	


	// 광원 추가
	{
		/*CGameObject* pLightObj = new CGameObject;
		pLightObj->SetName(L"Point Light");

		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CLight2D);
		pLightObj->Transform()->SetRelativeRot(Vec3(0.f, 0.f, XM_PI / 2.f));
		pLightObj->Light2D()->SetLightType(LIGHT_TYPE::POINT);
		pLightObj->Light2D()->SetLightDiffuse(Vec3(1.f, 1.f, 1.f));
		pLightObj->Light2D()->SetRadius(500.f);

		SpawnGameObject(pLightObj, Vec3(0.f, 0.f, 0.f), L"Default");*/
	}


	// 오브젝트 생성
	{
		CGameObject* pParent = new CGameObject;
		pParent->SetName(L"Player");
		pParent->AddComponent(new CTransform);
		pParent->AddComponent(new CMeshRender);
		pParent->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 200.f));
		pParent->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pParent->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"));
		SpawnGameObject(pParent, Vec3(0.f, 0.f, 500.f), L"Player");
	}


	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"TestObj");
}

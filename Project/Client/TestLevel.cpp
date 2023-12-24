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

	
	{
		// SkyBox 추가
		CGameObject* pSkyBox = new CGameObject;
		pSkyBox->SetName(L"SkyBox");

		pSkyBox->AddComponent(new CTransform);
		pSkyBox->AddComponent(new CSkyBox);

		pSkyBox->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));
		pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::CUBE);
		pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\SkyWater.dds"));

		SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), L"Default");
	}

	// 광원 추가
	{
		CGameObject* pLightObj = new CGameObject;
		pLightObj->SetName(L"Directional Light");

		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CLight3D);

		pLightObj->Transform()->SetRelativeRot(Vec3(XM_PIDIV4, XM_PIDIV4, 0.f));
		pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
		pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));	
		pLightObj->Light3D()->SetLightAmbient(Vec3(0.15f, 0.15f, 0.15f));

		SpawnGameObject(pLightObj, Vec3(-500.f, -250.f, 0.f), 0);


		pLightObj = new CGameObject;
		pLightObj->SetName(L"Point Light 2");

		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CLight3D);

		pLightObj->Light3D()->SetLightType(LIGHT_TYPE::POINT);
		pLightObj->Light3D()->SetLightColor(Vec3(0.2f, 0.2f, 1.f));
		pLightObj->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));
		pLightObj->Light3D()->SetRadius(1000.f);

		SpawnGameObject(pLightObj, Vec3(500.f, -250.f, 0.f), 0);
	}


	// 오브젝트 생성
	{
		// 메인 오므젝트
		CGameObject* pPlayer = new CGameObject;
		pPlayer->SetName(L"Player");
		pPlayer->AddComponent(new CTransform);
		pPlayer->AddComponent(new CMeshRender);
		pPlayer->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 200.f));
		pPlayer->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));
		pPlayer->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		pPlayer->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\tile\\TILE_01.tga"));
		pPlayer->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\tile\\TILE_01_N.tga"));

		SpawnGameObject(pPlayer, Vec3(0.f, 0.f, 500.f), L"Player");


		// 배경
		CGameObject* pGround = new CGameObject;
		pGround->SetName(L"Background");
		pGround->AddComponent(new CTransform);
		pGround->AddComponent(new CMeshRender);

		pGround->Transform()->SetRelativeScale(Vec3(2000.f, 2000.f, 1.f));
		pGround->Transform()->SetRelativeRot(Vec3(XM_PI / 2.f, 0.f, 0.f));

		pGround->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"CubeMesh"));
		pGround->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"));

		SpawnGameObject(pGround, Vec3(0.f, -500.f, 0.f), L"Background");
	}

	// 충돌 시킬 레이어 짝 지정
	CCollisionMgr::GetInst()->LayerCheck(L"Player", L"TestObj");
}

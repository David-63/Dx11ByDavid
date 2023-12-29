#include "pch.h"
#include "TestLevel.h"

#include <Engine\CLevelMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>
#include <Engine\CGameObject.h>
#include <Engine\components.h>

#include <Engine\CResMgr.h>
#include <Engine\CCollisionMgr.h>
#include "CLevelSaveLoad.h"


#include <Engine/CSetColorShader.h>
#include <Script/CPlanetScript.h>
#include <Script/CCameraMoveScript.h>

void CreateTestLevel()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurLevel();
	pCurLevel->ChangeState(LEVEL_STATE::STOP);

	// Layer 이름설정
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"background");
	pCurLevel->GetLayer(2)->SetName(L"star");
	pCurLevel->GetLayer(3)->SetName(L"planet");
	pCurLevel->GetLayer(31)->SetName(L"ViewPort UI");

	// camera
	{
		// Main Camera Object 생성
		CGameObject* pMainCam = new CGameObject;
		pMainCam->SetName(L"MainCamera");

		pMainCam->AddComponent(new CTransform);
		pMainCam->AddComponent(new CCamera);
		pMainCam->AddComponent(new CCameraMoveScript);


		pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		pMainCam->Camera()->SetCameraIndex(0);		// MainCamera 로 설정
		pMainCam->Camera()->SetLayerMaskAll(true);	// 모든 레이어 체크
		pMainCam->Camera()->SetLayerMask(31, false);// UI Layer 는 렌더링하지 않는다.
		pMainCam->Camera()->SetFar(20000.f);
		SpawnGameObject(pMainCam, Vec3(0.f, 0.f, -3000.f), 0);

		//// UI cameara
		//CGameObject* pUICam = new CGameObject;
		//pUICam->SetName(L"UICamera");

		//pUICam->AddComponent(new CTransform);
		//pUICam->AddComponent(new CCamera);

		//pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		//pUICam->Camera()->SetCameraIndex(1);		// Sub 카메라로 지정
		//pUICam->Camera()->SetLayerMask(31, true);	// 31번 레이어만 체크

		//SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), 0);
	}


	// SkyBox 추가
	{
		CGameObject* pSkyBox = new CGameObject;
		pSkyBox->SetName(L"SkyBox");

		pSkyBox->AddComponent(new CTransform);
		pSkyBox->AddComponent(new CSkyBox);

		pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100));
		pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::SPHERE);
		pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\Sky02.jpg"));

		SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);
	}

	// 광원 추가
	{
		CGameObject* pLightObj = new CGameObject;
		pLightObj->SetName(L"Point Light 1");

		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CLight3D);

		//pLightObj->Transform()->SetRelativeRot(Vec3(XM_PI / 4.f, XM_PI / 4.f, 0.f));
		pLightObj->Light3D()->SetLightType(LIGHT_TYPE::POINT);
		pLightObj->Light3D()->SetRadius(40000.f);
		pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
		pLightObj->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));

		SpawnGameObject(pLightObj, Vec3(0.f, 0.f, 0.f), 0);

		pLightObj = new CGameObject;
		pLightObj->SetName(L"Directional Light");

		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CLight3D);

		pLightObj->Transform()->SetRelativeRot(Vec3(XM_PI / 4.f, XM_PI / 4.f, 0.f));
		pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
		pLightObj->Light3D()->SetLightColor(Vec3(0.1f, 0.1f, 0.1f));
		pLightObj->Light3D()->SetLightAmbient(Vec3(0.2f, 0.2f, 0.2f));

		SpawnGameObject(pLightObj, Vec3(0.f, 0.f, 0.f), 0);
	}




	// sun
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"Sun");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);
		
		pObject->Transform()->SetRelativeScale(Vec3(1550.f, 1550.f, 1550.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));

		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\sunmap.jpg"));
		int isImissive = 1;
		planetMtrl->SetScalarParam(INT_0, &isImissive);
		
		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(0.15f);

		SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), 2);
	}
	
	// mercury
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"mercury");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(150.f, 150.f, 150.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\mercurymap.jpg"));
		//planetMtrl->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\mercurybump.jpg"));


		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(1.5f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.9f);
		SpawnGameObject(pObject, Vec3(2300.f, 0.f, 0.f), 3);
	}

	// venus
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"venus");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(220.f, 220.f, 220.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.2f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\venusmap.jpg"));
		//planetMtrl->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\venusbump.jpg"));

		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(1.f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.8f);
		SpawnGameObject(pObject, Vec3(2900.f, 0.f, 0.f), 3);
	}

	// earth
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"earth");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(300.f, 300.f, 300.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.4f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		
		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\earthmap1k.jpg"));
		//planetMtrl->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\earthbump1k.jpg"));
		
		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(0.7f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.7f);
		SpawnGameObject(pObject, Vec3(3700.f, 0.f, 0.f), 3);


		CGameObject* pObject2 = new CGameObject;
		pObject2->SetName(L"cloud");
		pObject2->AddComponent(new CTransform);
		pObject2->AddComponent(new CMeshRender);

		pObject2->Transform()->SetRelativeScale(Vec3(1.1f, 1.1f, 1.1f));
		pObject2->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
		pObject2->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));

		pObject2->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject2->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"));

		planetMtrl = pObject2->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\earthcloudmap.jpg"));
		pObject->AddChild(pObject2);


		CGameObject* moon = new CGameObject;
		moon->SetName(L"moon");
		moon->AddComponent(new CTransform);
		moon->AddComponent(new CMeshRender);
		moon->AddComponent(new CPlanetScript);

		moon->Transform()->SetRelativeScale(Vec3(0.4f, 0.4f, 0.4f));
		moon->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));
		moon->Transform()->SetRelativePos(Vec3(0.f, 1.4f, 0.f));
		
		moon->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		moon->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		planetMtrl = moon->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\lroc_color_poles_1k.jpg"));
		
		sunScript = moon->GetScript<CPlanetScript>();
	
		sunScript->SetMoveSpeed(4.8f);
		sunScript->SetSatellite();
		sunScript->SetRadius(1.4f);
		pObject->AddChild(moon);
	}

	// mars
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"mars");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(170.f, 170.f, 170.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.45f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		
		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\mars_1k_color.jpg"));
		//planetMtrl->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\mars_1k_topo.jpg"));

		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(1.f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.6f);
		SpawnGameObject(pObject, Vec3(4500.f, 0.f, 0.f), 3);
	}

	// jupiter
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"jupiter");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(550.f, 550.f, 550.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));

		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\jupiter2_1k.jpg"));

		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(1.f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.65f);
		SpawnGameObject(pObject, Vec3(5500.f, 0.f, 0.f), 3);
	}

	// saturn
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"saturn");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(450.f, 450.f, 450.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.6f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		
		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\saturnmap.jpg"));

		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(1.f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.5f);
		SpawnGameObject(pObject, Vec3(6700.f, 0.f, 0.f), 3);
	}

	// uranus
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"uranus");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(360.f, 360.f, 360.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 1.7f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		
		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\uranusmap.jpg"));

		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(1.2f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.55f);
		SpawnGameObject(pObject, Vec3(7900.f, 0.f, 0.f), 3);
	}

	// neptune
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"neptune");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(400.f, 400.f, 400.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.5f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		
		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\neptunemap.jpg"));

		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(0.6f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.3f);
		SpawnGameObject(pObject, Vec3(8700.f, 0.f, 0.f), 3);
	}

	// pluto
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"pluto");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);
		pObject->AddComponent(new CPlanetScript);

		pObject->Transform()->SetRelativeScale(Vec3(280.f, 280.f, 280.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		
		Ptr<CMaterial> planetMtrl = pObject->MeshRender()->GetDynamicMaterial();
		planetMtrl->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\plutomap1k.jpg"));
		//planetMtrl->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\solar\\plutobump1k.jpg"));

		CPlanetScript* sunScript = pObject->GetScript<CPlanetScript>();
		sunScript->SetRotateSpeed(2.5f);
		sunScript->SetOrbit();
		sunScript->SetMoveSpeed(0.4f);
		SpawnGameObject(pObject, Vec3(9900.f, 0.f, 0.f), 3);
	}

}

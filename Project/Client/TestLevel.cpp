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

	// Layer �̸�����
	pCurLevel->GetLayer(0)->SetName(L"Default");
	pCurLevel->GetLayer(1)->SetName(L"Background");
	pCurLevel->GetLayer(2)->SetName(L"Player");
	pCurLevel->GetLayer(3)->SetName(L"Objects");
	pCurLevel->GetLayer(31)->SetName(L"ViewPort UI");

	// camera
	{
		// Main Camera Object ����
		CGameObject* pMainCam = new CGameObject;
		pMainCam->SetName(L"MainCamera");

		pMainCam->AddComponent(new CTransform);
		pMainCam->AddComponent(new CCamera);
		pMainCam->AddComponent(new CCameraMoveScript);


		pMainCam->Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		pMainCam->Camera()->SetCameraIndex(0);		// MainCamera �� ����
		pMainCam->Camera()->SetLayerMaskAll(true);	// ��� ���̾� üũ
		pMainCam->Camera()->SetLayerMask(31, false);// UI Layer �� ���������� �ʴ´�.
		pMainCam->Camera()->SetFar(20000.f);
		SpawnGameObject(pMainCam, Vec3(0.f, 0.f, -3000.f), 0);

		// UI cameara
		CGameObject* pUICam = new CGameObject;
		pUICam->SetName(L"UICamera");

		pUICam->AddComponent(new CTransform);
		pUICam->AddComponent(new CCamera);

		pUICam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
		pUICam->Camera()->SetCameraIndex(1);		// Sub ī�޶�� ����
		pUICam->Camera()->SetLayerMask(31, true);	// 31�� ���̾ üũ
		pUICam->Camera()->TurnDeferredCamera(false);
		SpawnGameObject(pUICam, Vec3(0.f, 0.f, 0.f), 0);
	}
	// SkyBox �߰�
	{
		CGameObject* pSkyBox = new CGameObject;
		pSkyBox->SetName(L"SkyBox");

		pSkyBox->AddComponent(new CTransform);
		pSkyBox->AddComponent(new CSkyBox);

		pSkyBox->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 100));
		pSkyBox->SkyBox()->SetSkyBoxType(SKYBOX_TYPE::CUBE);
		pSkyBox->SkyBox()->SetSkyBoxTexture(CResMgr::GetInst()->FindRes<CTexture>(L"texture\\skybox\\SkyWater.dds"));

		SpawnGameObject(pSkyBox, Vec3(0.f, 0.f, 0.f), 0);
	}

	// ���� �߰�
	{
		CGameObject* pLightObj = new CGameObject;
		pLightObj->SetName(L"Directional Light");

		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CLight3D);

		pLightObj->Transform()->SetRelativeRot(Vec3(XM_PI / 4.f, XM_PI / 4.f, 0.f));
		pLightObj->Light3D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
		pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
		pLightObj->Light3D()->SetLightAmbient(Vec3(0.05f, 0.05f, 0.05f));


		SpawnGameObject(pLightObj, Vec3(-2000, 2000.f, -2000.f), 0);

		/*pLightObj = new CGameObject;
		pLightObj->SetName(L"Point Light 1");
		pLightObj->AddComponent(new CTransform);
		pLightObj->AddComponent(new CLight3D);

		pLightObj->Light3D()->SetLightType(LIGHT_TYPE::POINT);
		pLightObj->Light3D()->SetRadius(500.f);
		pLightObj->Light3D()->SetLightColor(Vec3(1.f, 1.f, 1.f));
		pLightObj->Light3D()->SetLightAmbient(Vec3(0.f, 0.f, 0.f));

		SpawnGameObject(pLightObj, Vec3(0.f, -750.f, 0.f), 0);	*/	
	}

	// player
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"Player");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);		

		pObject->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1000.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"SphereMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));
		pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\tile\\TILE_01.tga"));
		pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\tile\\TILE_01_N.tga"));

		SpawnGameObject(pObject, Vec3(0.f, 0.f, 0.f), L"Player");
	}

	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"maskObj");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);

		pObject->Transform()->SetRelativeScale(Vec3(1000.f, 1000.f, 1000.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3DMtrl"));
		pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_0, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\tile\\TILE_01.tga"));
		pObject->MeshRender()->GetMaterial()->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\tile\\TILE_01_N.tga"));

		SpawnGameObject(pObject, Vec3(0.f, -250.f, 0.f), L"ViewPort UI");
	}

	// Background
	{
		CGameObject* pObject = new CGameObject;
		pObject->SetName(L"Plane");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CMeshRender);

		pObject->Transform()->SetRelativeScale(Vec3(8000.f, 8000.f, 8000.f));
		pObject->Transform()->SetRelativeRot(Vec3(XM_PI / 2.f, 0.f, 0.f));

		pObject->MeshRender()->SetMesh(CResMgr::GetInst()->FindRes<CMesh>(L"RectMesh"));
		pObject->MeshRender()->SetMaterial(CResMgr::GetInst()->FindRes<CMaterial>(L"Std3D_DeferredMtrl"));

		SpawnGameObject(pObject, Vec3(0.f, -1000.f, 0.f), L"Background");

		pObject = new CGameObject;
		pObject->SetName(L"Decal");
		pObject->AddComponent(new CTransform);
		pObject->AddComponent(new CDecal);

		pObject->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 200.f));
		pObject->Transform()->SetRelativeRot(Vec3(0.f, 0.f, 0.f));

		pObject->Decal()->SetDeferredDecal(true);
		pObject->Decal()->ActivateEmissive(false);
		pObject->Decal()->GetMaterial()->SetTexParam(TEX_1, CResMgr::GetInst()->FindRes<CTexture>(L"texture\\MagicCircle.png"));

		SpawnGameObject(pObject, Vec3(0.f, -1000.f, 0.f), L"Background");
	}
}

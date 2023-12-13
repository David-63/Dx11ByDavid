#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CLevelMgr.h"
#include "CCollisionMgr.h"
#include "CRenderMgr.h"
#include "CEventMgr.h"
#include "CFontMgr.h"

CEngine::CEngine() { }
CEngine::~CEngine() { }

int CEngine::init(HWND _hWnd, UINT _iWidth, UINT _iHeight)
{
	m_hWnd = _hWnd;
	m_vResolution = Vec2((float)_iWidth, (float)_iHeight);
	

	// �ػ󵵿� �´� �۾����� ũ�� ����
	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - _iWidth / 2;
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - _iHeight / 2;

	RECT windRect;
	windRect.left = centerScreenX;
	windRect.top = centerScreenY;
	windRect.right = windRect.left + _iWidth;
	windRect.bottom = windRect.top+ _iHeight;

	ShowWindow(m_hWnd, SW_SHOW);
	AdjustWindowRect(&windRect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hWnd, nullptr, windRect.left, windRect.top, windRect.right - windRect.left, windRect.bottom - windRect.top, 0);
	
	



	// Device �ʱ�ȭ
	if (FAILED(CDevice::GetInst()->init(m_hWnd, _iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"Device �ʱ�ȭ ����", L"����", MB_OK);
		return E_FAIL;
	}


	// Manager �ʱ�ȭ
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CResMgr::GetInst()->init();
	CRenderMgr::GetInst()->init();
	CFontMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();

	return S_OK;
}

void CEngine::progress()
{	
	tick();
	render();	
	CEventMgr::GetInst()->tick();
}

void CEngine::tick()
{
	// Manager Tick
	CResMgr::GetInst()->tick();
	CTimeMgr::GetInst()->tick(); // DT(DeltaTime), FPS ���ϱ�
	CKeyMgr::GetInst()->tick();

	// FMOD Update
	CSound::g_pFMOD->update();

	// Level Update	
	CLevelMgr::GetInst()->tick();

	// Level ���� GameObject ���� �������� ���ؼ� �߻��� �浹�� üũ�Ѵ�.
	CCollisionMgr::GetInst()->tick();
}

void CEngine::render()
{
	CRenderMgr::GetInst()->render();	
}

// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Client.h"

//#include <Engine/Device.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// com 객체 초기화
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Failed to call CoInitialize.", L"에러", MB_OK);
		return -1;
	}

	// 앤진 객체 생성	
	if (!(CEngine::GetInst()->init(hInstance, L"David's game project", L"DavidClass", 1600, 900)))
		return -1;

	while (true == CEngine::GetInst()->ProcessMessages())
	{
		CEngine::GetInst()->progress();

		//Device::GetInst()->Present();
	}

	return 0;
}

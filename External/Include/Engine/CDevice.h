#pragma once
#include "ptr.h"
#include "CTexture.h"

class CConstantBuffer;
class CDevice : public CSingleton<CDevice>
{
private:
	ComPtr<ID3D11Device>			m_device;		// GPU 메모리 할당
	ComPtr<ID3D11DeviceContext>		m_context;		// GPU 제어, 렌더링, 동작 수행
	ComPtr<IDXGISwapChain>			m_swapChain;

	ComPtr<ID3D11SamplerState>		m_Sampler[3];
	ComPtr<ID3D11RasterizerState>	m_RSState[(UINT)RS_TYPE::END];
	ComPtr<ID3D11DepthStencilState>	m_DSState[(UINT)DS_TYPE::END];
	ComPtr<ID3D11BlendState>		m_BSState[(UINT)BS_TYPE::END];

	// 렌더타겟 해상도
	Vec2							m_renderResolution;
	CConstantBuffer*				m_arrConstBuffer[(UINT)CB_TYPE::END] = {};

private:
	int CreateSwapChain();
	int CreateView();
	int CreateSampler();
	int CreateRasterizerState();
	int CreateDepthStencilState();
	int CreateBlendState();
	void CreateConstBuffer();

public:
	int init(HWND _hWnd, UINT _iWidth, UINT _iHeight);

	void Present() { m_swapChain->Present(0, 0); }

	Vec2 GetRenderResolution() { return m_renderResolution; }

	ID3D11Device* GetDevice() { return m_device.Get(); }
	ID3D11DeviceContext* GetDeviceContext() { return m_context.Get(); }
	CConstantBuffer* GetConstBuffer(CB_TYPE _Type) { return m_arrConstBuffer[(UINT)_Type]; }

	ComPtr<ID3D11RasterizerState> GetRSState(RS_TYPE _Type) { return m_RSState[(UINT)_Type]; }
	ComPtr<ID3D11DepthStencilState> GetDSState(DS_TYPE _Type) { return m_DSState[(UINT)_Type]; }
	ComPtr<ID3D11BlendState> GetBSState(BS_TYPE _Type) { return m_BSState[(UINT)_Type]; }



public:
	CDevice();
	~CDevice();
};


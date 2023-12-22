#include "pch.h"
#include "CMRT.h"
#include "CDevice.h"

CMRT::CMRT() { }
CMRT::~CMRT() { }

void CMRT::Create(Ptr<CTexture>* _arrRTTex, UINT _RTCount, Ptr<CTexture> _DSTex)
{
	for (UINT idx = 0; idx < _RTCount; idx++)
	{
		m_arrRT[idx] = _arrRTTex[idx];
	}
	m_RTCount = _RTCount;
	m_DSTex = _DSTex;
}

void CMRT::ClearTarget()
{
	for (UINT idx = 0; idx < m_RTCount; idx++)
	{
		CONTEXT->ClearRenderTargetView(m_arrRT[idx]->GetRTV().Get(), m_ClearColor[idx]);
	}
	if (nullptr != m_DSTex)
	{
		CONTEXT->ClearDepthStencilView(m_DSTex->GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0.f);
	}
}

void CMRT::OMSet(bool _isStay)
{
	ID3D11RenderTargetView* arrRTV[8] = {};
	for (UINT idx = 0; idx < m_RTCount; idx++)
	{
		arrRTV[idx] = m_arrRT[idx]->GetRTV().Get();
	}

	if (nullptr != m_DSTex)
	{
		CONTEXT->OMSetRenderTargets(m_RTCount, arrRTV, m_DSTex->GetDSV().Get());
	}
	else
	{
		ComPtr<ID3D11DepthStencilView> pDSV = nullptr;
		if (_isStay)
		{
			CONTEXT->OMGetRenderTargets(0, nullptr, pDSV.GetAddressOf());
		}
		CONTEXT->OMSetRenderTargets(m_RTCount, arrRTV, pDSV.Get());
	}
}
#include "pch.h"
#include "CRenderMgr.h"

#include "CStructuredBuffer.h"
#include "CMRT.h"

#include "CResMgr.h"
#include "CTexture.h"

#include "CDevice.h"

void CRenderMgr::init()
{
    // Light2DBuffer 구조화 버퍼 생성
    m_light2DBuffer = new CStructuredBuffer;
    m_light2DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);
    // Light3DBuffer 구조화 버퍼 생성
    m_light3DBuffer = new CStructuredBuffer;
    m_light3DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);

    createMRT();
}

void CRenderMgr::createMRT()
{
    Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
    // ===================
    // SwapChain MRT 만들기
    // ===================
    {
        m_MRT[(UINT)MRT_TYPE::SWAPCHAIN] = new CMRT;
        Ptr<CTexture> arrRTTex[8] = {};
        arrRTTex[0] = CResMgr::GetInst()->FindRes<CTexture>(L"RenderTargetTex");
        Ptr<CTexture> pDSTex = CResMgr::GetInst()->FindRes<CTexture>(L"DepthStencilTex");

        m_MRT[(UINT)MRT_TYPE::SWAPCHAIN]->Create(arrRTTex, 1, pDSTex);
        m_MRT[(UINT)MRT_TYPE::SWAPCHAIN]->SetClearColor(Vec4(0.3f, 0.8f, 0.24f, 1.0f), 0);
    }

    // ==================
    // Deferred MRT 만들기
    // ==================
    {
        m_MRT[(UINT)MRT_TYPE::DEFERRED] = new CMRT;
        Ptr<CTexture> arrRTTex[8] = {};

        arrRTTex[0] = CResMgr::GetInst()->CreateTexture(L"ColorTargetTex", vResolution.x, vResolution.y
            , DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET);

        arrRTTex[1] = CResMgr::GetInst()->CreateTexture(L"NormalTargetTex", vResolution.x, vResolution.y
            , DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET);

        arrRTTex[2] = CResMgr::GetInst()->CreateTexture(L"PositionTargetTex", vResolution.x, vResolution.y
            , DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET);

        arrRTTex[3] = CResMgr::GetInst()->CreateTexture(L"EmissiveTargetTex", vResolution.x, vResolution.y
            , DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET);

        arrRTTex[4] = CResMgr::GetInst()->CreateTexture(L"DataTargetTex", vResolution.x, vResolution.y
            , DXGI_FORMAT_R32G32B32A32_FLOAT, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET);

        m_MRT[(UINT)MRT_TYPE::DEFERRED]->Create(arrRTTex, 5, nullptr);
    }

    // ===============
    // Light MRT 만들기
    // ===============
    {
        m_MRT[(UINT)MRT_TYPE::LIGHT] = new CMRT;
        Ptr<CTexture> arrRTTex[8] = {};

        arrRTTex[0] = CResMgr::GetInst()->CreateTexture(L"DiffuseTargetTex", vResolution.x, vResolution.y
            , DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET);

        arrRTTex[1] = CResMgr::GetInst()->CreateTexture(L"SpecularTargetTex", vResolution.x, vResolution.y
            , DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET);

        m_MRT[(UINT)MRT_TYPE::LIGHT]->Create(arrRTTex, 2, nullptr);
    }
}

void CRenderMgr::clearMRT()
{
    for (UINT idx = 0; idx < (UINT)MRT_TYPE::END; idx++)
    {
        if (nullptr != m_MRT[idx])
            m_MRT[idx]->ClearTarget();
    }
}

#include "pch.h"
#include "CRenderMgr.h"

#include "CStructuredBuffer.h"
#include "CMRT.h"

#include "CResMgr.h"
#include "CTexture.h"

void CRenderMgr::init()
{
    // Light2DBuffer ����ȭ ���� ����
    m_light2DBuffer = new CStructuredBuffer;
    m_light2DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);
    // Light3DBuffer ����ȭ ���� ����
    m_light3DBuffer = new CStructuredBuffer;
    m_light3DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);

    CreateMRT();
}

void CRenderMgr::CreateMRT()
{
    // ====================
    // SwapChain MRT �����
    // ====================
    {
        m_MRT[(UINT)MRT_TYPE::SWAPCHAIN] = new CMRT;

        Ptr<CTexture> arrRTTex[8] = {};
        arrRTTex[0] = CResMgr::GetInst()->FindRes<CTexture>(L"RenderTargetTex");

        Ptr<CTexture> pDSTex = CResMgr::GetInst()->FindRes<CTexture>(L"DepthStencilTex");

        m_MRT[(UINT)MRT_TYPE::SWAPCHAIN]->Create(arrRTTex, 1, pDSTex);
    }

}
#include "pch.h"
#include "CRenderMgr.h"

#include "CDevice.h"
#include "CConstantBuffer.h"
#include "CStructuredBuffer.h"

#include "CCamera.h"
#include "CLight2D.h"

#include "CResMgr.h"
#include "CMRT.h"

CRenderMgr::CRenderMgr()
{
    Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
    m_RTCopyTex = CResMgr::GetInst()->CreateTexture(L"RTCopyTex"
        , (UINT)vResolution.x, (UINT)vResolution.y
        , DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE
        , D3D11_USAGE_DEFAULT);

    CResMgr::GetInst()->FindRes<CMaterial>(L"GrayMtrl")->SetTexParam(TEX_0, m_RTCopyTex);

    CResMgr::GetInst()->FindRes<CMaterial>(L"DistortionMtrl")->SetTexParam(TEX_0, m_RTCopyTex);
}

CRenderMgr::~CRenderMgr()
{
    if (nullptr != m_light2DBuffer)
        delete m_light2DBuffer;
    if (nullptr != m_light3DBuffer)
        delete m_light3DBuffer;
    DeleteArray(m_MRT);
}



void CRenderMgr::render()
{    UpdateData();

    m_MRT[(UINT)MRT_TYPE::SWAPCHAIN]->OMSet();
    (this->*RENDER_FUNC)();

    clear();
}


void CRenderMgr::render_play()
{
    clearMRT();
    m_MRT[(UINT)MRT_TYPE::SWAPCHAIN]->OMSet();

    for (size_t idx = 0; idx < m_vecCam.size(); ++idx)
    {
        if (nullptr == m_vecCam[idx])
            continue;

        m_vecCam[idx]->SortObject();
        m_vecCam[idx]->render();
    }
}

void CRenderMgr::render_editor()
{
    clearMRT();
    m_MRT[(UINT)MRT_TYPE::SWAPCHAIN]->OMSet();

    m_editorCam->SortObject();
    m_editorCam->render();
}


int CRenderMgr::RegisterCamera(CCamera* _Cam, int _idx)
{
    if (m_vecCam.size() <= _idx)
    {
        m_vecCam.resize(_idx + 1);
    }

    m_vecCam[_idx] = _Cam;
    return _idx;
}

void CRenderMgr::SetRenderFunc(bool _IsPlay)
{
    if (_IsPlay)
        RENDER_FUNC = &CRenderMgr::render_play;
    else
        RENDER_FUNC = &CRenderMgr::render_editor;
}

void CRenderMgr::CopyRenderTarget()
{
    Ptr<CTexture> pRTTex = CResMgr::GetInst()->FindRes<CTexture>(L"RenderTargetTex");
    CONTEXT->CopyResource(m_RTCopyTex->GetTex2D().Get(), pRTTex->GetTex2D().Get());
}

void CRenderMgr::UpdateData()
{
    // GlobalData 에 광원 개수정보 세팅
    g_globalData.Light2DCount = static_cast<UINT>(m_vecLight2D.size());
    g_globalData.Light3DCount = static_cast<UINT>(m_vecLight3D.size());

    // 구조화버퍼의 크기가 모자라면 더 크게 새로 만든다.
    if (m_light2DBuffer->GetElementCount() < m_vecLight2DInfo.size())
    {
        m_light2DBuffer->Create(sizeof(tLightInfo), static_cast<UINT>(m_vecLight2DInfo.size()), SB_TYPE::READ_ONLY, true);
    }

    // 구조화버퍼로 광원 데이터를 옮긴다.
    m_light2DBuffer->SetData(m_vecLight2DInfo.data(), sizeof(tLightInfo) * static_cast<UINT>(m_vecLight2DInfo.size()));
    m_light2DBuffer->UpdateData(12, PIPELINE_STAGE::PS_PIXEL);

    // 구조화버퍼의 크기가 모자라면 더 크게 새로 만든다.
    if (m_light3DBuffer->GetElementCount() < m_vecLight3DInfo.size())
    {
        m_light3DBuffer->Create(sizeof(tLightInfo), static_cast<UINT>(m_vecLight3DInfo.size()), SB_TYPE::READ_ONLY, true);
    }

    // 구조화버퍼로 광원 데이터를 옮긴다.
    m_light3DBuffer->SetData(m_vecLight3DInfo.data(), sizeof(tLightInfo) * static_cast<UINT>(m_vecLight3DInfo.size()));
    m_light3DBuffer->UpdateData(13, PIPELINE_STAGE::PS_PIXEL);


    // 전역 상수 데이터 바인딩
    CConstantBuffer* pGlobalBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::GLOBAL);
    pGlobalBuffer->SetData(&g_globalData, sizeof(tGlobal));
    pGlobalBuffer->UpdateData();
    pGlobalBuffer->UpdateData_CS();
}


void CRenderMgr::clear()
{
    m_vecLight2D.clear();
    m_vecLight2DInfo.clear();
    m_vecLight3D.clear();
    m_vecLight3DInfo.clear();
}

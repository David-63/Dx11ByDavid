#include "pch.h"
#include "CRenderMgr.h"

#include "CDevice.h"
#include "CConstantBuffer.h"
#include "CStructuredBuffer.h"

#include "CCamera.h"
#include "CLight2D.h"

#include "CResMgr.h"

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
}


void CRenderMgr::init()
{
    // Light2DBuffer ����ȭ ���� ����
    m_light2DBuffer = new CStructuredBuffer;
    m_light2DBuffer->Create(sizeof(tLightInfo), 10, SB_TYPE::READ_ONLY, true);
}

void CRenderMgr::render()
{
    // ������ ����
    float arrColor[4] = { 0.30f, 0.450f, 0.20f, 1.0f };
    CDevice::GetInst()->ClearTarget(arrColor);

    // ��� Ÿ�� ����    
    CDevice::GetInst()->OMSet();

    // ���� �� ���� ������ ������Ʈ �� ���ε�
    UpdateData();

    // ���� �Լ� ȣ��
    (this->*RENDER_FUNC)();

    // ���� ����
    Clear();
}


void CRenderMgr::render_play()
{
    // ī�޶� ���� ������
    for (size_t i = 0; i < m_vecCam.size(); ++i)
    {
        if (nullptr == m_vecCam[i])
            continue;

        // ��ü �з��۾�
        // - �ش� ī�޶� �� �� �ִ� ��ü(���̾� �з�)
        // - ������ ���� �з� (����->���̴�) ���̴� ������
        //   ���̴� �����ο� ���� ������ �����з�
        m_vecCam[i]->SortObject();


        m_vecCam[i]->render();
    }
}

void CRenderMgr::render_editor()
{
    // ��ü �з��۾�
    // - �ش� ī�޶� �� �� �ִ� ��ü(���̾� �з�)
    // - ������ ���� �з� (����->���̴�) ���̴� ������
    //   ���̴� �����ο� ���� ������ �����з�
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
    // GlobalData �� ���� �������� ����
    g_globalData.Light2DCount = static_cast<UINT>(m_vecLight2D.size());

    // ����ȭ������ ũ�Ⱑ ���ڶ�� �� ũ�� ���� �����.
    if (m_light2DBuffer->GetElementCount() < m_vecLight2D.size())
    {
        m_light2DBuffer->Create(sizeof(tLightInfo), static_cast<UINT>(m_vecLight2D.size()), SB_TYPE::READ_ONLY, true);
    }

    // ����ȭ���۷� ���� �����͸� �ű��.
    m_light2DBuffer->SetData(m_vecLight2D.data(), sizeof(tLightInfo) * static_cast<UINT>(m_vecLight2D.size()));
    m_light2DBuffer->UpdateData(12, PIPELINE_STAGE::PS_PIXEL);


    // ���� ��� ������ ���ε�
    CConstantBuffer* pGlobalBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::GLOBAL);
    pGlobalBuffer->SetData(&g_globalData, sizeof(tGlobal));
    pGlobalBuffer->UpdateData();
    pGlobalBuffer->UpdateData_CS();
}


void CRenderMgr::Clear()
{
    m_vecLight2D.clear();
}

#pragma once

#include "ptr.h"
#include "CTexture.h"

class CCamera;
class CLight2D;
class CLight3D;
class CStructuredBuffer;
class CMRT;

class CRenderMgr : public CSingleton<CRenderMgr>
{
    SINGLE(CRenderMgr);
private:
    vector<CCamera*>            m_vecCam;               // 현재 레벨 내에 존재하는 카메라를 등록 받아둠
    CCamera*                    m_editorCam = nullptr;  // 외부 에디터쪽에서 관리하는 카메라를 등록 받아둠

    vector<tDebugShapeInfo>     m_vecShapeInfo;

    vector<CLight2D*>           m_vecLight2D;
    vector<tLightInfo>          m_vecLight2DInfo;
    vector<CLight3D*>           m_vecLight3D;
    vector<tLightInfo>          m_vecLight3DInfo;

    CStructuredBuffer*          m_light2DBuffer = nullptr;
    CStructuredBuffer*          m_light3DBuffer = nullptr;

    CMRT*                       m_MRT[(UINT)MRT_TYPE::END];
    Ptr<CTexture>               m_RTCopyTex;
    void (CRenderMgr::*         RENDER_FUNC)(void) = nullptr;


public:
    void init();
    void render();

public:
    int RegisterCamera(CCamera* _Cam, int _idx);
    void RegisterEditorCamera(CCamera* _Cam) { m_editorCam = _Cam; }
    void SetRenderFunc(bool _IsPlay);
    UINT RegisterLight2D(CLight2D* _light2D, const tLightInfo& _info)
    {
        m_vecLight2D.push_back(_light2D);
        m_vecLight2DInfo.push_back(_info);
        return m_vecLight2D.size() - 1;
    }
    UINT RegisterLight3D(CLight3D* _light3D, const tLightInfo& _info)
    {
        m_vecLight3D.push_back(_light3D);
        m_vecLight3DInfo.push_back(_info);
        return m_vecLight3D.size() - 1;
    }
    void ClearCamera() { m_vecCam.clear(); }

    void AddDebugShapeInfo(const tDebugShapeInfo& _info) { m_vecShapeInfo.push_back(_info); }
    vector<tDebugShapeInfo>& GetDebugShapeInfo() { return m_vecShapeInfo; }

    const vector<CLight2D*>& GetLight2D() { return m_vecLight2D; }
    const vector<CLight3D*>& GetLight3D() { return m_vecLight3D; }

    CCamera* GetMainCam()
    {
        if (m_vecCam.empty())
            return nullptr;

        return m_vecCam[0];
    }

    void CopyRenderTarget();

    CMRT* GetMRT(MRT_TYPE _type) { return m_MRT[(UINT)_type]; }


private:
    void UpdateData();
    void render_play();
    void render_editor();
    void clear();


    void createMRT();
    void clearMRT();
};


#pragma once
#include "CComponent.h"

#include "CMesh.h"
#include "CMaterial.h"
#include "ptr.h"

class CRenderComp : public CComponent
{
private:
    Ptr<CMesh>              m_mesh;

    Ptr<CMaterial>          m_sharedMtrl;  // 원본 메테리얼
    Ptr<CMaterial>          m_dynamicMtrl; // SharedMaterial 복사본
    Ptr<CMaterial>          m_currentMtrl; // 현재 사용 중인 재질

public:
    virtual void render() = 0;

public:
    void SetMesh(Ptr<CMesh> _Mesh) { m_mesh = _Mesh; }
    void SetMaterial(Ptr<CMaterial> _Mtrl);

    Ptr<CMesh> GetMesh() { return m_mesh; }
    Ptr<CMaterial> GetMaterial() { return m_currentMtrl; }
    Ptr<CMaterial> GetSharedMaterial();
    Ptr<CMaterial> GetDynamicMaterial();


    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


public:
    CRenderComp(COMPONENT_TYPE _type);
    ~CRenderComp();
};

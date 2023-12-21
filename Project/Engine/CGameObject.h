#pragma once
#include "CEntity.h"

class CComponent;
class CTransform;
class CCollider2D;
class CAnimator2D;
class CLight2D;
class CLight3D;
class CCamera;
class CRenderComp;
class CMeshRender;
class CParticleSystem;
class CTilemap;
class CScript;

#define GET_COMPONENT(Type, TYPE) C##Type* Type() const { return (C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::TYPE]; }

class CGameObject : public CEntity
{
private:
    CComponent*             m_arrCom[(UINT)COMPONENT_TYPE::END] = {};
    CRenderComp*            m_renderCom = nullptr;
    vector<CScript*>        m_vecScript;

    CGameObject*            m_parent = nullptr;
    vector<CGameObject*>    m_vecChild;

    int                     m_layerIdx = -1; // 소속된 레이어 인덱스값
    bool                    m_isDead = false;
    float                   m_lifeTime = 0.0f;
    float                   m_curLifeTime = 0.0f;
    bool                    m_isLifeSpan = false;

public:
    // 레벨이 시작될 때 호출 or 시작 된 레벨에 합류할 때 호출
    void begin();
    void tick();
    virtual void finaltick();
    void render();

public:
    void AddComponent(CComponent* _Component);
    void AddChild(CGameObject* _Object);

    CComponent* GetComponent(COMPONENT_TYPE _ComType) { return m_arrCom[(UINT)_ComType]; }
    const vector<CGameObject*>& GetChild() { return m_vecChild; }

    CGameObject* GetParent() const { return m_parent; }

    GET_COMPONENT(Transform, TRANSFORM);
    GET_COMPONENT(MeshRender, MESHRENDER);
    GET_COMPONENT(ParticleSystem, PARTICLESYSTEM);
    GET_COMPONENT(Camera, CAMERA);
    GET_COMPONENT(Collider2D, COLLIDER2D);
    GET_COMPONENT(Light2D, LIGHT2D);
    GET_COMPONENT(Tilemap, TILEMAP);
    GET_COMPONENT(Animator2D, ANIMATOR2D);
    GET_COMPONENT(Light3D, LIGHT3D);

    CRenderComp* GetRenderComponent() const { return m_renderCom; }


    int GetLayerIndex() { return m_layerIdx; }

    template<typename T>
    T* GetScript();

    const vector<CScript*>& GetScripts() { return m_vecScript; }

    void SetLifeSpan(float _fTime)
    {
        if (m_isLifeSpan)
            return;

        m_lifeTime = _fTime;
        m_isLifeSpan = true;
    }

    bool IsDead() { return m_isDead; }
    bool IsAncestor(CGameObject* _Target);


private:
    void DisconnectFromParent();
    void ChangeToChildType();
    void AddParentList();


    CLONE(CGameObject)
public:
    CGameObject();
    CGameObject(const CGameObject& _Other);
    ~CGameObject();

    friend class CLayer;
    friend class CEventMgr;
};

template<typename T>
inline T* CGameObject::GetScript()
{
    for (size_t i = 0; i < m_vecScript.size(); ++i)
    {
        T* pScript = dynamic_cast<T*> (m_vecScript[i]);
        if (nullptr != pScript)
            return pScript;
    }

    return nullptr;
}

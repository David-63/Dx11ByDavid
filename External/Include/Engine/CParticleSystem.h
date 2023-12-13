#pragma once
#include "CRenderComp.h"

#include "ptr.h"
#include "CParticleUpdateShader.h"

class CStructuredBuffer;

class CParticleSystem : public CRenderComp
{
private:
    CStructuredBuffer* m_ParticleBuffer = nullptr;
    CStructuredBuffer* m_RWBuffer = nullptr;
    CStructuredBuffer* m_ModuleDataBuffer = nullptr;

    tParticleModule             m_ModuleData = {};
    Ptr<CParticleUpdateShader>  m_UpdateCS;

    float                       m_AccTime = 0.0f;

public:
    void ActiveModule(PARTICLE_MODULE _ModuleType) { m_ModuleData.ModuleCheck[(UINT)_ModuleType] = true; }
    void DeactivateModule(PARTICLE_MODULE _ModuleType) { m_ModuleData.ModuleCheck[(UINT)_ModuleType] = false; }


    // �ʴ� ���� ���� ����
    void SetSpawnRate(int _SpawnRate) { m_ModuleData.SpawnRate = _SpawnRate; }

    // ���� �� �ʱ� ���� ����
    void SetSpawnInitialColor(Vec3 _vInitialColor) { m_ModuleData.vSpawnColor = _vInitialColor; }





public:
    virtual void finaltick() override;
    virtual void render() override;

    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;

    CLONE(CParticleSystem);
public:
    CParticleSystem();
    ~CParticleSystem();
};


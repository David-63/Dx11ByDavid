#pragma once
#include "CRenderComp.h"

class CStructuredBuffer;

class CTilemap : public CRenderComp
{
private:
    UINT                m_iTileCountX = 1;  // Ÿ�� ����
    UINT                m_iTileCountY = 1;  // Ÿ�� ����
    Vec2                m_vSliceSize;       // Ÿ�� �ϳ��� ũ��(UV ����)
    vector<tTile>       m_vecTile;
    CStructuredBuffer*  m_Buffer;

public:
    virtual void finaltick() override;
    virtual void render() override;

    void UpdateData();

    void SetTileCount(UINT _iXCount, UINT _iYCount);
    void SetSliceSize(Vec2 _vSliceSize) { m_vSliceSize = _vSliceSize; }


    virtual void SaveToLevelFile(FILE* _File) override;
    virtual void LoadFromLevelFile(FILE* _File) override;


    CLONE(CTilemap);
public:
    CTilemap();
    ~CTilemap();
};


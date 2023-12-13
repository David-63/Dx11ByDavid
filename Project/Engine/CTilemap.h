#pragma once
#include "CRenderComp.h"

class CStructuredBuffer;

class CTilemap : public CRenderComp
{
private:
    UINT                m_iTileCountX = 1;  // 타일 가로
    UINT                m_iTileCountY = 1;  // 타일 세로
    Vec2                m_vSliceSize;       // 타일 하나의 크기(UV 단위)
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


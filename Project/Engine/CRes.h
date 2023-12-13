#pragma once
#include "CEntity.h"

class CRes : public CEntity
{
private:
    const RES_TYPE  m_resType;
    int             m_refCount = 0;

    wstring         m_key;
    wstring         m_relativePath;

    bool            m_isEngine;  // 엔진이 관리하는 리소스

private:
    void SetKey(const wstring& _strKey) { m_key = _strKey; }
    void SetRelativePath(const wstring& _strPath) { m_relativePath = _strPath; }

    void AddRef() { ++m_refCount; }
    void Release();

    // 리소스 바인딩
    virtual void UpdateData() = 0;

private:
    // 파일로부터 로딩
    virtual int Load(const wstring& _strFilePath) = 0;
public:
    // 파일로 저장
    virtual int Save(const wstring&) = 0;

    // 리소스는 Clone 을 구현하지 않는다.
    virtual CRes* Clone() { return nullptr; assert(nullptr); }

public:
    const wstring& GetKey() { return m_key; }
    const wstring& GetRelativePath() { return m_relativePath; }
    RES_TYPE GetResType() { return m_resType; }
    bool IsEngineRes() { return m_isEngine; }

public:
    CRes(RES_TYPE _type, bool _bEngine = false);
    CRes(const CRes& _Other);
    virtual ~CRes();

    friend class CResMgr;

    template<typename T>
    friend class Ptr;
};


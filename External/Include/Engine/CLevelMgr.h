#pragma once

class CLevel;
class CGameObject;

class CLevelMgr : public CSingleton<CLevelMgr>
{
    SINGLE(CLevelMgr);
private:
    CLevel* m_curLevel = nullptr;

public:
    CLevel* GetCurLevel() { return m_curLevel; }
    CGameObject* FindObjectByName(const wstring& _strName);
    void FindObjectByName(const wstring& _strName, vector<CGameObject*>& _Out);

    void ChangeLevel(CLevel* _NextLevel);

public:
    void init();
    void tick();
};


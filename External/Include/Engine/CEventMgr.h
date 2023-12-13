#pragma once

class CEventMgr : public CSingleton<CEventMgr>
{
    SINGLE(CEventMgr);
private:
    vector<tEvent>          m_vecEvent;
    vector<CGameObject*>    m_vecGC;

    bool                    m_levelChanged = false;

public:
    void AddEvent(const tEvent& _evn) { m_vecEvent.push_back(_evn); }
    bool IsLevelChanged() { return m_levelChanged; }

private:
    void GC_Clear();

public:
    void tick();
};


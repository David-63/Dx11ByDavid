#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr::CTimeMgr() { }
CTimeMgr::~CTimeMgr()
{
    start = std::chrono::high_resolution_clock::now();
    stop = std::chrono::high_resolution_clock::now();
}

void CTimeMgr::init()
{
    start = std::chrono::high_resolution_clock::now();
    stop = std::chrono::high_resolution_clock::now();
}

void CTimeMgr::tick()
{
    m_deltaTime = (float)this->GetMilisecondsElapsed();
    g_globalData.tDT = static_cast<float>(m_deltaTime);
    g_globalData.tAccTime += static_cast<float>(m_deltaTime);
    m_deltaTimeScaled = m_deltaTime * m_timeScale;

    this->Restart();
}

void CTimeMgr::Restart()
{
    m_isRunning = true;
    start = std::chrono::high_resolution_clock::now();
}

bool CTimeMgr::Stop()
{
    if (!m_isRunning)
        return false;
    else
    {
        stop = std::chrono::high_resolution_clock::now();
        m_isRunning = false;
        return true;
    }
}

bool CTimeMgr::Start()
{
    if (m_isRunning)
        return false;
    else
    {
        start = std::chrono::high_resolution_clock::now();
        m_isRunning = true;
        return true;
    }
}

double CTimeMgr::GetMilisecondsElapsed()
{
    if (m_isRunning)
    {
        auto elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start);
        return elapsed.count();
    }
    else
    {
        auto elapsed = std::chrono::duration<double, std::milli>(stop - start);
        return elapsed.count();
    }
}

#pragma once
class CTimeMgr : public CSingleton<CTimeMgr>
{
	SINGLE(CTimeMgr);
private:
	bool m_isRunning = false;
	float m_timeScale = 1.0f;
	double m_deltaTime = 0.0;
	double m_deltaTimeScaled = 0.0;
#ifdef _WIN32
	std::chrono::time_point<std::chrono::steady_clock> start;
	std::chrono::time_point<std::chrono::steady_clock> stop;
#else
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> stop;
#endif // _WIN32

public:
	void init();
	void tick();

public:
	void SetTimeScale(float _timeScale) { m_timeScale = _timeScale; }
	double GetDeltaTime() { return m_deltaTime; }
	double GetDeltaTimeScaled() { return m_deltaTimeScaled; }

public:
	void Restart();
	bool Stop();
	bool Start();

	double GetMilisecondsElapsed();

};


#include "Timer/Timer.h"
#include "Commons/Logger.h"

namespace sglib::timer
{

PerformanceTimer::PerformanceTimer(const TimerSpec& a_TimerSpec) : m_spec(a_TimerSpec)
{
	start = std::chrono::system_clock::now();
}

PerformanceTimer::~PerformanceTimer()
{
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsedSeconds = end - start;
	double sec = elapsedSeconds.count();
	if (m_spec.bIsLog)
	{
		SG_LOG_INFO("elapsed ms: {}", sec * 1000.0);
	}
	if (m_spec.bIsAssert)
	{
		assert(sec < m_spec.assertSeconds);
	}
}

}	 // namespace sglib::timer
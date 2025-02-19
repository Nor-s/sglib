#ifndef SGLIB_TIMER
#define SGLIB_TIMER

#include <chrono>

namespace sglib::timer
{

struct TimerSpec
{
	bool bIsLog = true;
	bool bIsAssert = false;
	double assertSeconds = 1.0;
};

class PerformanceTimer
{
public:
	PerformanceTimer(const TimerSpec& a_TimerSpec);
	~PerformanceTimer();

private:
	TimerSpec m_spec;
	std::chrono::time_point<std::chrono::system_clock> start, end;
};

template <typename Func>
void InvokeWithTimer(const TimerSpec& _timerSpec, Func _function)
{
	auto timer = PerformanceTimer(_timerSpec);
	_function();
}

}	 // namespace sglib::timer

#endif
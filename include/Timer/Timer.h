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

class ScopePerformanceTimer
{
public:
	ScopePerformanceTimer(const TimerSpec& a_TimerSpec);
	~ScopePerformanceTimer();

private:
	TimerSpec m_spec;
	std::chrono::time_point<std::chrono::system_clock> start, end;
};

template <typename Func, typename... Args>
void InvokeWithTimer(const TimerSpec& _timerSpec, Func _function, Args&&... _args)
{
	auto timer = ScopePerformanceTimer(_timerSpec);
	_function(std::forward<Args>(_args)...);
}

}	 // namespace sglib::timer

#endif
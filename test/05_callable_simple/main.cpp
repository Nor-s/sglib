#include <sglib.h>

constexpr int TEST_COUNT = 100000;

class Functor
{
public:
	int operator()(int value)
	{
		return value * 2;
	}
};

int Function(int value)
{
	return value * 2;
}

void TestFunctor()
{
	Functor functor;
	int result = 0;

	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			result += functor(i);
		}
	}
}

void TestLambda()
{
	auto lambda = [](int value) { return value * 2; };
	int result = 0;

	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			result += lambda(i);
		}
	}
}

void TestFunctionPointer()
{
	{
		int result = 0;
		int (*fp)(int) = Function;
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			result += fp(i);
		}
	}
	{
		int result = 0;
		int (*fp)(int) = [](int value) { return value * 2; };
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			result += fp(i);
		}
	}
}

void TestStdFunction()
{
	// release mode -> optimization not work
	{
		int result = 0;
		std::function<int(int)> func = Function;
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			result += func(i);
		}
	}
	{
		int result = 0;
		std::function<int(int)> func = [](int value) { return value * 2; };
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			result += func(i);
		}
	}
	{
		int result = 0;
		std::function<int(int)> func = Functor();
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			result += func(i);
		}
	}
}

int main()
{
	sglib::Logger::SetLogPrefix(TEXT("05_callable_simple"));

	SG_LOG_WARN(TEXT("TestStdFunction"));
	TestStdFunction();

	SG_LOG_WARN(TEXT("TestLambda"));
	TestLambda();

	SG_LOG_WARN(TEXT("TestFunctionPointer"));
	TestFunctionPointer();

	SG_LOG_WARN(TEXT("TestFunctor"));
	TestFunctor();
}

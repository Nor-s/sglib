#include <sglib.h>
#include <memory>

#include <chrono>
#include <vector>

class Object
{
public:
	Object() = default;
	~Object() = default;
	void DoSomething()
	{
		value++;
	}

private:
	int value = 0;
};

constexpr int TEST_COUNT = 1000000;

void TestUniquePtr()
{
	std::vector<std::unique_ptr<Object>> objects;
	objects.reserve(TEST_COUNT);

	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			objects.push_back(std::make_unique<Object>());
		}
	}
	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (auto& obj : objects)
		{
			obj->DoSomething();
		}
	}
}

void TestSharedPtr()
{
	std::vector<std::shared_ptr<Object>> objects;
	objects.reserve(TEST_COUNT);

	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			objects.push_back(std::make_shared<Object>());
		}
	}

	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (auto& obj : objects)
		{
			obj->DoSomething();
		}
	}
}

void TestRawPtr()
{
	std::vector<Object*> objects;
	objects.reserve(TEST_COUNT);

	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (int i = 0; i < TEST_COUNT; ++i)
		{
			objects.push_back(new Object());
		}
	}

	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (auto obj : objects)
		{
			obj->DoSomething();
		}
	}

	{
		sglib::timer::ScopePerformanceTimer timer{{}};
		for (auto obj : objects)
		{
			delete obj;
		}
	}
}

int main()
{
	sglib::Logger::SetLogPrefix(TEXT("04_smart_pointer_vs_raw_pointer"));

	SG_LOG_WARN(TEXT("TestUniquePtr (cons, call member function)"));
	sglib::timer::InvokeWithTimer({}, TestUniquePtr);

	SG_LOG_WARN(TEXT("TestSharedPtr (cons, call member function)"));
	sglib::timer::InvokeWithTimer({}, TestSharedPtr);

	SG_LOG_WARN(TEXT("TestRawPtr (new, call member function, delete)"));
	sglib::timer::InvokeWithTimer({}, TestRawPtr);
}

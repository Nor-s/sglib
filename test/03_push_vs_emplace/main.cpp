#include <iostream>
#include <deque>
#include <list>
#include <sglib.h>

#define TEST_COUNT 1000000

class People
{
public:
	People() = default;
	People(const People&) = default;
	People(People&&) = default;
	People& operator=(const People&) = default;
	People& operator=(People&&) = default;
	~People() = default;

	People(const std::string& name, uint8_t age, float weight, float height)
		: name(name), age(age), weight(weight), height(height)
	{
	}
	void setWeight(float w)
	{
		weight = w;
	}

private:
	std::string name;
	uint8_t age;
	float weight;
	float height;
};

template <typename T>
class Peoples
{
public:
	void reserve(size_t size)
	{
		// peoples.reserve(size);
	}

	void emplace_back_rv(People&& people)
	{
		peoples.emplace_back(std::move(people));
	}
	void emplace_back_ref(const People& people)
	{
		peoples.emplace_back(people);
	}

	void push_back_rv(People&& people)
	{
		peoples.push_back(std::move(people));
	}
	void push_back_ref(const People& people)
	{
		peoples.push_back(people);
	}

	template <typename... Args>
	void emplace_back_varargs(Args&&... args)
	{
		peoples.emplace_back(std::forward<Args>(args)...);
	}

private:
	T peoples;
};

template <typename T>
void emplace_back_copy_in(T& peoples)
{
	for (int i = 0; i < TEST_COUNT; i++)
	{
		People people("John", 20, 70.0 + i * 0.001f, 175.0);
		peoples.emplace_back_ref(people);
	}
}
template <typename T>
void emplace_back_copy_out(T& peoples)
{
	People people("John", 20, 70.0, 175.0);
	for (int i = 0; i < TEST_COUNT; i++)
	{
		people.setWeight(70.0 + i * 0.001f);
		peoples.emplace_back_ref(people);
	}
}
template <typename T>
void emplace_back_move(T& peoples)
{
	for (int i = 0; i < TEST_COUNT; i++)
	{
		People people("John", 20, 70.0 + i * 0.001f, 175.0);
		peoples.emplace_back_rv(std::move(people));
	}
}
template <typename T>
void emplace_back_move_direct(T& peoples)
{
	for (int i = 0; i < TEST_COUNT; i++)
	{
		peoples.emplace_back_rv(People("John", 20, 70.0f + i * 0.001f, 175.0));
	}
}

template <typename T>
void emplace_back_parameter(T& peoples)
{
	for (int i = 0; i < TEST_COUNT; i++)
	{
		peoples.emplace_back_varargs("John", 20, 70.0 + i * 0.001f, 175.0);
	}
}

template <typename T>
void push_back_copy_in(T& peoples)
{
	for (int i = 0; i < TEST_COUNT; i++)
	{
		People people("John", 20, 70.0 + i * 0.001f, 175.0);
		peoples.push_back_ref(people);
	}
}
template <typename T>
void push_back_copy_out(T& peoples)
{
	People people("John", 20, 70.0, 175.0);
	for (int i = 0; i < TEST_COUNT; i++)
	{
		people.setWeight(70.0 + i * 0.001f);
		peoples.push_back_ref(people);
	}
}
template <typename T>
void push_back_move(T& peoples)
{
	for (int i = 0; i < TEST_COUNT; i++)
	{
		People people("John", 20, 70.0 + i * 0.001f, 175.0);
		peoples.push_back_rv(std::move(people));
	}
}
template <typename T>
void push_back_move_direct(T& peoples)
{
	for (int i = 0; i < TEST_COUNT; i++)
	{
		peoples.push_back_rv(People("John", 20, 70.0f + i * 0.001f, 175.0));
	}
}

template <typename T>
void test()
{
	SG_LOG_WARN("emplace");
	{
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { emplace_back_copy_in(peoples); });
	}
	{
		// rank 1
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { emplace_back_copy_out(peoples); });
	}
	{
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { emplace_back_move(peoples); });
	}
	{
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { emplace_back_move_direct(peoples); });
	}
	{
		// rank 2
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { emplace_back_parameter(peoples); });
	}

	SG_LOG_WARN("push");
	{
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { push_back_copy_in(peoples); });
	}
	{
		// rank 1
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { push_back_copy_out(peoples); });
	}
	{
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { push_back_move(peoples); });
	}
	{
		T peoples;
		peoples.reserve(TEST_COUNT);
		sglib::timer::InvokeWithTimer({}, [&]() { push_back_move_direct(peoples); });
	}
}

int main()
{
	sglib::Logger::SetLogPrefix(TEXT("push_vs_emplace"));

	SG_LOG_ERROR("vector");
	test<Peoples<std::vector<People>>>();
	SG_LOG_ERROR("deque");
	test<Peoples<std::deque<People>>>();
}
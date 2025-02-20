#include <algorithm>
#include <sglib.h>

#define SIZE 20000

// Structure of Arrays
template <typename T>
struct PointList3D
{
	T x[SIZE] = {
		0,
	};
	T y[SIZE] = {
		0,
	};
	T z[SIZE] = {
		0,
	};
};

// Array of Structures
template <typename T>
struct Point3D
{
	T x = 0.0f;
	T y = 0.0f;
	T z = 0.0f;
};

template <typename T>
void updateAllPointSOA(T* p_point_SOA)
{
	auto& point_SOA = *p_point_SOA;
	for (int i = 0; i < SIZE; i++)
	{
		point_SOA.x[i] += 0.1;
		point_SOA.y[i] += 0.1;
		point_SOA.z[i] += 0.1;
	}
}

template <typename T>
void updateAllPointSOA2(T* p_point_SOA)
{
	auto& point_SOA = *p_point_SOA;
	for (int i = 0; i < SIZE; i++)
	{
		point_SOA.x[i] += 0.1;
	}
	for (int i = 0; i < SIZE; i++)
	{
		point_SOA.y[i] += 0.1;
	}
	for (int i = 0; i < SIZE; i++)
	{
		point_SOA.z[i] += 0.1;
	}
}

template <typename T>
void updateAllPointAOS(T* p_point_AOS)
{
	for (int i = 0; i < SIZE; i++)
	{
		p_point_AOS[i].x += 0.1;
		p_point_AOS[i].y += 0.1;
		p_point_AOS[i].z += 0.1;
	}
}

template <typename T>
void update_X_PointSOA(T* p_point_SOA)
{
	auto& point_SOA = *p_point_SOA;
	for (int i = 0; i < SIZE; i++)
	{
		point_SOA.x[i] += 0.1;
	}
}

template <typename T>
void update_X_PointAOS(T* p_point_AOS)
{
	for (int i = 0; i < SIZE; i++)
	{
		p_point_AOS[i].x += 0.1;
	}
}

template <typename T>
void check()
{
	PointList3D<T> point_SOA;
	Point3D<T> point_AOS[SIZE];

	SG_LOG_LOG("ALL UPDATE  SOA");
	sglib::timer::InvokeWithTimer({}, std::bind(updateAllPointSOA<PointList3D<T>>, &point_SOA));
	SG_LOG_LOG("ALL UPDATE  AOS");
	sglib::timer::InvokeWithTimer({}, std::bind(updateAllPointAOS<Point3D<T>>, point_AOS));

	SG_LOG_LOG("ALL UPDATE  SOA2");
	sglib::timer::InvokeWithTimer({}, std::bind(updateAllPointSOA2<PointList3D<T>>, &point_SOA));

	SG_LOG_LOG("ALL  X UPDATE SOA");
	sglib::timer::InvokeWithTimer({}, std::bind(update_X_PointSOA<PointList3D<T>>, &point_SOA));
	SG_LOG_LOG("ALL X UPDATE AOS");
	sglib::timer::InvokeWithTimer({}, std::bind(update_X_PointAOS<Point3D<T>>, point_AOS));
}

int main()
{
	sglib::Logger::SetLogPrefix(TEXT("SOA_VS_AOS"));
	SG_LOG_WARN("DOUBLE");
	check<double>();
	SG_LOG_WARN("FLOAT");
	check<float>();
	SG_LOG_WARN("INT");
	check<int>();
	SG_LOG_WARN("LONG LONG");
	check<long long>();
}
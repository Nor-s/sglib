#ifndef SGLIB_SINGLEINSTANCE_H
#define SGLIB_SINGLEINSTANCE_H

namespace sglib
{

template <typename T>
class SingleInstance
{
protected:
	SingleInstance() = default;

public:
	SingleInstance(SingleInstance<T>&&) = delete;
	SingleInstance(const SingleInstance<T>&) = delete;

	SingleInstance<T>& operator=(const SingleInstance<T>&) = delete;
	SingleInstance<T>& operator=(SingleInstance<T>&&) = delete;

	~SingleInstance() = default;

	static T& Get()
	{
		static T s_instance;
		return s_instance;
	}
};

}	 // namespace sglib

#endif
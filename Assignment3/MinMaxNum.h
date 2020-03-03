#pragma once
#include <limits>
#include <float.h>

namespace assignment3
{
	template <typename T>
	class MinMaxNum
	{
	public:
		static T Min();
		static T Max();
	};

	template<typename T>
	inline T MinMaxNum<T>::Min()
	{
		return std::numeric_limits<T>::min();
	}

	template<typename T>
	inline T MinMaxNum<T>::Max()
	{
		return std::numeric_limits<T>::max();
	}

	template<>
	inline float MinMaxNum<float>::Min()
	{
		return -FLT_MAX;
	}

	template<>
	inline double MinMaxNum<double>::Min()
	{
		return -DBL_MAX;
	}

}
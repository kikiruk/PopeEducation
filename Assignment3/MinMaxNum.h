#pragma once
#include <limits>
#include <float.h>

namespace assignment3
{
	template <typename T>
	class MinMaxNum
	{
	public:
		static T min();
		static T max();
	};

	template<typename T>
	inline T MinMaxNum<T>::min()
	{
		return std::numeric_limits<T>::min();
	}

	template<typename T>
	inline T MinMaxNum<T>::max()
	{
		return std::numeric_limits<T>::max();
	}

	template<>
	inline float MinMaxNum<float>::min()
	{
		return -FLT_MAX;
	}

	template<>
	inline double MinMaxNum<double>::min()
	{
		return -DBL_MAX;
	}

}
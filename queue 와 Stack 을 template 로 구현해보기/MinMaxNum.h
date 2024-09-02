#pragma once
#include <limits>
#include <float.h>

namespace assignment3
{
	template <typename T>
	class MinMaxNum
	{
	public:
		static T GetMin();
		static T GetMax();
	};

	template<typename T>
	inline T MinMaxNum<T>::GetMin()
	{
		return std::numeric_limits<T>::min();
	}

	template<typename T>
	inline T MinMaxNum<T>::GetMax()
	{
		return std::numeric_limits<T>::max();
	}

	template<>
	inline float MinMaxNum<float>::GetMin()
	{
		return -FLT_MAX;
	}

	template<>
	inline double MinMaxNum<double>::GetMin()
	{
		return -DBL_MAX;
	}

}
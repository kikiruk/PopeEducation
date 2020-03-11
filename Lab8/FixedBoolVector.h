#pragma once
#include "FixedVector.h"

namespace lab8
{
	template<uint32_t N>
	inline bool FixedVector<bool, N>::Add(const bool& data)
	{
		if (mSize == N)
			return false;
		
		mArr[mSize++] = data;
		
		return true;
	}

	//template<class T, uint32_t N>
	//inline bool FixedVector<T, N>::Remove(const T & data)
	//{
	//	for (uint32_t i = 0; i < N; i++)
	//	{
	//		if (mArr[i] == data)
	//		{
	//			if (i != mSize - 1)
	//				memcpy(mArr + i, mArr + i + 1, sizeof(T) * (N - (i + 1)));
	//
	//			memset(mArr + --mSize, 0, sizeof(T));
	//			return true;
	//		}
	//	}
	//
	//	return false;
	//}
	//
	//template<class T, uint32_t N>
	//inline const T& FixedVector<T, N>::Get(const uint32_t index) const
	//{
	//	return mArr[index];
	//}
	//
	//template<class T, uint32_t N>
	//inline T& FixedVector<T, N>::operator[](const uint32_t index)
	//{
	//	return mArr[index];
	//}
	//
	//template<class T, uint32_t N>
	//inline const int FixedVector<T, N>::GetIndex(const T & data) const
	//{
	//	for (uint32_t i = 0; i < N; i++)
	//	{
	//		if (mArr[i] == data)
	//			return i;
	//	}
	//
	//	return -1;
	//}
	//
	//template<class T, uint32_t N>
	//inline const size_t FixedVector<T, N>::GetSize() const
	//{
	//	return mSize;
	//}
	//
	//template<class T, uint32_t N>
	//inline const size_t FixedVector<T, N>::GetCapacity() const
	//{
	//	return N;
	//}
}
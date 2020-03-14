#include <cstdint>
#include <cstring>
#include <cassert>
#pragma once

namespace lab8
{
	template <class T, size_t N>
	class FixedVector
	{
	public:
		FixedVector();
		FixedVector(const FixedVector& copy);
		const FixedVector& operator=(const FixedVector& copy);

		bool Add(const T& data);
		bool Remove(const T& data);
		const T& Get(const size_t index) const;
		T& operator[](const size_t index);
		const int GetIndex(const T& data) const;
		const size_t GetSize() const;
		const size_t GetCapacity() const;

	private:
		size_t mSize;
		T mArr[N];
	};

	template<class T, size_t N>
	inline FixedVector<T, N>::FixedVector() :
		mSize(0)
	{
		memset(mArr, 0, sizeof(mArr));
	}

	template<class T, size_t N>
	inline FixedVector<T, N>::FixedVector(const FixedVector& copy) :
		mSize(copy.mSize)
	{
		memcpy(mArr, copy.mArr, sizeof(mArr));
	}

	template<class T, size_t N>
	const FixedVector<T, N>& FixedVector<T, N>::operator=(const FixedVector& copy)
	{
		if (this != &copy)
		{
			mSize = copy.mSize;
			memcpy(mArr, copy.mArr, sizeof(mArr));
		}

		return *this;
	}

	template<class T, size_t N>
	inline bool FixedVector<T, N>::Add(const T& data)
	{
		if (mSize == N)
			return false;

		mArr[mSize++] = data;

		return true;
	}



	template<class T, size_t N>
	inline bool FixedVector<T, N>::Remove(const T& data)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			if (mArr[i] == data)
			{
				if (i != mSize - 1)
					memcpy(mArr + i, mArr + i + 1, sizeof(T) * (mSize - (i + 1)));

				memset(mArr + --mSize, 0, sizeof(T));
				return true;
			}
		}

		return false;
	}

	template<class T, size_t N>
	inline const T& FixedVector<T, N>::Get(const size_t index) const
	{
		return mArr[index];
	}

	template<class T, size_t N>
	inline T& FixedVector<T, N>::operator[](const size_t index)
	{
		return mArr[index];
	}


	template<class T, size_t N>
	inline const int FixedVector<T, N>::GetIndex(const T& data) const
	{
		for (size_t i = 0; i < N; i++)
		{
			if (mArr[i] == data)
				return i;
		}

		return -1;
	}

	template<class T, size_t N>
	inline const size_t FixedVector<T, N>::GetSize() const
	{
		return mSize;
	}

	template<class T, size_t N>
	inline const size_t FixedVector<T, N>::GetCapacity() const
	{
		return N;
	}
}
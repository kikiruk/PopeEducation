#include <cstdint>
#include <cstring>
#pragma once


namespace lab8
{
	template <class T, uint32_t N>
	class FixedVector
	{
	public:
		FixedVector<T, N>();
		FixedVector<T, N>(const FixedVector<T, N>& copy);
		const FixedVector<T, N>& operator=(const FixedVector<T, N>& copy);

		bool Add(const T& data);
		bool Remove(const T& data);
		const T& Get(const uint32_t index) const;
		T& operator[](const uint32_t index);
		const int GetIndex(const T& data) const;
		const size_t GetSize() const;
		const size_t GetCapacity() const;

	private:
		uint32_t mSize;
		T mArr[N];
	};

	template<class T, size_t N>
	inline FixedVector<T, N>::FixedVector<T, N>() :
		mSize(0)
	{
		memset(mArr, 0, sizeof(T) * N);
	}

	template<class T, size_t N>
	inline FixedVector<T, N>::FixedVector<T, N>(const FixedVector<T, N>& copy) :
		mSize(copy.mSize)
	{
		memcpy(mArr, copy.mArr, sizeof(T) * N);
	}

	template<class T, size_t N>
	const FixedVector<T, N>& FixedVector<T, N>::operator=(const FixedVector<T, N>& copy)
	{
		if (this != &copy)
		{
			mSize = copy.mSize;
			memcpy(mArr, copy.mArr, sizeof(T) * N);
		}

		return *this;
	}

	template<class T, uint32_t N>
	inline bool FixedVector<T, N>::Add(const T& data)
	{
		if (mSize == N)
			return false;

		mArr[mSize++] = data;

		return true;
	}



	template<class T, uint32_t N>
	inline bool FixedVector<T, N>::Remove(const T& data)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (mArr[i] == data)
			{
				if (i != mSize - 1)
					memcpy(mArr + i, mArr + i + 1, sizeof(T) * (N - (i + 1)));

				memset(mArr + --mSize, 0, sizeof(T));
				return true;
			}
		}

		return false;
	}

	template<class T, uint32_t N>
	inline const T& FixedVector<T, N>::Get(const uint32_t index) const
	{
		return mArr[index];
	}

	template<class T, uint32_t N>
	inline T& FixedVector<T, N>::operator[](const uint32_t index)
	{
		return mArr[index];
	}


	template<class T, uint32_t N>
	inline const int FixedVector<T, N>::GetIndex(const T& data) const
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (mArr[i] == data)
				return i;
		}

		return -1;
	}

	template<class T, uint32_t N>
	inline const size_t FixedVector<T, N>::GetSize() const
	{
		return mSize;
	}

	template<class T, uint32_t N>
	inline const size_t FixedVector<T, N>::GetCapacity() const
	{
		return N;
	}
}
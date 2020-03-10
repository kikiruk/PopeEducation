#include <cstdint>
#include <cstring>
#pragma once


namespace lab8
{
	template <class T, uint32_t N>
	class FixedVector
	{
	public:
		FixedVector();
		FixedVector(const FixedVector& copy);
		const FixedVector& operator=(const FixedVector& copy);

		bool Add(const T& data);
		bool Remove(const T& data);
		const T& Get(const uint32_t index) const;
		T& operator[](const uint32_t index);
		const int GetIndex(const T& data) const;
		const size_t GetSize() const;
		const size_t GetCapacity() const;

	private:
		uint32_t size;
		T arr[N];
	};

	template<class T, size_t N>
	inline FixedVector<T, N>::FixedVector() :
		size(0)
	{
		memset(arr, 0, sizeof(T) * N);
	}

	template<class T, size_t N>
	inline FixedVector<T, N>::FixedVector(const FixedVector& copy) :
		size(copy.size)
	{
		memset(arr, 0, sizeof(T) * N);
	}

	template<class T, size_t N>
	const FixedVector<T, N>& FixedVector<T, N>::operator=(const FixedVector& copy)
	{
		if (this != &copy)
		{
			size = copy.size;
		}

		return *this;
	}

	template<class T, uint32_t N>
	inline bool FixedVector<T, N>::Add(const T& data)
	{
		if (size == N)
			return false;

		arr[size++] = data;

		return true;
	}

	template<class T, uint32_t N>
	inline bool FixedVector<T, N>::Remove(const T& data)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (arr[i] == data)
			{
				memcpy(arr + i, arr + i + 1, sizeof(T) * (N - (i + 1)));
				memset(arr + size, 0, sizeof(T));
				--size;
				return true;
			}
		}

		return false;
	}

	template<class T, uint32_t N>
	inline const T& FixedVector<T, N>::Get(const uint32_t index) const
	{
		return arr[index];
	}

	template<class T, uint32_t N>
	inline T& FixedVector<T, N>::operator[](const uint32_t index)
	{
		return arr[index];
	}

	template<class T, uint32_t N>
	inline const int FixedVector<T, N>::GetIndex(const T& data) const
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (arr[i] == data)
				return i;
		}

		return -1;
	}

	template<class T, uint32_t N>
	inline const size_t FixedVector<T, N>::GetSize() const
	{
		return size;
	}

	template<class T, uint32_t N>
	inline const size_t FixedVector<T, N>::GetCapacity() const
	{
		return N;
	}

}
#pragma once

namespace lab8
{
	template <uint32_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector<bool, N>();
		FixedVector(const FixedVector& copy);
		const FixedVector& operator=(const FixedVector& copy);
		
		bool Add(const bool data);
		bool Remove(const bool data);
		const bool Get(const uint32_t index) const;
		bool& operator[](const uint32_t index);
		const int GetIndex(const bool data) const;
		const size_t GetSize() const;
		const size_t GetCapacity() const;
	
	private:
		uint32_t mSize;
		bool mArr[N];
	};
	
	template<size_t N>
	inline FixedVector<bool, N>::FixedVector() :
		mSize(0)
	{
		memset(mArr, 0, sizeof(bool) * N);
	}
	
	template<size_t N>
	inline FixedVector<bool, N>::FixedVector(const FixedVector& copy) :
		mSize(copy.mSize)
	{
		memcpy(mArr, copy.mArr, sizeof(bool) * N);
	}
	
	template<size_t N>
	const FixedVector<bool, N>& FixedVector<bool, N>::operator=(const FixedVector& copy)
	{
		if (this != &copy)
		{
			mSize = copy.mSize;
			memcpy(mArr, copy.mArr, sizeof(bool) * N);
		}
	
		return *this;
	}
	
	
	template<uint32_t N>
	inline bool FixedVector<bool, N>::Add(const bool data)
	{
		if (mSize == N)
			return false;
	
		mArr[mSize++] = data;
	
		return true;
	}
	
	template<uint32_t N>
	inline bool FixedVector<bool, N>::Remove(const bool data)
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (mArr[i] == data)
			{
				if (i != mSize - 1)
					memcpy(mArr + i, mArr + i + 1, sizeof(bool) * (N - (i + 1)));
	
				memset(mArr + --mSize, 0, sizeof(bool));
				return true;
			}
		}
	
		return false;
	}
	
	template<uint32_t N>
	inline const bool FixedVector<bool, N>::Get(const uint32_t index) const
	{
		return mArr[index];
	}
	
	template<uint32_t N>
	inline bool& FixedVector<bool, N>::operator[](const uint32_t index)
	{
		return mArr[index];
	}
	
	template<uint32_t N>
	inline const int FixedVector<bool, N>::GetIndex(const bool data) const
	{
		for (uint32_t i = 0; i < N; i++)
		{
			if (mArr[i] == data)
				return i;
		}
	
		return -1;
	}
	
	template<uint32_t N>
	inline const size_t FixedVector<bool, N>::GetSize() const
	{
		return mSize;
	
	}
	
	template<uint32_t N>
	inline const size_t FixedVector<bool, N>::GetCapacity() const
	{
		return N;
	}

}




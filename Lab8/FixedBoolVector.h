#pragma once

namespace lab8
{
	template <size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector<bool, N>();
		FixedVector<bool, N>(const FixedVector<bool, N>& copy);
		const FixedVector<bool, N>& operator=(const FixedVector<bool, N>& copy);
		
		bool Add(const bool data);
		bool Remove(const bool data);
		const bool Get(const size_t index) const;
		bool& operator[](const size_t index);
		const int GetIndex(const bool data) const;
		const size_t GetSize() const;
		const size_t GetCapacity() const;
	
	private:
		uint8_t mSize;
		bool mArr[N];
	};
	
	template<size_t N>
	inline FixedVector<bool, N>::FixedVector<bool, N>() :
		mSize(0)
	{
		memset(mArr, 0, sizeof(bool) * N);
	}
	
	template<size_t N>
	inline FixedVector<bool, N>::FixedVector<bool, N>(const FixedVector<bool, N>& copy) :
		mSize(copy.mSize)
	{
		memcpy(mArr, copy.mArr, sizeof(bool) * N);
	}
	
	template<size_t N>
	const FixedVector<bool, N>& FixedVector<bool, N>::operator=(const FixedVector<bool, N>& copy)
	{
		if (this != &copy)
		{
			mSize = copy.mSize;
			memcpy(mArr, copy.mArr, sizeof(bool) * N);
		}
	
		return *this;
	}
	
	
	template<size_t N>
	inline bool FixedVector<bool, N>::Add(const bool data)
	{
		if (mSize == N)
			return false;
	
		mArr[mSize++] = data;
	
		return true;
	}
	
	template<size_t N>
	inline bool FixedVector<bool, N>::Remove(const bool data)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			if (mArr[i] == data)
			{
				if (i != mSize - 1)
					memcpy(mArr + i, mArr + i + 1, sizeof(bool) * (mSize - (i + 1)));
	
				memset(mArr + --mSize, 0, sizeof(bool));
				return true;
			}
		}
	
		return false;
	}
	
	template<size_t N>
	inline const bool FixedVector<bool, N>::Get(const size_t index) const
	{
		return mArr[index];
	}
	
	template<size_t N>
	inline bool& FixedVector<bool, N>::operator[](const size_t index)
	{
		return mArr[index];
	}
	
	template<size_t N>
	inline const int FixedVector<bool, N>::GetIndex(const bool data) const
	{
		for (size_t i = 0; i < N; i++)
		{
			if (mArr[i] == data)
				return i;
		}
	
		return -1;
	}
	
	template<size_t N>
	inline const size_t FixedVector<bool, N>::GetSize() const
	{
		return mSize;
	
	}
	
	template<size_t N>
	inline const size_t FixedVector<bool, N>::GetCapacity() const
	{
		return N;
	}

}




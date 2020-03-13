#pragma once
#include <cmath>

namespace lab8
{
	template <size_t N>
	class FixedVector<bool, N>
	{
	public:
		FixedVector();
		FixedVector(const FixedVector& copy);
		const FixedVector& operator=(const FixedVector& copy);
		
		bool Add(const bool data);
		bool Remove(const bool data);
		const bool Get(const size_t index) const;
		bool operator[](const size_t index);
		const int GetIndex(const bool data) const;
		const size_t GetSize() const;
		const size_t GetCapacity() const;
	
	private:
		uint32_t mSize;
		uint32_t mArr;
	};
	
	template<size_t N>
	inline FixedVector<bool, N>::FixedVector<bool, N>() :
		mSize(0),
		mArr(0)
	{
	}
	
	template<size_t N>
	inline FixedVector<bool, N>::FixedVector<bool, N>(const FixedVector<bool, N>& copy) :
		mSize(copy.mSize),
		mArr(copy.mArr)
	{
	}
	
	template<size_t N>
	const FixedVector<bool, N>& FixedVector<bool, N>::operator=(const FixedVector<bool, N>& copy)
	{
		if (this != &copy)
		{
			mSize = copy.mSize;
			mArr = copy.mArr;
		}
	
		return *this;
	}
	
	
	template<size_t N>
	inline bool FixedVector<bool, N>::Add(const bool data)
	{
		if (mSize == N)
			return false;

		if(data == true)
			mArr |= static_cast<uint32_t>(std::pow(2, mSize++));
		else
			mArr &= ~static_cast<uint32_t>(std::pow(2, mSize++));

		return true;
	}
	
	template<size_t N>
	inline bool FixedVector<bool, N>::Remove(const bool data)
	{
		for (uint32_t i = 0; i < mSize; i++)
		{
			if (((mArr | static_cast<uint32_t>(std::pow(2, i))) == mArr) == data)
			{
				for (uint32_t j = i + 1; j < mSize; j++)
				{
					if ((mArr | static_cast<uint32_t>(std::pow(2, j))) == mArr)
						mArr |= static_cast<uint32_t>(std::pow(2, j - 1));
					else
						mArr &= ~static_cast<uint32_t>(std::pow(2, j - 1));
				}
		
				--mSize;
				return true;
			}
		}

		return false;
	}
	
	template<size_t N>
	inline const bool FixedVector<bool, N>::Get(const size_t index) const
	{
		return ((mArr | static_cast<uint32_t>(std::pow(2, index))) == mArr);
	}
	
	template<size_t N>
	inline bool FixedVector<bool, N>::operator[](const size_t index)
	{
		return ((mArr | static_cast<uint32_t>(std::pow(2, index))) == mArr);
	}
	
	template<size_t N>
	inline const int FixedVector<bool, N>::GetIndex(const bool data) const
	{
		for (uint32_t i = 0; i < mSize; i++)
		{
			if (((mArr | static_cast<uint32_t>(std::pow(2, i))) == mArr) == data)
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




#pragma once

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
		uint32_t squared(uint32_t num) const;
		uint32_t mSize;
		uint32_t mArr[N / 32 + 1];
	};
	
	template<size_t N>
	inline FixedVector<bool, N>::FixedVector<bool, N>() :
		mSize(0)
	{
		memset(mArr, 0, sizeof(mArr));
	}
	
	template<size_t N>
	inline FixedVector<bool, N>::FixedVector<bool, N>(const FixedVector<bool, N>& copy) :
		mSize(copy.mSize)
	{
		memcpy(mArr, copy.mArr, sizeof(mArr));
	}
	
	template<size_t N>
	const FixedVector<bool, N>& FixedVector<bool, N>::operator=(const FixedVector<bool, N>& copy)
	{
		if (this != &copy)
		{
			mSize = copy.mSize;
			memcpy(mArr, copy.mArr, sizeof(mArr));
		}
	
		return *this;
	}
	
	
	template<size_t N>
	inline bool FixedVector<bool, N>::Add(const bool data)
	{
		if (mSize == N)
			return false;

		if(data == true)
			mArr[mSize / 32] |= squared(mSize % 32);
		else
			mArr[mSize / 32] &= ~squared(mSize % 32);

		++mSize;

		return true;
	}
	
	template<size_t N>
	inline bool FixedVector<bool, N>::Remove(const bool data)
	{
		for (uint32_t i = 0; i < mSize; i++)
		{
			if (((mArr[i / 32] | squared(i)) == mArr[i / 32]) == data)
			{
				for (uint32_t j = i + 1; j < mSize; j++)
				{
					if ((mArr[j / 32] | squared(j % 32)) == mArr[j / 32])
						mArr[(j - 1) / 32] |= squared((j - 1) % 32);
					else
						mArr[(j - 1) / 32] &= ~squared((j - 1) % 32);
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
		return ((mArr[index / 32] | squared(index % 32)) == mArr[index / 32]);
	}
	
	template<size_t N>
	inline bool FixedVector<bool, N>::operator[](const size_t index)
	{
		return ((mArr[index / 32] | squared(index % 32)) == mArr[index / 32]);
	}
	
	template<size_t N>
	inline const int FixedVector<bool, N>::GetIndex(const bool data) const
	{
		for (uint32_t i = 0; i < mSize; i++)
		{
			if (((mArr[i / 32] | squared(i % 32)) == mArr[i / 32]) == data)
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

	template<size_t N>
	inline uint32_t FixedVector<bool, N>::squared(uint32_t num) const
	{
		switch (num)
		{
		case 0:
			return 1;
			break;
		case 1:
			return 2;
			break;
		case 2:
			return 4;
			break;
		case 3:
			return 8;
			break;
		case 4:
			return 16;
			break;
		case 5:
			return 32;
			break;
		case 6:
			return 64;
			break;
		case 7:
			return 128;
			break;
		case 8:
			return 256;
			break;
		case 9:
			return 512;
			break;
		case 10:
			return 1024;
			break;
		case 11:
			return 2048;
			break;
		case 12:
			return 4096;
			break;
		case 13:
			return 8192;
			break;
		case 14:
			return 16384;
			break;
		case 15:
			return 32768;
			break;
		case 16:
			return 65536;
			break;
		case 17:
			return 131072;
			break;
		case 18:
			return 262144;
			break;
		case 19:
			return 524288;
			break;
		case 20:
			return 1048576;
			break;
		case 21:
			return 2097152;
			break;
		case 22:
			return 4194304;
			break;
		case 23:
			return 8388608;
			break;
		case 24:
			return 16777216;
			break;
		case 25:
			return 33554432;
			break;
		case 26:
			return 67108864;
			break;
		case 27:
			return 134217728;
			break;
		case 28:
			return 268435456;
			break;
		case 29:
			return 536870912;
			break;
		case 30:
			return 1073741824;
			break;
		case 31:
			return 2147483648;
			break;
		default:
			return -1;
			break;
		}
	}
}


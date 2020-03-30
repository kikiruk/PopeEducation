#pragma once

#include <memory>

namespace lab11
{
	template<typename T>
	class Storage
	{
	public:
		Storage(unsigned int length);
		Storage(unsigned int length, const T& initialValue);
		Storage(const Storage& other);
		Storage(Storage&& other);
		~Storage() = default;

		const Storage& operator=(const Storage& other);
		const Storage& operator=(Storage&& other);

		bool Update(unsigned int index, const T& data);
		const std::unique_ptr<T[]>& GetData() const;
		unsigned int GetSize() const;

	private:
		unsigned int mSize;
		std::unique_ptr<T[]> mArray;
	};

	template<typename T>
	Storage<T>::Storage(unsigned int length)
		: mSize(length)
		, mArray(new T[length])
	{
		std::memset(mArray.get(), 0, sizeof(T) * length);
	}

	template<typename T>
	Storage<T>::Storage(unsigned int length, const T& initialValue)
		: mSize(length)
		, mArray(new T[length])
	{
		for (unsigned int i = 0; i < length; i++)
			mArray[i] = initialValue;
	}

	template<typename T>
	inline Storage<T>::Storage(const Storage& other)
		: mSize(other.mSize)
		, mArray(new T[other.mSize])
	{
		std::memcpy(mArray.get(), other.mArray.get(), sizeof(T) * other.mSize);
	}

	template<typename T>
	inline Storage<T>::Storage(Storage&& other)
		: mSize(other.mSize)
		, mArray(std::move(other.mArray))
	{
		other.mSize = 0;
	}

	template<typename T>
	inline const Storage<T>& Storage<T>::operator=(const Storage& other)
	{
		if (this != &other)
		{
			mSize = other.mSize;
			mArray = new T[other.mSize];

			std::memcpy(mArray.get(), other.mArray.get(), sizeof(T) * other.mSize);
		}
		
		return *this;
	}

	template<typename T>
	inline const Storage<T>& Storage<T>::operator=(Storage&& other)
	{
		if (this != &other)
		{
			mSize = other.mSize;
			mArray = std::move(other.mArray);
			other.mSize = 0;
		}

		return *this;
	}

	template<typename T>
	bool Storage<T>::Update(unsigned int index, const T& data)
	{
		if (index >= mSize)
			return false;

		mArray[index] = data;
		return true;
	}

	template<typename T>
	const std::unique_ptr<T[]>& Storage<T>::GetData() const
	{
		return mArray;
	}

	template<typename T>
	unsigned int Storage<T>::GetSize() const
	{
		return mSize;
	}
}
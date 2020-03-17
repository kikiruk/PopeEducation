#pragma once
#include <vector>
#include <cstring>

template <class T>
class ObjectPool
{
public:
	ObjectPool(size_t maxPoolSize);
	~ObjectPool();
	ObjectPool(const ObjectPool& copy) = delete;

	ObjectPool& operator = (const ObjectPool&) = delete;
	T* const Get();
	void Return(T* const objectPointer);
	const size_t GetFreeObjectCount() const;
	const size_t GetMaxFreeObjectCount() const;

private:
	const size_t mMaxPoolSize;
	std::vector<T*> mArr;
};

template<class T>
inline ObjectPool<T>::ObjectPool(size_t maxPoolSize) :
	mMaxPoolSize(maxPoolSize)
{
	mArr.reserve(mMaxPoolSize);
}

template<class T>
inline ObjectPool<T>::~ObjectPool()
{
	for (auto it = mArr.begin(); it != mArr.end(); ++it)
	{
		delete (*it);
	}

	mArr.clear();
}

template<class T>
inline T* const ObjectPool<T>::Get()
{
	if (mArr.size() == 0)
		return new T();

	T* tmp = mArr[0];
	mArr.erase(mArr.begin());

	return tmp;
}

template<class T>
inline void ObjectPool<T>::Return(T* const objectPointer)
{
	if (mArr.size() == mMaxPoolSize)
		delete objectPointer;

	size_t size = mArr.size();
	for (size_t i = 0; i < size; i++)
	{
		if (objectPointer == mArr[i])
			return;
	}

	mArr.push_back(objectPointer);
}

template<class T>
inline const size_t ObjectPool<T>::GetFreeObjectCount() const
{
	return mArr.size();
}

template<class T>
inline const size_t ObjectPool<T>::GetMaxFreeObjectCount() const
{
	return mMaxPoolSize;
}

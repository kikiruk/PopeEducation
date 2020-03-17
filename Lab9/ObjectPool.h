#pragma once

template <class T>
class ObjectPool
{
public:
	ObjectPool(size_t maxPoolSize);
	ObjectPool(const ObjectPool& copy) = delete;
	ObjectPool& operator = (const ObjectPool&) = delete;
	
private:
	const size_t mMaxPoolSize;

};

template<class T>
inline ObjectPool<T>::ObjectPool(size_t maxPoolSize) :
	mMaxPoolSize(maxPoolSize)
{
}

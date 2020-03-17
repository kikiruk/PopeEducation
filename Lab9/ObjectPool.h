#pragma once
#include <queue>
#include <cstring>

namespace lab9
{
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
		std::queue<T*> mArr;
	};

	template<class T>
	inline ObjectPool<T>::ObjectPool(size_t maxPoolSize) :
		mMaxPoolSize(maxPoolSize)
	{}

	template<class T>
	inline ObjectPool<T>::~ObjectPool()
	{
		while (!mArr.empty())
		{
			delete mArr.front();
			mArr.pop();
		}
	}

	template<class T>
	inline T* const ObjectPool<T>::Get()
	{
		if (mArr.size() == 0)
			return new T();

		T* tmp = mArr.front();
		mArr.pop();

		return tmp;
	}

	template<class T>
	inline void ObjectPool<T>::Return(T* const objectPointer)
	{
		if (mArr.size() == mMaxPoolSize)
			delete objectPointer;

		mArr.push(objectPointer);
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
}

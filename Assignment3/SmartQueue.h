#pragma once
#include <limits>
#include <cmath>

#include "Node.h"

namespace assignment3
{
	template<typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		~SmartQueue();
		SmartQueue(const SmartQueue<T>& copy);
		const SmartQueue<T>& operator=(const SmartQueue<T>& copy);

		inline void Enqueue(const T& number);
		inline const T& Peek() const;
		inline const T Dequeue();
		inline const T& GetMax() const;
		inline const T& GetMin() const;
		inline const double GetAverage() const;
		inline const T& GetSum() const;
		inline const double GetVariance() const;
		inline const double GetStandardDeviation() const;
		inline const unsigned int GetCount() const;

	private:
		inline void copyFunc(const SmartQueue<T>& copy);

		Node<T>* mHead;
		Node<T>* mTail;
		unsigned int mCount;
		T mSum;
		Node<T>* mMaxNum;
		Node<T>* mMinNum;
	};

	template<typename T>
	SmartQueue<T>::SmartQueue() :
		mHead(nullptr),
		mTail(nullptr),
		mCount(0),
		mSum(0),
		mMaxNum(nullptr),
		mMinNum(nullptr) 
	{
	}

	template<typename T>
	SmartQueue<T>::~SmartQueue()
	{
		for (Node<T>* i = mHead; i != nullptr;)
		{
			Node<T>* tmp = i;
			i = i->mNext;
			delete tmp;
		}
	}

	template<typename T>
	SmartQueue<T>::SmartQueue(const SmartQueue<T>& copy)	:
		mCount(copy.mCount),
		mSum(copy.mSum)
	{
		copyFunc(copy);
	}

	template<typename T>
	const SmartQueue<T>& SmartQueue<T>::operator=(const SmartQueue<T>& copy)
	{
		if (this != &copy)
		{
			for (Node<T>* i = mHead; i != nullptr;)
			{
				Node<T>* tmp = i;
				i = i->mNext;
				delete tmp;
			}

			mCount = copy.mCount;
			mSum = copy.mSum;

			copyFunc(copy);
		}

		return *this;
	}

	template<typename T>
	inline void SmartQueue<T>::Enqueue(const T& number)
	{
		if (mHead == nullptr)
		{
			mHead = mTail = new Node<T>(number, nullptr);
			mMaxNum = mMinNum = mTail;
		}
		else
		{
			mTail->mNext = new Node<T>(number, nullptr);
			mTail = mTail->mNext;

			if (mMaxNum->mNumber < number)
				mMaxNum = mTail;

			if (mMinNum->mNumber > number)
				mMinNum = mTail;
		}

		mSum += number;
		++mCount;

	}

	template<typename T>
	inline const T& SmartQueue<T>::Peek() const
	{
		return mHead->mNumber;
	}

	template<typename T>
	inline const T SmartQueue<T>::Dequeue()
	{
		T answer = mHead->mNumber;

		if (mMaxNum == mHead)
		{
			mMaxNum = nullptr;
			T minNum = std::numeric_limits<T>::max();
			for (Node<T>* i = mHead->mNext; i != nullptr; i = i->mNext)
			{
				if (minNum >= i->mNumber)
				{
					minNum = i->mNumber;
					mMinNum = i;
				}
			}
		}

		if (mMinNum == mHead)
		{
			mMinNum = nullptr;
			T maxNum = std::numeric_limits<T>::min();
			for (Node<T>* i = mHead->mNext; i != nullptr; i = i->mNext)
			{
				if (maxNum <= i->mNumber)
				{
					maxNum = i->mNumber;
					mMaxNum = i;
				}
			}
		}

		if (mHead == mTail)
		{
			delete mHead;
			mHead = mTail = nullptr;
		}
		else
		{
			Node<T>* tmp = mHead;
			mHead = mHead->mNext;
			delete tmp;
		}

		mSum -= answer;
		--mCount;


		return answer;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetMax() const
	{
		if (mHead == nullptr)
			return std::numeric_limits<T>::min();

		return mMaxNum->mNumber;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetMin() const
	{
		if (mHead == nullptr)
			return std::numeric_limits<T>::max();

		return mMinNum->mNumber;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetSum() const
	{
		return mSum;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetVariance() const
	{
		double average = GetAverage();
		double deviationSquareSum = 0;

		for (Node<T>* i = mHead; i != nullptr; i = i->mNext)
			deviationSquareSum += std::pow(i->mNumber - average, 2);

		return std::round(deviationSquareSum / mCount * 1000) / 1000;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetStandardDeviation() const
	{
		double average = GetAverage();
		double standardDeviation = 0;

		for (Node<T>* i = mHead; i != nullptr; i = i->mNext)
			standardDeviation += std::pow(i->mNumber - average, 2);

		standardDeviation = sqrt(standardDeviation / mCount);

		return std::round(standardDeviation * 1000) / 1000;
	}

	template<typename T>
	inline const unsigned int SmartQueue<T>::GetCount() const
	{
		return mCount;
	}

	template<typename T>
	inline void SmartQueue<T>::copyFunc(const SmartQueue<T>& copy)
	{
		this->mHead = new Node<T>(*copy.mHead);

		Node<T>* i = this->mHead;
		Node<T>* j = copy.mHead;

		while (true)
		{
			if (j->mNext == nullptr)
			{
				mTail = i;
				break;
			}

			i->mNext = new Node<T>(*j->mNext);

			if (j == copy.mMaxNum)
				mMaxNum = i->mNext;

			if (j == copy.mMinNum)
				mMinNum = i->mNext; 

			i = i->mNext;
			j = j->mNext;
		}
	}
}
#pragma once
#include <cmath>

#include "MinMaxNum.h"
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
		inline const T GetMax() const;
		inline const T GetMin() const;
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
		T mSumOfSquared;
		Node<T>* mMaxNum;
		Node<T>* mMinNum;
	};

	template<typename T>
	SmartQueue<T>::SmartQueue() :
		mHead(nullptr),
		mTail(nullptr),
		mCount(0),
		mSum(0),
		mSumOfSquared(0),
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
			i = i->MNext;
			delete tmp;
		}
	}

	template<typename T>
	SmartQueue<T>::SmartQueue(const SmartQueue<T>& copy)	:
		mCount(copy.mCount),
		mSum(copy.mSum),
		mSumOfSquared(copy.mSumOfSquared)
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
				i = i->MNext;
				delete tmp;
			}

			mCount = copy.mCount;
			mSum = copy.mSum;
			mSumOfSquared = copy.mSumOfSquared;

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
			mTail->MNext = new Node<T>(number, nullptr);
			mTail = mTail->MNext;

			if (mMaxNum->MNumber < number)
				mMaxNum = mTail;

			if (mMinNum->MNumber > number)
				mMinNum = mTail;
		}

		mSum += number;
		mSumOfSquared += std::pow(number, 2);
		++mCount;

	}

	template<typename T>
	inline const T& SmartQueue<T>::Peek() const
	{
		return mHead->MNumber;
	}

	template<typename T>
	inline const T SmartQueue<T>::Dequeue()
	{
		T answer = mHead->MNumber;

		if (mMinNum == mHead)
		{
			mMinNum = nullptr;
			T minNum = MinMaxNum<T>::GetMax();
			for (Node<T>* i = mHead->MNext; i != nullptr; i = i->MNext)
			{
				if (minNum >= i->MNumber)
				{
					minNum = i->MNumber;
					mMinNum = i;
				}
			}
		}

		if (mMaxNum == mHead)
		{
			mMaxNum = nullptr;
			T maxNum = MinMaxNum<T>::GetMin();
			for (Node<T>* i = mHead->MNext; i != nullptr; i = i->MNext)
			{
				if (maxNum <= i->MNumber)
				{
					maxNum = i->MNumber;
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
			mHead = mHead->MNext;
			delete tmp;
		}

		mSum -= answer;
		mSumOfSquared -= std::pow(answer, 2);
		--mCount;


		return answer;
	}

	template<typename T>
	inline const T SmartQueue<T>::GetMax() const
	{
		if (mHead == nullptr)
			return MinMaxNum<T>::GetMin();

		return mMaxNum->MNumber;
	}

	template<typename T>
	inline const T SmartQueue<T>::GetMin() const
	{
		if (mHead == nullptr)
			return MinMaxNum<T>::GetMax();

		return mMinNum->MNumber;
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
		double deviationSquareSum = (mSumOfSquared / mCount) - std::pow((average), 2);

		return std::round(deviationSquareSum / mCount * 1000) / 1000;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetStandardDeviation() const
	{
		return std::sqrt(GetVariance());
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
			if (j->MNext == nullptr)
			{
				mTail = i;
				break;
			}

			i->MNext = new Node<T>(*j->MNext);

			if (j == copy.mMaxNum)
				mMaxNum = i->MNext;

			if (j == copy.mMinNum)
				mMinNum = i->MNext; 

			i = i->MNext;
			j = j->MNext;
		}
	}
}
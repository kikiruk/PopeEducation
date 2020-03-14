#pragma once
#include <cassert>
#include <cmath>

#include "MinMaxNum.h"
#include "Node.h"

namespace assignment3
{
	template<typename T>
	class QueueStack;

	template <typename T>// int, unsigned int, double, short
	class SmartStack
	{
		friend QueueStack<T>;

	public:
		SmartStack();
		SmartStack(const SmartStack<T>& copy);
		~SmartStack();

		const SmartStack<T>& operator=(const SmartStack<T>& copy);
		inline void Push(const T& data);
		inline const T Pop();
		inline const T& Peek() const;
		inline const T GetMax() const;
		inline const T GetMin() const;
		inline const double GetAverage() const;
		inline const T& GetSum() const;

		inline const double GetVariance() const;
		inline const double GetStandardDeviation() const;
		inline const unsigned int GetCount() const;

	private:
		inline void copyFunc(const SmartStack<T>& copy);

		NodeForStack<T>* mTop;
		unsigned int mCount;
		T mSum;
		double mSumOfSquared;
		T mMaxNum;
		T mMinNum;
	};


	//±¸ÇöºÎ
	template<typename T>
	SmartStack<T>::SmartStack() : 
		mTop(nullptr),
		mCount(0),
		mSum(0),
		mSumOfSquared(0),
		mMaxNum(MinMaxNum<T>::GetMin()),
		mMinNum(MinMaxNum<T>::GetMax())
	{
	}

	template<typename T>
	inline SmartStack<T>::SmartStack(const SmartStack<T>& copy) :
		mCount(copy.mCount),
		mSum(copy.mSum),
		mSumOfSquared(copy.mSumOfSquared),
		mMaxNum(copy.mMaxNum),
		mMinNum(copy.mMinNum)
	{
		copyFunc(copy);
	}

	template<typename T>
	SmartStack<T>::~SmartStack()
	{
		for (NodeForStack<T>* i = mTop; i != nullptr;)
		{
			NodeForStack<T>* tmp = i;
			i = i->MNext;
			delete tmp;
		}
	}

	template<typename T>
	inline const SmartStack<T>& SmartStack<T>::operator=(const SmartStack<T>& copy)
	{
		if (this != &copy)
		{
			for (NodeForStack<T>* i = mTop; i != nullptr;)
			{
				NodeForStack<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			mCount = copy.mCount;
			mSum = copy.mSum;
			mSumOfSquared = copy.mSumOfSquared;
			mMaxNum = copy.mMaxNum;
			mMinNum = copy.mMinNum;

			copyFunc(copy);
		}

		return *this;
	}

	template<typename T>
	inline void SmartStack<T>::Push(const T& data)
	{
		mSum += data;
		mSumOfSquared += std::pow(data, 2);
		++mCount;

		if (mTop == nullptr)
		{
			mTop = new NodeForStack<T>(data, nullptr);
			mMaxNum = mMinNum = data ;
		}
		else
		{
			mTop = new NodeForStack<T>(data, mTop);

			if (data > mMaxNum)
				mMaxNum = data;

			if (data < mMinNum)
				mMinNum = data;
		}
		
		mTop->MMaxData = mMaxNum;
		mTop->MMinData = mMinNum;
	}

	template<typename T>
	inline const T SmartStack<T>::Pop()
	{
		mSum -= mTop->MNumber;
		mSumOfSquared -= std::pow(mTop->MNumber, 2);
		--mCount;

		if (mTop->MNext != nullptr)
		{
			mMinNum = mTop->MNext->MMinData;
			mMaxNum = mTop->MNext->MMaxData;
		}
		else
		{
			mMinNum = MinMaxNum<T>::GetMax();
			mMaxNum = MinMaxNum<T>::GetMin();
		}

		T returnNum = mTop->MNumber;
		NodeForStack<T>* tmp = mTop;
		mTop = mTop->MNext;
		delete tmp;

		return returnNum;
	}

	template<typename T>
	inline const T& SmartStack<T>::Peek() const
	{
		return mTop->MNumber;
	}

	template<typename T>
	inline const T SmartStack<T>::GetMax() const
	{
		return mMaxNum;
	}

	template<typename T>
	inline const T SmartStack<T>::GetMin() const
	{
		return mMinNum;
	}

	template<typename T>
	inline const double SmartStack<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	template<typename T>
	inline const T& SmartStack<T>::GetSum() const
	{
		return mSum;
	}

	template<typename T>
	inline const double SmartStack<T>::GetVariance() const
	{
		double deviationSquareSum = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);

		return std::round(deviationSquareSum * 1000) / 1000;
	}

	template<typename T>
	inline const double SmartStack<T>::GetStandardDeviation() const
	{
		double standardDeviation = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);
		standardDeviation = std::sqrt(standardDeviation);

		return std::round(standardDeviation * 1000) / 1000;
	}

	template<typename T>
	inline const unsigned int SmartStack<T>::GetCount() const
	{
		return mCount;
	}

	template<typename T>
	inline void SmartStack<T>::copyFunc(const SmartStack<T>& copy)
	{
		NodeForStack<T> tmp(0, nullptr);
		NodeForStack<T>* j = &tmp;
		NodeForStack<T>* i = copy.mTop;

		T  minNum = MinMaxNum<T>::GetMax();
		T  maxNum = MinMaxNum<T>::GetMin();

		for (; i != nullptr; i = i->MNext, j = j->MNext)
		{
			j->MNext = new NodeForStack<T>(*i);
			j->MNext->MMaxData = i->MMaxData;
			j->MNext->MMinData = i->MMinData;

			if (i == copy.mTop)
				mTop = j->MNext;

			if (i == copy.mMaxNum)
				mMaxNum = j->MNext;

			if (i == copy.mMinNum)
				mMinNum = j->MNext;
		}
	}

}

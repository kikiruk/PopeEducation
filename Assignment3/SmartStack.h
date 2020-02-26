#pragma once
#include <cassert>
#include <limits>
#include <cmath>

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
		inline const T& GetMax() const;
		inline const T& GetMin() const;
		inline const double GetAverage() const;
		inline const T& GetSum() const;

		inline const double GetVariance() const;
		inline const double GetStandardDeviation() const;
		inline const unsigned int GetCount() const;

	private:
		inline void copyFunc(const SmartStack<T>& copy);

		Node<T>* mTop;
		unsigned int mCount;
		T mSum;
		Node<T>* mMaxNum;
		Node<T>* mMinNum;
	};


	//±¸ÇöºÎ
	template<typename T>
	SmartStack<T>::SmartStack() : 
		mTop(nullptr),
		mCount(0),
		mSum(0),
		mMaxNum(nullptr),
		mMinNum(nullptr)
	{
	}

	template<typename T>
	inline SmartStack<T>::SmartStack(const SmartStack<T>& copy) :
		mCount(copy.mCount),
		mSum(copy.mSum)
	{
		copyFunc(copy);
	}

	template<typename T>
	SmartStack<T>::~SmartStack()
	{
		for (Node<T>* i = mTop; i != nullptr;)
		{
			Node<T>* tmp = i;
			i = i->MNext;
			delete tmp;
		}
	}

	template<typename T>
	inline const SmartStack<T>& SmartStack<T>::operator=(const SmartStack<T>& copy)
	{
		if (this != &copy)
		{
			for (Node<T>* i = mTop; i != nullptr;)
			{
				Node<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			mCount = copy.mCount;
			mSum = copy.mSum;

			copyFunc(copy);
		}

		return *this;
	}

	template<typename T>
	inline void SmartStack<T>::Push(const T& data)
	{
		mSum += data;
		++mCount;

		if (mTop == nullptr)
		{
			mTop = new Node<T>(data, nullptr);
			mMaxNum = mMinNum = mTop ;
		}
		else
		{
			mTop = new Node<T>(data, mTop);

			if (data > mMaxNum->MNumber)
				mMaxNum = mTop;

			if (data < mMinNum->MNumber)
				mMinNum = mTop;
		}
	}

	template<typename T>
	inline const T SmartStack<T>::Pop()
	{
		mSum -= mTop->MNumber;
		--mCount;

		if (mTop == mMinNum)
		{
			mMinNum = nullptr;
			T minNum = std::numeric_limits<T>::max();
			for (Node<T>* i = mTop->MNext; i != nullptr; i = i->MNext)
			{
				if (i->MNumber <= minNum)
				{
					minNum = i->MNumber;
					mMinNum = i;
				}
			}
		}

		if (mTop == mMaxNum)
		{
			mMaxNum = nullptr;
			T maxNum = std::numeric_limits<T>::min();
			for (Node<T>* i = mTop->MNext; i != nullptr; i = i->MNext)
			{
				if (i->MNumber >= maxNum)
				{
					maxNum = i->MNumber;
					mMaxNum = i;
				}
			}
		}

		T returnNum = mTop->MNumber;
		Node<T>* tmp = mTop;
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
	inline const T& SmartStack<T>::GetMax() const
	{
		if (mMaxNum == nullptr)
			return std::numeric_limits<T>::min();

		return mMaxNum->MNumber;
	}

	template<typename T>
	inline const T& SmartStack<T>::GetMin() const
	{
		if (mMinNum == nullptr)
			return std::numeric_limits<T>::max();

		return mMinNum->MNumber;
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
		double average = GetAverage();
		double deviationSquareSum = 0;

		for (Node<T>* i = mTop; i != nullptr; i = i->MNext)
			deviationSquareSum += std::pow(i->MNumber - average, 2);

		return std::round(deviationSquareSum / mCount * 1000) / 1000;
	}

	template<typename T>
	inline const double SmartStack<T>::GetStandardDeviation() const
	{
		double average = GetAverage();
		double standardDeviation = 0;

		for (Node<T>* i = mTop; i != nullptr; i = i->MNext)
			standardDeviation += std::pow(i->MNumber - average, 2);

		standardDeviation = sqrt(standardDeviation / mCount);

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
		this->mTop = new Node<T>(*copy.mTop);
		Node<T>* j = this->mTop;

		for (Node<T>* i = copy.mTop->MNext; i != nullptr; i = i->MNext, j = j->MNext)
		{
			j->MNext = new Node<T>(*i);

			if (i == copy.mMaxNum)
				mMaxNum = j->MNext;

			if (i == copy.mMinNum)
				mMinNum = j->MNext;
		}
	}

}

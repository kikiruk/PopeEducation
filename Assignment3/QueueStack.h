#pragma once

#include "SmartStack.h"

template<typename T>
class StackNode
{
public:
	StackNode(StackNode<T>* next) :
		MStack(),
		MNext(next)
	{}

	StackNode(const StackNode<T>& copy) :
		MStack(copy.MStack),
		MNext(nullptr)
	{}

	assignment3::SmartStack<T> MStack;
	StackNode<T>* MNext;
};

namespace assignment3
{
	template<typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize);
		~QueueStack();
		QueueStack(const QueueStack<T>& copy);
		const QueueStack<T>& operator=(const QueueStack<T>& copy);

		inline void Enqueue(const T& number);
		inline const T& Peek() const;
		inline const T Dequeue();
		inline const T GetMax() const;
		inline const T GetMin() const;
		inline const double GetAverage() const;
		inline const T& GetSum() const;
		inline const unsigned int GetCount() const;
		inline const unsigned int GetStackCount() const;

	private:
		inline void copyFunc(const QueueStack<T>& copy);

		StackNode<T>* mHead;
		StackNode<T>* mTail;
		unsigned int mMaxStackSize;
		unsigned int mCount;
		unsigned int mStackCount;
		T mSum;
		StackNode<T>* mMaxNum;
		StackNode<T>* mMinNum;
	};

	template<typename T>
	QueueStack<T>::QueueStack(unsigned int maxStackSize) :
		mHead(nullptr),
		mTail(nullptr),
		mMaxStackSize(maxStackSize),
		mCount(0),
		mStackCount(0),
		mSum(0),
		mMaxNum(nullptr),
		mMinNum(nullptr)
	{
	}

	template<typename T>
	QueueStack<T>::~QueueStack()
	{
		for (StackNode<T>* i = mHead; i != nullptr;)
		{
			StackNode<T>* tmp = i;
			i = i->MNext;
			delete tmp;
		}
	}

	template<typename T>
	QueueStack<T>::QueueStack(const QueueStack<T>& copy) : 
		mMaxStackSize(copy.mMaxStackSize),
		mCount(copy.mCount),
		mStackCount(copy.mStackCount),
		mSum(copy.mSum)
	{
		copyFunc(copy);
	}

	template<typename T>
	inline const QueueStack<T>& QueueStack<T>::operator=(const QueueStack<T>& copy)
	{
		if (this != &copy)
		{
			for (StackNode<T>* i = mHead; i != nullptr;)
			{
				StackNode<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			mMaxStackSize = copy.mMaxStackSize;
			mCount = copy.mCount;
			mStackCount = copy.mStackCount;
			mSum = copy.mSum;

			copyFunc(copy);
		}

		return *this;
	}

	template<typename T>
	inline void QueueStack<T>::Enqueue(const T& number)
	{
		if (mHead == nullptr)
		{
			mHead = mTail = new StackNode<T>(nullptr);
			++mStackCount;

			mTail->MStack.Push(number);

			mMaxNum = mMinNum = mTail;
		}
		else
		{
			if (mTail->MStack.mCount == mMaxStackSize)
			{
				mTail->MNext = new StackNode<T>(nullptr);
				++mStackCount;
				mTail = mTail->MNext;
			}

			mTail->MStack.Push(number);

			if (mMaxNum->MStack.mMaxNum < number)
				mMaxNum = mTail;

			if (mMinNum->MStack.mMinNum > number)
				mMinNum = mTail;
		}

		mSum += number;
		++mCount;

	}

	template<typename T>
	inline const T& QueueStack<T>::Peek() const
	{
		return mHead->MStack.mTop->MNumber;
	}

	template<typename T>
	inline const T QueueStack<T>::Dequeue()
	{
		bool bFindMinNum = false;
		bool bFindMaxNum = false;

		if (mHead->MStack.mTop->MNumber == mMaxNum->MStack.mMaxNum)
			bFindMaxNum = true;

		if (mHead->MStack.mTop->MNumber == mMinNum->MStack.mMinNum)
			bFindMinNum = true;

		T answer = mHead->MStack.mTop->MNumber;

		if (mHead->MStack.mCount == 1)
		{
			if (mHead == mTail)
			{
				delete mHead;
				mHead = mTail = nullptr;
			}
			else
			{
				StackNode<T>* tmp = mHead;
				mHead = mHead->MNext;
				delete tmp;
			}

			--mStackCount;
		}
		else
		{
			mHead->MStack.Pop();
		}

		if (bFindMinNum)
		{
			mMinNum = nullptr;
			T minNum = MinMaxNum<T>::GetMax();
			for (StackNode<T>* i = mHead; i != nullptr; i = i->MNext)
			{
				if (minNum >= i->MStack.mMinNum)
				{
					mMinNum = i;
					minNum = i->MStack.mMinNum;
				}
			}
		}

		if (bFindMaxNum)
		{
			mMaxNum = nullptr;
			T maxNum = MinMaxNum<T>::GetMin();
			for (StackNode<T>* i = mHead; i != nullptr; i = i->MNext)
			{
				if (maxNum <= i->MStack.mMaxNum)
				{
					mMaxNum = i;
					maxNum = i->MStack.mMaxNum;
				}
			}
		}

		mSum -= answer;
		--mCount;

		return answer;
	}

	template<typename T>
	inline const T QueueStack<T>::GetMax() const
	{
		if (mMaxNum == nullptr)
			return MinMaxNum<T>::GetMin();

		return mMaxNum->MStack.mMaxNum;
	}

	template<typename T>
	inline const T QueueStack<T>::GetMin() const
	{
		if (mMinNum == nullptr)
			return MinMaxNum<T>::GetMax();

		return mMinNum->MStack.mMinNum;
	}

	template<typename T>
	inline const double QueueStack<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	template<typename T>
	inline const T& QueueStack<T>::GetSum() const
	{
		return mSum;
	}

	template<typename T>
	inline const unsigned int QueueStack<T>::GetCount() const
	{
		return mCount;
	}

	template<typename T>
	inline const unsigned int QueueStack<T>::GetStackCount() const
	{
		return mStackCount;
	}
	template<typename T>

	inline void QueueStack<T>::copyFunc(const QueueStack<T>& copy)
	{
		this->mHead = new StackNode<T>(*copy.mHead);

		StackNode<T>* i = this->mHead;
		StackNode<T>* j = copy.mHead;

		while (true)
		{
			if (j == copy.mMaxNum)
				mMaxNum = i;

			if (j == copy.mMinNum)
				mMinNum = i;

			j = j->MNext;

			if (j == nullptr)
			{
				mTail = i;
				break;
			}

			i->MNext = new StackNode<T>(*j);
			i = i->MNext;
		}
	}
}
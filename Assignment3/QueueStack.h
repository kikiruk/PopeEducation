#pragma once

#include "SmartStack.h"

template<typename T>
class StackNode
{
public:
	StackNode(StackNode<T>* mNext) :
		mStack(),
		mNext(mNext)
	{}

	StackNode(const StackNode<T>& copy) :
		mStack(copy.mStack),
		mNext(nullptr)
	{}

	assignment3::SmartStack<T> mStack;
	StackNode<T>* mNext;
};

namespace assignment3
{
	template<typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int mMaxStackSize);
		~QueueStack();
		QueueStack(const QueueStack<T>& copy);
		const QueueStack<T>& operator=(const QueueStack<T>& copy);

		inline void Enqueue(const T& number);
		inline const T& Peek() const;
		inline const T Dequeue();
		inline const T& GetMax() const;
		inline const T& GetMin() const;
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
		Node<T>* mMaxNum;
		Node<T>* mMinNum;
	};

	template<typename T>
	QueueStack<T>::QueueStack(unsigned int mMaxStackSize) :
		mHead(nullptr),
		mTail(nullptr),
		mMaxStackSize(mMaxStackSize),
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
			i = i->mNext;
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
				i = i->mNext;
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

			mTail->mStack.Push(number);

			mMaxNum = mMinNum = mTail->mStack.mTop;
		}
		else
		{
			if (mTail->mStack.mCount == mMaxStackSize)
			{
				mTail->mNext = new StackNode<T>(nullptr);
				++mStackCount;
				mTail = mTail->mNext;
			}

			mTail->mStack.Push(number);

			if (mMaxNum->mNumber < number)
				mMaxNum = mTail->mStack.mMaxNum;

			if (mMinNum->mNumber > number)
				mMinNum = mTail->mStack.mMinNum;
		}

		mSum += number;
		++mCount;

	}

	template<typename T>
	inline const T& QueueStack<T>::Peek() const
	{
		return mHead->mStack.mTop->mNumber;
	}

	template<typename T>
	inline const T QueueStack<T>::Dequeue()
	{
		bool bFindMinNum = false;
		bool bFindMaxNum = false;

		if (mHead->mStack.mTop == mMaxNum)
			bFindMaxNum = true;

		if (mHead->mStack.mTop == mMinNum)
			bFindMinNum = false;

		T answer = mHead->mStack.mTop->mNumber;

		if (mHead->mStack.mCount == 1)
		{
			if (mHead == mTail)
			{
				delete mHead;
				mHead = mTail = nullptr;
			}
			else
			{
				StackNode<T>* tmp = mHead;
				mHead = mHead->mNext;
				delete tmp;
			}

			--mStackCount;
		}
		else
		{
			mHead->mStack.Pop();
		}

		if (bFindMinNum)
		{
			mMinNum = nullptr;
			T minNum = std::numeric_limits<T>::max();
			for (StackNode<T>* i = mHead; i != nullptr; i = i->mNext)
			{
				if (minNum >= i->mStack.mMinNum->mNumber)
				{
					mMinNum = i->mStack.mMinNum;
					minNum = i->mStack.mMinNum->mNumber;
				}
			}
		}

		if (bFindMaxNum)
		{
			mMaxNum = nullptr;
			T maxNum = std::numeric_limits<T>::min();
			for (StackNode<T>* i = mHead; i != nullptr; i = i->mNext)
			{
				if (maxNum <= i->mStack.mMaxNum->mNumber)
				{
					mMaxNum = i->mStack.mMaxNum;
					maxNum = i->mStack.mMaxNum->mNumber;
				}
			}
		}

		mSum -= answer;
		--mCount;

		return answer;
	}

	template<typename T>
	inline const T& QueueStack<T>::GetMax() const
	{
		if (mMaxNum == nullptr)
			return std::numeric_limits<T>::min();

		return mMaxNum->mNumber;
	}

	template<typename T>
	inline const T& QueueStack<T>::GetMin() const
	{
		if (mMinNum == nullptr)
			return std::numeric_limits<T>::max();

		return mMinNum->mNumber;
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
			if (j->mStack.mMaxNum == copy.mMaxNum)
				mMaxNum = i->mStack.mMaxNum;

			if (j->mStack.mMinNum == copy.mMinNum)
				mMinNum = i->mStack.mMinNum;

			j = j->mNext;

			if (j == nullptr)
			{
				mTail = i;
				break;
			}

			i->mNext = new StackNode<T>(*j);
			i = i->mNext;
		}
	}
}
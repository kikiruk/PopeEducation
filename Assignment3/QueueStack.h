#pragma once

#include "SmartStack.h"

template<typename T>
class StackNode
{
public:
	StackNode(StackNode<T>* MNext) :
		MStack(),
		MNext(MNext)
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
		unsigned int MStackCount;
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
		MStackCount(0),
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
		MStackCount(copy.MStackCount),
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
			MStackCount = copy.MStackCount;
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
			++MStackCount;

			mTail->MStack.Push(number);

			mMaxNum = mMinNum = mTail->MStack.mTop;
		}
		else
		{
			if (mTail->MStack.mCount == mMaxStackSize)
			{
				mTail->MNext = new StackNode<T>(nullptr);
				++MStackCount;
				mTail = mTail->MNext;
			}

			mTail->MStack.Push(number);

			if (mMaxNum->MNumber < number)
				mMaxNum = mTail->MStack.mMaxNum;

			if (mMinNum->MNumber > number)
				mMinNum = mTail->MStack.mMinNum;
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

		if (mHead->MStack.mTop == mMaxNum)
			bFindMaxNum = true;

		if (mHead->MStack.mTop == mMinNum)
			bFindMinNum = false;

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

			--MStackCount;
		}
		else
		{
			mHead->MStack.Pop();
		}

		if (bFindMinNum)
		{
			mMinNum = nullptr;
			T minNum = std::numeric_limits<T>::max();
			for (StackNode<T>* i = mHead; i != nullptr; i = i->MNext)
			{
				if (minNum >= i->MStack.mMinNum->MNumber)
				{
					mMinNum = i->MStack.mMinNum;
					minNum = i->MStack.mMinNum->MNumber;
				}
			}
		}

		if (bFindMaxNum)
		{
			mMaxNum = nullptr;
			T maxNum = std::numeric_limits<T>::min();
			for (StackNode<T>* i = mHead; i != nullptr; i = i->MNext)
			{
				if (maxNum <= i->MStack.mMaxNum->MNumber)
				{
					mMaxNum = i->MStack.mMaxNum;
					maxNum = i->MStack.mMaxNum->MNumber;
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

		return mMaxNum->MNumber;
	}

	template<typename T>
	inline const T& QueueStack<T>::GetMin() const
	{
		if (mMinNum == nullptr)
			return std::numeric_limits<T>::max();

		return mMinNum->MNumber;
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
		return MStackCount;
	}
	template<typename T>

	inline void QueueStack<T>::copyFunc(const QueueStack<T>& copy)
	{
		this->mHead = new StackNode<T>(*copy.mHead);

		StackNode<T>* i = this->mHead;
		StackNode<T>* j = copy.mHead;

		while (true)
		{
			if (j->MStack.mMaxNum == copy.mMaxNum)
				mMaxNum = i->MStack.mMaxNum;

			if (j->MStack.mMinNum == copy.mMinNum)
				mMinNum = i->MStack.mMinNum;

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
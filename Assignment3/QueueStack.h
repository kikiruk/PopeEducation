#pragma once

#include "SmartStack.h"

template<typename T>
struct StackNode
{
	StackNode(StackNode<T>* next) :
		stack(),
		next(next)
	{}

	StackNode(const StackNode<T>& copy) :
		stack(copy.stack),
		next(nullptr)
	{}

	assignment3::SmartStack<T> stack;
	StackNode<T>* next;
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
		unsigned int maxStackSize;
		unsigned int mCount;
		unsigned int mStackCount;
		T mSum;
		T mMaxNum;
		T mMinNum;
	};

	template<typename T>
	QueueStack<T>::QueueStack(unsigned int maxStackSize) :
		mHead(nullptr),
		mTail(nullptr),
		maxStackSize(maxStackSize),
		mCount(0),
		mStackCount(0),
		mSum(0),
		mMaxNum(std::numeric_limits<T>::min()),
		mMinNum(std::numeric_limits<T>::max())
	{
	}

	template<typename T>
	QueueStack<T>::~QueueStack()
	{
		for (StackNode<T>* i = mHead; i != nullptr;)
		{
			StackNode<T>* tmp = i;
			i = i->next;
			delete tmp;
		}
	}

	template<typename T>
	QueueStack<T>::QueueStack(const QueueStack<T>& copy) : 
		maxStackSize(copy.maxStackSize),
		mCount(copy.mCount),
		mStackCount(copy.mStackCount),
		mSum(copy.mSum),
		mMaxNum(copy.mMaxNum),
		mMinNum(copy.mMinNum)
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
				i = i->next;
				delete tmp;
			}

			maxStackSize = copy.maxStackSize;
			mCount = copy.mCount;
			mStackCount = copy.mStackCount;
			mSum = copy.mSum;
			mMaxNum = copy.mMaxNum;
			mMinNum = copy.mMinNum;

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
		}
		else
		{
			if (mTail->stack.mCount == maxStackSize)
			{
				mTail->next = new StackNode<T>(nullptr);
				++mStackCount;
				mTail = mTail->next;
			}
		}

		mTail->stack.Push(number);

		mSum += number;
		++mCount;

		if (mMaxNum < number)
			mMaxNum = number;

		if (mMinNum > number)
			mMinNum = number;
	}

	template<typename T>
	inline const T& QueueStack<T>::Peek() const
	{
		return mHead->stack.mTop->number;
	}

	template<typename T>
	inline const T QueueStack<T>::Dequeue()
	{
		T answer = mHead->stack.mTop->number;

		if (mHead->stack.mCount == 1)
		{
			if (mHead == mTail)
			{
				delete mHead;
				mHead = mTail = nullptr;
			}
			else
			{
				StackNode<T>* tmp = mHead;
				mHead = mHead->next;
				delete tmp;
			}

			--mStackCount;
		}
		else
		{
			mHead->stack.Pop();
		}

		mSum -= answer;
		--mCount;

		if (mMaxNum == answer)
		{
			T minNum = std::numeric_limits<T>::max();
			for (StackNode<T>* i = mHead; i != nullptr; i = i->next)
			{
				if (minNum > i->stack.mMinNum)
					minNum = i->stack.mMinNum;
			}

			mMinNum = minNum;
		}

		if (mMinNum == answer)
		{
			T maxNum = std::numeric_limits<T>::min();
			for (StackNode<T>* i = mHead; i != nullptr; i = i->next)
			{
				if (maxNum < i->stack.mMaxNum)
					maxNum = i->stack.mMaxNum;
			}

			mMaxNum = maxNum;
		}

		return answer;
	}

	template<typename T>
	inline const T& QueueStack<T>::GetMax() const
	{
		return mMaxNum;
	}

	template<typename T>
	inline const T& QueueStack<T>::GetMin() const
	{
		return mMinNum;
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
			if (j->next == nullptr)
			{
				mTail = i;
				break;
			}

			i->next = new StackNode<T>(*j->next);
			i = i->next;
			j = j->next;
		}
	}
}
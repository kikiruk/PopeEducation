
#pragma once

#include "SmartStack.h"

// StackNode Ŭ����: QueueStack ������ ������ �����ϴ� �� ��带 ����
template<typename T>
class StackNode
{
public:
	// ������: ���� ��带 ����Ű�� �����͸� �ʱ�ȭ
	StackNode(StackNode<T>* next) :
		MStack(),
		MNext(next)
	{}

	// ���� ������: StackNode ��ü�� �����Ͽ� ����
	StackNode(const StackNode<T>& copy) :
		MStack(copy.MStack),
		MNext(nullptr)
	{}

	assignment3::SmartStack<T> MStack; // SmartStack ��ü�� ����� ����
	StackNode<T>* MNext; // ���� ��带 ����Ű�� ������
};

namespace assignment3
{
	// QueueStack Ŭ����: SmartStack�� ���� ����ϴ� ť�� ������ ���� �ڷᱸ��
	template<typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize); // ������: �ִ� ���� ũ�⸦ ����
		~QueueStack(); // �Ҹ���: ��� ��带 ����
		QueueStack(const QueueStack<T>& copy); // ���� ������
		const QueueStack<T>& operator=(const QueueStack<T>& copy); // ���� ������ �����ε�

		// QueueStack�� �ֿ� �����
		inline void Enqueue(const T& number); // �����͸� ť�� �߰�
		inline const T& Peek() const; // ť�� ù ��° ��Ҹ� Ȯ��
		inline const T Dequeue(); // ť���� ù ��° ��Ҹ� �����ϰ� ��ȯ
		inline const T GetMax() const; // ť �� �ִ밪 ��ȯ
		inline const T GetMin() const; // ť �� �ּҰ� ��ȯ
		inline const double GetAverage() const; // ť �� ��հ� ��ȯ
		inline const T& GetSum() const; // ť �� �������� �� ��ȯ
		inline const unsigned int GetCount() const; // ť �� ������ ���� ��ȯ
		inline const unsigned int GetStackCount() const; // ť �� ������ ���� ��ȯ

	private:
		// ���� �۾��� �����ϴ� �Լ�
		inline void copyFunc(const QueueStack<T>& copy);

		StackNode<T>* mHead; // ť�� ù ��° ��带 ����Ű�� ������
		StackNode<T>* mTail; // ť�� ������ ��带 ����Ű�� ������
		unsigned int mMaxStackSize; // �ϳ��� ���ÿ� �� �� �ִ� �ִ� ������ ����
		unsigned int mCount; // ť�� �ִ� ��ü ������ ����
		unsigned int mStackCount; // ť�� �ִ� ������ ����
		T mSum; // ť �� �������� ��
		StackNode<T>* mMaxNum; // ť �� �ִ밪�� ���� ��带 ����Ű�� ������
		StackNode<T>* mMinNum; // ť �� �ּҰ��� ���� ��带 ����Ű�� ������
	};

	// ������: �ʱ� ���¸� ����
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

	// �Ҹ���: ��� ��带 �����Ͽ� �޸𸮸� ����
	template<typename T>
	QueueStack<T>::~QueueStack()
	{
		for (StackNode<T>* i = mHead; i != nullptr;)
		{
			StackNode<T>* tmp = i;
			i = i->MNext;
			delete tmp; // ��� �޸� ����
		}
	}

	// ���� ������: �ٸ� QueueStack ��ü�� �����Ͽ� ���ο� ��ü�� ����ϴ�.
	template<typename T>
	QueueStack<T>::QueueStack(const QueueStack<T>& copy) :
		mMaxStackSize(copy.mMaxStackSize),
		mCount(copy.mCount),
		mStackCount(copy.mStackCount),
		mSum(copy.mSum)
	{
		copyFunc(copy); // ���� �۾� ����
	}

	// ���� ������ �����ε�: �ٸ� QueueStack ��ü�� ���� ��ü�� �����մϴ�.
	template<typename T>
	inline const QueueStack<T>& QueueStack<T>::operator=(const QueueStack<T>& copy)
	{
		if (this != &copy) // �ڱ� �ڽŰ��� ������ ����
		{
			// ���� ������ ����
			for (StackNode<T>* i = mHead; i != nullptr;)
			{
				StackNode<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			// ���ο� ���� ����
			mMaxStackSize = copy.mMaxStackSize;
			mCount = copy.mCount;
			mStackCount = copy.mStackCount;
			mSum = copy.mSum;

			copyFunc(copy); // ���� �۾� ����
		}

		return *this;
	}

	// Enqueue: �����͸� ť�� �߰��ϸ� ������ ����
	template<typename T>
	inline void QueueStack<T>::Enqueue(const T& number)
	{
		if (mHead == nullptr) // ť�� ����ִ� ��� ���ο� ��� ����
		{
			mHead = mTail = new StackNode<T>(nullptr);
			++mStackCount;

			mTail->MStack.Push(number); // ���ÿ� ������ �߰�

			// �ִ밪�� �ּҰ� ��带 �ʱ�ȭ
			mMaxNum = mMinNum = mTail;
		}
		else
		{
			// ������ ������ ���� á�ٸ� ���ο� ��带 �����Ͽ� �߰�
			if (mTail->MStack.mCount == mMaxStackSize)
			{
				mTail->MNext = new StackNode<T>(nullptr);
				++mStackCount;
				mTail = mTail->MNext;
			}

			mTail->MStack.Push(number); // ���ο� ������ �߰�

			// �ִ밪�� �ּҰ� ����
			if (mMaxNum->MStack.mMaxNum < number)
				mMaxNum = mTail;

			if (mMinNum->MStack.mMinNum > number)
				mMinNum = mTail;
		}

		mSum += number; // ��ü �� ����
		++mCount; // ��ü ������ ���� ����
	}

	// Peek: ť�� ù ��° ��Ҹ� ��ȯ�մϴ�.
	template<typename T>
	inline const T& QueueStack<T>::Peek() const
	{
		return mHead->MStack.mTop->MNumber;
	}

	// Dequeue: ť���� ù ��° ��Ҹ� �����ϰ� ��ȯ�մϴ�.
	template<typename T>
	inline const T QueueStack<T>::Dequeue()
	{
		bool bFindMinNum = false;
		bool bFindMaxNum = false;

		// ������ �����Ͱ� �ִ밪 �Ǵ� �ּҰ����� Ȯ��
		if (mHead->MStack.mTop->MNumber == mMaxNum->MStack.mMaxNum)
			bFindMaxNum = true;

		if (mHead->MStack.mTop->MNumber == mMinNum->MStack.mMinNum)
			bFindMinNum = true;

		T answer = mHead->MStack.mTop->MNumber; // ��ȯ�� ���� ����

		// ù ��° ���ÿ� �ϳ��� ��Ҹ� �ִ� ���
		if (mHead->MStack.mCount == 1)
		{
			// ť�� �ϳ��� ��常 �ִ� ���
			if (mHead == mTail)
			{
				delete mHead;
				mHead = mTail = nullptr;
			}
			else
			{
				// ù ��° ��带 �����ϰ� ���� ���� �̵�
				StackNode<T>* tmp = mHead;
				mHead = mHead->MNext;
				delete tmp;
			}

			--mStackCount;
		}
		else
		{
			mHead->MStack.Pop(); // ù ��° ���ÿ��� ��Ҹ� ����
		}

		// �ּҰ��� ã�Ҵ� ���, ���ο� �ּҰ��� ã���ϴ�.
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

		// �ִ밪�� ã�Ҵ� ���, ���ο� �ִ밪�� ã���ϴ�.
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

		mSum -= answer; // ��ü �տ��� ������ ���� ���ϴ�.
		--mCount; // ��ü ������ ������ ���ҽ�ŵ�ϴ�.

		return answer; // ������ ���� ��ȯ�մϴ�.
	}

	// GetMax: ť �� �ִ밪�� ��ȯ�մϴ�.
	template<typename T>
	inline const T QueueStack<T>::GetMax() const
	{
		if (mMaxNum == nullptr)
			return MinMaxNum<T>::GetMin();

		return mMaxNum->MStack.mMaxNum;
	}

	// GetMin: ť �� �ּҰ��� ��ȯ�մϴ�.
	template<typename T>
	inline const T QueueStack<T>::GetMin() const
	{
		if (mMinNum == nullptr)
			return MinMaxNum<T>::GetMax();

		return mMinNum->MStack.mMinNum;
	}

	// GetAverage: ť �� �������� ����� ��ȯ�մϴ�.
	template<typename T>
	inline const double QueueStack<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	// GetSum: ť �� �������� ���� ��ȯ�մϴ�.
	template<typename T>
	inline const T& QueueStack<T>::GetSum() const
	{
		return mSum;
	}

	// GetCount: ť �� ������ ������ ��ȯ�մϴ�.
	template<typename T>
	inline const unsigned int QueueStack<T>::GetCount() const
	{
		return mCount;
	}

	// GetStackCount: ť �� ������ ������ ��ȯ�մϴ�.
	template<typename T>
	inline const unsigned int QueueStack<T>::GetStackCount() const
	{
		return mStackCount;
	}

	// copyFunc: ���� �۾��� �����ϴ� �Լ�
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
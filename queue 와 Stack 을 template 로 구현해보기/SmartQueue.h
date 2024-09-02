#pragma once
#include <cmath>

#include "MinMaxNum.h"
#include "Node.h"

namespace assignment3
{
	// SmartQueue Ŭ����: Queue �ڷᱸ���� ��� ���� ����� �߰��� ����Ʈ ť Ŭ����
	template<typename T>
	class SmartQueue
	{
	public:
		SmartQueue(); // �⺻ ������
		~SmartQueue(); // �Ҹ���
		SmartQueue(const SmartQueue<T>& copy); // ���� ������
		const SmartQueue<T>& operator=(const SmartQueue<T>& copy); // ���� ������ �����ε�

		// SmartQueue�� �ֿ� �����
		inline void Enqueue(const T& number); // ť�� �����͸� �߰�
		inline const T& Peek() const; // ť�� ù ��° ��Ҹ� ��ȯ (�������� ����)
		inline const T Dequeue(); // ť�� ù ��° ��Ҹ� �����ϰ� ��ȯ
		inline const T GetMax() const; // ť �� �ִ밪 ��ȯ
		inline const T GetMin() const; // ť �� �ּҰ� ��ȯ
		inline const double GetAverage() const; // ť �� �������� ��հ� ��ȯ
		inline const T& GetSum() const; // ť �� �������� �� ��ȯ
		inline const double GetVariance() const; // ť �� �������� �л� ��ȯ
		inline const double GetStandardDeviation() const; // ť �� �������� ǥ������ ��ȯ
		inline const unsigned int GetCount() const; // ť �� ������ ���� ��ȯ

	private:
		// ���� �۾��� �����ϴ� �Լ�
		inline void copyFunc(const SmartQueue<T>& copy);

		Node<T>* mHead; // ť�� ù ��° ��带 ����Ű�� ������
		Node<T>* mTail; // ť�� ������ ��带 ����Ű�� ������
		unsigned int mCount; // ť�� �ִ� �������� ����
		T mSum; // ť �� �������� ��
		double mSumOfSquared; // ť �� ������ ������ ��
		Node<T>* mMaxNum; // ť �� �ִ밪�� ���� ��带 ����Ű�� ������
		Node<T>* mMinNum; // ť �� �ּҰ��� ���� ��带 ����Ű�� ������
	};

	// �⺻ ������: �ʱ� ���¸� ����
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

	// �Ҹ���: ť�� ��� ��带 �����Ͽ� �޸𸮸� ����
	template<typename T>
	SmartQueue<T>::~SmartQueue()
	{
		for (Node<T>* i = mHead; i != nullptr;)
		{
			Node<T>* tmp = i;
			i = i->MNext;
			delete tmp; // ��� �޸� ����
		}
	}

	// ���� ������: �ٸ� SmartQueue ��ü�� �����Ͽ� ���ο� ��ü�� ����ϴ�.
	template<typename T>
	SmartQueue<T>::SmartQueue(const SmartQueue<T>& copy)	:
		mCount(copy.mCount),
		mSum(copy.mSum),
		mSumOfSquared(copy.mSumOfSquared)
	{
		copyFunc(copy); // ���� �۾� ����
	}

	// ���� ������ �����ε�: �ٸ� SmartQueue ��ü�� ���� ��ü�� �����մϴ�.
	template<typename T>
	const SmartQueue<T>& SmartQueue<T>::operator=(const SmartQueue<T>& copy)
	{
		if (this != &copy) // �ڱ� �ڽŰ��� ������ ����
		{
			// ���� ������ ����
			for (Node<T>* i = mHead; i != nullptr;)
			{
				Node<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			// ���ο� ���� ����
			mCount = copy.mCount;
			mSum = copy.mSum;
			mSumOfSquared = copy.mSumOfSquared;

			copyFunc(copy); // ���� �۾� ����
		}

		return *this;
	}

	// Enqueue: �����͸� ť�� �߰��ϸ� ��� ���� ����
	template<typename T>
	inline void SmartQueue<T>::Enqueue(const T& number)
	{
		if (mHead == nullptr) // ť�� ����ִ� ��� ���ο� ��带 ����
		{
			mHead = mTail = new Node<T>(number, nullptr);
			mMaxNum = mMinNum = mTail; // �ִ밪�� �ּҰ� ��带 �ʱ�ȭ
		}
		else
		{
			// ť�� ���� ���ο� ��带 �߰�
			mTail->MNext = new Node<T>(number, nullptr);
			mTail = mTail->MNext;

			// �ִ밪�� �ּҰ� ����
			if (mMaxNum->MNumber < number)
				mMaxNum = mTail;

			if (mMinNum->MNumber > number)
				mMinNum = mTail;
		}

		mSum += number; // ��ü �� ����
		mSumOfSquared += std::pow(number, 2); // ���� �� ����
		++mCount; // ������ ���� ����
	}

	// Peek: ť�� ù ��° ��Ҹ� ��ȯ (�������� ����)
	template<typename T>
	inline const T& SmartQueue<T>::Peek() const
	{
		return mHead->MNumber;
	}

	// Dequeue: ť�� ù ��° ��Ҹ� �����ϰ� ��ȯ�մϴ�.
	template<typename T>
	inline const T SmartQueue<T>::Dequeue()
	{
		T answer = mHead->MNumber; // ��ȯ�� ���� ����

		// �ּҰ��� ������ ��� ���ο� �ּҰ��� ã���ϴ�.
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

		// �ִ밪�� ������ ��� ���ο� �ִ밪�� ã���ϴ�.
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

		// ť�� ù ��° ��带 �����ϰ� ���� ���� �̵�
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

		mSum -= answer; // ��ü �տ��� ������ ���� ���ϴ�.
		mSumOfSquared -= std::pow(answer, 2); // ���� �տ��� ������ ���� ������ ���ϴ�.
		--mCount; // ������ ������ ���ҽ�ŵ�ϴ�.

		return answer; // ������ ���� ��ȯ�մϴ�.
	}

	// GetMax: ť �� �ִ밪�� ��ȯ�մϴ�.
	template<typename T>
	inline const T SmartQueue<T>::GetMax() const
	{
		if (mHead == nullptr)
			return MinMaxNum<T>::GetMin(); // ť�� ����ִٸ� �ּҰ� ��ȯ

		return mMaxNum->MNumber; // �ִ밪 ��ȯ
	}

	// GetMin: ť �� �ּҰ��� ��ȯ�մϴ�.
	template<typename T>
	inline const T SmartQueue<T>::GetMin() const
	{
		if (mHead == nullptr)
			return MinMaxNum<T>::GetMax(); // ť�� ����ִٸ� �ִ밪 ��ȯ

		return mMinNum->MNumber; // �ּҰ� ��ȯ
	}

	// GetAverage: ť �� �������� ��հ��� ��ȯ�մϴ�.
	template<typename T>
	inline const double SmartQueue<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	// GetSum: ť �� �������� ���� ��ȯ�մϴ�.
	template<typename T>
	inline const T& SmartQueue<T>::GetSum() const
	{
		return mSum;
	}

	// GetVariance: ť �� �������� �л��� ����Ͽ� ��ȯ�մϴ�.
	template<typename T>
	inline const double SmartQueue<T>::GetVariance() const
	{
		double deviationSquareSum = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);

		return std::round(deviationSquareSum * 1000) / 1000;
	}

	// GetStandardDeviation: ť �� �������� ǥ�������� ����Ͽ� ��ȯ�մϴ�.
	template<typename T>
	inline const double SmartQueue<T>::GetStandardDeviation() const
	{
		double standardDeviation = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);
		standardDeviation = std::sqrt(standardDeviation);

		return std::round(standardDeviation * 1000) / 1000;
	}

	// GetCount: ť �� ������ ������ ��ȯ�մϴ�.
	template<typename T>
	inline const unsigned int SmartQueue<T>::GetCount() const
	{
		return mCount;
	}

	// copyFunc: ���� �۾��� �����ϴ� �Լ�
	template<typename T>
	inline void SmartQueue<T>::copyFunc(const SmartQueue<T>& copy)
	{
		this->mHead = new Node<T>(*copy.mHead); // ù ��° ��带 ����

		Node<T>* i = this->mHead;
		Node<T>* j = copy.mHead;

		// ��� ��带 �����Ͽ� ���ο� ť�� ����
		while (true)
		{
			if (j->MNext == nullptr) // ������ ������ ���� �Ϸ�
			{
				mTail = i; // ������ ��带 ����
				break;
			}

			i->MNext = new Node<T>(*j->MNext); // ���� ��带 ����

			// �ִ밪 �� �ּҰ� ��带 ����
			if (j == copy.mMaxNum)
				mMaxNum = i->MNext;

			if (j == copy.mMinNum)
				mMinNum = i->MNext; 

			i = i->MNext;
			j = j->MNext;
		}
	}
}
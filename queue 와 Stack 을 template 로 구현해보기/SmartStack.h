#pragma once
#include <cassert>
#include <cmath>

#include "MinMaxNum.h"
#include "Node.h"

namespace assignment3
{
	template<typename T>
	class QueueStack;

	// SmartStack Ŭ���� ����: Stack �ڷᱸ���� ������� �پ��� ��� ���� ����� �����ϴ� ����Ʈ ���� Ŭ����
	template <typename T> // T�� ������ Ÿ�� (��: int, double ��)
	class SmartStack
	{
		friend QueueStack<T>; // QueueStack Ŭ������ SmartStack�� ����� ����� ������ �� �ֵ��� ����

	public:
		SmartStack(); // �⺻ ������
		SmartStack(const SmartStack<T>& copy); // ���� ������
		~SmartStack(); // �Ҹ���

		// ���� ������ �����ε�
		const SmartStack<T>& operator=(const SmartStack<T>& copy);

		// ���� ���� �� ��� ���� �޼����
		inline void Push(const T& data); // ���ÿ� ������ �߰�
		inline const T Pop(); // ���ÿ��� ������ ���� �� ��ȯ
		inline const T& Peek() const; // ������ �� �� ������ ����
		inline const T GetMax() const; // ���� �� �ִ밪 ��ȯ
		inline const T GetMin() const; // ���� �� �ּҰ� ��ȯ
		inline const double GetAverage() const; // ���� �� ������ ��� ��ȯ
		inline const T& GetSum() const; // ���� �� ������ �հ� ��ȯ

		// �߰� ��� ���� �޼����
		inline const double GetVariance() const; // �л� ��� �� ��ȯ
		inline const double GetStandardDeviation() const; // ǥ������ ��� �� ��ȯ
		inline const unsigned int GetCount() const; // ���ÿ� �ִ� ������ ���� ��ȯ

	private:
		inline void copyFunc(const SmartStack<T>& copy); // ���� �۾��� ó���ϴ� �Լ�

		NodeForStack<T>* mTop; // ������ �� �� ��带 ����Ű�� ������
		unsigned int mCount; // ���ÿ� �ִ� �������� ����
		T mSum; // ���ÿ� �ִ� �������� ��
		double mSumOfSquared; // ���ÿ� �ִ� �������� ������ ��
		T mMaxNum; // ���� �� �ִ밪
		T mMinNum; // ���� �� �ּҰ�
	};


	// �⺻ ������: �ʱ� ���¸� ����
	template<typename T>
	SmartStack<T>::SmartStack() :
		mTop(nullptr),
		mCount(0),
		mSum(0),
		mSumOfSquared(0),
		mMaxNum(MinMaxNum<T>::GetMin()), // �ʱ� �ִ밪�� ���� ���� ������ ����
		mMinNum(MinMaxNum<T>::GetMax()) // �ʱ� �ּҰ��� ���� ū ������ ����
	{
	}

	// ���� ������: �ٸ� SmartStack ��ü�� �����Ͽ� �� ��ü�� ����ϴ�.
	template<typename T>
	inline SmartStack<T>::SmartStack(const SmartStack<T>& copy) :
		mCount(copy.mCount),
		mSum(copy.mSum),
		mSumOfSquared(copy.mSumOfSquared),
		mMaxNum(copy.mMaxNum),
		mMinNum(copy.mMinNum)
	{
		copyFunc(copy); // ���� �۾� ����
	}

	// �Ҹ���: ������ ��� ��带 �����մϴ�.
	template<typename T>
	SmartStack<T>::~SmartStack()
	{
		for (NodeForStack<T>* i = mTop; i != nullptr;)
		{
			NodeForStack<T>* tmp = i;
			i = i->MNext;
			delete tmp; // ���� �Ҵ�� ��� �޸� ����
		}
	}

	// ���� ������ �����ε�: �ٸ� SmartStack ��ü�� ���� ��ü�� ����
	template<typename T>
	inline const SmartStack<T>& SmartStack<T>::operator=(const SmartStack<T>& copy)
	{
		if (this != &copy) // �ڱ� �ڽŰ��� ������ ����
		{
			// ���� ���� ��带 ��� ����
			for (NodeForStack<T>* i = mTop; i != nullptr;)
			{
				NodeForStack<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			// ���ο� ���� ����
			mCount = copy.mCount;
			mSum = copy.mSum;
			mSumOfSquared = copy.mSumOfSquared;
			mMaxNum = copy.mMaxNum;
			mMinNum = copy.mMinNum;

			copyFunc(copy); // ���� �۾� ����
		}

		return *this;
	}

	// Push: ���ÿ� �����͸� �߰��ϸ� ��� ���� �����մϴ�.
	template<typename T>
	inline void SmartStack<T>::Push(const T& data)
	{
		mSum += data; // �հ� ����
		mSumOfSquared += std::pow(data, 2); // ���� �� ����
		++mCount; // ������ ���� ����

		// ������ ����ִٸ� �� ��带 �����ϰ�, �ִ밪�� �ּҰ��� �ʱ�ȭ
		if (mTop == nullptr)
		{
			mTop = new NodeForStack<T>(data, nullptr);
			mMaxNum = mMinNum = data;
		}
		else
		{
			mTop = new NodeForStack<T>(data, mTop); // �� ��带 ������ �� ���� �߰�

			if (data > mMaxNum)
				mMaxNum = data; // �ִ밪 ����

			if (data < mMinNum)
				mMinNum = data; // �ּҰ� ����
		}

		mTop->MMaxData = mMaxNum; // ��忡 ���� �ִ밪 ����
		mTop->MMinData = mMinNum; // ��忡 ���� �ּҰ� ����
	}

	// Pop: ������ �� �� �����͸� �����ϰ� ��ȯ�մϴ�.
	template<typename T>
	inline const T SmartStack<T>::Pop()
	{
		mSum -= mTop->MNumber; // �հ迡�� �� �� ������ ���� ���ϴ�.
		mSumOfSquared -= std::pow(mTop->MNumber, 2); // ���� �տ��� �� �� ������ ���� ���� ���ϴ�.
		--mCount; // ������ ���� ����

		// ���ÿ� ���� ��尡 �ִٸ�, �� ����� �ִ밪�� �ּҰ����� ����
		if (mTop->MNext != nullptr)
		{
			mMinNum = mTop->MNext->MMinData;
			mMaxNum = mTop->MNext->MMaxData;
		}
		else
		{
			// ������ ��� �ȴٸ� �ִ밪�� �ּҰ��� �ʱ�ȭ
			mMinNum = MinMaxNum<T>::GetMax();
			mMaxNum = MinMaxNum<T>::GetMin();
		}

		T returnNum = mTop->MNumber; // �� �� �����͸� ��ȯ�ϱ� ���� ����
		NodeForStack<T>* tmp = mTop;
		mTop = mTop->MNext; // �� �� ��带 �����ϰ� ���� ���� �̵�
		delete tmp; // ���ŵ� ��� �޸� ����

		return returnNum; // �� �� ������ ��ȯ
	}

	// Peek: ������ �� �� �����͸� ��ȯ�մϴ�.
	template<typename T>
	inline const T& SmartStack<T>::Peek() const
	{
		return mTop->MNumber;
	}

	// GetMax: ���� �� �ִ밪�� ��ȯ�մϴ�.
	template<typename T>
	inline const T SmartStack<T>::GetMax() const
	{
		return mMaxNum;
	}

	// GetMin: ���� �� �ּҰ��� ��ȯ�մϴ�.
	template<typename T>
	inline const T SmartStack<T>::GetMin() const
	{
		return mMinNum;
	}

	// GetAverage: ���� �� �������� ����� ��ȯ�մϴ�.
	template<typename T>
	inline const double SmartStack<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	// GetSum: ���� �� �������� ���� ��ȯ�մϴ�.
	template<typename T>
	inline const T& SmartStack<T>::GetSum() const
	{
		return mSum;
	}

	// GetVariance: �л��� ����ϰ� ��ȯ�մϴ�.
	template<typename T>
	inline const double SmartStack<T>::GetVariance() const
	{
		double deviationSquareSum = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);

		return std::round(deviationSquareSum * 1000) / 1000;
	}

	// GetStandardDeviation: ǥ�������� ����ϰ� ��ȯ�մϴ�.
	template<typename T>
	inline const double SmartStack<T>::GetStandardDeviation() const
	{
		double standardDeviation = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);
		standardDeviation = std::sqrt(standardDeviation);

		return std::round(standardDeviation * 1000) / 1000;
	}

	// GetCount: ���ÿ� �ִ� ������ ������ ��ȯ�մϴ�.
	template<typename T>
	inline const unsigned int SmartStack<T>::GetCount() const
	{
		return mCount;
	}

	// copyFunc: ���� �۾��� �����ϴ� �Լ�
	template<typename T>
	inline void SmartStack<T>::copyFunc(const SmartStack<T>& copy)
	{
		NodeForStack<T> tmp(0, nullptr); // �ӽ� ��� ����
		NodeForStack<T>* j = &tmp; // �ӽ� ��带 ����Ű�� ������
		NodeForStack<T>* i = copy.mTop; // ������ ������ �� �� ��带 ����Ű�� ������

		T  minNum = MinMaxNum<T>::GetMax(); // �ʱ� �ּҰ� ����
		T  maxNum = MinMaxNum<T>::GetMin(); // �ʱ� �ִ밪 ����

		// ������ ������ ��ȸ�ϸ鼭 ��� ����
		for (; i != nullptr; i = i->MNext, j = j->MNext)
		{
			j->MNext = new NodeForStack<T>(*i); // ���� ��带 �����Ͽ� ���ο� ��� ����
			j->MNext->MMaxData = i->MMaxData; // �ִ밪 ����
			j->MNext->MMinData = i->MMinData; // �ּҰ� ����

			if (i == copy.mTop)
				mTop = j->MNext; // ������ ������ �� �� ��� ����
		}
	}
}
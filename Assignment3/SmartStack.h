#pragma once
#include <cassert>
#include <limits>
#include <cmath>

template<typename T>
struct Node
{
	Node(T number, Node* next) :
		number(number),
		next(next)
	{}

	T number;
	Node* next;
};

namespace assignment3
{
	template <typename T>// int, unsigned int, double, short
	class SmartStack
	{
	public:
		SmartStack();
		~SmartStack();
		inline void Push(const T& data);
		inline const T Pop();
		inline const T& Peek() const;
		inline const T& GetMax() const;
		inline const T& GetMin() const;
		inline const double GetAverage() const;
		inline const T& GetSum() const;

		//ť�� �ִ� ������ �л��� ��ȯ�մϴ�. ��ȯ ���� �Ҽ� ��° �ڸ����� �ݿø��ؾ� �մϴ�.
		//������ �������� �� �޼����� �ð� ���⵵�� O(1)�̾�� �մϴ�.
		//���庿�� ť�� ��� ���� ���� ���� �� �޼��带 �׽�Ʈ�մϴ�.
		inline const double GetVariance() const;
		inline const double GetStandardDeviation() const;
		inline const unsigned int GetCount() const;

	private:
		Node<T>* mTop;
		unsigned int mCount;
		T mSum;
		T mMaxNum;
		T mMinNum;
	};


	//������
	template<typename T>
	SmartStack<T>::SmartStack() : 
		mTop(nullptr),
		mCount(0),
		mSum(0),
		mMaxNum(std::numeric_limits<T>::max()),
		mMinNum(std::numeric_limits<T>::min())
	{
	}

	template<typename T>
	SmartStack<T>::~SmartStack()
	{
		for (Node<T>* i = mTop; i != nullptr;)
		{
			Node<T>* tmp = i;
			i = i->next;
			delete tmp;
		}
	}

	template<typename T>
	inline void SmartStack<T>::Push(const T& data)
	{
		if (data > mMaxNum)
			mMaxNum = data;

		if (data < mMinNum)
			mMinNum = data;

		mSum += data;
		++mCount;

		if (mTop == nullptr)
			mTop = new Node<T>(data, nullptr);
		else
			mTop = new Node<T>(data, mTop);
	}

	template<typename T>
	inline const T SmartStack<T>::Pop()
	{
		mSum -= mTop->number;
		--mCount;

		T returnNum = mTop->number;
		Node<T>* tmp = mTop;
		mTop = mTop->next;
		delete tmp;

		if (returnNum == mMinNum)
		{
			mMinNum = std::numeric_limits<T>::max();
			for (Node<T>* i = mTop; i != nullptr; i = i->next)
			{
				if (i->number < mMinNum)
					mMinNum = i->number;
			}
		}

		if (returnNum == mMaxNum)
		{
			mMaxNum = std::numeric_limits<T>::min();
			for (Node<T>* i = mTop; i != nullptr; i = i->next)
			{
				if (i->number > mMaxNum)
					mMaxNum = i->number;
			}
		}

		return returnNum;
	}

	template<typename T>
	inline const T& SmartStack<T>::Peek() const
	{
		return mTop->number;
	}

	template<typename T>
	inline const T& SmartStack<T>::GetMax() const
	{
		return mMaxNum;
	}

	template<typename T>
	inline const T& SmartStack<T>::GetMin() const
	{
		return mMinNum;
	}

	template<typename T>
	inline const double SmartStack<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 10000) / 10000;
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

		for (Node<T>* i = mTop; i != nullptr; i = i->next)
			deviationSquareSum += std::pow(i->number - average,2);

		return std::round(deviationSquareSum / mCount * 10000) / 10000;
	}

	template<typename T>
	inline const double SmartStack<T>::GetStandardDeviation() const
	{
		double average = GetAverage();
		double standardDeviation = 0;

		for (Node<T>* i = mTop; i != nullptr; i = i->next)
			standardDeviation += std::pow(i->number - average, 2);

		standardDeviation = sqrt(standardDeviation / mCount);

		return std::round(standardDeviation * 10000) / 10000;
	}

	template<typename T>
	inline const unsigned int SmartStack<T>::GetCount() const
	{
		return mCount;
	}

}

#pragma once
#include <limits>
#include <cmath>

template<typename T>
struct Node
{
	Node(T number, Node* next) :
		number(number),
		next(next)
	{}

	Node(const Node<T>& copy) :
		number(copy.number),
		next(nullptr)
	{}

	T number;
	Node* next;
};

namespace assignment3
{
	template<typename T>
	class SmartQueue
	{
	public:
		SmartQueue();
		~SmartQueue();
		SmartQueue(const SmartQueue<T>& copy);
		const SmartQueue& operator=(const SmartQueue<T>& copy);

		inline void Enqueue(const T& number);
		inline const T& Peek() const;
		inline const T Dequeue();
		inline const T& GetMax() const;
		inline const T& GetMin() const;
		inline const double GetAverage() const;
		inline const T& GetSum() const;
		inline const double GetVariance() const;
		inline const double GetStandardDeviation() const;
		inline const unsigned int GetCount() const;

	private:
		inline void copyFunc(const SmartQueue<T>& copy);

		Node<T>* mHead;
		Node<T>* mTail;
		unsigned int mCount;
		T mSum;
		T mMaxNum;
		T mMinNum;
		T mTmp;
	};

	template<typename T>
	inline SmartQueue<T>::SmartQueue() :
		mHead(nullptr),
		mTail(nullptr),
		mCount(0),
		mSum(0),
		mMaxNum(std::numeric_limits<T>::max()),
		mMinNum(std::numeric_limits<T>::min())
	{
		mTmp = 0;
	}

	template<typename T>
	inline SmartQueue<T>::~SmartQueue()
	{
		for (Node<T>* i = mHead; i != nullptr;)
		{
			Node<T>* tmp = i;
			i = i->next;
			delete tmp;
		}
	}

	template<typename T>
	inline SmartQueue<T>::SmartQueue(const SmartQueue<T>& copy)	:
		mCount(copy.mCount),
		mSum(copy.mSum),
		mMaxNum(copy.mMaxNum),
		mMinNum(copy.mMinNum)
	{
		copyFunc(copy);
	}

	template<typename T>
	const SmartQueue<T>& SmartQueue<T>::operator=(const SmartQueue<T>& copy)
	{
		if (this != &copy)
		{
			for (Node<T>* i = mHead; i != nullptr;)
			{
				Node<T>* tmp = i;
				i = i->next;
				delete tmp;
			}

			copyFunc(copy);
		}

		return *this;
	}

	template<typename T>
	inline void SmartQueue<T>::Enqueue(const T& number)
	{
		if (mHead == nullptr)
		{
			mHead = mTail = new Node<T>(number,nullptr);
		}
		else
		{
			mTail->next = new Node<T>(number, nullptr);
			mTail = mTail->next;
		}

		mSum += number;
		++mCount;

		if (mMax < number)
			mMax = number;

		if (mMin > number)
			mMin = number;
	}

	template<typename T>
	inline const T& SmartQueue<T>::Peek() const
	{
		return mHead->number;
	}

	template<typename T>
	inline const T SmartQueue<T>::Dequeue()
	{
		T answer = mHead->number;

		if (mHead == mTail)
		{
			delete mHead;
			mHead = mTail = nullptr;
		}
		else
		{
			Node<T>* tmp = mHead;
			mHead = mHead->next;
			delete tmp;
		}

		mSum -= number;
		--mCount;

		if (mMax == number)
		{
			T minNum = std::numeric_limits<T>::max();
			for (Node<T>* i = mHead; i != nullptr; i = i->next)
			{
				if (minNum > i->number)
					minNum = i->number;
			}

			mMinNum = minNum;
		}

		if (mMin == number)
		{
			T maxNum = std::numeric_limits<T>::min();
			for (Node<T>* i = mHead; i != nullptr; i = i->next)
			{
				if (maxNum < i->number)
					maxNum = i->number;
			}

			mMaxNum = maxNum;
		}

		return answer;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetMax() const
	{
		return mMaxNum;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetMin() const
	{
		return mMinNum;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetAverage() const
	{
		return static_cast<double>(mSum) / mCount;
	}

	template<typename T>
	inline const T& SmartQueue<T>::GetSum() const
	{
		return mSum;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetVariance() const
	{
		double average = GetAverage();
		double deviationSquareSum = 0;

		for (Node<T>* i = mHead; i != nullptr; i = i->next)
			deviationSquareSum += std::pow(i->number - average, 2);

		return std::round(deviationSquareSum / mCount * 10000) / 10000;
	}

	template<typename T>
	inline const double SmartQueue<T>::GetStandardDeviation() const
	{
		double average = GetAverage();
		double standardDeviation = 0;

		for (Node<T>* i = mHead; i != nullptr; i = i->next)
			standardDeviation += std::pow(i->number - average, 2);

		standardDeviation = sqrt(standardDeviation / mCount);

		return std::round(standardDeviation * 10000) / 10000;
	}

	template<typename T>
	inline const unsigned int SmartQueue<T>::GetCount() const
	{
		return mCount;
	}

	template<typename T>
	inline void SmartQueue<T>::copyFunc(const SmartQueue<T>& copy)
	{
		this->mHead = new Node<T>(*copy.mHead);

		Node<T>* i = this->mHead;
		Node<T>* j = copy.mHead;

		while (true)
		{
			if (j->next == nullptr)
			{
				mTail = i;
				break;
			}

			i->next = new Node<T>(*j->next);
			i = i->next;
			j = j->next;
		}
	}
}
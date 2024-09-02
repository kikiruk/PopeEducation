#pragma once
#include <cmath>

#include "MinMaxNum.h"
#include "Node.h"

namespace assignment3
{
	// SmartQueue 클래스: Queue 자료구조에 통계 연산 기능을 추가한 스마트 큐 클래스
	template<typename T>
	class SmartQueue
	{
	public:
		SmartQueue(); // 기본 생성자
		~SmartQueue(); // 소멸자
		SmartQueue(const SmartQueue<T>& copy); // 복사 생성자
		const SmartQueue<T>& operator=(const SmartQueue<T>& copy); // 대입 연산자 오버로드

		// SmartQueue의 주요 연산들
		inline void Enqueue(const T& number); // 큐에 데이터를 추가
		inline const T& Peek() const; // 큐의 첫 번째 요소를 반환 (제거하지 않음)
		inline const T Dequeue(); // 큐의 첫 번째 요소를 제거하고 반환
		inline const T GetMax() const; // 큐 내 최대값 반환
		inline const T GetMin() const; // 큐 내 최소값 반환
		inline const double GetAverage() const; // 큐 내 데이터의 평균값 반환
		inline const T& GetSum() const; // 큐 내 데이터의 합 반환
		inline const double GetVariance() const; // 큐 내 데이터의 분산 반환
		inline const double GetStandardDeviation() const; // 큐 내 데이터의 표준편차 반환
		inline const unsigned int GetCount() const; // 큐 내 데이터 개수 반환

	private:
		// 복사 작업을 수행하는 함수
		inline void copyFunc(const SmartQueue<T>& copy);

		Node<T>* mHead; // 큐의 첫 번째 노드를 가리키는 포인터
		Node<T>* mTail; // 큐의 마지막 노드를 가리키는 포인터
		unsigned int mCount; // 큐에 있는 데이터의 개수
		T mSum; // 큐 내 데이터의 합
		double mSumOfSquared; // 큐 내 데이터 제곱의 합
		Node<T>* mMaxNum; // 큐 내 최대값을 가진 노드를 가리키는 포인터
		Node<T>* mMinNum; // 큐 내 최소값을 가진 노드를 가리키는 포인터
	};

	// 기본 생성자: 초기 상태를 설정
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

	// 소멸자: 큐의 모든 노드를 삭제하여 메모리를 해제
	template<typename T>
	SmartQueue<T>::~SmartQueue()
	{
		for (Node<T>* i = mHead; i != nullptr;)
		{
			Node<T>* tmp = i;
			i = i->MNext;
			delete tmp; // 노드 메모리 해제
		}
	}

	// 복사 생성자: 다른 SmartQueue 객체를 복사하여 새로운 객체를 만듭니다.
	template<typename T>
	SmartQueue<T>::SmartQueue(const SmartQueue<T>& copy)	:
		mCount(copy.mCount),
		mSum(copy.mSum),
		mSumOfSquared(copy.mSumOfSquared)
	{
		copyFunc(copy); // 복사 작업 수행
	}

	// 대입 연산자 오버로드: 다른 SmartQueue 객체를 현재 객체로 복사합니다.
	template<typename T>
	const SmartQueue<T>& SmartQueue<T>::operator=(const SmartQueue<T>& copy)
	{
		if (this != &copy) // 자기 자신과의 대입을 방지
		{
			// 기존 노드들을 삭제
			for (Node<T>* i = mHead; i != nullptr;)
			{
				Node<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			// 새로운 값을 복사
			mCount = copy.mCount;
			mSum = copy.mSum;
			mSumOfSquared = copy.mSumOfSquared;

			copyFunc(copy); // 복사 작업 수행
		}

		return *this;
	}

	// Enqueue: 데이터를 큐에 추가하며 통계 값을 갱신
	template<typename T>
	inline void SmartQueue<T>::Enqueue(const T& number)
	{
		if (mHead == nullptr) // 큐가 비어있는 경우 새로운 노드를 생성
		{
			mHead = mTail = new Node<T>(number, nullptr);
			mMaxNum = mMinNum = mTail; // 최대값과 최소값 노드를 초기화
		}
		else
		{
			// 큐의 끝에 새로운 노드를 추가
			mTail->MNext = new Node<T>(number, nullptr);
			mTail = mTail->MNext;

			// 최대값과 최소값 갱신
			if (mMaxNum->MNumber < number)
				mMaxNum = mTail;

			if (mMinNum->MNumber > number)
				mMinNum = mTail;
		}

		mSum += number; // 전체 합 갱신
		mSumOfSquared += std::pow(number, 2); // 제곱 합 갱신
		++mCount; // 데이터 개수 증가
	}

	// Peek: 큐의 첫 번째 요소를 반환 (제거하지 않음)
	template<typename T>
	inline const T& SmartQueue<T>::Peek() const
	{
		return mHead->MNumber;
	}

	// Dequeue: 큐의 첫 번째 요소를 제거하고 반환합니다.
	template<typename T>
	inline const T SmartQueue<T>::Dequeue()
	{
		T answer = mHead->MNumber; // 반환할 값을 저장

		// 최소값을 제거할 경우 새로운 최소값을 찾습니다.
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

		// 최대값을 제거할 경우 새로운 최대값을 찾습니다.
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

		// 큐의 첫 번째 노드를 제거하고 다음 노드로 이동
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

		mSum -= answer; // 전체 합에서 제거한 값을 뺍니다.
		mSumOfSquared -= std::pow(answer, 2); // 제곱 합에서 제거한 값의 제곱을 뺍니다.
		--mCount; // 데이터 개수를 감소시킵니다.

		return answer; // 제거한 값을 반환합니다.
	}

	// GetMax: 큐 내 최대값을 반환합니다.
	template<typename T>
	inline const T SmartQueue<T>::GetMax() const
	{
		if (mHead == nullptr)
			return MinMaxNum<T>::GetMin(); // 큐가 비어있다면 최소값 반환

		return mMaxNum->MNumber; // 최대값 반환
	}

	// GetMin: 큐 내 최소값을 반환합니다.
	template<typename T>
	inline const T SmartQueue<T>::GetMin() const
	{
		if (mHead == nullptr)
			return MinMaxNum<T>::GetMax(); // 큐가 비어있다면 최대값 반환

		return mMinNum->MNumber; // 최소값 반환
	}

	// GetAverage: 큐 내 데이터의 평균값을 반환합니다.
	template<typename T>
	inline const double SmartQueue<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	// GetSum: 큐 내 데이터의 합을 반환합니다.
	template<typename T>
	inline const T& SmartQueue<T>::GetSum() const
	{
		return mSum;
	}

	// GetVariance: 큐 내 데이터의 분산을 계산하여 반환합니다.
	template<typename T>
	inline const double SmartQueue<T>::GetVariance() const
	{
		double deviationSquareSum = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);

		return std::round(deviationSquareSum * 1000) / 1000;
	}

	// GetStandardDeviation: 큐 내 데이터의 표준편차를 계산하여 반환합니다.
	template<typename T>
	inline const double SmartQueue<T>::GetStandardDeviation() const
	{
		double standardDeviation = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);
		standardDeviation = std::sqrt(standardDeviation);

		return std::round(standardDeviation * 1000) / 1000;
	}

	// GetCount: 큐 내 데이터 개수를 반환합니다.
	template<typename T>
	inline const unsigned int SmartQueue<T>::GetCount() const
	{
		return mCount;
	}

	// copyFunc: 복사 작업을 수행하는 함수
	template<typename T>
	inline void SmartQueue<T>::copyFunc(const SmartQueue<T>& copy)
	{
		this->mHead = new Node<T>(*copy.mHead); // 첫 번째 노드를 복사

		Node<T>* i = this->mHead;
		Node<T>* j = copy.mHead;

		// 모든 노드를 복사하여 새로운 큐를 생성
		while (true)
		{
			if (j->MNext == nullptr) // 마지막 노드까지 복사 완료
			{
				mTail = i; // 마지막 노드를 설정
				break;
			}

			i->MNext = new Node<T>(*j->MNext); // 다음 노드를 복사

			// 최대값 및 최소값 노드를 설정
			if (j == copy.mMaxNum)
				mMaxNum = i->MNext;

			if (j == copy.mMinNum)
				mMinNum = i->MNext; 

			i = i->MNext;
			j = j->MNext;
		}
	}
}
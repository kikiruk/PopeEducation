#pragma once
#include <cassert>
#include <cmath>

#include "MinMaxNum.h"
#include "Node.h"

namespace assignment3
{
	template<typename T>
	class QueueStack;

	// SmartStack 클래스 정의: Stack 자료구조를 기반으로 다양한 통계 연산 기능을 제공하는 스마트 스택 클래스
	template <typename T> // T는 데이터 타입 (예: int, double 등)
	class SmartStack
	{
		friend QueueStack<T>; // QueueStack 클래스가 SmartStack의 비공개 멤버에 접근할 수 있도록 설정

	public:
		SmartStack(); // 기본 생성자
		SmartStack(const SmartStack<T>& copy); // 복사 생성자
		~SmartStack(); // 소멸자

		// 대입 연산자 오버로드
		const SmartStack<T>& operator=(const SmartStack<T>& copy);

		// 스택 연산 및 통계 연산 메서드들
		inline void Push(const T& data); // 스택에 데이터 추가
		inline const T Pop(); // 스택에서 데이터 제거 및 반환
		inline const T& Peek() const; // 스택의 맨 위 데이터 참조
		inline const T GetMax() const; // 스택 내 최대값 반환
		inline const T GetMin() const; // 스택 내 최소값 반환
		inline const double GetAverage() const; // 스택 내 데이터 평균 반환
		inline const T& GetSum() const; // 스택 내 데이터 합계 반환

		// 추가 통계 연산 메서드들
		inline const double GetVariance() const; // 분산 계산 및 반환
		inline const double GetStandardDeviation() const; // 표준편차 계산 및 반환
		inline const unsigned int GetCount() const; // 스택에 있는 데이터 개수 반환

	private:
		inline void copyFunc(const SmartStack<T>& copy); // 복사 작업을 처리하는 함수

		NodeForStack<T>* mTop; // 스택의 맨 위 노드를 가리키는 포인터
		unsigned int mCount; // 스택에 있는 데이터의 개수
		T mSum; // 스택에 있는 데이터의 합
		double mSumOfSquared; // 스택에 있는 데이터의 제곱의 합
		T mMaxNum; // 스택 내 최대값
		T mMinNum; // 스택 내 최소값
	};


	// 기본 생성자: 초기 상태를 설정
	template<typename T>
	SmartStack<T>::SmartStack() :
		mTop(nullptr),
		mCount(0),
		mSum(0),
		mSumOfSquared(0),
		mMaxNum(MinMaxNum<T>::GetMin()), // 초기 최대값을 가장 작은 값으로 설정
		mMinNum(MinMaxNum<T>::GetMax()) // 초기 최소값을 가장 큰 값으로 설정
	{
	}

	// 복사 생성자: 다른 SmartStack 객체를 복사하여 새 객체를 만듭니다.
	template<typename T>
	inline SmartStack<T>::SmartStack(const SmartStack<T>& copy) :
		mCount(copy.mCount),
		mSum(copy.mSum),
		mSumOfSquared(copy.mSumOfSquared),
		mMaxNum(copy.mMaxNum),
		mMinNum(copy.mMinNum)
	{
		copyFunc(copy); // 복사 작업 수행
	}

	// 소멸자: 스택의 모든 노드를 삭제합니다.
	template<typename T>
	SmartStack<T>::~SmartStack()
	{
		for (NodeForStack<T>* i = mTop; i != nullptr;)
		{
			NodeForStack<T>* tmp = i;
			i = i->MNext;
			delete tmp; // 동적 할당된 노드 메모리 해제
		}
	}

	// 대입 연산자 오버로드: 다른 SmartStack 객체를 현재 객체로 복사
	template<typename T>
	inline const SmartStack<T>& SmartStack<T>::operator=(const SmartStack<T>& copy)
	{
		if (this != &copy) // 자기 자신과의 대입을 방지
		{
			// 기존 스택 노드를 모두 삭제
			for (NodeForStack<T>* i = mTop; i != nullptr;)
			{
				NodeForStack<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			// 새로운 값을 복사
			mCount = copy.mCount;
			mSum = copy.mSum;
			mSumOfSquared = copy.mSumOfSquared;
			mMaxNum = copy.mMaxNum;
			mMinNum = copy.mMinNum;

			copyFunc(copy); // 복사 작업 수행
		}

		return *this;
	}

	// Push: 스택에 데이터를 추가하며 통계 값을 갱신합니다.
	template<typename T>
	inline void SmartStack<T>::Push(const T& data)
	{
		mSum += data; // 합계 갱신
		mSumOfSquared += std::pow(data, 2); // 제곱 합 갱신
		++mCount; // 데이터 개수 증가

		// 스택이 비어있다면 새 노드를 생성하고, 최대값과 최소값을 초기화
		if (mTop == nullptr)
		{
			mTop = new NodeForStack<T>(data, nullptr);
			mMaxNum = mMinNum = data;
		}
		else
		{
			mTop = new NodeForStack<T>(data, mTop); // 새 노드를 스택의 맨 위에 추가

			if (data > mMaxNum)
				mMaxNum = data; // 최대값 갱신

			if (data < mMinNum)
				mMinNum = data; // 최소값 갱신
		}

		mTop->MMaxData = mMaxNum; // 노드에 현재 최대값 저장
		mTop->MMinData = mMinNum; // 노드에 현재 최소값 저장
	}

	// Pop: 스택의 맨 위 데이터를 제거하고 반환합니다.
	template<typename T>
	inline const T SmartStack<T>::Pop()
	{
		mSum -= mTop->MNumber; // 합계에서 맨 위 데이터 값을 뺍니다.
		mSumOfSquared -= std::pow(mTop->MNumber, 2); // 제곱 합에서 맨 위 데이터 제곱 값을 뺍니다.
		--mCount; // 데이터 개수 감소

		// 스택에 다음 노드가 있다면, 그 노드의 최대값과 최소값으로 갱신
		if (mTop->MNext != nullptr)
		{
			mMinNum = mTop->MNext->MMinData;
			mMaxNum = mTop->MNext->MMaxData;
		}
		else
		{
			// 스택이 비게 된다면 최대값과 최소값을 초기화
			mMinNum = MinMaxNum<T>::GetMax();
			mMaxNum = MinMaxNum<T>::GetMin();
		}

		T returnNum = mTop->MNumber; // 맨 위 데이터를 반환하기 위해 저장
		NodeForStack<T>* tmp = mTop;
		mTop = mTop->MNext; // 맨 위 노드를 제거하고 다음 노드로 이동
		delete tmp; // 제거된 노드 메모리 해제

		return returnNum; // 맨 위 데이터 반환
	}

	// Peek: 스택의 맨 위 데이터를 반환합니다.
	template<typename T>
	inline const T& SmartStack<T>::Peek() const
	{
		return mTop->MNumber;
	}

	// GetMax: 스택 내 최대값을 반환합니다.
	template<typename T>
	inline const T SmartStack<T>::GetMax() const
	{
		return mMaxNum;
	}

	// GetMin: 스택 내 최소값을 반환합니다.
	template<typename T>
	inline const T SmartStack<T>::GetMin() const
	{
		return mMinNum;
	}

	// GetAverage: 스택 내 데이터의 평균을 반환합니다.
	template<typename T>
	inline const double SmartStack<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	// GetSum: 스택 내 데이터의 합을 반환합니다.
	template<typename T>
	inline const T& SmartStack<T>::GetSum() const
	{
		return mSum;
	}

	// GetVariance: 분산을 계산하고 반환합니다.
	template<typename T>
	inline const double SmartStack<T>::GetVariance() const
	{
		double deviationSquareSum = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);

		return std::round(deviationSquareSum * 1000) / 1000;
	}

	// GetStandardDeviation: 표준편차를 계산하고 반환합니다.
	template<typename T>
	inline const double SmartStack<T>::GetStandardDeviation() const
	{
		double standardDeviation = (mSumOfSquared / mCount) -
			std::pow((static_cast<double>(mSum) / mCount), 2);
		standardDeviation = std::sqrt(standardDeviation);

		return std::round(standardDeviation * 1000) / 1000;
	}

	// GetCount: 스택에 있는 데이터 개수를 반환합니다.
	template<typename T>
	inline const unsigned int SmartStack<T>::GetCount() const
	{
		return mCount;
	}

	// copyFunc: 복사 작업을 수행하는 함수
	template<typename T>
	inline void SmartStack<T>::copyFunc(const SmartStack<T>& copy)
	{
		NodeForStack<T> tmp(0, nullptr); // 임시 노드 생성
		NodeForStack<T>* j = &tmp; // 임시 노드를 가리키는 포인터
		NodeForStack<T>* i = copy.mTop; // 복사할 스택의 맨 위 노드를 가리키는 포인터

		T  minNum = MinMaxNum<T>::GetMax(); // 초기 최소값 설정
		T  maxNum = MinMaxNum<T>::GetMin(); // 초기 최대값 설정

		// 복사할 스택을 순회하면서 노드 복사
		for (; i != nullptr; i = i->MNext, j = j->MNext)
		{
			j->MNext = new NodeForStack<T>(*i); // 현재 노드를 복사하여 새로운 노드 생성
			j->MNext->MMaxData = i->MMaxData; // 최대값 복사
			j->MNext->MMinData = i->MMinData; // 최소값 복사

			if (i == copy.mTop)
				mTop = j->MNext; // 복사한 스택의 맨 위 노드 설정
		}
	}
}
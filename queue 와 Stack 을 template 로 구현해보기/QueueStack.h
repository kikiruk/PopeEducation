
#pragma once

#include "SmartStack.h"

// StackNode 클래스: QueueStack 내에서 스택을 구성하는 각 노드를 정의
template<typename T>
class StackNode
{
public:
	// 생성자: 다음 노드를 가리키는 포인터를 초기화
	StackNode(StackNode<T>* next) :
		MStack(),
		MNext(next)
	{}

	// 복사 생성자: StackNode 객체를 복사하여 생성
	StackNode(const StackNode<T>& copy) :
		MStack(copy.MStack),
		MNext(nullptr)
	{}

	assignment3::SmartStack<T> MStack; // SmartStack 객체를 멤버로 포함
	StackNode<T>* MNext; // 다음 노드를 가리키는 포인터
};

namespace assignment3
{
	// QueueStack 클래스: SmartStack을 노드로 사용하는 큐와 스택의 결합 자료구조
	template<typename T>
	class QueueStack
	{
	public:
		QueueStack(unsigned int maxStackSize); // 생성자: 최대 스택 크기를 설정
		~QueueStack(); // 소멸자: 모든 노드를 삭제
		QueueStack(const QueueStack<T>& copy); // 복사 생성자
		const QueueStack<T>& operator=(const QueueStack<T>& copy); // 대입 연산자 오버로드

		// QueueStack의 주요 연산들
		inline void Enqueue(const T& number); // 데이터를 큐에 추가
		inline const T& Peek() const; // 큐의 첫 번째 요소를 확인
		inline const T Dequeue(); // 큐에서 첫 번째 요소를 제거하고 반환
		inline const T GetMax() const; // 큐 내 최대값 반환
		inline const T GetMin() const; // 큐 내 최소값 반환
		inline const double GetAverage() const; // 큐 내 평균값 반환
		inline const T& GetSum() const; // 큐 내 데이터의 합 반환
		inline const unsigned int GetCount() const; // 큐 내 데이터 개수 반환
		inline const unsigned int GetStackCount() const; // 큐 내 스택의 개수 반환

	private:
		// 복사 작업을 수행하는 함수
		inline void copyFunc(const QueueStack<T>& copy);

		StackNode<T>* mHead; // 큐의 첫 번째 노드를 가리키는 포인터
		StackNode<T>* mTail; // 큐의 마지막 노드를 가리키는 포인터
		unsigned int mMaxStackSize; // 하나의 스택에 들어갈 수 있는 최대 데이터 개수
		unsigned int mCount; // 큐에 있는 전체 데이터 개수
		unsigned int mStackCount; // 큐에 있는 스택의 개수
		T mSum; // 큐 내 데이터의 합
		StackNode<T>* mMaxNum; // 큐 내 최대값을 가진 노드를 가리키는 포인터
		StackNode<T>* mMinNum; // 큐 내 최소값을 가진 노드를 가리키는 포인터
	};

	// 생성자: 초기 상태를 설정
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

	// 소멸자: 모든 노드를 삭제하여 메모리를 해제
	template<typename T>
	QueueStack<T>::~QueueStack()
	{
		for (StackNode<T>* i = mHead; i != nullptr;)
		{
			StackNode<T>* tmp = i;
			i = i->MNext;
			delete tmp; // 노드 메모리 해제
		}
	}

	// 복사 생성자: 다른 QueueStack 객체를 복사하여 새로운 객체를 만듭니다.
	template<typename T>
	QueueStack<T>::QueueStack(const QueueStack<T>& copy) :
		mMaxStackSize(copy.mMaxStackSize),
		mCount(copy.mCount),
		mStackCount(copy.mStackCount),
		mSum(copy.mSum)
	{
		copyFunc(copy); // 복사 작업 수행
	}

	// 대입 연산자 오버로드: 다른 QueueStack 객체를 현재 객체로 복사합니다.
	template<typename T>
	inline const QueueStack<T>& QueueStack<T>::operator=(const QueueStack<T>& copy)
	{
		if (this != &copy) // 자기 자신과의 대입을 방지
		{
			// 기존 노드들을 삭제
			for (StackNode<T>* i = mHead; i != nullptr;)
			{
				StackNode<T>* tmp = i;
				i = i->MNext;
				delete tmp;
			}

			// 새로운 값을 복사
			mMaxStackSize = copy.mMaxStackSize;
			mCount = copy.mCount;
			mStackCount = copy.mStackCount;
			mSum = copy.mSum;

			copyFunc(copy); // 복사 작업 수행
		}

		return *this;
	}

	// Enqueue: 데이터를 큐에 추가하며 스택을 관리
	template<typename T>
	inline void QueueStack<T>::Enqueue(const T& number)
	{
		if (mHead == nullptr) // 큐가 비어있는 경우 새로운 노드 생성
		{
			mHead = mTail = new StackNode<T>(nullptr);
			++mStackCount;

			mTail->MStack.Push(number); // 스택에 데이터 추가

			// 최대값과 최소값 노드를 초기화
			mMaxNum = mMinNum = mTail;
		}
		else
		{
			// 마지막 스택이 가득 찼다면 새로운 노드를 생성하여 추가
			if (mTail->MStack.mCount == mMaxStackSize)
			{
				mTail->MNext = new StackNode<T>(nullptr);
				++mStackCount;
				mTail = mTail->MNext;
			}

			mTail->MStack.Push(number); // 새로운 데이터 추가

			// 최대값과 최소값 갱신
			if (mMaxNum->MStack.mMaxNum < number)
				mMaxNum = mTail;

			if (mMinNum->MStack.mMinNum > number)
				mMinNum = mTail;
		}

		mSum += number; // 전체 합 갱신
		++mCount; // 전체 데이터 개수 증가
	}

	// Peek: 큐의 첫 번째 요소를 반환합니다.
	template<typename T>
	inline const T& QueueStack<T>::Peek() const
	{
		return mHead->MStack.mTop->MNumber;
	}

	// Dequeue: 큐에서 첫 번째 요소를 제거하고 반환합니다.
	template<typename T>
	inline const T QueueStack<T>::Dequeue()
	{
		bool bFindMinNum = false;
		bool bFindMaxNum = false;

		// 제거할 데이터가 최대값 또는 최소값인지 확인
		if (mHead->MStack.mTop->MNumber == mMaxNum->MStack.mMaxNum)
			bFindMaxNum = true;

		if (mHead->MStack.mTop->MNumber == mMinNum->MStack.mMinNum)
			bFindMinNum = true;

		T answer = mHead->MStack.mTop->MNumber; // 반환할 값을 저장

		// 첫 번째 스택에 하나의 요소만 있는 경우
		if (mHead->MStack.mCount == 1)
		{
			// 큐에 하나의 노드만 있는 경우
			if (mHead == mTail)
			{
				delete mHead;
				mHead = mTail = nullptr;
			}
			else
			{
				// 첫 번째 노드를 삭제하고 다음 노드로 이동
				StackNode<T>* tmp = mHead;
				mHead = mHead->MNext;
				delete tmp;
			}

			--mStackCount;
		}
		else
		{
			mHead->MStack.Pop(); // 첫 번째 스택에서 요소를 제거
		}

		// 최소값을 찾았던 경우, 새로운 최소값을 찾습니다.
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

		// 최대값을 찾았던 경우, 새로운 최대값을 찾습니다.
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

		mSum -= answer; // 전체 합에서 제거한 값을 뺍니다.
		--mCount; // 전체 데이터 개수를 감소시킵니다.

		return answer; // 제거한 값을 반환합니다.
	}

	// GetMax: 큐 내 최대값을 반환합니다.
	template<typename T>
	inline const T QueueStack<T>::GetMax() const
	{
		if (mMaxNum == nullptr)
			return MinMaxNum<T>::GetMin();

		return mMaxNum->MStack.mMaxNum;
	}

	// GetMin: 큐 내 최소값을 반환합니다.
	template<typename T>
	inline const T QueueStack<T>::GetMin() const
	{
		if (mMinNum == nullptr)
			return MinMaxNum<T>::GetMax();

		return mMinNum->MStack.mMinNum;
	}

	// GetAverage: 큐 내 데이터의 평균을 반환합니다.
	template<typename T>
	inline const double QueueStack<T>::GetAverage() const
	{
		return std::round(static_cast<double>(mSum) / mCount * 1000) / 1000;
	}

	// GetSum: 큐 내 데이터의 합을 반환합니다.
	template<typename T>
	inline const T& QueueStack<T>::GetSum() const
	{
		return mSum;
	}

	// GetCount: 큐 내 데이터 개수를 반환합니다.
	template<typename T>
	inline const unsigned int QueueStack<T>::GetCount() const
	{
		return mCount;
	}

	// GetStackCount: 큐 내 스택의 개수를 반환합니다.
	template<typename T>
	inline const unsigned int QueueStack<T>::GetStackCount() const
	{
		return mStackCount;
	}

	// copyFunc: 복사 작업을 수행하는 함수
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
#pragma once
#include <queue>    // 큐 자료구조를 사용하기 위해 포함
#include <cstring>  // memset 등을 사용하기 위해 포함

namespace lab9
{
    // ObjectPool 클래스 템플릿 정의
    // 객체를 재사용하기 위해 객체 풀을 관리하는 클래스
    template <class T>
    class ObjectPool
    {
    public:
        ObjectPool(size_t maxPoolSize);  // 생성자: 최대 풀 크기를 설정
        ~ObjectPool();  // 소멸자: 풀에 남아 있는 모든 객체를 삭제
        ObjectPool(const ObjectPool& copy) = delete;  // 복사 생성자 사용 금지

        ObjectPool& operator = (const ObjectPool&) = delete;  // 복사 대입 연산자 사용 금지
        T* const Get();  // 풀에서 객체를 가져오거나 새로 생성
        void Return(T* const objectPointer);  // 객체를 풀로 반환
        const size_t GetFreeObjectCount() const;  // 현재 풀에 남아 있는 객체 수를 반환
        const size_t GetMaxFreeObjectCount() const;  // 최대 풀 크기를 반환

    private:
        const size_t mMaxPoolSize;  // 최대 풀 크기
        std::queue<T*> mArr;  // 객체를 저장할 큐
    };

    // 생성자: 최대 풀 크기를 설정하고 초기화
    template<class T>
    inline ObjectPool<T>::ObjectPool(size_t maxPoolSize) :
        mMaxPoolSize(maxPoolSize)  // 최대 풀 크기를 설정
    {}

    // 소멸자: 풀에 남아 있는 모든 객체를 삭제
    template<class T>
    inline ObjectPool<T>::~ObjectPool()
    {
        // 큐에 남아 있는 모든 객체를 삭제하고 큐를 비움
        while (!mArr.empty())
        {
            delete mArr.front();  // 큐의 맨 앞 객체 삭제
            mArr.pop();  // 큐에서 객체 제거
        }
    }

    // Get 함수: 풀에서 객체를 가져오거나 새로 생성하여 반환
    template<class T>
    inline T* const ObjectPool<T>::Get()
    {
        if (mArr.size() == 0)  // 풀에 사용 가능한 객체가 없는 경우
            return new T();  // 새 객체를 생성하여 반환

        T* tmp = mArr.front();  // 큐의 맨 앞 객체를 가져옴
        mArr.pop();  // 큐에서 객체 제거

        return tmp;  // 가져온 객체 반환
    }

    // Return 함수: 객체를 풀로 반환
    template<class T>
    inline void ObjectPool<T>::Return(T* const objectPointer)
    {
        if (mArr.size() == mMaxPoolSize)  // 풀에 빈 공간이 없는 경우
        {
            delete objectPointer;  // 객체를 삭제
            return;
        }

        mArr.push(objectPointer);  // 객체를 풀에 추가
    }

    // GetFreeObjectCount 함수: 현재 풀에 남아 있는 객체 수를 반환
    template<class T>
    inline const size_t ObjectPool<T>::GetFreeObjectCount() const
    {
        return mArr.size();  // 큐의 크기를 반환
    }

    // GetMaxFreeObjectCount 함수: 최대 풀 크기를 반환
    template<class T>
    inline const size_t ObjectPool<T>::GetMaxFreeObjectCount() const
    {
        return mMaxPoolSize;  // 최대 풀 크기를 반환
    }
}
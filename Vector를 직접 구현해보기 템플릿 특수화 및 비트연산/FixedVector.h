#include <cstdint>  // 정수형 자료형들을 정의하기 위해 포함
#include <cstring>  // 메모리 조작을 위한 함수들 포함 (memset, memcpy)
#include <cassert>  // 디버깅을 위한 assert 포함
#pragma once       // 헤더 파일의 중복 포함을 방지

namespace lab8
{
    // 고정 크기의 벡터 클래스를 정의하는 템플릿 클래스
    template <class T, size_t N>
    class FixedVector
    {
    public:
        FixedVector();  // 기본 생성자
        FixedVector(const FixedVector& copy);  // 복사 생성자
        const FixedVector& operator=(const FixedVector& copy);  // 복사 대입 연산자

        bool Add(const T& data);  // 벡터에 데이터 추가
        bool Remove(const T& data);  // 벡터에서 데이터 제거
        const T& Get(const size_t index) const;  // 특정 인덱스의 데이터를 반환 (상수형)
        T& operator[](const size_t index);  // 특정 인덱스의 데이터를 반환 (비상수형)
        const int GetIndex(const T& data) const;  // 특정 데이터의 인덱스를 반환
        const size_t GetSize() const;  // 현재 벡터의 크기를 반환
        const size_t GetCapacity() const;  // 벡터의 최대 크기를 반환

    private:
        size_t mSize;  // 현재 벡터에 저장된 요소의 수
        T mArr[N];  // 고정 크기의 배열로 벡터를 구현
    };

    // 기본 생성자: 벡터의 크기를 0으로 초기화하고 배열을 초기화
    template<class T, size_t N>
    inline FixedVector<T, N>::FixedVector() :
        mSize(0)
    {
        memset(mArr, 0, sizeof(mArr));  // 배열을 0으로 초기화
    }

    // 복사 생성자: 다른 FixedVector 객체로부터 데이터를 복사하여 초기화
    template<class T, size_t N>
    inline FixedVector<T, N>::FixedVector(const FixedVector& copy) :
        mSize(copy.mSize)
    {
        memcpy(mArr, copy.mArr, sizeof(mArr));  // 배열의 내용을 복사
    }

    // 복사 대입 연산자: 객체에 다른 FixedVector 객체의 데이터를 복사
    template<class T, size_t N>
    const FixedVector<T, N>& FixedVector<T, N>::operator=(const FixedVector& copy)
    {
        if (this != &copy)  // 자기 자신과의 대입을 방지
        {
            mSize = copy.mSize;
            memcpy(mArr, copy.mArr, sizeof(mArr));  // 배열의 내용을 복사
        }

        return *this;  // 현재 객체를 반환
    }

    // Add 함수: 벡터에 데이터를 추가, 성공 시 true 반환, 실패 시 false 반환
    template<class T, size_t N>
    inline bool FixedVector<T, N>::Add(const T& data)
    {
        if (mSize == N)  // 벡터가 꽉 찬 경우
            return false;

        mArr[mSize++] = data;  // 데이터를 추가하고 크기를 증가

        return true;
    }

    // Remove 함수: 벡터에서 특정 데이터를 제거, 성공 시 true 반환, 실패 시 false 반환
    template<class T, size_t N>
    inline bool FixedVector<T, N>::Remove(const T& data)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            if (mArr[i] == data)  // 데이터를 찾은 경우
            {
                if (i != mSize - 1)  // 마지막 요소가 아닌 경우
                    memcpy(mArr + i, mArr + i + 1, sizeof(T) * (mSize - (i + 1)));  // 데이터를 이동

                memset(mArr + --mSize, 0, sizeof(T));  // 마지막 요소를 0으로 설정하고 크기를 감소
                return true;
            }
        }

        return false;  // 데이터를 찾지 못한 경우
    }

    // Get 함수: 특정 인덱스의 데이터를 반환 (상수형)
    template<class T, size_t N>
    inline const T& FixedVector<T, N>::Get(const size_t index) const
    {
        return mArr[index];
    }

    // operator[]: 특정 인덱스의 데이터를 반환 (비상수형)
    template<class T, size_t N>
    inline T& FixedVector<T, N>::operator[](const size_t index)
    {
        return mArr[index];
    }

    // GetIndex 함수: 특정 데이터의 인덱스를 반환, 찾지 못하면 -1 반환
    template<class T, size_t N>
    inline const int FixedVector<T, N>::GetIndex(const T& data) const
    {
        for (size_t i = 0; i < N; i++)
        {
            if (mArr[i] == data)  // 데이터를 찾은 경우
                return i;
        }

        return -1;  // 데이터를 찾지 못한 경우
    }

    // GetSize 함수: 현재 벡터에 저장된 요소의 수를 반환
    template<class T, size_t N>
    inline const size_t FixedVector<T, N>::GetSize() const
    {
        return mSize;
    }

    // GetCapacity 함수: 벡터의 최대 크기를 반환
    template<class T, size_t N>
    inline const size_t FixedVector<T, N>::GetCapacity() const
    {
        return N;
    }
}
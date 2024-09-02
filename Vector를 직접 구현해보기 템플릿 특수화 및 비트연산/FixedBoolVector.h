#pragma once

using namespace std;

namespace lab8
{
    // 고정 크기의 bool 타입 벡터를 정의하는 템플릿 클래스
    // bool 타입을 비트 단위로 저장하여 메모리 사용을 최적화
    template <size_t N>
    class FixedVector<bool, N>
    {
    public:
        FixedVector();  // 기본 생성자
        FixedVector(const FixedVector& copy);  // 복사 생성자
        const FixedVector& operator=(const FixedVector& copy);  // 복사 대입 연산자

        bool Add(const bool data);  // 벡터에 데이터 추가
        bool Remove(const bool data);  // 벡터에서 데이터 제거
        const bool Get(const size_t index) const;  // 특정 인덱스의 데이터를 반환 (상수형)
        bool operator[](const size_t index);  // 특정 인덱스의 데이터를 반환 (비상수형)
        const int GetIndex(const bool data) const;  // 특정 데이터의 인덱스를 반환
        const size_t GetSize() const;  // 현재 벡터의 크기를 반환
        const size_t GetCapacity() const;  // 벡터의 최대 크기를 반환

    private:
        uint32_t doSquared(uint32_t num) const;  // 주어진 수의 2의 거듭제곱을 반환
        uint32_t mSize;  // 현재 벡터에 저장된 요소의 수
        uint32_t mArr[N / 32 + 1];  // 고정 크기의 배열로 비트 벡터를 구현 (32비트 단위로 저장)
    };

    // 기본 생성자: 벡터의 크기를 0으로 초기화하고 배열을 0으로 초기화
    template<size_t N>
    inline FixedVector<bool, N>::FixedVector() :
        mSize(0)
    {
        memset(mArr, 0, sizeof(mArr));  // 배열을 0으로 초기화
    }

    // 복사 생성자: 다른 FixedVector 객체로부터 데이터를 복사하여 초기화
    template<size_t N>
    inline FixedVector<bool, N>::FixedVector(const FixedVector& copy) :
        mSize(copy.mSize)
    {
        memcpy(mArr, copy.mArr, sizeof(mArr));  // 배열의 내용을 복사
    }

    // 복사 대입 연산자: 객체에 다른 FixedVector 객체의 데이터를 복사
    template<size_t N>
    const FixedVector<bool, N>& FixedVector<bool, N>::operator=(const FixedVector& copy)
    {
        if (this != &copy)  // 자기 자신과의 대입을 방지
        {
            mSize = copy.mSize;
            memcpy(mArr, copy.mArr, sizeof(mArr));  // 배열의 내용을 복사
        }

        return *this;  // 현재 객체를 반환
    }

    // Add 함수: 벡터에 데이터를 추가, 성공 시 true 반환, 실패 시 false 반환
    template<size_t N>
    inline bool FixedVector<bool, N>::Add(const bool bData)
    {
        if (mSize == N)  // 벡터가 꽉 찬 경우
            return false;

        if (bData == true)  // true인 경우 비트를 설정
            mArr[mSize / 32] |= doSquared(mSize % 32);
        else  // false인 경우 비트를 해제
            mArr[mSize / 32] &= ~doSquared(mSize % 32);

        ++mSize;  // 크기를 증가

        return true;
    }

    // Remove 함수: 벡터에서 특정 데이터를 제거, 성공 시 true 반환, 실패 시 false 반환
    template<size_t N>
    inline bool FixedVector<bool, N>::Remove(const bool bData)
    {
        for (uint32_t i = 0; i < mSize; i++)
        {
            // 데이터를 찾은 경우
            if (((mArr[i / 32] | doSquared(i % 32)) == mArr[i / 32]) == bData)
            {
                // 데이터를 제거하고 남은 요소들을 이동
                for (uint32_t j = i + 1; j < mSize; j++)
                {
                    if ((mArr[j / 32] | doSquared(j % 32)) == mArr[j / 32])
                        mArr[(j - 1) / 32] |= doSquared((j - 1) % 32);
                    else
                        mArr[(j - 1) / 32] &= ~doSquared((j - 1) % 32);
                }

                --mSize;  // 크기를 감소
                return true;
            }
        }

        return false;  // 데이터를 찾지 못한 경우
    }

    // Get 함수: 특정 인덱스의 데이터를 반환 (상수형)
    template<size_t N>
    inline const bool FixedVector<bool, N>::Get(const size_t index) const
    {
        return ((mArr[index / 32] | doSquared(index % 32)) == mArr[index / 32]);
    }

    // operator[]: 특정 인덱스의 데이터를 반환 (비상수형)
    template<size_t N>
    inline bool FixedVector<bool, N>::operator[](const size_t index)
    {
        return ((mArr[index / 32] | doSquared(index % 32)) == mArr[index / 32]);
    }

    // GetIndex 함수: 특정 데이터의 인덱스를 반환, 찾지 못하면 -1 반환
    template<size_t N>
    inline const int FixedVector<bool, N>::GetIndex(const bool bData) const
    {
        for (uint32_t i = 0; i < mSize; i++)
        {
            if (((mArr[i / 32] | doSquared(i % 32)) == mArr[i / 32]) == bData)
                return i;
        }

        return -1;  // 데이터를 찾지 못한 경우
    }

    // GetSize 함수: 현재 벡터에 저장된 요소의 수를 반환
    template<size_t N>
    inline const size_t FixedVector<bool, N>::GetSize() const
    {
        return mSize;
    }

    // GetCapacity 함수: 벡터의 최대 크기를 반환
    template<size_t N>
    inline const size_t FixedVector<bool, N>::GetCapacity() const
    {
        return N;
    }

    // doSquared 함수: 주어진 숫자의 2의 거듭제곱 값을 반환
    template<size_t N>
    inline uint32_t FixedVector<bool, N>::doSquared(uint32_t num) const
    {
        switch (num)
        {
        case 0:
            return 1;
        case 1:
            return 2;
        case 2:
            return 4;
        case 3:
            return 8;
        case 4:
            return 16;
        case 5:
            return 32;
        case 6:
            return 64;
        case 7:
            return 128;
        case 8:
            return 256;
        case 9:
            return 512;
        case 10:
            return 1024;
        case 11:
            return 2048;
        case 12:
            return 4096;
        case 13:
            return 8192;
        case 14:
            return 16384;
        case 15:
            return 32768;
        case 16:
            return 65536;
        case 17:
            return 131072;
        case 18:
            return 262144;
        case 19:
            return 524288;
        case 20:
            return 1048576;
        case 21:
            return 2097152;
        case 22:
            return 4194304;
        case 23:
            return 8388608;
        case 24:
            return 16777216;
        case 25:
            return 33554432;
        case 26:
            return 67108864;
        case 27:
            return 134217728;
        case 28:
            return 268435456;
        case 29:
            return 536870912;
        case 30:
            return 1073741824;
        case 31:
            return 2147483648;
        default:
            assert(false);  // 잘못된 입력을 방지하기 위한 assert
            return 0;
        }
    }
}
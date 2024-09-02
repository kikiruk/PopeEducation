#include <cstdint>  // ������ �ڷ������� �����ϱ� ���� ����
#include <cstring>  // �޸� ������ ���� �Լ��� ���� (memset, memcpy)
#include <cassert>  // ������� ���� assert ����
#pragma once       // ��� ������ �ߺ� ������ ����

namespace lab8
{
    // ���� ũ���� ���� Ŭ������ �����ϴ� ���ø� Ŭ����
    template <class T, size_t N>
    class FixedVector
    {
    public:
        FixedVector();  // �⺻ ������
        FixedVector(const FixedVector& copy);  // ���� ������
        const FixedVector& operator=(const FixedVector& copy);  // ���� ���� ������

        bool Add(const T& data);  // ���Ϳ� ������ �߰�
        bool Remove(const T& data);  // ���Ϳ��� ������ ����
        const T& Get(const size_t index) const;  // Ư�� �ε����� �����͸� ��ȯ (�����)
        T& operator[](const size_t index);  // Ư�� �ε����� �����͸� ��ȯ (������)
        const int GetIndex(const T& data) const;  // Ư�� �������� �ε����� ��ȯ
        const size_t GetSize() const;  // ���� ������ ũ�⸦ ��ȯ
        const size_t GetCapacity() const;  // ������ �ִ� ũ�⸦ ��ȯ

    private:
        size_t mSize;  // ���� ���Ϳ� ����� ����� ��
        T mArr[N];  // ���� ũ���� �迭�� ���͸� ����
    };

    // �⺻ ������: ������ ũ�⸦ 0���� �ʱ�ȭ�ϰ� �迭�� �ʱ�ȭ
    template<class T, size_t N>
    inline FixedVector<T, N>::FixedVector() :
        mSize(0)
    {
        memset(mArr, 0, sizeof(mArr));  // �迭�� 0���� �ʱ�ȭ
    }

    // ���� ������: �ٸ� FixedVector ��ü�κ��� �����͸� �����Ͽ� �ʱ�ȭ
    template<class T, size_t N>
    inline FixedVector<T, N>::FixedVector(const FixedVector& copy) :
        mSize(copy.mSize)
    {
        memcpy(mArr, copy.mArr, sizeof(mArr));  // �迭�� ������ ����
    }

    // ���� ���� ������: ��ü�� �ٸ� FixedVector ��ü�� �����͸� ����
    template<class T, size_t N>
    const FixedVector<T, N>& FixedVector<T, N>::operator=(const FixedVector& copy)
    {
        if (this != &copy)  // �ڱ� �ڽŰ��� ������ ����
        {
            mSize = copy.mSize;
            memcpy(mArr, copy.mArr, sizeof(mArr));  // �迭�� ������ ����
        }

        return *this;  // ���� ��ü�� ��ȯ
    }

    // Add �Լ�: ���Ϳ� �����͸� �߰�, ���� �� true ��ȯ, ���� �� false ��ȯ
    template<class T, size_t N>
    inline bool FixedVector<T, N>::Add(const T& data)
    {
        if (mSize == N)  // ���Ͱ� �� �� ���
            return false;

        mArr[mSize++] = data;  // �����͸� �߰��ϰ� ũ�⸦ ����

        return true;
    }

    // Remove �Լ�: ���Ϳ��� Ư�� �����͸� ����, ���� �� true ��ȯ, ���� �� false ��ȯ
    template<class T, size_t N>
    inline bool FixedVector<T, N>::Remove(const T& data)
    {
        for (size_t i = 0; i < mSize; i++)
        {
            if (mArr[i] == data)  // �����͸� ã�� ���
            {
                if (i != mSize - 1)  // ������ ��Ұ� �ƴ� ���
                    memcpy(mArr + i, mArr + i + 1, sizeof(T) * (mSize - (i + 1)));  // �����͸� �̵�

                memset(mArr + --mSize, 0, sizeof(T));  // ������ ��Ҹ� 0���� �����ϰ� ũ�⸦ ����
                return true;
            }
        }

        return false;  // �����͸� ã�� ���� ���
    }

    // Get �Լ�: Ư�� �ε����� �����͸� ��ȯ (�����)
    template<class T, size_t N>
    inline const T& FixedVector<T, N>::Get(const size_t index) const
    {
        return mArr[index];
    }

    // operator[]: Ư�� �ε����� �����͸� ��ȯ (������)
    template<class T, size_t N>
    inline T& FixedVector<T, N>::operator[](const size_t index)
    {
        return mArr[index];
    }

    // GetIndex �Լ�: Ư�� �������� �ε����� ��ȯ, ã�� ���ϸ� -1 ��ȯ
    template<class T, size_t N>
    inline const int FixedVector<T, N>::GetIndex(const T& data) const
    {
        for (size_t i = 0; i < N; i++)
        {
            if (mArr[i] == data)  // �����͸� ã�� ���
                return i;
        }

        return -1;  // �����͸� ã�� ���� ���
    }

    // GetSize �Լ�: ���� ���Ϳ� ����� ����� ���� ��ȯ
    template<class T, size_t N>
    inline const size_t FixedVector<T, N>::GetSize() const
    {
        return mSize;
    }

    // GetCapacity �Լ�: ������ �ִ� ũ�⸦ ��ȯ
    template<class T, size_t N>
    inline const size_t FixedVector<T, N>::GetCapacity() const
    {
        return N;
    }
}
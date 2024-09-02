#pragma once

using namespace std;

namespace lab8
{
    // ���� ũ���� bool Ÿ�� ���͸� �����ϴ� ���ø� Ŭ����
    // bool Ÿ���� ��Ʈ ������ �����Ͽ� �޸� ����� ����ȭ
    template <size_t N>
    class FixedVector<bool, N>
    {
    public:
        FixedVector();  // �⺻ ������
        FixedVector(const FixedVector& copy);  // ���� ������
        const FixedVector& operator=(const FixedVector& copy);  // ���� ���� ������

        bool Add(const bool data);  // ���Ϳ� ������ �߰�
        bool Remove(const bool data);  // ���Ϳ��� ������ ����
        const bool Get(const size_t index) const;  // Ư�� �ε����� �����͸� ��ȯ (�����)
        bool operator[](const size_t index);  // Ư�� �ε����� �����͸� ��ȯ (������)
        const int GetIndex(const bool data) const;  // Ư�� �������� �ε����� ��ȯ
        const size_t GetSize() const;  // ���� ������ ũ�⸦ ��ȯ
        const size_t GetCapacity() const;  // ������ �ִ� ũ�⸦ ��ȯ

    private:
        uint32_t doSquared(uint32_t num) const;  // �־��� ���� 2�� �ŵ������� ��ȯ
        uint32_t mSize;  // ���� ���Ϳ� ����� ����� ��
        uint32_t mArr[N / 32 + 1];  // ���� ũ���� �迭�� ��Ʈ ���͸� ���� (32��Ʈ ������ ����)
    };

    // �⺻ ������: ������ ũ�⸦ 0���� �ʱ�ȭ�ϰ� �迭�� 0���� �ʱ�ȭ
    template<size_t N>
    inline FixedVector<bool, N>::FixedVector() :
        mSize(0)
    {
        memset(mArr, 0, sizeof(mArr));  // �迭�� 0���� �ʱ�ȭ
    }

    // ���� ������: �ٸ� FixedVector ��ü�κ��� �����͸� �����Ͽ� �ʱ�ȭ
    template<size_t N>
    inline FixedVector<bool, N>::FixedVector(const FixedVector& copy) :
        mSize(copy.mSize)
    {
        memcpy(mArr, copy.mArr, sizeof(mArr));  // �迭�� ������ ����
    }

    // ���� ���� ������: ��ü�� �ٸ� FixedVector ��ü�� �����͸� ����
    template<size_t N>
    const FixedVector<bool, N>& FixedVector<bool, N>::operator=(const FixedVector& copy)
    {
        if (this != &copy)  // �ڱ� �ڽŰ��� ������ ����
        {
            mSize = copy.mSize;
            memcpy(mArr, copy.mArr, sizeof(mArr));  // �迭�� ������ ����
        }

        return *this;  // ���� ��ü�� ��ȯ
    }

    // Add �Լ�: ���Ϳ� �����͸� �߰�, ���� �� true ��ȯ, ���� �� false ��ȯ
    template<size_t N>
    inline bool FixedVector<bool, N>::Add(const bool bData)
    {
        if (mSize == N)  // ���Ͱ� �� �� ���
            return false;

        if (bData == true)  // true�� ��� ��Ʈ�� ����
            mArr[mSize / 32] |= doSquared(mSize % 32);
        else  // false�� ��� ��Ʈ�� ����
            mArr[mSize / 32] &= ~doSquared(mSize % 32);

        ++mSize;  // ũ�⸦ ����

        return true;
    }

    // Remove �Լ�: ���Ϳ��� Ư�� �����͸� ����, ���� �� true ��ȯ, ���� �� false ��ȯ
    template<size_t N>
    inline bool FixedVector<bool, N>::Remove(const bool bData)
    {
        for (uint32_t i = 0; i < mSize; i++)
        {
            // �����͸� ã�� ���
            if (((mArr[i / 32] | doSquared(i % 32)) == mArr[i / 32]) == bData)
            {
                // �����͸� �����ϰ� ���� ��ҵ��� �̵�
                for (uint32_t j = i + 1; j < mSize; j++)
                {
                    if ((mArr[j / 32] | doSquared(j % 32)) == mArr[j / 32])
                        mArr[(j - 1) / 32] |= doSquared((j - 1) % 32);
                    else
                        mArr[(j - 1) / 32] &= ~doSquared((j - 1) % 32);
                }

                --mSize;  // ũ�⸦ ����
                return true;
            }
        }

        return false;  // �����͸� ã�� ���� ���
    }

    // Get �Լ�: Ư�� �ε����� �����͸� ��ȯ (�����)
    template<size_t N>
    inline const bool FixedVector<bool, N>::Get(const size_t index) const
    {
        return ((mArr[index / 32] | doSquared(index % 32)) == mArr[index / 32]);
    }

    // operator[]: Ư�� �ε����� �����͸� ��ȯ (������)
    template<size_t N>
    inline bool FixedVector<bool, N>::operator[](const size_t index)
    {
        return ((mArr[index / 32] | doSquared(index % 32)) == mArr[index / 32]);
    }

    // GetIndex �Լ�: Ư�� �������� �ε����� ��ȯ, ã�� ���ϸ� -1 ��ȯ
    template<size_t N>
    inline const int FixedVector<bool, N>::GetIndex(const bool bData) const
    {
        for (uint32_t i = 0; i < mSize; i++)
        {
            if (((mArr[i / 32] | doSquared(i % 32)) == mArr[i / 32]) == bData)
                return i;
        }

        return -1;  // �����͸� ã�� ���� ���
    }

    // GetSize �Լ�: ���� ���Ϳ� ����� ����� ���� ��ȯ
    template<size_t N>
    inline const size_t FixedVector<bool, N>::GetSize() const
    {
        return mSize;
    }

    // GetCapacity �Լ�: ������ �ִ� ũ�⸦ ��ȯ
    template<size_t N>
    inline const size_t FixedVector<bool, N>::GetCapacity() const
    {
        return N;
    }

    // doSquared �Լ�: �־��� ������ 2�� �ŵ����� ���� ��ȯ
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
            assert(false);  // �߸��� �Է��� �����ϱ� ���� assert
            return 0;
        }
    }
}
#pragma once
#include <queue>    // ť �ڷᱸ���� ����ϱ� ���� ����
#include <cstring>  // memset ���� ����ϱ� ���� ����

namespace lab9
{
    // ObjectPool Ŭ���� ���ø� ����
    // ��ü�� �����ϱ� ���� ��ü Ǯ�� �����ϴ� Ŭ����
    template <class T>
    class ObjectPool
    {
    public:
        ObjectPool(size_t maxPoolSize);  // ������: �ִ� Ǯ ũ�⸦ ����
        ~ObjectPool();  // �Ҹ���: Ǯ�� ���� �ִ� ��� ��ü�� ����
        ObjectPool(const ObjectPool& copy) = delete;  // ���� ������ ��� ����

        ObjectPool& operator = (const ObjectPool&) = delete;  // ���� ���� ������ ��� ����
        T* const Get();  // Ǯ���� ��ü�� �������ų� ���� ����
        void Return(T* const objectPointer);  // ��ü�� Ǯ�� ��ȯ
        const size_t GetFreeObjectCount() const;  // ���� Ǯ�� ���� �ִ� ��ü ���� ��ȯ
        const size_t GetMaxFreeObjectCount() const;  // �ִ� Ǯ ũ�⸦ ��ȯ

    private:
        const size_t mMaxPoolSize;  // �ִ� Ǯ ũ��
        std::queue<T*> mArr;  // ��ü�� ������ ť
    };

    // ������: �ִ� Ǯ ũ�⸦ �����ϰ� �ʱ�ȭ
    template<class T>
    inline ObjectPool<T>::ObjectPool(size_t maxPoolSize) :
        mMaxPoolSize(maxPoolSize)  // �ִ� Ǯ ũ�⸦ ����
    {}

    // �Ҹ���: Ǯ�� ���� �ִ� ��� ��ü�� ����
    template<class T>
    inline ObjectPool<T>::~ObjectPool()
    {
        // ť�� ���� �ִ� ��� ��ü�� �����ϰ� ť�� ���
        while (!mArr.empty())
        {
            delete mArr.front();  // ť�� �� �� ��ü ����
            mArr.pop();  // ť���� ��ü ����
        }
    }

    // Get �Լ�: Ǯ���� ��ü�� �������ų� ���� �����Ͽ� ��ȯ
    template<class T>
    inline T* const ObjectPool<T>::Get()
    {
        if (mArr.size() == 0)  // Ǯ�� ��� ������ ��ü�� ���� ���
            return new T();  // �� ��ü�� �����Ͽ� ��ȯ

        T* tmp = mArr.front();  // ť�� �� �� ��ü�� ������
        mArr.pop();  // ť���� ��ü ����

        return tmp;  // ������ ��ü ��ȯ
    }

    // Return �Լ�: ��ü�� Ǯ�� ��ȯ
    template<class T>
    inline void ObjectPool<T>::Return(T* const objectPointer)
    {
        if (mArr.size() == mMaxPoolSize)  // Ǯ�� �� ������ ���� ���
        {
            delete objectPointer;  // ��ü�� ����
            return;
        }

        mArr.push(objectPointer);  // ��ü�� Ǯ�� �߰�
    }

    // GetFreeObjectCount �Լ�: ���� Ǯ�� ���� �ִ� ��ü ���� ��ȯ
    template<class T>
    inline const size_t ObjectPool<T>::GetFreeObjectCount() const
    {
        return mArr.size();  // ť�� ũ�⸦ ��ȯ
    }

    // GetMaxFreeObjectCount �Լ�: �ִ� Ǯ ũ�⸦ ��ȯ
    template<class T>
    inline const size_t ObjectPool<T>::GetMaxFreeObjectCount() const
    {
        return mMaxPoolSize;  // �ִ� Ǯ ũ�⸦ ��ȯ
    }
}
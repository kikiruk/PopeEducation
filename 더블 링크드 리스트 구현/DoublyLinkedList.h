#pragma once

#include <memory>

namespace lab10
{
    // Node Ŭ������ ���� ����
    template<typename T>
    class Node;

    // ���� ���� ����Ʈ�� �����ϴ� ���ø� Ŭ����
    template<typename T>
    class DoublyLinkedList
    {
    public:
        DoublyLinkedList();  // �⺻ ������
        void Insert(std::unique_ptr<T> data);  // �����͸� ����Ʈ�� ���� ����
        void Insert(std::unique_ptr<T> data, unsigned int index);  // �����͸� Ư�� ��ġ�� ����
        bool Delete(const T& data);  // ����Ʈ���� Ư�� �����͸� ����
        bool Search(const T& data) const;  // ����Ʈ���� Ư�� �����͸� �˻�

        std::shared_ptr<Node<T>> operator[](unsigned int index) const;  // �ε����� ��带 �˻�
        unsigned int GetLength() const;  // ����Ʈ�� ���̸� ��ȯ

    private:
        size_t mLength;  // ����Ʈ�� ����
        std::shared_ptr<Node<T>> mHead;  // ����Ʈ�� ù ��° ���
        std::shared_ptr<Node<T>> mTail;  // ����Ʈ�� ������ ���
    };

    // �⺻ ������: ����Ʈ�� �ʱ�ȭ
    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList()
        : mLength(0)  // ����Ʈ�� ���̸� 0���� �ʱ�ȭ
        , mHead(nullptr)  // ��� ������ �ʱ�ȭ
        , mTail(nullptr)  // ���� ������ �ʱ�ȭ
    {
    }

    // ����Ʈ ���� �����͸� ����
    template<typename T>
    inline void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
    {
        ++mLength;  // ����Ʈ ���̸� ����

        if (mHead.get() == nullptr)  // ����Ʈ�� ����ִ� ���
        {
            // ���ο� ��带 �����ϰ� ���� ������ ����
            mTail = std::make_shared<Node<T>>(std::move(data));
            mHead = mTail;
        }
        else
        {
            // ����Ʈ ���� ���ο� ��带 �߰�
            mTail->Next = std::make_shared<Node<T>>(std::move(data), mTail);
            mTail = mTail->Next;
        }
    }

    // ����Ʈ�� Ư�� ��ġ�� �����͸� ����
    template<typename T>
    void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
    {
        if (mLength <= index)  // �ε����� ����Ʈ ���̺��� ũ�ų� ���� ���
        {
            Insert(std::move(data));  // ����Ʈ ���� ����
        }
        else if (index == 0)  // �ε����� 0�� ��� (����Ʈ�� ù ��ġ)
        {
            ++mLength;  // ����Ʈ ���̸� ����
            std::shared_ptr<Node<T>> newNode
                = std::make_shared<Node<T>>(std::move(data));  // ���ο� ��� ����

            newNode->Next = mHead;  // ���ο� ����� ������ ���� ���� ����

            mHead->Previous = newNode;  // ���� ����� ������ ���ο� ���� ����

            mHead = newNode;  // ��带 ���ο� ���� ����
        }
        else  // ����Ʈ �߰��� �����ϴ� ���
        {
            ++mLength;  // ����Ʈ ���̸� ����

            std::weak_ptr<Node<T>> ptr(this->operator[](index));  // ���� ��ġ�� ��� ������ ��������

            std::shared_ptr<Node<T>> newNode
                = std::make_shared<Node<T>>(std::move(data), ptr.lock()->Previous.lock());  // ���ο� ��� ����

            newNode->Next = ptr.lock();  // ���ο� ����� ������ ���� ���� ����

            if (index != 0)
                ptr.lock()->Previous.lock()->Next = newNode;  // ���� ����� ������ ���ο� ���� ����

            ptr.lock()->Previous = newNode;  // ���� ����� ������ ���ο� ���� ����
        }
    }

    // ����Ʈ���� Ư�� �����͸� ����
    template<typename T>
    bool DoublyLinkedList<T>::Delete(const T& data)
    {
        // ����Ʈ�� ��ȸ�ϸ� �����͸� ã��
        for (std::weak_ptr<Node<T>> ptr(mHead); ptr.lock().get() != nullptr; ptr = ptr.lock()->Next)
        {
            if (*ptr.lock()->Data == data)  // �����͸� ã�� ���
            {
                --mLength;  // ����Ʈ ���̸� ����

                if (ptr.lock().get() == mHead.get())  // ������ ��尡 ����� ���
                {
                    mHead = mHead->Next;  // ��带 ���� ���� �̵�
                }
                else if (ptr.lock().get() == mTail.get())  // ������ ��尡 ������ ���
                {
                    mTail = mTail->Previous.lock();  // ������ ���� ���� �̵�
                    mTail->Next.reset();  // ���� ������ ������ nullptr�� ����
                }
                else  // �߰� ��带 �����ϴ� ���
                {
                    ptr.lock()->Next->Previous = ptr.lock()->Previous.lock();  // ���� ����� ������ ���� ����� �������� ����
                    ptr.lock()->Previous.lock()->Next = ptr.lock()->Next;  // ���� ����� ������ ���� ����� �������� ����
                }

                return true;  // ���� ����
            }
        }

        return false;  // ������ �����͸� ã�� ���� ���
    }

    // ����Ʈ���� Ư�� �����͸� �˻�
    template<typename T>
    bool DoublyLinkedList<T>::Search(const T& data) const
    {
        // ����Ʈ�� ��ȸ�ϸ� �����͸� ã��
        for (std::weak_ptr<Node<T>> ptr(mHead); ptr.lock().get() != nullptr; ptr = ptr.lock()->Next)
        {
            if (*ptr.lock()->Data == data)  // �����͸� ã�� ���
                return true;
        }

        return false;  // �����͸� ã�� ���� ���
    }

    // �ε����� ��带 �˻�
    template<typename T>
    std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
    {
        if (index >= mLength)  // �ε����� ����Ʈ ���̺��� ũ�ų� ���� ���
            return nullptr;

        if (mLength - index > index)  // ��忡������ �˻��ϴ� ���� �� ȿ������ ���
        {
            std::weak_ptr<Node<T>> search(mHead);  // ��忡�� ����

            for (unsigned int i = 0; i < index; i++)
                search = search.lock()->Next;  // ���� ���� �̵�

            return search.lock();  // �˻��� ��� ��ȯ
        }
        else  // ���Ͽ������� �˻��ϴ� ���� �� ȿ������ ���
        {
            std::weak_ptr<Node<T>> search(mTail);  // ���Ͽ��� ����

            for (unsigned int i = 0; i < mLength - (index + 1); i++)
                search = search.lock()->Previous.lock();  // ���� ���� �̵�

            return search.lock();  // �˻��� ��� ��ȯ
        }
    }

    // ����Ʈ�� ���̸� ��ȯ
    template<typename T>
    unsigned int DoublyLinkedList<T>::GetLength() const
    {
        return mLength;
    }
}
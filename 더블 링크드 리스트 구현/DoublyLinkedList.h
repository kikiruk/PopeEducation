#pragma once

#include <memory>

namespace lab10
{
    // Node 클래스의 전방 선언
    template<typename T>
    class Node;

    // 이중 연결 리스트를 구현하는 템플릿 클래스
    template<typename T>
    class DoublyLinkedList
    {
    public:
        DoublyLinkedList();  // 기본 생성자
        void Insert(std::unique_ptr<T> data);  // 데이터를 리스트의 끝에 삽입
        void Insert(std::unique_ptr<T> data, unsigned int index);  // 데이터를 특정 위치에 삽입
        bool Delete(const T& data);  // 리스트에서 특정 데이터를 삭제
        bool Search(const T& data) const;  // 리스트에서 특정 데이터를 검색

        std::shared_ptr<Node<T>> operator[](unsigned int index) const;  // 인덱스로 노드를 검색
        unsigned int GetLength() const;  // 리스트의 길이를 반환

    private:
        size_t mLength;  // 리스트의 길이
        std::shared_ptr<Node<T>> mHead;  // 리스트의 첫 번째 노드
        std::shared_ptr<Node<T>> mTail;  // 리스트의 마지막 노드
    };

    // 기본 생성자: 리스트를 초기화
    template<typename T>
    DoublyLinkedList<T>::DoublyLinkedList()
        : mLength(0)  // 리스트의 길이를 0으로 초기화
        , mHead(nullptr)  // 헤드 포인터 초기화
        , mTail(nullptr)  // 테일 포인터 초기화
    {
    }

    // 리스트 끝에 데이터를 삽입
    template<typename T>
    inline void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
    {
        ++mLength;  // 리스트 길이를 증가

        if (mHead.get() == nullptr)  // 리스트가 비어있는 경우
        {
            // 새로운 노드를 생성하고 헤드와 테일을 설정
            mTail = std::make_shared<Node<T>>(std::move(data));
            mHead = mTail;
        }
        else
        {
            // 리스트 끝에 새로운 노드를 추가
            mTail->Next = std::make_shared<Node<T>>(std::move(data), mTail);
            mTail = mTail->Next;
        }
    }

    // 리스트의 특정 위치에 데이터를 삽입
    template<typename T>
    void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
    {
        if (mLength <= index)  // 인덱스가 리스트 길이보다 크거나 같은 경우
        {
            Insert(std::move(data));  // 리스트 끝에 삽입
        }
        else if (index == 0)  // 인덱스가 0인 경우 (리스트의 첫 위치)
        {
            ++mLength;  // 리스트 길이를 증가
            std::shared_ptr<Node<T>> newNode
                = std::make_shared<Node<T>>(std::move(data));  // 새로운 노드 생성

            newNode->Next = mHead;  // 새로운 노드의 다음을 기존 헤드로 설정

            mHead->Previous = newNode;  // 기존 헤드의 이전을 새로운 노드로 설정

            mHead = newNode;  // 헤드를 새로운 노드로 설정
        }
        else  // 리스트 중간에 삽입하는 경우
        {
            ++mLength;  // 리스트 길이를 증가

            std::weak_ptr<Node<T>> ptr(this->operator[](index));  // 삽입 위치의 노드 포인터 가져오기

            std::shared_ptr<Node<T>> newNode
                = std::make_shared<Node<T>>(std::move(data), ptr.lock()->Previous.lock());  // 새로운 노드 생성

            newNode->Next = ptr.lock();  // 새로운 노드의 다음을 기존 노드로 설정

            if (index != 0)
                ptr.lock()->Previous.lock()->Next = newNode;  // 이전 노드의 다음을 새로운 노드로 설정

            ptr.lock()->Previous = newNode;  // 기존 노드의 이전을 새로운 노드로 설정
        }
    }

    // 리스트에서 특정 데이터를 삭제
    template<typename T>
    bool DoublyLinkedList<T>::Delete(const T& data)
    {
        // 리스트를 순회하며 데이터를 찾음
        for (std::weak_ptr<Node<T>> ptr(mHead); ptr.lock().get() != nullptr; ptr = ptr.lock()->Next)
        {
            if (*ptr.lock()->Data == data)  // 데이터를 찾은 경우
            {
                --mLength;  // 리스트 길이를 감소

                if (ptr.lock().get() == mHead.get())  // 삭제할 노드가 헤드인 경우
                {
                    mHead = mHead->Next;  // 헤드를 다음 노드로 이동
                }
                else if (ptr.lock().get() == mTail.get())  // 삭제할 노드가 테일인 경우
                {
                    mTail = mTail->Previous.lock();  // 테일을 이전 노드로 이동
                    mTail->Next.reset();  // 이전 테일의 다음을 nullptr로 설정
                }
                else  // 중간 노드를 삭제하는 경우
                {
                    ptr.lock()->Next->Previous = ptr.lock()->Previous.lock();  // 다음 노드의 이전을 현재 노드의 이전으로 설정
                    ptr.lock()->Previous.lock()->Next = ptr.lock()->Next;  // 이전 노드의 다음을 현재 노드의 다음으로 설정
                }

                return true;  // 삭제 성공
            }
        }

        return false;  // 삭제할 데이터를 찾지 못한 경우
    }

    // 리스트에서 특정 데이터를 검색
    template<typename T>
    bool DoublyLinkedList<T>::Search(const T& data) const
    {
        // 리스트를 순회하며 데이터를 찾음
        for (std::weak_ptr<Node<T>> ptr(mHead); ptr.lock().get() != nullptr; ptr = ptr.lock()->Next)
        {
            if (*ptr.lock()->Data == data)  // 데이터를 찾은 경우
                return true;
        }

        return false;  // 데이터를 찾지 못한 경우
    }

    // 인덱스로 노드를 검색
    template<typename T>
    std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
    {
        if (index >= mLength)  // 인덱스가 리스트 길이보다 크거나 같은 경우
            return nullptr;

        if (mLength - index > index)  // 헤드에서부터 검색하는 것이 더 효율적인 경우
        {
            std::weak_ptr<Node<T>> search(mHead);  // 헤드에서 시작

            for (unsigned int i = 0; i < index; i++)
                search = search.lock()->Next;  // 다음 노드로 이동

            return search.lock();  // 검색된 노드 반환
        }
        else  // 테일에서부터 검색하는 것이 더 효율적인 경우
        {
            std::weak_ptr<Node<T>> search(mTail);  // 테일에서 시작

            for (unsigned int i = 0; i < mLength - (index + 1); i++)
                search = search.lock()->Previous.lock();  // 이전 노드로 이동

            return search.lock();  // 검색된 노드 반환
        }
    }

    // 리스트의 길이를 반환
    template<typename T>
    unsigned int DoublyLinkedList<T>::GetLength() const
    {
        return mLength;
    }
}
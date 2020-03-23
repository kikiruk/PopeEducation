#pragma once

#include <memory>

namespace lab10
{
	template<typename T>
	class Node;

	template<typename T>
	class DoublyLinkedList
	{
	public:
		DoublyLinkedList();
		void Insert(std::unique_ptr<T> data);
		void Insert(std::unique_ptr<T> data, unsigned int index);
		bool Delete(const T& data);
		bool Search(const T& data) const;

		std::shared_ptr<Node<T>> operator[](unsigned int index) const;
		unsigned int GetLength() const;

	private:
		size_t mLength;
		std::shared_ptr<Node<T>> mHead;
		std::shared_ptr<Node<T>> mTail;
	};

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedList()
		: mLength(0),
		mHead(nullptr),
		mTail(nullptr)
	{
	}

	template<typename T>
	inline void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data)
	{
		++mLength;

		if (mHead.get() == nullptr)
		{
			mTail = std::make_shared<Node<T>>(std::move(data));
			mHead = mTail;
		}
		else
		{
			mTail->Next = std::make_shared<Node<T>>(std::move(data), mTail);
			mTail = mTail->Next;
		}
	}

	template<typename T>
	void DoublyLinkedList<T>::Insert(std::unique_ptr<T> data, unsigned int index)
	{
		if (mLength <= index)
		{
			Insert(std::move(data));
		}
		else if (index == 0)
		{
			++mLength;
			std::shared_ptr<Node<T>> newNode
				= std::make_shared<Node<T>>(std::move(data));

			newNode->Next = mHead;

			mHead->Previous = newNode;

			mHead = newNode;
		}
		else
		{
			++mLength;

			std::weak_ptr<Node<T>> ptr(this->operator[](index));

			std::shared_ptr<Node<T>> newNode
				= std::make_shared<Node<T>>(std::move(data), ptr.lock()->Previous.lock());

			newNode->Next = ptr.lock();

			if (index != 0)
				ptr.lock()->Previous.lock()->Next = newNode;

			ptr.lock()->Previous = newNode;
		}
	}

	template<typename T>
	bool DoublyLinkedList<T>::Delete(const T& data)
	{
		for (std::weak_ptr<Node<T>> ptr(mHead); ptr.lock().get() != nullptr; ptr = ptr.lock()->Next)
		{
			if (*ptr.lock()->Data == data)
			{
				--mLength;

				if (ptr.lock().get() == mHead.get())
				{
					mHead = mHead->Next;
				}
				else if (ptr.lock().get() == mTail.get())
				{
					mTail = mTail->Previous.lock();
					mTail->Next.reset();
				}
				else
				{
					ptr.lock()->Next->Previous = ptr.lock()->Previous.lock();
					ptr.lock()->Previous.lock()->Next = ptr.lock()->Next;
				}

				return true;
			}
		}

		return false;
	}

	template<typename T>
	bool DoublyLinkedList<T>::Search(const T& data) const
	{
		for (std::weak_ptr<Node<T>> ptr(mHead); ptr.lock().get() != nullptr; ptr = ptr.lock()->Next)
		{
			if (*ptr.lock()->Data == data)
				return true;
		}

		return false;
	}

	template<typename T>
	std::shared_ptr<Node<T>> DoublyLinkedList<T>::operator[](unsigned int index) const
	{

		if (index >= mLength)
			return nullptr;

		if (mLength - index > index)
		{
			//search from mHead
			std::weak_ptr<Node<T>> search(mHead);

			for (unsigned int i = 0; i < index; i++)
				search = search.lock()->Next;

			return search.lock();
		}
		else
		{
			//search from tail
			std::weak_ptr<Node<T>> search(mTail);

			for (unsigned int i = 0; i < mLength - (index + 1); i++)
				search = search.lock()->Previous.lock();

			return search.lock();
		}

	}

	template<typename T>
	unsigned int DoublyLinkedList<T>::GetLength() const
	{
		return mLength;
	}
}





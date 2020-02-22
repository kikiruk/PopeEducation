#pragma once

template<typename T>
class Node
{
public:
	Node(T mNumber, Node<T>* mNext) :
		mNumber(mNumber),
		mNext(mNext)
	{}

	Node(const Node<T>& copy) :
		mNumber(copy.mNumber),
		mNext(nullptr)
	{}

	T mNumber;
	Node<T>* mNext;
};



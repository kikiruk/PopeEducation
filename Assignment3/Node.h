#pragma once

template<typename T>
class Node
{
public:
	Node(T MNumber, Node<T>* MNext) :
		MNumber(MNumber),
		MNext(MNext)
	{}

	Node(const Node<T>& copy) :
		MNumber(copy.MNumber),
		MNext(nullptr)
	{}

	T MNumber;
	Node<T>* MNext;
};



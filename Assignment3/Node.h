#pragma once

template<typename T>
class Node
{
public:
	Node(T number, Node<T>* next) :
		MNumber(number),
		MNext(next)
	{}

	Node(const Node<T>& copy) :
		MNumber(copy.MNumber),
		MNext(nullptr)
	{}

	T MNumber;
	Node<T>* MNext;
};



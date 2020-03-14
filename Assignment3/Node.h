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

template<typename T>
class NodeForStack
{
public:
	NodeForStack(T number, NodeForStack<T>* next) :
		MNumber(number),
		MNext(next),
		MMinData(nullptr),
		MMaxData(nullptr)
	{}

	NodeForStack(const NodeForStack<T>& copy) :
		MNumber(copy.MNumber),
		MNext(nullptr),
		MMinData(nullptr),
		MMaxData(nullptr)
	{}

	T MNumber;
	NodeForStack<T>* MNext;
	NodeForStack<T>* MMinData;
	NodeForStack<T>* MMaxData;
};



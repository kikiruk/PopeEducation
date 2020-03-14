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
		MMinData(0),
		MMaxData(0)
	{}

	NodeForStack(const NodeForStack<T>& copy) :
		MNumber(copy.MNumber),
		MNext(nullptr),
		MMinData(0),
		MMaxData(0)
	{}

	T MNumber;
	NodeForStack<T>* MNext;
	T MMinData;
	T MMaxData;
};


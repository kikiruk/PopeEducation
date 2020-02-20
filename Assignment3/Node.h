#pragma once

template<typename T>
struct Node
{
	Node(T number, Node<T>* next) :
		number(number),
		next(next)
	{}

	Node(const Node<T>& copy) :
		number(copy.number),
		next(nullptr)
	{}

	T number;
	Node<T>* next;
};



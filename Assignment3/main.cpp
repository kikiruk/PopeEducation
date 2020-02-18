#include <iostream>
#include "SmartStack.h"

using namespace assignment3;
using namespace std;

int main()
{
	SmartStack<int> s;
	s.Push(6);
	s.Push(5);
	s.Push(-2); // [ 6, 5, -2 ]

	int x = s.Peek(); // -2를 반환. 그러나 스택의 요소는 여전히 [ 6, 5, -2 ]

	cout << x << endl;

}
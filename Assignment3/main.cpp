#include <cassert>
#include <iostream>
#include "SmartStack.h"
#include "SmartQueue.h"
#include "QueueStack.h"

using namespace assignment3;
using namespace std;

int main()
{
	SmartStack<long> ss;
	ss.Push(1);

	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(1);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(1);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(1);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(1);
	ss.Push(1);
	ss.Push(1);
	ss.Push(1);
	ss.Push(1);
	ss.Push(1);
	ss.Push(1);
	ss.Push(1);
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	ss.Pop();
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
}
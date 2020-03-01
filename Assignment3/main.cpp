#include <cassert>
#include <iostream>
#include "SmartStack.h"
#include "SmartQueue.h"
#include "QueueStack.h"
#include <float.h>


using namespace assignment3;
using namespace std;

int main()
{
	SmartStack<float> ss;


	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(1);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(-9000);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(1);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(9000);
	ss.Push(1);
	ss.Push(1);
	ss.Push(FLT_MAX);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Push(FLT_MIN);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
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

	ss.Pop();
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;

	cout << FLT_MAX << " < " << -FLT_MAX << endl;

	return 0;
}
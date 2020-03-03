#include <cassert>
#include <iostream>
#include "SmartStack.h"
#include "SmartQueue.h"
#include "QueueStack.h"

using namespace assignment3;
using namespace std;

int main()
{
	SmartStack<int> ss;
	ss.Push(1);

	ss.Push(123);
	ss.Push(12);
	ss.Push(134);
	ss.Push(154);
	ss.Push(164);
	ss.Push(145);
	ss.Push(1455);
	ss.Push(1466);
	ss.Push(146);
	ss.Push(1465);
	ss.Push(145);

	cout << "Variance : " << ss.GetVariance() << endl;

	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Pop(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
}
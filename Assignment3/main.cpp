#include <cassert>
#include <iostream>
#include "SmartStack.h"
#include "SmartQueue.h"
#include "QueueStack.h"

using namespace assignment3;
using namespace std;

int main()
{
	SmartStack<float> ss;

	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(3.4999f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(1.2f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(4.6555f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(3.3299f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(10.2f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(1.1f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(-5.9f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(1.1f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(-12.4f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(9.2f);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;

	cout << "----------------------------------------------------------" << endl;

	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	cout << ss.Pop() << endl;
	cout << ss.GetMin() << "," << ss.GetMax() << endl;

}

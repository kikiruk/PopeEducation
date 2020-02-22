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

	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(100);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(100);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(100);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(100);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(100);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(100);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(100);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(100);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(-102);
	cout << ss.GetMin() << "," << ss.GetMax() << endl;
	ss.Push(-103);
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

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

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(2);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(3);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(4);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(5);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(6);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(7);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(8);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(9);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Push(10);

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;

	ss.Pop();

	cout << "Min : " << ss.GetMin() << ", Max : " << ss.GetMax() << endl;


}
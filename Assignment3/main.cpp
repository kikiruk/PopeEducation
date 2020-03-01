#include <cassert>
#include <iostream>
#include "SmartStack.h"
#include "SmartQueue.h"
#include "QueueStack.h"

using namespace assignment3;
using namespace std;

int main()
{
	SmartQueue<int> ss;
	ss.Enqueue(1);

	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Enqueue(1);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Enqueue(-2);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Enqueue(3);
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	ss.Dequeue();
	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
}
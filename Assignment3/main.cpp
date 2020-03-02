#include <cassert>
#include <iostream>
#include "SmartStack.h"
#include "SmartQueue.h"
#include "QueueStack.h"

using namespace assignment3;
using namespace std;

int main()
{
	QueueStack<int> ss(3);
	ss.Enqueue(1);

	ss.Enqueue(1);
	ss.Enqueue(-2);
	ss.Enqueue(3);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);
	ss.Enqueue(1);

	QueueStack<int> tt(ss);


	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
	ss.Dequeue(); 	cout << ss.GetMin() << " < " << ss.GetMax() << endl;
}
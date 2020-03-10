#include <cassert>
#include <iostream>

#include "FixedVector.h"
#include "FixedBoolVector.h"

using namespace std;
using namespace lab8;

int main()
{
	int i1 = 23;
	int i2 = 25;
	int i3 = 10;
	int i4 = -4;
	int i5 = 70;
	
	FixedVector<int, 33> iv;
	
	assert(iv.GetCapacity() == 33);
	
	iv.Add(i1);
	iv.Add(i2);
	iv.Add(i3);
	iv.Add(i4);
	
	cout << iv.Remove(i1) << endl;
	cout << iv.Remove(i2) << endl;
	cout << iv.Remove(i3) << endl;
	cout << iv.Remove(i4) << endl;
}
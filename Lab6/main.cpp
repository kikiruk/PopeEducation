#include <vector>
#include <iostream>
#include "Lab6.h"

using namespace std;

int main()
{
	std::vector<int> v;
	v.push_back(4);
	v.push_back(3);
	v.push_back(4);
	v.push_back(12);
	v.push_back(7);
	v.push_back(11);

	cout << (float)lab6::Average(v) << endl; // 41
}
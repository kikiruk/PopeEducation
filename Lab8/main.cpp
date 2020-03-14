#include <cassert>
#include <iostream>

#include "FixedVector.h"
#include "FixedBoolVector.h"

using namespace std;
using namespace lab8;
 
int main()
{
	FixedVector<bool, 65> boolVector2;
	cout << sizeof(boolVector2) << endl;
	cout << (sizeof(int32_t) * 3) + sizeof(size_t) << endl;
	assert(sizeof(boolVector2) == ((sizeof(int32_t) * 3) + sizeof(size_t)));
	std::cout << "Test FixedBoolVector constructor - fit memroy: PASS" << std::endl;
	//for (int i = 0; i < 65; i++)
	//{
	//	
	//}

	boolVector2.Add(true);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(true);

	boolVector2.Add(true);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(false);
	boolVector2.Add(true);

	boolVector2.Add(true);


	assert(boolVector2.Add(true) == false);
	//assert(boolVector2.GetSize() == 65);
	//assert(boolVector2.GetIndex(true) == -1);
	std::cout << "Test FixedBoolVector GetIndex(): PASS" << std::endl;
	
	return 0;
}
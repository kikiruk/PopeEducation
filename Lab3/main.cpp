#include <iostream>
#include "TimeSheet.h"

using namespace lab3;
using namespace std;

int main()
{
	lab3::TimeSheet employee2("John", 10);
	employee2.AddTime(7);
	employee2.AddTime(8);
	
	lab3::TimeSheet employee1(employee2);

	employee1 = employee1;

	std::cout << "Employee: " << employee1.GetName() << " / AverageTime: " 
		<< employee1.GetAverageTime() << " / TotalTime: " << employee1.GetTotalTime() << std::endl;

	return 0;
}
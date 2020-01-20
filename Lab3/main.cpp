#include <iostream>
#include "TimeSheet.h"

using namespace lab3;
using namespace std;

int main()
{
	lab3::TimeSheet employee1("John", 10);
	employee1.AddTime(4);
	employee1.AddTime(7);
	std::cout << "Employee: " << employee1.GetName() << " / AverageTime: " << employee1.GetAverageTime() << " / TotalTime: " << employee1.GetTotalTime() << std::endl;

	return 0;
}
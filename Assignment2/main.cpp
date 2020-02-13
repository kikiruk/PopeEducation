#include <cassert>
#include <iostream>
#include <iomanip>

#include "Vehicle.h"
#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"
#include "Motorcycle.h"
#include "Sedan.h"
#include "UBoat.h"
#include "Trailer.h"
#include "DeusExMachina.h"
#include "Person.h"


#define STR(name) #name

using namespace assignment2;
using namespace std;

int main()
{
	Sedan a;
	
	a.AddPassenger(new Person("a",1));
	a.AddPassenger(new Person("b",2));

	Sedan b(a);

	for (int i = 0; i < b.GetPassengersCount(); i++)
	{
		cout << b.GetPassenger(i)->GetName() << endl;
	}
}

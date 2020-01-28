#include <iostream>
#include "Point.h"
#include "PolyLine.h"

using namespace std;
using namespace lab4;

int main()
{
	PolyLine pl;

	pl.AddPoint(1, 2);
	pl.AddPoint(2, 3);
	pl.AddPoint(2, 4);
	pl.AddPoint(2, 5);
	pl.AddPoint(2, 6);

	pl.RemovePoint(2);

	for (int i = 0; i < 10; i++)
	{
		if (pl[i] != nullptr)
		{
			cout << pl[i]->GetX() << "," << pl[i]->GetY() << endl;
		}
	}
}

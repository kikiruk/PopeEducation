#include <iostream>
#include "Point.h"
#include "PolyLine.h"

using namespace std;
using namespace lab4;

int main()
{
	PolyLine pl;

	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);
	pl.AddPoint(1, 2);

	pl.RemovePoint(7);

	for (int i = 0; i < 10; i++)
	{
		if (pl[i] != nullptr)
		{
			cout << pl[i]->GetX() << "," << pl[i]->GetY() << endl;
		}
	}
}

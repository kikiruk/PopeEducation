#include <cassert>
#include <iostream>

#include "Lawn.h"
#include "IFenceable.h"
#include "RectangleLawn.h"
#include "CircleLawn.h"
#include "SquareLawn.h"
#include "EquilateralTriangleLawn.h"

using namespace std;
using namespace lab5;

int main()
{
	Lawn* lawn = new RectangleLawn(10, 20);
	unsigned int area = lawn->GetArea();
	unsigned int grassPrice = lawn->GetGrassPrice(eGrassType::BERMUDA);
	unsigned int sodRollsCount = lawn->GetMinimumSodRollsCount();

	cout << area << endl;
	cout << grassPrice << endl;
	cout << sodRollsCount << endl;

	assert(area == 200);
	assert(grassPrice == 1600);
	assert(sodRollsCount == 667);

	RectangleLawn* rectangleLawn = (RectangleLawn*)lawn;

	unsigned int fencePrice = rectangleLawn->GetFencePrice(eFenceType::RED_CEDAR);
	unsigned int fencesCount = rectangleLawn->GetMinimumFencesCount();


	cout << fencePrice << endl;
	cout << fencesCount << endl;

	assert(fencePrice == 360);
	assert(fencesCount == 240);

	// 위와 같은 방식으로 다른 구체 클래스들도 테스트할 수 있음
	return 0;
}
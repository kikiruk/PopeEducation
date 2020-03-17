#include <cassert>
#include <iostream>
#include "IceCube.h"
#include "ObjectPool.h"
#include "Game.h"



using namespace lab9;
using namespace std;

int main()
{
	ObjectPool<IceCube> op(1);
	cout << op.GetFreeObjectCount() << endl; // 0을 반환

	IceCube* i1 = op.Get();
	IceCube* i2 = op.Get();

	op.Return(i1);
	op.GetFreeObjectCount(); // 1을 반환

	op.Return(i2);
	op.GetFreeObjectCount(); // 1을 반환

	return 0;
}
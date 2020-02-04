#include <cmath>
#include "Lawn.h"
#include "eGrassType.h"


namespace lab5
{
	unsigned int Lawn::GetGrassPrice(eGrassType grassType) const
	{
		double price = 0;

		switch (grassType)
		{
		case BERMUDA :
			price = 8;
			break;

		case BAHIA :
			price = 5;
			break;

		case BENTGRASS :
			price = 3;
			break;

		case PERENNIAL_RYEGRASS :
			price = 2.5;
			break;

		case ST_AUGUSTINE:
			price = 4.5;
			break;

		default:
			break;
		}

		price *= GetArea();

		return static_cast<unsigned int>(price + 0.5);
	}

	unsigned int Lawn::GetMinimumSodRollsCount() const
	{
		return static_cast<unsigned int>(ceil(GetArea() / 0.3 + 0.5));
	}
}